
#include <stdio.h>

#include <cuda_runtime.h>

__global__ void matrixMulAdd(const float *A, const float *B, const float *C, float *D, int numElements)
{
  int col = blockDim.x * blockIdx.x + threadIdx.x;
  int row = blockDim.y * blockIdx.y + threadIdx.y;

  float sum = 0.0f;

  // Do matrix multiplication first
  for (int k = 0; k < numElements; ++k)
    sum += A[row * numElements + k] * B[k];

  // Now add the third vector
  D[col] = sum +  C[col];
}

int main(int argc, char** argv)
{
    if (argc < 1){
        printf("a.out block_size");
        exit;
    }
    int blocksPerGrid = atoi(argv[1]);

    int numElements = 512;
    size_t size_bytes = numElements * sizeof(float);
    printf("[Vector addition of %d elements]\n", numElements);

    // Allocate CPU device
    // Allocate the host input vector A, B, C, D
    float *h_A = (float *)malloc(numElements * size_bytes);    
    float *h_B = (float *)malloc(size_bytes);
    float *h_C = (float *)malloc(size_bytes);
    float *h_D = (float *)malloc(size_bytes);

    //Verify that allocations succeeded
    if (h_A == NULL || h_B == NULL || h_C == NULL || h_D == NULL ) 
    {
        fprintf(stderr, "Failed to allocate host vectors!\n");
        exit(EXIT_FAILURE);
    }

    // Allocate GPU device
    float *d_A = NULL;
    float *d_B = NULL;
    float *d_C = NULL;
    float *d_D = NULL;

    cudaMalloc((void **)&d_A, numElements * size_bytes);
    cudaMalloc((void **)&d_B, size_bytes);
    cudaMalloc((void **)&d_C, size_bytes);
    cudaMalloc((void **)&d_D, size_bytes);

    // Fill memory
    for (int i=0; i < numElements; ++i)
    {
        for (int j=0; j < numElements; ++j)
            h_A[i*numElements + j] = 1.0;
        h_B[i] = 1.0;
        h_C[i] = 3.0; 
    }

    // Copy from host to device
    printf("Copy input data from the host memory to the CUDA device\n");
    cudaMemcpy(d_A, h_A, numElements * size_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_C, h_C, size_bytes, cudaMemcpyHostToDevice);

    // Launch the matrixMulAdd CUDA Kernel
    int threadsPerBlock = (numElements + blocksPerGrid - 1) / blocksPerGrid;
    //int blocksPerGrid = (numElements + threadsPerBlock - 1) / threadsPerBlock;
    printf("CUDA kernel launch with %d blocks of %d threads\n", blocksPerGrid,
         threadsPerBlock);
    matrixMulAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, d_D, numElements);

    printf("Copy output data from the CUDA device to the host memory\n");
    cudaMemcpy(h_D, d_D, size_bytes, cudaMemcpyDeviceToHost);

    // Debug Printing
    // for (int i=0; i< numElements; ++i)
    //    printf("%f ", h_D[i]);

    // Free device global memory
    delete [] h_A;
    delete [] h_B;
    delete [] h_C;
    delete [] h_D;    

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    cudaFree(d_D);

    return 0;
}
