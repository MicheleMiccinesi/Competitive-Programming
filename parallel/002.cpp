#include <mpi.h>
#include <iostream>
#include <random>

struct communicator_info{
	int size, rank;
};

int product(){
	return 1;
}
template <class ...INTS>
int product(int n, INTS... ns){
	return n*product(ns...);
}

/* This temporary struct is for careful users: I still have to implement proper protected/private interface */
template <class INTEGER>
struct tensor{
	int *data;
	int *d;
	int *dslice;
	int n;
	MPI_Datatype MPI_datatype_handle;
	MPI_Datatype &handle_mpi(){
		return MPI_datatype_handle;
	}

	template <class ...Ds>
	explicit tensor(MPI_Datatype _mpi_type, int d0, Ds... ds): n{0}, MPI_TYPE(_mpi_type){
		count_ds(d0, ds...);
		d = new int[n];
		set_ds(0, d0, ds...);
		dslice = new int[n];
		dslice[n-1] = d[n-1];
		for( int i=n-2; i>=0; --i )
			dslice[i] = dslice[i+1]*d[i];
		data = new INTEGER[dslice[0]];
		MPI_Type_contiguous(dslice[0], MPI_TYPE, &MPI_datatype_handle);
		MPI_Type_commit(&MPI_datatype_handle);
	}

	void rnd_fill(INTEGER a, INTEGER b){
	    std::random_device r; 

	    std::seed_seq seed1{r(), r(), r(), r(), r(), r(), r(), r()};
	    std::mt19937 e1(seed1);
	    std::uniform_int_distribution<INTEGER> uniformDist(a, b);
	    for(int i=0; i!=dslice[0]; ++i) 
	    	data[i] = uniformDist(e1);
	}

	friend std::ostream& operator<<(std::ostream& out, tensor<INTEGER>& T){
		int i{0};
		T.print(out, 0, i);
		return out;
	}

	~tensor(){
		MPI_Type_free(&MPI_datatype_handle);
		delete[] d;
		delete[] dslice;
		delete[] data;
	}
protected:
	void print(std::ostream& out, int dim, int& i){
		if( dim==n-1 ){
			for( int j=0; j!=d[n-1]; ++j, ++i )
				out << data[i] << '\t';
		}
		else{
			++dim;
			for( int j=0; j!=d[0]; ++j ){
				print(out, dim, i);
				out << '\n';
			}
		}
	}

	MPI_Datatype MPI_TYPE;
	void count_ds(){}
	template <class ...Ds>
	void count_ds(int i, Ds... ds){		//look at the variadic possibilities of iteration
		++n;
		count_ds(ds...);
	}
	
	void set_ds(int&& i){}
	template <class ...Ds>
	void set_ds(int&& i, int d_i, Ds... ds){
		d[i]=d_i;
		set_ds(i+1, ds...);
	} 
};


struct communicator_info_cyclic:communicator_info{
	communicator_info_cyclic(const communicator_info& comm_base): communicator_info(comm_base){
		prevrank = rank?rank-1:size-1;
		nextrank = rank==size-1?0:rank+1;
	}
	int nextrank, prevrank;
};

//just the first idea, could parametrize lots of other things... not worth the effort by now.

