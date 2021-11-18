#include <stdio.h>

// __global__ functions, or "kernels", execute on the device
__global__ void hello_kernel(void)
{
  printf("Hello from GPU, I'm thread %d on block %d!\n", threadIdx.x, blockIdx.x);
  
}

int main(void)
{
  // greet from the host
  printf("Hello, world from the host!\n");

  // launch a kernel with a single thread to greet from the device
  hello_kernel<<<2,2>>>();

  // wait for the device to finish so that we see the message
  cudaError_t cuda_err = cudaDeviceSynchronize();
  if (cuda_err != cudaSuccess)
    printf("launch error \"%s\".\n", cudaGetErrorString(cuda_err));

  return 0;
}
