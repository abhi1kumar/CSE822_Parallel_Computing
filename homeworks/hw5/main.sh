#===============================================================================
# Compile C++
#===============================================================================
g++ -fopenmp function/integration.cpp -o integration.o


#===============================================================================
# Run integration
# thread cnt, left, right and number of traps argument
#===============================================================================
./integration.o 2 4 5 1
./integration.o 2 4 5 2
./integration.o 2 4 5 4
./integration.o 2 4 5 8
./integration.o 2 4 5 16
./integration.o 2 4 5 32
./integration.o 2 4 5 64
./integration.o 2 4 5 128
./integration.o 2 4 5 256
./integration.o 2 4 5 512
./integration.o 2 4 5 1024
./integration.o 2 4 5 2048
./integration.o 2 4 5 4096
./integration.o 2 4 5 8192
./integration.o 2 4 5 16384

printf "\n==============================================================================="
printf "\nStrong Scaling"
printf "\n===============================================================================\n"
./integration.o 1 4 5 16384
./integration.o 2 4 5 16384
./integration.o 4 4 5 16384
./integration.o 8 4 5 16384
./integration.o 16 4 5 16384
./integration.o 32 4 5 16384
./integration.o 64 4 5 16384
./integration.o 128 4 5 16384
./integration.o 256 4 5 16384
./integration.o 512 4 5 16384

printf "\n==============================================================================="
printf "\nWeak Scaling"
printf "\n===============================================================================\n"
./integration.o 2 4 5 32
./integration.o 4 4 5 64
./integration.o 8 4 5 128
./integration.o 16 4 5 256
./integration.o 32 4 5 512
./integration.o 64 4 5 1024
./integration.o 128 4 5 2048
./integration.o 256 4 5 4096
./integration.o 512 4 5 8192
./integration.o 1024 4 5 16384
