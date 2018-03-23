// Not working, just a sketch of the idea; I have to put proper locks...etc
#include <iostream>
#include <queue>
#include <set>
#include <mpi.h>

template <int K>
class asyncSend{
	int _stop{0};
	MPI_Comm communicator;
	int rank, size;
	std::array<MPI_Request, K> requests;
	std::array<MPI_Status, K> statuses;
	std::queue<int> freeTags;
public:
	asyncSend(MPI_Comm comm): communicator(comm), freeTags(){
		MPI_Comm_rank(communicator, &rank);
		MPI_Comm_size(communicator, &size);
		for( int i=1; i<=K; ++i ){
			freeTags.push(i);
			requests[i-1]=MPI_REQUEST_NULL;
		}
	}
	template <typename dataType>
	bool send(dataType *const data, const int& count, const MPI_Datatype& _mpiType, const int& dest){
		if( dest>size )
			return false;
		if( freeTags.empty() ){
			int index;
			MPI_Waitany(K, requests.data, &index, MPI_STATUS_IGNORE);
			MPI_ISend(data, count, _mpiType, dest, index+1, communicator, &(requests.data[index]));

		} else {
			//warning MUTEX
			int tag = queue.front();
			queue.pop();
			MPI_ISend(data, count, _mpiType, dest, tag, communicator, &(requests.data[tag-1]));
		}
		return true;
	}
	~asyncSend(){
		MPI_Waitall(K, requests, MPI_STATUSES_IGNORE);
		// should send void message: how?
		MPI_Bbcast(&_stop, 1, MPI_INT, rank, communicator);
	}
};

class asyncRecv{
	bool channelClosed{false};
	int source, size;
	MPI_Comm communicator;
	int _stop;
public:
	asyncRecv(int src, MPI_Comm comm):communicator(comm), source(src){}
	template <typename dataType>
	bool receive(dataType *const data, const int& count, const MPI_Datatype& _mpiType, const int& src, MPI_request *const prequest){
		if( channelClosed ) 
			return false;
		int flag;
		MPI_Iprobe(source, 0, communicator, &flag, MPI_STATUS_IGNORE);
		if( flag ){
			MPI_IRecv(&_stop, 1, MPI_INT, source, 0, communicator, MPI_STATUS_IGNORE);
			channelClosed = true;
			return false;
		}
		MPI_Irecv(data, count, _mpiType, source, MPI_ANY_TAG, communicator, prequest);
		//TODO: if errors return false
		return true;
	}
};
