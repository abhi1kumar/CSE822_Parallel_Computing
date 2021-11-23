#include<iostream>
using std::cout; using std::endl;
#include<cmath>
#include <stdlib.h>
#include "omp.h"

#include <sstream>
using std::stringstream;

double humps (double x){
  return 1/((x-0.3)*(x-0.3) + 0.01) + 1/((x-0.9)*(x-0.9) + 0.04) - 6;
}

double sinc (double x){
  return sin(M_PI * x)/(M_PI * x);
}

void trap_interval(double a, double b, int n, double &global_result)
{
    int t_cnt = omp_get_num_threads();
    int thread_int_id = omp_get_thread_num();

    double dx = (b-a)/n;
    double x = 0.0;
    int slice = n/t_cnt;
    double left = a + thread_int_id * slice * dx;
    double right = left + slice * dx;

    // alias the function we want to test to f
    const auto& f = humps;

    // Trapezoidal Rule
    // dx = (b-a)/n
    // area = dx/2 * ( f(a) + 2*f(x_1) + 2*f(x_2) + ... + 2*f(x_n-1) + f(x_n) )
    //      = dx *   ( f(a)/2+  f(x_1) +   f(x_2) + ... +   f(x_n-1) + f(x_n)/2)
    // x_i = a + i*dx
    double result = (f(left) + f(right)) / 2.0;
    for (int i=1; i<slice-1; ++i)
    {
        x = left + i*dx;
        result += f(x);
    }
    result *= dx;
    // cout << thread_int_id <<":"<<left<<":"<<right<<" got "<< result << endl;

    # pragma omp critical
        global_result += result;
}

void simpson_interval(double a, double b, int n, double &global_result)
{
    // alias the function we want to test to f
    const auto& f = humps;

    int t_cnt         = omp_get_num_threads();
    int thread_int_id = omp_get_thread_num();

    double dx    = (b-a)/n;
    double x     = 0.0;
    int slice    = n/t_cnt;
    double left  = a + thread_int_id * slice * dx;
    double right = left + (slice-1) * dx;

    bool debug   = false;
    stringstream ss;

    // Composite Simpson Rule
    // dx = (b-a)/n
    // area = dx/3 * ( f(a) + 4*f(x_1) + 2*f(x_2) + ... + 4*f(x_n-1) + f(x_n) )
    // x_i = a + i*dx
    double result = f(left) + f(right);

    for (int i=1; i<slice-1; ++i)
    {
        x = left + i*dx;

        if (debug)
            ss << i << "\t" << x << endl;

        if (i%2 == 0)
            result += 2.0 * f(x);
        else
            result += 4.0 * f(x);
    }
    result *= dx/3.0;

    # pragma omp critical
        global_result += result;

    if (debug)
    {
        ss << 0 << "\t" << left << endl;
        ss << slice-1 << "\t" << right << endl;
        ss << "Sum= " << result << endl;
        cout << ss.str();
    }
}

