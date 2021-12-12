#===============================================================================
# Compile C++
#===============================================================================
g++ function/matrix_mul_and_add_cpu.cpp -o cpu.out

nvcc function/matrix_mul_and_add.cu

#===============================================================================
# Run matrix vector multiplication and addition
# dimension
#===============================================================================
./cpu.out
printf "\n==============================================================================="
printf "\nRunning Matrix Vector Multiplication and addition"
printf "\n===============================================================================\n"
nvprof ./a.out 1
nvprof ./a.out 2
nvprof ./a.out 4
nvprof ./a.out 8
nvprof ./a.out 16
nvprof ./a.out 32
nvprof ./a.out 64
nvprof ./a.out 128
nvprof ./a.out 256
nvprof ./a.out 512
