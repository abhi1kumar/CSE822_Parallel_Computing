#===============================================================================
# Compile C++
#===============================================================================
#g++ -pthread -std=c++17 function/atm.cpp -o atm.o
g++ -pthread -std=c++17 function/atm_shared.cpp -o atm_shared.o


#===============================================================================
# Run atm
#===============================================================================
#./atm.o
./atm_shared.o