void parallel_simpson_interval(double a, double b, int n, double &global_result)
{
    // alias the function we want to test to f
    const auto& f = humps;

    int t_cnt         = omp_get_num_threads();
    int thread_int_id = omp_get_thread_num();

    double dx    = (b-a)/n;
    double x     = 0.0;
    int slice    = n/t_cnt;
    double left  = a + thread_int_id * slice * dx;
    double right = left + (slice-1) * dx;

    // Composite Simpson Rule
    // dx = (b-a)/n
    // area = dx/3 * ( f(a) + 4*f(x_1) + 2*f(x_2) + ... + 4*f(x_n-1) + f(x_n) )
    // x_i = a + i*dx
    double result = f(left) + f(right);

    bool debug = false;
    stringstream ss2;
    if (debug)
        ss2 << 0 << "\t" << left << endl;

    #pragma omp parallel for
        for (int j=0; j<2; ++j)
        {
            double even_odd_result = 0.0;
            stringstream ss;

            if (debug)
                ss << endl << "thread " << thread_int_id << " " << j << endl;

            for (int i=1; i< ((slice-1)/2 +1); ++i)
            {
                // In sequential version, we have indices as 1, 2, 3, 4, 5, 6, 7, 8
                // Even operates on 2, 4, 6, 8
                // Odd operates on 1, 3, 5, 7
                // Odd indices lag index of 1 and so there is a minus
                int curr_index = (2*i-j);

                if (curr_index <= slice-2)
                {
                    x = left + curr_index*dx;
                    even_odd_result += f(x);

                    // If you put debug statement before, the error b/w sequential
                    // and parallel simpson increases
                    if (debug)
                        ss << curr_index << "\t" << x << endl;
                }
            }

            // Multiply even by 2 and odd by 4
            even_odd_result *= 2*(j+1);
            # pragma omp critical
                result += even_odd_result;
            cout << ss.str();
        }

    result *= dx/3.0;

    # pragma omp critical
        global_result += result;

    if (debug)
    {
        ss2 << slice-1 << "\t" << right << endl;
        ss2 << "Sum= " << result << endl;
        cout << ss2.str();
    }
}


int main (int argc, char* argv[])
{
    if (argc != 5)
        cout << "need thread cnt, left, right and number of traps argument";
    else
    {
        int t_cnt     = atoi(argv[1]);
        double left   = atof(argv[2]);
        double right  = atof(argv[3]);
        int num_point = atoi(argv[4]);

        int num_repeat = 10;

        double simpson_result;
        double parallel_simpson_result;

        double vanilla_simpson_time_sum = 0.0;
        double parallel_simpson_time_sum = 0.0;
        double vanilla_simpson_avg = 0.0;
        double parallel_simpson_avg = 0.0;
        

        for (int i= 0; i < num_repeat; ++i)
        {
            // =====================================================================
            // Use Vanilla Composite Simpson Rule and time it
            // =====================================================================
            simpson_result = 0.0;
            double start = omp_get_wtime();

            #pragma omp parallel num_threads(t_cnt)
                simpson_interval(left, right, num_point, simpson_result);

            double end = omp_get_wtime();
            double elapsed_time = end-start;
            vanilla_simpson_time_sum += elapsed_time;

            // =====================================================================
            // Use Parallel Composite Simpson Rule and time it
            // =====================================================================
            parallel_simpson_result = 0.0;
            start = omp_get_wtime();

            #pragma omp parallel num_threads(t_cnt)
                parallel_simpson_interval(left, right, num_point, parallel_simpson_result);

            end = omp_get_wtime();
            double parallel_elapsed_time = end-start;
            parallel_simpson_time_sum += parallel_elapsed_time;
        }

        // =====================================================================
        // Use trapezoidal rule to check the result
        // =====================================================================
        double trap_result= 0.0;

        #pragma omp parallel num_threads(t_cnt)
            trap_interval(left, right, num_point, trap_result);


        // =====================================================================
        // Average out time taken and report
        // =====================================================================
        vanilla_simpson_avg  = vanilla_simpson_time_sum / num_repeat;
        parallel_simpson_avg = parallel_simpson_time_sum / num_repeat;

        cout << "Num_thread= " << t_cnt << " Num_point= " << num_point << " Range= [" << left << "," << right << "] ";
        cout << "Vanilla_simpson_area= "<< simpson_result << " Parallel_simpson_area= "<< parallel_simpson_result << " Trapezoidal_rule_area= " << trap_result;
        //cout << " Diff_simp_parallel= " << abs(parallel_simpson_result - simpson_result) << " Diff_simp_trap= " << abs(simpson_result - trap_result);
        cout << " Vanilla_simpson_time= " << vanilla_simpson_avg << " Parallel_simpson_time= " << parallel_simpson_avg << endl;
    }
    return 0;
}