template <class TYPE_DATA>
void mpi_cycle(int cycles, communicator_info& comm_base, TYPE_DATA *data, const MPI_Datatype& MPI_TYPE_BASE){
	communicator_info_cyclic comm(comm_base);

	int bounces=cycles*comm.size;
	int counter{0};

	MPI_Datatype BAG_TYPE;
	{
		int BAG_blocks[2] = {1, 1};
		MPI_Aint BAG_displacements[2] = {0, reinterpret_cast<char *>(data)-reinterpret_cast<char *>(&counter)};
		MPI_Datatype BAG_types[2] = {MPI_INT, MPI_TYPE_BASE};

		MPI_Type_create_struct(2, BAG_blocks, BAG_displacements, BAG_types, &BAG_TYPE);
	}
	MPI_Type_commit(&BAG_TYPE);

	while(counter<bounces){
		if( counter%comm.size == comm.rank ){
			std::cout << "Giocatore " << comm.rank << " lancia la palla" << std::endl;
			++counter;
			MPI_Send(&counter, 1, BAG_TYPE, comm.nextrank, 0, MPI_COMM_WORLD);																				
			if( counter+comm.size>bounces+1 )
				break;
		} else {
			MPI_Recv(&counter, 1, BAG_TYPE, comm.prevrank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			std::cout << "Giocatore " << comm.rank << " riceve il rimbalzo " << counter << std::endl;
		}
	}
	std::cout << "Il giocatore " << comm.rank << " se ne va " << std::endl;

	MPI_Type_free(&BAG_TYPE);

	return;
}

// The number of cycles should be specified as a parameter to the program
int main(int argc, char *argv[]){
	int N=20;
	
	MPI_Init(&argc, &argv);
	communicator_info world;
	MPI_Comm_size(MPI_COMM_WORLD, &world.size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world.rank);
	{
		tensor<int> T(MPI_INT, N, N);
		T.rnd_fill(-100, 100);
		int cycles = argc>1?atoi(argv[1]):30;
		std::cout << "Cycles: " << cycles << std::endl;

	 	mpi_cycle(cycles, world, T.data, T.handle_mpi());

		MPI_Datatype column;							//start from j+beginning of matrix
		MPI_Type_vector(N, 1, N, MPI_INT, &column);
		MPI_Type_commit(&column);
		mpi_cycle(cycles, world, T.data, column);
		MPI_Type_free(&column);

		MPI_Datatype row;
		MPI_Type_contiguous(N, MPI_INT, &row);			//start from i*N + beginning of matrix (i: number row from 0)
		MPI_Type_commit(&row);
		mpi_cycle(cycles, world, T.data, row);
		MPI_Type_free(&row);

		MPI_Datatype diagWE;
		MPI_Type_vector(N, 1, N+1, MPI_INT, &diagWE);	//start from the beginning of the matrix
		MPI_Type_commit(&diagWE);
		mpi_cycle(cycles, world, T.data, diagWE);
		MPI_Type_free(&diagWE);

		MPI_Datatype diagEW;
		MPI_Type_vector(N, 1, N-1, MPI_INT, &diagEW);	//start from Nth element of the matrix 
		MPI_Type_commit(&diagEW);
		mpi_cycle(cycles, world, T.data, diagEW);
		MPI_Type_free(&diagEW);

		{
			struct triE{
				MPI_Datatype mpi_type;
				triE(int n, MPI_Datatype MPI_TYPE_BASE){
					displacements = new int[n];
					blocklengths = new int[n];
					for(int i=0; i!=n; ++i){
						displacements[i] = (n+1)*i;
						blocklengths[i] = n-i;
					}
					MPI_Type_indexed(n, blocklengths, displacements, MPI_TYPE_BASE, &mpi_type);
					MPI_Type_commit(&mpi_type);
					delete[] displacements;
					delete[] blocklengths;
				}
				~triE(){
					MPI_Type_free(&mpi_type);
				}
			protected:
				int *displacements, *blocklengths;
			};

			struct triET{
				MPI_Datatype mpi_type;
				triET(int n, MPI_Datatype MPI_TYPE_BASE){
					int N = (n*(n+1))>>1;
					displacements = new int[N];
					blocklengths = new int[N];
					for(int i=0, k=0; i!=n; ++i)
						for(int j=i; j!=n; ++j, ++k){
							blocklengths[k] = 1;
							displacements[k] = i+j*n;
						}

					MPI_Type_indexed(N, blocklengths, displacements, MPI_TYPE_BASE, &mpi_type);
					MPI_Type_commit(&mpi_type);
					delete[] displacements;
					delete[] blocklengths;
				}
				~triET(){
					MPI_Type_free(&mpi_type);
				}
			protected:
				int *displacements, *blocklengths;
			};

			struct triW{
				MPI_Datatype mpi_type;
				triW(int n, MPI_Datatype MPI_TYPE_BASE){
					displacements = new int[n];
					blocklengths = new int[n];
					for(int i=0; i!=n; ++i){
						displacements[i] = n*i;
						blocklengths[i] = i+1;
					}
					MPI_Type_indexed(n, blocklengths, displacements, MPI_TYPE_BASE, &mpi_type);
					MPI_Type_commit(&mpi_type);
					delete[] displacements;
					delete[] blocklengths;
				}
				~triW(){
					MPI_Type_free(&mpi_type);
				}
			protected:
				int *displacements, *blocklengths;
			};

			struct triWT{
				MPI_Datatype mpi_type;
				triWT(int n, MPI_Datatype MPI_TYPE_BASE){
					int N = (n*(n-1))>>1;
					displacements = new int[N];
					blocklengths = new int[N];
					for(int i=0, k=0; i!=n; ++i)
						for(int j=0; j<=i; ++j, ++k){
							displacements[k] = i+j*n;
							blocklengths[k] = 1;
						}
					MPI_Type_indexed(N, blocklengths, displacements, MPI_TYPE_BASE, &mpi_type);
					MPI_Type_commit(&mpi_type);
					delete[] displacements;
					delete[] blocklengths;
				}
				~triWT(){
					MPI_Type_free(&mpi_type);
				}
			protected:
				int *displacements, *blocklengths;
			};

			//let's try a ping-pong:
			if( world.size>1 ){
				switch(world.rank){
				case 0:
				{
					std::cout << T << std::endl;
					triE T_triE(N, MPI_INT);

					MPI_Send(T.data, 1, T_triE.mpi_type, 1, 0, MPI_COMM_WORLD);
					triW T_triW(N, MPI_INT);

					MPI_Recv(T.data, 1, T_triW.mpi_type, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					std::cout << "After symmetric merge:\n" << T << std::endl;
					break;
				}
				case 1:
				{
					triET T_triET(N, MPI_INT);
					MPI_Recv(T.data, 1, T_triET.mpi_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					triW T_triW(N, MPI_INT);
					MPI_Send(T.data, 1, T_triW.mpi_type, 0, 0, MPI_COMM_WORLD);
					break;
				}
				}
			}
			
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	
	return 0;
}
