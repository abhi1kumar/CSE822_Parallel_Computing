# Number of threads 
export OMP_NUM_THREADS=5

# Compile
gcc -fopenmp hello_openmp.c -o hello_openmp.o
g++ -fopenmp hello_openmp.cpp -o hello_openmp_cpp.o

# Run
#./hello_openmp.o
./hello_openmp_cpp.o 4
