#===============================================================================
# Compile C++
#===============================================================================
mpic++ function/threepoint.cpp -o threepoint.out
mpic++ function/threepoint_v2.cpp -o threepoint_non.out

#===============================================================================
# Run heat_transfer
# dimension, thread_cnt, temp0, temp1, temp2, temp3, timesteps, tolerance 
#===============================================================================
printf "\n==============================================================================="
printf "\nRunning Programs"
printf "\n===============================================================================\n"

mpirun -n 1   threepoint_non.out 100
mpirun -n 1   threepoint.out 100
mpirun -n 2   threepoint_non.out 200
mpirun -n 2   threepoint.out 200
mpirun -n 4   threepoint_non.out 400
mpirun -n 4   threepoint.out 400


mpirun -n 1   threepoint_non.out 200
mpirun -n 1   threepoint.out 200
mpirun -n 2   threepoint_non.out 400
mpirun -n 2   threepoint.out 400
mpirun -n 4   threepoint_non.out 800
mpirun -n 4   threepoint.out 800
