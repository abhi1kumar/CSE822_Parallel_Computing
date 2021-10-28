#include <iostream>
using std::cout; using std::endl;
#include <mpi.h>     

int main(int argc, char **argv)
{
    int comm_sz;  // total procs
    int my_rank;  // my id              

    // MPI from here
    MPI_Init(&argc, &argv); 

    // get # of procs from communicator
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

    // get my id from the communicator
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
    if (my_rank == 0)
        cout <<"I'm the master process 0"<<endl;
    else
        cout <<"Hello from process "<<my_rank<<" of "<<comm_sz<<endl;
    
    // MPI finished here 
    MPI_Finalize(); 
}
