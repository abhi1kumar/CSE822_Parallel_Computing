#include <iostream>
using std::cout; using std::endl;

#include <vector>
using std::vector;

#include <omp.h>

#include <fstream>

#include <stdlib.h>     /* abs */


//==============================================================================
// Utility functions
//==============================================================================
vector<vector<double>> generateTempGrid(int nx, int ny, int ng)
{
    // Makes empty 2D array with dim (nx,ny)
    // We also pad 2 zeros for the case so that the borders are not treated
    // specially in the code. We could simply run from index 1 to new_length-1
    // instead of index 0 to new_length
    vector<vector<double>> T ((ny+2 * ng), vector<double> (nx+2 * ng));

    return T;
}

void fillTGrid(vector<vector<double>> &T, int n, double T0) 
{
    // All indices initialized to 0
//  #pragma omp for    
    for (int i = 1; i<T.size()-1; ++i)
        for (int j = 1; j<T[i].size()-1; ++j)
           T[i][j] = 0.0;

    // Central Indices kept at T0
    T[n/2][n/2]     = T0;
    T[n/2 + 1][n/2] = T0;
    T[n/2][n/2 + 1] = T0;
    T[n/2+1][n/2+1] = T0;
}

void print_mat(vector<vector<double>> T)
{
    for (auto& row : T)
    {
        for (auto col : row)
            cout << col << " ";
        cout << "\n";
    }
    cout << "\n";
}

void saveTtoCSV(vector<vector<double>> T, char* outfile) 
{
    std::ofstream out(outfile);

    for (auto& row : T)
    {
        for (auto col : row)
            out << col << ",";
        out << "\n";
    }
}

//==============================================================================
// All simulation related functions propagate, diff calculator, updating
//==============================================================================
void computeOneTimestep(vector<vector<double>> &T, vector<vector<double>> &T_np1, int num_th= 1) 
{    
    int i, j;
    #pragma omp parallel for num_threads(num_th) shared(T, T_np1) private(i,j) schedule (guided)
        for (i = 1; i<T.size()-1; ++i)
            for (j = 1; j<T[i].size()-1; ++j)
                T_np1[i][j] = 0.25 * (T[i+1][j] + T[i-1][j] + T[i][j+1] + T[i][j-1]);
}

double calcLargestDiff(vector<vector<double>> &T, vector<vector<double>> &T_np1, int num_th= 1) 
{    
    double min_val = 1e20;
    //double max_val = 0.0;
    vector<double> max_val(num_th, -1.0);
    double largest_of_max = -1.0;

    int i, j;

    // First get the max of each thread
    // NOTE: If we use a critical section while calculating the difference 
    // between plate temperature at time (t) and (t+1), the code would 
    // effectively serialize. Therefore, we get the max of each thread and then 
    // get the largest of max of each thread.
    #pragma omp parallel for num_threads(num_th) shared(max_val, min_val, T, T_np1) private(i,j) schedule (guided)
        for (i = 1; i<T.size()-1; ++i)
        {
            int tid = omp_get_thread_num();
            
            for (j = 1; j<T[i].size()-1; ++j)
            {
                // Difference between plate pixels at time (t) and (t+1)            
                double diff = abs(T_np1[i][j] - T[i][j]);
                
                if (diff > max_val[tid])
                    max_val[tid] = diff;
            }
        }

    // Now get the largest of the max of each thread
    for (i= 0; i < num_th; ++i)
        if (max_val[i] > largest_of_max)
            largest_of_max = max_val[i];

    //double largest_diff = max_val - min_val;
    //return largest_diff;

    return largest_of_max;
}

void updateArrays(vector<vector<double>> &T, vector<vector<double>> &T_np1, int num_th= 1)
{
    int i, j;
    #pragma omp parallel for num_threads(num_th) shared(T, T_np1) private(i,j) schedule (guided)
        for (i = 1; i<T.size()-1; ++i)
            for (j = 1; j<T[i].size()-1; ++j)
                T[i][j] = T_np1[i][j];
}

void runSimulation(vector<vector<double>> &T, vector<vector<double>> &T_np1,
                   int nsteps, double tol, int num_threads= 1)
{
    double largest_diff = 100.0;  
    
    for (int iter=0; iter<nsteps; ++iter) 
    {
        // Propagate one step        
        computeOneTimestep(T, T_np1, num_threads);

        // Calculate difference and decide want to continue or not
        largest_diff = calcLargestDiff(T, T_np1, num_threads);
        if (largest_diff <= tol) 
        {
            //cout << "Tolerance reached, quitting simulation, " << largest_diff << endl;
            break;
        }
        updateArrays(T, T_np1, num_threads);
    }
}

//==============================================================================
// main function
//==============================================================================
int main(int argc, char* argv[])
{
    if (argc != 6)
        cout << "Please specify 5 parameters dimension, thread_cnt, temp0, timesteps, tolerance ..." << endl;
    else
    {
        int n           = atoi(argv[1]);
        int num_threads = atoi(argv[2]);
        float T0        = atof(argv[3]);
        int nsteps      = atoi(argv[4]);
        float tol       = atof(argv[5]);

        int repeat      = 10;
        double time_elapsed_sum = 0.0;
        double time_elapsed_avg = 0.0;

        omp_set_num_threads(num_threads);

        for(int r=0; r < repeat; ++r)
        {

            char initial[] = "output/T_init.csv";
            char outfile[] = "output/T_final.csv";

            vector<vector<double>> T     = generateTempGrid(n, n, 1);
            vector<vector<double>> T_np1 = generateTempGrid(n, n, 1);
            fillTGrid(T, n, T0);

            // Save the initial plate to CSV
            saveTtoCSV(T, initial);

            double start = omp_get_wtime();

            runSimulation(T, T_np1, nsteps, tol, num_threads);
            
            double end = omp_get_wtime();
            time_elapsed_sum += (end-start);
            
            // Save the final plate to CSV
            saveTtoCSV(T, outfile);
        }
        
        time_elapsed_avg = time_elapsed_sum/repeat;
        cout << "Size= "<< n << " Num_threads= " << num_threads << " Repeat= ";
        cout << repeat << " Init_temp= " << T0 << " nsteps= " << nsteps;
        cout << " tol= " << tol << " Time= " << time_elapsed_avg << endl;
    }
}
