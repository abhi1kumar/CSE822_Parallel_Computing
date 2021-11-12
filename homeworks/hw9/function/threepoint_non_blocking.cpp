#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <vector>

int main(int argc, char *argv[])
{
    // Initialize the MPI communicator
    MPI_Init(&argc, &argv);

    MPI_Request request[4];

    // Get rank/size
    int myRank, numRanks;

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &numRanks);

    int nGlobal = atoi(argv[1]);
    
    // Setup local array
    int nLocal = (int)nGlobal/numRanks;
    if (myRank==0) nLocal += nGlobal%numRanks;

    // Allocate and initialize the vector
    // x is allocate with 2 ghost zones
    std::vector<float> x(nLocal+2);
    std::vector<float> y(nLocal);
    for (int i=1; i<nLocal+1; i++){
        x[i] = i + myRank*(nLocal+nGlobal%numRanks);
    }

    // Now specify neighbors
    int leftNeigh = myRank-1;
    if (myRank==0) leftNeigh = numRanks-1;
    int rghtNeigh = myRank+1;
    if (myRank==numRanks-1) rghtNeigh = 0;

    int num_repeat = 5;
    std::vector<double>  time_all(num_repeat);
    double starttime, endtime;

    for (int r=0; r<num_repeat; ++r)
    {
        starttime = MPI_Wtime();
        // =========================================================================
        // Send the stuff we have in air and later check the status
        // =========================================================================
        if (myRank%2 == 0){
            // exchange with left neighbor rank
            MPI_Isend(&x[1], 1, MPI_FLOAT, leftNeigh, 0, MPI_COMM_WORLD, &request[0]);
            MPI_Irecv(&x[0], 1, MPI_FLOAT, leftNeigh, 0, MPI_COMM_WORLD, &request[1]);
        }
        else {
            // exchange with right neighbor rank
            MPI_Irecv(&x[nLocal+1], 1, MPI_FLOAT, rghtNeigh, 0, MPI_COMM_WORLD, &request[0]);
            MPI_Isend(&x[nLocal]  , 1, MPI_FLOAT, rghtNeigh, 0, MPI_COMM_WORLD, &request[1]);
        }

        // Now do the other exchanges
        if (myRank%2==1){
            // exchange with left neighbor rank
            MPI_Isend(&x[1], 1, MPI_FLOAT, leftNeigh, 0, MPI_COMM_WORLD, &request[2]);
            MPI_Irecv(&x[0], 1, MPI_FLOAT, leftNeigh, 0, MPI_COMM_WORLD, &request[3]);
        }
        else{
            // exchange with right neighbor rank
            MPI_Irecv(&x[nLocal+1], 1, MPI_FLOAT, rghtNeigh, 0, MPI_COMM_WORLD, &request[2]);
            MPI_Isend(&x[nLocal]  , 1, MPI_FLOAT, rghtNeigh, 0, MPI_COMM_WORLD, &request[3]);
        }

        // =========================================================================
        // Calculate the floating point averages of stuff we have
        // =========================================================================
        for (int i = 1; i < nLocal-1; ++i)
            y[i] = (x[i]+x[i+1]+x[i+2])/3.;

        // =========================================================================
        // Check if all 4 (2 send, 2 receive) finalized
        // =========================================================================
        MPI_Waitall(4, request, MPI_STATUSES_IGNORE);
        y[0]         = (x[0] + x[1] + x[2])/3.;
        y[nLocal-1]  = (x[nLocal-1] + x[nLocal] + x[nLocal+1])/3.;

        endtime   = MPI_Wtime();
        /*
        for (int i = 0; i < nLocal + 2; i++)
        {
            std::cout << i << " " << x[i] << std::endl;
        }

        for (int i = 0; i < nLocal; i++)
        {
            std::cout << i << " " << y[i] << std::endl;
        }
        */
        time_all[r] = endtime - starttime;
    }

    if (myRank == 0)
    {
        double t_avg = 0.0;
        for (int r= 0; r < num_repeat; ++r)
            t_avg += time_all[r];
        t_avg /= num_repeat;
        std::cout << "Non-Blocking nLocal = " << nLocal << " numRanks = " << numRanks << " nGlobal = " << nGlobal << " time = " << t_avg << std::endl;
    }

    MPI_Finalize();
}
