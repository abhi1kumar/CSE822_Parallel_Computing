
#include <stdio.h>

#include <cuda_runtime.h>

#include <helper_cuda.h>


__global__ void scalarMulAdd(const float *A, const float *B, const float *C, float *D, int numElements)
{
  int i = blockDim.x * blockIdx.x + threadIdx.x;

  if (i < numElements) 
  {
    D[i] = A[i]*B[0] + C[0] + 0.0f;
  }
}

int main(void)
{
    cudaError_t error = cudaSuccess;

    int numElements = 50000;
    size_t size = numElements * sizeof(float);
    printf("[Vector addition of %d elements]\n", numElements);

    // Allocate CPU device
    // Allocate the host input vector A, D
    float *h_A = (float *)malloc(size);
    float *h_D = (float *)malloc(size);

    // Allocate the host input B and C
    float *h_B = (float *)malloc(sizeof(float));
    float *h_C = (float *)malloc(sizeof(float));

    //Verify that allocations succeeded
    if (h_A == NULL || h_B == NULL || h_C == NULL || h_D == NULL ) 
    {
        fprintf(stderr, "Failed to allocate host vectors!\n");
        exit(EXIT_FAILURE);
    }

    // Allocate GPU device
    float *d_A = NULL;
    err_A = cudaMalloc((void **)&d_A, size);
    float *d_D = NULL;
    err_D = cudaMalloc((void **)&d_D, size);

    float *d_B = NULL;
    err_B = cudaMalloc((void **)&d_B, sizeof(float));
    float *d_C = NULL;
    err_C = cudaMalloc((void **)&d_C, sizeof(float));

    if (err_A != cudaSuccess || err_B != cudaSuccess || err_C != cudaSuccess || err_D != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device vector (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);

    }

    // Fill memory
    for (int i=0; i < numElements; ++i)
        h_A[i] = 1.0;
    h_B[0] = 2.0;
    h_C[0] = 3.0; 


    // Copy from host to device
    printf("Copy input data from the host memory to the CUDA device\n");
    err = cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    err = cudaMemcpy(d_B, h_B, sizeof(float), cudaMemcpyHostToDevice);
    err = cudaMemcpy(d_C, h_C, sizeof(float), cudaMemcpyHostToDevice);


    // Launch the Vector Add CUDA Kernel
    int threadsPerBlock = 256;
    int blocksPerGrid = (numElements + threadsPerBlock - 1) / threadsPerBlock;
    printf("CUDA kernel launch with %d blocks of %d threads\n", blocksPerGrid,
         threadsPerBlock);
    scalarMulAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, d_D, numElements);
    err = cudaGetLastError();

    if (err != cudaSuccess) {
    fprintf(stderr, "Failed to launch scalarMulAdd kernel (error code %s)!\n",
            cudaGetErrorString(err));
    exit(EXIT_FAILURE);
    }

    printf("Copy output data from the CUDA device to the host memory\n");
    err = cudaMemcpy(h_D, d_D, size, cudaMemcpyDeviceToHost);

    for (int i=0; i< numElements; ++i)
        printf("%d %d", h_A[i] * h_B[0] + h_C[0], h_D[0]);

    // Free device global memory
    err = cudaFree(d_A);
    err = cudaFree(d_B);
    err = cudaFree(d_C);
    err = cudaFree(d_D);
}
