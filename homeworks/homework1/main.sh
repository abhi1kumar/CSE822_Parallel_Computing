g++ branch_prediction.cpp -O0 -o normal_branch_prediction.o
g++ branch_prediction.cpp -O2 -o optimized_branch_prediction.o

#===============================================================================
printf "Normal Branch Prediction without Sorting\n"
./normal_branch_prediction.o 0 32
./normal_branch_prediction.o 0 64
./normal_branch_prediction.o 0 128
./normal_branch_prediction.o 0 256
./normal_branch_prediction.o 0 512
./normal_branch_prediction.o 0 1024
./normal_branch_prediction.o 0 2048
./normal_branch_prediction.o 0 4096
./normal_branch_prediction.o 0 8192
./normal_branch_prediction.o 0 16384
./normal_branch_prediction.o 0 32768

#===============================================================================
printf "\nNormal Branch Prediction with Sorting\n"
./normal_branch_prediction.o 1 32
./normal_branch_prediction.o 1 64
./normal_branch_prediction.o 1 128
./normal_branch_prediction.o 1 256
./normal_branch_prediction.o 1 512
./normal_branch_prediction.o 1 1024
./normal_branch_prediction.o 1 2048
./normal_branch_prediction.o 1 4096
./normal_branch_prediction.o 1 8192
./normal_branch_prediction.o 1 16384
./normal_branch_prediction.o 1 32768

#===============================================================================
printf "\n\nOptimized Branch Prediction without Sorting\n"
./optimized_branch_prediction.o 0 32
./optimized_branch_prediction.o 0 64
./optimized_branch_prediction.o 0 128
./optimized_branch_prediction.o 0 256
./optimized_branch_prediction.o 0 512
./optimized_branch_prediction.o 0 1024
./optimized_branch_prediction.o 0 2048
./optimized_branch_prediction.o 0 4096
./optimized_branch_prediction.o 0 8192
./optimized_branch_prediction.o 0 16384
./optimized_branch_prediction.o 0 32768

#===============================================================================
printf "\nOptimized Branch Prediction with Sorting\n"
./optimized_branch_prediction.o 1 32
./optimized_branch_prediction.o 1 64
./optimized_branch_prediction.o 1 128
./optimized_branch_prediction.o 1 256
./optimized_branch_prediction.o 1 512
./optimized_branch_prediction.o 1 1024
./optimized_branch_prediction.o 1 2048
./optimized_branch_prediction.o 1 4096
./optimized_branch_prediction.o 1 8192
./optimized_branch_prediction.o 1 16384
./optimized_branch_prediction.o 1 32768
