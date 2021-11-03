#include<iostream>
using std::cout; using std::endl;
using namespace std;
#include<random>
using std::default_random_engine; using std::uniform_int_distribution;

#include<algorithm>
using std::fill_n;

#include <mpi.h>

int main (int argc, char **argv){

  int comm_sz, my_rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  MPI_Status status;

  int sz = atoi(argv[1]);

  cout << "Size = " << sz << endl;

    // Buffer Creation
    double* send_ary = new double[sz];
    double* rec_ary = new double[sz];

    fill_n(send_ary, sz, 3);
    fill_n(rec_ary , sz, 3);

  if (my_rank == 0){
    // Send
    MPI_Send(send_ary, sz, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);    
    MPI_Recv(rec_ary, sz, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status);
    
  }
  else{
    MPI_Send(send_ary, sz, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    MPI_Recv(rec_ary, sz, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);

  }
  MPI_Finalize();
}
