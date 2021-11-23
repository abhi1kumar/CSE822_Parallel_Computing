#include<iostream>
using std::cout; using std::endl;

using namespace std;

#include<vector>
using std::vector;

#include<random>
using std::default_random_engine; using std::uniform_int_distribution;

#include<mpi.h>

int main(int argc, char** argv){

    if (argc < 3){
        cout << "a.out a_size b_size seed"<<endl;
        exit;
    }
    int a_size = atoi(argv[1]);
    int b_size = atoi(argv[2]);
    int seed   = atoi(argv[3]);

    int comm_size, my_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    bool debug = false; 

    int max_size    = max(a_size, b_size);
    int global_size = max_size*comm_size; 
    vector <int> vec1 (global_size);
    vector <int> vec2 (global_size);
    int *global_result;

    int num_repeat = 5;
    vector<double>  time_all(num_repeat);
    double starttime, endtime;

    for (int r=0; r<num_repeat; ++r)
    {
        // =========================================================================
        // Initialization stuff
        // =========================================================================
        if (my_rank == 0)
        {
            // Fill data
            default_random_engine dre(seed);
            uniform_int_distribution<int> dist(1, max_size);
            for (int i=0; i< global_size; ++i)
            {
                if (i >= a_size*comm_size)
                    vec1[i] = 0;
                else
                    vec1[i] = dist(dre);
                if (i >= b_size*comm_size)
                    vec2[i] = 0;
                else
                    vec2[i] = dist(dre);

            }

            global_result = new int[global_size];
            for (int i=0; i< global_size; ++i)
                global_result [i] = 0;

            if (debug)
            {
                // Print data
                for (int i=0; i< global_size; ++i)
                    cout << vec1[i] << " " << vec2[i] << "\n";
                cout << endl;
            }

        }
        // Put a barrier so that output only proceeds when the initializations are done
        MPI_Barrier(MPI_COMM_WORLD);


        starttime = MPI_Wtime();

        // =========================================================================
        // Scatter the data to different processors
        // =========================================================================
        vector<int> vec1_chunk(max_size), vec2_chunk(max_size);
        MPI_Scatter(&vec1.front(), max_size, MPI_INT, &vec1_chunk.front(), max_size, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(&vec2.front(), max_size, MPI_INT, &vec2_chunk.front(), max_size, MPI_INT, 0, MPI_COMM_WORLD);

        if (debug)
        {
            // Print inputs on processor
            cout << "Input on processor " << my_rank << "\n";
            for (int i=0; i< max_size; ++i)
                cout << vec1_chunk[i] << " " << vec2_chunk[i] << " ";
            cout << "\n";
        }

        // =========================================================================
        // Get local addition result
        // =========================================================================
        vector <int> local_result (max_size);
        for (int i=0; i< max_size; ++i)
        {
            //local_result[i] = vec1_chunk[i] + vec2_chunk[i];

            // BETTER ROOFLINE PERFORMANCE
            local_result[i] = atan(sqrt(vec1_chunk[i])) + atan(sqrt(vec2_chunk[i]));
        }
        if (debug)
        {
            // Print local addition result
            cout << "Local result on processor " << my_rank << "\n";
            for (int i=0; i< max_size; ++i)
                cout << local_result[i] << " ";
            cout << "\n";
        }

        // =========================================================================
        // Do gather
        // =========================================================================
        MPI_Gather(&local_result.front(), max_size, MPI_INT, global_result, max_size, MPI_INT, 0, MPI_COMM_WORLD);
        
        endtime     = MPI_Wtime();
        time_all[r] = endtime - starttime;

        if (my_rank == 0)
        {
            //cout << "Gathered \n";
            //for (int i=0; i < global_size; ++i)
            //  cout <<  global_result[i] << " ";
            //cout << "\n";

            delete global_result;
        }

    }

    if (my_rank == 0)
    {
        double t_avg = 0.0;
        for (int r= 0; r < num_repeat; ++r)
            t_avg += time_all[r];
        t_avg /= num_repeat;
        cout << "a_size = " << a_size << " b_size = " << b_size << " repeat = " << num_repeat << " time = " << t_avg << endl;
    }


    MPI_Finalize();

}
