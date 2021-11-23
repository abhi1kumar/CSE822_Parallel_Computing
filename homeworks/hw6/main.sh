#===============================================================================
# Compile C++
#===============================================================================
rm heat_transfer.o
g++ -fopenmp function/heat_transfer.cpp -o heat_transfer.o

#===============================================================================
# Run heat_transfer
# dimension, thread_cnt, temp0, timesteps, tolerance
#===============================================================================
printf "\n==============================================================================="
printf "\nRunning Heat Transfer"
printf "\n===============================================================================\n"
./heat_transfer.o 100 1 1 100 0.001
./heat_transfer.o 100 2 1 100 0.001
./heat_transfer.o 100 4 1 100 0.001
./heat_transfer.o 100 8 1 100 0.001
./heat_transfer.o 100 16 1 100 0.001
./heat_transfer.o 100 32 1 100 0.001
