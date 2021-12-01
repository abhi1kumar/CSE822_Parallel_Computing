#include<iostream>
using std::cout; using std::endl;
#include<random>
using std::mt19937_64; using std::uniform_real_distribution; using std::random_device;
#include<algorithm>
using std::generate; using std::fill_n;
#include<chrono>
using namespace std::chrono_literals;

void fill_ary(float *ary, long cnt){
  mt19937_64 reng(random_device{}() );
  uniform_real_distribution<float> dist(0,10);
  generate(ary, ary+cnt, [&](){return dist(reng);});
}

void matmul_cpu (float *A, float *B, float *C, int size){
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      C[i*size + j] = 0;
      for (int k = 0; k < size; k++) {
	C[i*size +j] += A[i*size + k] * B[k*size + j];
      }
    }
  }
}

__global__ void matmul_basic(float* A, float* B, float* C, int width) {
  //calculate the row and column for this element of the matrix
  int row = threadIdx.y + (blockDim.y * blockIdx.y);
  int col = threadIdx.x + (blockDim.x * blockIdx.x);
  
  if ((row < width) && (col < width)) {
    float result = 0;
    for (int k = 0; k < width; k++) {
      result += A[(row * width) + k] * B[(k * width) + col];
    }
    C[(row * width) + col] = result;
  }
}

const int TILE_WIDTH = 32;
__global__ void matmul_shared(float* A, float* B, float* C, int width) {
  __shared__ float Ashare[TILE_WIDTH][TILE_WIDTH];
  __shared__ float Bshare[TILE_WIDTH][TILE_WIDTH];
  int bx = blockIdx.x;
  int by = blockIdx.y;
  int tx = threadIdx.x;
  int ty = threadIdx.y;
  
  //calculate the row and column for this element of the matrix
  int row = by * TILE_WIDTH + ty;
  int col = bx * TILE_WIDTH + tx;
  
  float result = 0;
  //loop over the A and B tiles required to compute the C element
  for (int m = 0; m < width / TILE_WIDTH; m++) {
    /*
      Indexing parameters:
      For A:
                       row * width : Index global row for this thread (invariant)
	            m * TILE_WIDTH : Index new columns for each iter
	                        tx : Index column of this set
      For B:
            m * TILE_WIDTH * width : index, new set of rows each iter
	                ty * width : index row in that set
			       col : the global column (invariant)
    */				
    Ashare[ty][tx] = A[(row * width) + (m * TILE_WIDTH + tx)];
    Bshare[ty][tx] = B[(m * TILE_WIDTH * width) + (ty * width) + col];
    __syncthreads(); //wait for all the shared memory to be loaded

    for (int k = 0; k < TILE_WIDTH; k++) {
      result +=	Ashare[ty][k] * Bshare[k][tx];
    }
    __syncthreads(); //make sure all threads have done their calculation
                     //before modifying the shared memory.
  }
  C[(row * width) + col] = result;
}


int main (int argc, char **argv){
  if (argc != 2){
    cout << "Need a size"<<endl;
    exit(1);
  }
  int n = atoi(argv[1]);
  long sz = n*n;
  float *A_host, *B_host, *C_host, *A_dev, *B_dev, *C_dev;
  int nerror;

  int block_cnt, thread_cnt;

  A_host = new float[sz];
  B_host = new float[sz];
  C_host = new float[sz];

  std::chrono::time_point<std::chrono::steady_clock> start, stop;
  using time_span = std::chrono::milliseconds;

  // fill_ary(x_host, n);
  // fill_ary(y_host, n);

  // just to check our results.
  fill_n(A_host, sz, 1.0);
  fill_n(B_host, sz, 2.0);
  
  int bytes = sz * sizeof(float);
  cudaMalloc((void **) &A_dev, bytes);
  cudaMalloc((void **) &B_dev, bytes);
  cudaMalloc((void **) &C_dev, bytes);

  cudaMemcpy(A_dev, A_host, bytes, cudaMemcpyHostToDevice);
  cudaMemcpy(B_dev, B_host, bytes, cudaMemcpyHostToDevice);

  thread_cnt = 512;
  block_cnt = sz/thread_cnt + (sz % thread_cnt > 0);

  start = std::chrono::steady_clock::now();
  for (int i=0; i<10; ++i)
    matmul_basic<<<block_cnt, thread_cnt>>>(A_dev, B_dev, C_dev, n);
  //  cudaDeviceSynchronize();
  cudaMemcpy(C_host, C_dev, bytes, cudaMemcpyDeviceToHost);
  stop = std::chrono::steady_clock::now();
  auto elapsed_gpu_1 = std::chrono::duration_cast<time_span>(stop - start).count();

  start = std::chrono::steady_clock::now();
  for (int i=0; i<10; ++i)
    matmul_shared<<<block_cnt, thread_cnt>>>(A_dev, B_dev, C_dev, n);
  // cudaDeviceSynchronize();
  cudaMemcpy(C_host, C_dev, bytes, cudaMemcpyDeviceToHost);
  stop = std::chrono::steady_clock::now();
  auto elapsed_gpu_2 = std::chrono::duration_cast<time_span>(stop - start).count();
  
  /* start = std::chrono::steady_clock::now(); */
  /* for (int i=0; i<10; ++i) */
  /*   matmul_cpu(A_host, B_host, C_host, n); */
  /* stop = std::chrono::steady_clock::now(); */
  /* auto elapsed_cpu = std::chrono::duration_cast<time_span>(stop - start).count(); */
  cout <<", GPU basic: "<<elapsed_gpu_1 <<", GPU shared: "<<elapsed_gpu_2<<endl;
  // cout << "CPU: "<<elapsed_cpu<<", GPU basic: "<<elapsed_gpu_1 <<", GPU shared: "<<elapsed_gpu_2<<endl;
}
