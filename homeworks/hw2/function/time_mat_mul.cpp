/*
    Sample Run:
    ./a.out row_size repeat
    ./a.out 32768 1000
*/

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <iomanip>
#include <chrono>

using namespace std;

double** get_2d_array(int row_count, int col_count)
{
    /* Get 2D array */
    // If we want a variable length or dynamically sized array in C++, we have to
    // dynamically allocate memory ourself:
    double** a = new double*[row_count];
    for(int i = 0; i < row_count; ++i)
        a[i] = new double[col_count];

    return a;
}

double** matrix_mul(double** a, double** b, int m, int n, int p)
{    
    double** output = get_2d_array(m, p);
    
    /* Get 2D matrix multiplication */
    for (int i = 0; i < m; ++i)
    {
        for (int k= 0; k < p; ++k)
        {
            output[i][k] = 0.0;
            for (int j = 0; j < n; ++j)
            {
                output[i][k] += a[i][j] * b[j][k];    
            }
        }
    }

    return output;
}

int main(int argc, char* argv[])
{
    int seed             = 0;
    int MAX_VAL_IN_ARRAY = 256;
    int PRECISION        = 8;

    int row_size       = 100; // This is number of rows
    int repeat           = 10;

    std::mt19937_64 dre(seed);
    uniform_int_distribution<int> dist(0, MAX_VAL_IN_ARRAY-1);    
    using duration = std::chrono::nanoseconds; 

    // =========================================================================
    // Command Line Arguments
    // =========================================================================
    if (argc >= 3)
        repeat = atoi(argv[2]);

    if (argc >= 2)
        row_size = atoi(argv[1]);

    // rows and cols both same as array size
    long int m = row_size;
    long int n = row_size;
    long int p = row_size;

    // =========================================================================
    // Array Declaration
    // =========================================================================
    double** a      = get_2d_array(m, n);
    double** b      = get_2d_array(n, p);
    double** output;

    double total_elapsed_time = 0;

    // =========================================================================
    // Repeat 
    // =========================================================================
    for (int r= 0; r < repeat; ++r)
    {
        // Array Initialization
        for (int i= 0; i < m; ++i)
        {
            for (int k= 0; k < p; ++k)
            {
                a[i][k]=dist(dre);
                b[i][k]=dist(dre);
            }
        }
    
        long long int count = 0;

        // Time Declare
        auto t1 = std::chrono::steady_clock::now();
            
        // Matrix Multiply
        output = matrix_mul(a, b, m, n, p);

        // Time 
        auto t2             = std::chrono::steady_clock::now();
        double elapsed_time = std::chrono::duration_cast<duration>(t2-t1).count();
        total_elapsed_time += elapsed_time;
    }

    long double avg_flops      = 2*m*n*p;
    long double avg_giga_flops = avg_flops/1e+9;

    double total_time_sec = total_elapsed_time/ 1e+9;
    double avg_time       = total_elapsed_time/repeat;
    double avg_time_sec   = avg_time / 1e+9;

    cout << "R= " << row_size << " N= " << row_size*row_size <<" " << "Repeat= " << repeat << " Flops_avg= " << avg_flops << " ";
    cout.setf(ios::fixed);
    cout << " Time_avg= " << setprecision(PRECISION) << avg_time_sec << "s Time_total= " << setprecision(PRECISION) << total_time_sec << "s";
    cout << " GFlops/s= " << avg_giga_flops / avg_time_sec << "\n";
}
