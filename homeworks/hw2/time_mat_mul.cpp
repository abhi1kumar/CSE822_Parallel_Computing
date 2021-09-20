/*
    Sample Run:
    ./a.out array_size repeat
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

void matrix_mul(double** a, double** b, int m, int n, int p)
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
}

int main(int argc, char* argv[])
{
    int seed             = 0;
    int MAX_VAL_IN_ARRAY = 256;
    int PRECISION        = 8;

    int array_size       = 100;
    int repeat           = 100;

    std::mt19937_64 dre(seed);
    uniform_int_distribution<int> dist(0, MAX_VAL_IN_ARRAY-1);    
    using duration = std::chrono::milliseconds; 

    // =========================================================================
    // Command Line Arguments
    // =========================================================================
    if (argc >= 3)
        repeat = atoi(argv[2]);

    if (argc >= 2)
        array_size = atoi(argv[1]);

    // rows and cols both same as array size
    int m = array_size;
    int n = array_size;
    int p = array_size;

    // =========================================================================
    // Array Declaration
    // =========================================================================
    double** a      = get_2d_array(m, n);
    double** b      = get_2d_array(n, p);

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
        matrix_mul(a, b, m, n, p);

        // Time 
        auto t2             = std::chrono::steady_clock::now();
        double elapsed_time = std::chrono::duration_cast<duration>(t2-t1).count();
        total_elapsed_time += elapsed_time;
    }

    cout << "Array_size = " << array_size << " " << "Repeat= " << repeat << " ";
    cout.setf(ios::fixed);
    cout << "Flops= " << 2*m*n*p << " Time_avg= " << setprecision(PRECISION) << total_elapsed_time/repeat << "ms Time_total= " << setprecision(PRECISION) << total_elapsed_time << "ms\n";
}
