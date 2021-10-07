# Number of threads 
export OMP_NUM_THREADS=5

# Compile
gcc -fopenmp hello_openmp.c -o hello_openmp.o

# Run
./hello_openmp.o
