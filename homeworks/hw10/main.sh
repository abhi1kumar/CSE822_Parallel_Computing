#===============================================================================
# Compile C++
#===============================================================================
rm vector_addition.out
mpic++ function/vector_addition_final.cpp -o vector_addition.out


#===============================================================================
# Run vector_addition
# size1, size2, seed
#===============================================================================
printf "\n==============================================================================="
printf "\nRunning Addition"
printf "\n===============================================================================\n"
mpirun -n 2 ./vector_addition.out 4 8 2
mpirun -n 2 ./vector_addition.out 4 16 2
mpirun -n 2 ./vector_addition.out 4 32 2
mpirun -n 2 ./vector_addition.out 4 64 2
mpirun -n 2 ./vector_addition.out 4 128 2
mpirun -n 2 ./vector_addition.out 4 256 2
mpirun -n 2 ./vector_addition.out 4 512 2
mpirun -n 2 ./vector_addition.out 4 1024 2
mpirun -n 2 ./vector_addition.out 4 2048 2
mpirun -n 2 ./vector_addition.out 4 4096 2
mpirun -n 2 ./vector_addition.out 4 8192 2
