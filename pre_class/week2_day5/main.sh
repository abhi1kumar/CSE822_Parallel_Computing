g++ -pthread 1.1-thread-hello.cpp
./a.out

g++ -pthread 1.2-thread-hello-lambda.cpp
./a.out

g++ -pthread 1.3-thread-hello-obj.cpp
./a.out

# Effect of thread join after terminate and join
g++ -pthread thread_join.cpp
./a.out
