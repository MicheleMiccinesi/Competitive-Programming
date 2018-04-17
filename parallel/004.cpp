#include <iostream> 
#include <string> 
#include <algorithm> 
#include <memory>
#include <fstream>
#include "tbb/parallel_for.h"
#include "tbb/blocked_range2d.h"

// BEGIN of the (corrected) interface given in classroom
//default square area, lower left angle and size 
const double DEFAULT_X {-0.96};
const double  DEFAULT_Y {-0.2625}; 
const double DEFAULT_SIZE {0.0000001}; 
const size_t DEFAULT_PIXELS {4000};
const int DEFAULT_ITERATIONS {6*256}; 
const int MAX_SMODULUS {40}; //we assume a point diverges if squared modulus exceeds this value 

static int maxIter {DEFAULT_ITERATIONS}; 

//returns the number of iteration until divergence 
int mand_compute(double cx, double cy) { 
	int i; 
	double x{0.}, y{0.};
	for (i=0; i<maxIter; ++i) { 
		double tx{x}, ty{y};
		x = tx*tx - ty*ty + cx; 
		y = 2*tx*ty + cy; 
		if ( x*x + y*y > MAX_SMODULUS ) 
			break; 
	} 
	return i; 
} 
//END of the given interface

template <class T>
class matrix{
	T* M{nullptr};
	size_t r, c;
public:
	matrix(const size_t& r_, const size_t& c_) : r(r_), c(c_){
		M = new T[r*c];
	}
	matrix(matrix&& M_) : r(M_.r), c(M_.c){
		M = M_.M;
		M_.M = nullptr;
	}
	T& operator[](const size_t& l){
		return M[l];
	}
	T& operator()(const size_t& x, const size_t& y){
		return M[x*c+y];
	}
	~matrix(){
		if( M!=nullptr )
			delete[] M;
	}
	int int_dim_r(){
		return r;
	}
	int int_dim_c(){
		return c;
	}
	T* raw(){
		return M;
	}
};

struct region2d{
	region2d(const size_t& dim_x_, const size_t& dim_y_, const double& base_x_, const double& base_y_, const double& pixel_size_) :
	dim_x{dim_x_}, dim_y{dim_y_}, base_x{base_x_}, base_y{base_y_}, pixel_size{pixel_size_}, values(dim_x_, dim_y_) {}
	size_t dim_x, dim_y;
	double base_x, base_y, pixel_size; 
	matrix<int> values;
	matrix<char> to_char_image(const int max_color=255) {
		matrix<char> image(dim_y, dim_x*3);
		for( int i=0, j=0; i!=dim_x*dim_y; ++i, ++j ){
			//some color effects
			if( values[i]<=max_color ){
				image[j]=values[i];
				image[++j]=0;
				image[++j]=0;
			} else if( values[i]<2*(max_color+1) ) {
				image[j]=0;
				image[++j]=values[i]-(max_color+1);
				image[++j]=0;
			} else if( values[i]<3*(max_color+1) ) {
				image[j]=0;
				image[++j]=0;
				image[++j]=values[i]-2*(max_color+1);
			} else if( values[i]<4*(max_color+1) ) {
				image[j]=values[i]-3*(max_color+1);
				image[++j]=0;
				image[++j]=max_color;
			} else if( values[i]<5*(max_color+1) ) {
				image[j]=max_color;
				image[++j]=values[i]-4*(max_color+1);
				image[++j]=max_color;
			} else {
				image[j]=max_color;
				image[++j]=max_color;
				image[++j]=max_color;
			}
		}
		return image;
	}
};

struct ppm_image{
	matrix<char> M;
	ppm_image(matrix<char>&& mat) : M(std::move(mat)) {}
	void to_file(const std::string& filename, const int max_color=255){
		std::ofstream imageFile;
		imageFile.open(filename, std::ios::trunc | std::ios::out | std::ios::binary);
		imageFile << "P6\n" << M.int_dim_r() << ' ' << M.int_dim_c()/3 << '\n' << max_color << '\n';
		imageFile.write(M.raw(), M.int_dim_r()*M.int_dim_c());
		imageFile.close();
	}
};

class tbb_mandel{
	std::shared_ptr<region2d> fractal;		//required by TBB partitioner
public:
	explicit tbb_mandel( const size_t dim_x_ = DEFAULT_PIXELS, const size_t dim_y_ = DEFAULT_PIXELS, 
		const double base_x_ = DEFAULT_X, const double& base_y_ = DEFAULT_Y, const double& pixel_size_ = DEFAULT_SIZE) :
		fractal(std::make_shared<region2d>(dim_x_, dim_y_, base_x_, base_y_, pixel_size_))
	{}

	tbb_mandel(const tbb_mandel& O) : fractal(O.fractal) {	}

	void operator() (const tbb::blocked_range2d<size_t, size_t>& rng) const {
		size_t i{rng.rows().begin()};
		for( double y=fractal->base_y+fractal->pixel_size*i; i!=rng.rows().end(); ++i, y+=fractal->pixel_size ){
			size_t j{rng.cols().begin()};
			for( double x=fractal->base_x+fractal->pixel_size*j; j!=rng.cols().end(); ++j, x+=fractal->pixel_size ){
				fractal->values(i, j) = mand_compute(x, y);
				//std::cout << x << ' ' << x <<' '<<mand_compute(x, y) << std::endl;
			}
		}
	}

	int read(const size_t& i, const size_t& j) const {
		return fractal->values(i, j);
	}	

	auto to_raw_image() const {
		return fractal->to_char_image();
	}
};

int main () { 
	tbb_mandel myFractal;	

	tbb::parallel_for( tbb::blocked_range2d<size_t, size_t>(0, DEFAULT_PIXELS, 0, DEFAULT_PIXELS), myFractal );
  
	ppm_image fractalImage(myFractal.to_raw_image());
	fractalImage.to_file("Frattale");

	return 0;
} 
