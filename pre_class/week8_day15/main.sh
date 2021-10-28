#===============================================================================
# Compile CPP file and execute with 3 processes
#===============================================================================
mpic++ print_message.cpp -o print_message.o
mpic++ --showme
mpiexec -n 3 ./print_message.o

#===============================================================================
# Compile CPP file and execute with 3 processes
#===============================================================================
mpic++ file_write.cpp -o file_write.o
mpic++ --showme
mpiexec -n 3 ./file_write.o
