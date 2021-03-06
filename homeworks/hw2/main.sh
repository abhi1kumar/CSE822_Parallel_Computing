#===============================================================================
# Get CPU info
#===============================================================================
lscpu | egrep 'CPU'
lscpu | egrep 'cache'
printf "\n"

#===============================================================================
# Compile C++
#===============================================================================
g++ function/time_mat_mul.cpp -o binary.o

#===============================================================================
# Get running time
#===============================================================================
./binary.o 10 30
./binary.o 32 30
./binary.o 64 30
./binary.o 128 30
./binary.o 256 30
#./binary.o 512
#./binary.o 1024
#./binary.o 2048 1
#./binary.o 3162 1

#===============================================================================
# Plot data in Python
#===============================================================================
python function/plot_graph.py
