g++ -pthread 3_race.cpp -o 3_race
#./3_race

printf "\n"
g++ -pthread 3.1_mutex.cpp -o 3.1_mutex
./3.1_mutex

printf "\n"
g++ -pthread 3.2_lock_guard.cpp -o 3.2_lock_guard
./3.2_lock_guard

printf "\n"
g++ -pthread 3.3_race_with_lock.cpp -o 3.3_race_with_lock
./3.3_race_with_lock
