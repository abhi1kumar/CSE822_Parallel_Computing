
#include <stdio.h>
#include<stdlib.h>
#include <chrono>

using namespace std;

void matrixMulAdd(const float *A, const float *B, const float *C, float *D, int numElements)
{
  for (int row = 0; row < numElements; ++row)
  {
      float sum = 0.0f;
      // Do matrix multiplication first
      for (int col = 0; col < numElements; ++col)
        sum += A[row * numElements + col] * B[col];

      // Now add the third vector
      D[row] = sum +  C[row];
  }
}

int main(int argc, char** argv)
{

    int numElements = 512;
    size_t size_bytes = numElements * sizeof(float);
    printf("[Vector Matmul of %d elements on CPU]\n", numElements);

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
    }

    // Fill memory
    for (int i=0; i < numElements; ++i)
    {
        for (int j=0; j < numElements; ++j)
            h_A[i*numElements + j] = 1.0;
        h_B[i] = 1.0;
        h_C[i] = 3.0; 
    }
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    float total_time = 0.0f;
    int num_repeat = 500;

    for (int r=0; r<num_repeat; ++r)
    {
        // Launch the matrixMulAdd
        auto t1 = high_resolution_clock::now();
        matrixMulAdd(h_A, h_B, h_C, h_D, numElements);
        auto t2 = high_resolution_clock::now();

        // Getting number of milliseconds as a double.
        duration<double, std::micro> ms_double = t2 - t1;

        total_time += ms_double.count();
        // Debug Printing
        // for (int i=0; i< numElements; ++i)
        //    printf("%f ", h_D[i]);
    }
    printf("Average time = %f\n", total_time/num_repeat);

    // Free device global memory
    delete [] h_A;
    delete [] h_B;
    delete [] h_C;
    delete [] h_D;

    return 0;
}
