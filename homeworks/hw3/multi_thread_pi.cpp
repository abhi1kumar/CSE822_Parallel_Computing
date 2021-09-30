/*
    Sample Run:
    ./multi_thread_pi.o N_total num_threads
    ./multi_thread_pi    1000     10
*/

#include <iostream>
#include <random>
#include <thread>

using namespace std;
using std::cout; using std::endl;
using std::atoi;

#include <ctime>
#include <chrono>
using duration = std::chrono::nanoseconds;

#include<vector>
vector <long int> Nin_per_thread;
vector <double>   time_per_thread;

int get_Nin_per_thread(long int Npoints, int seed, int thread_int_id)
{
    /*
    Function to randomly sample points from a square of side length 1,
    and count number on points that lie within the unit circle by each thread
    */

    std::mt19937_64 dre(seed);
    std::uniform_real_distribution<double> dist(0, 1);

    long int N_in = 0;
    double x;
    double y;
    
    // Time Declare
    auto t1 = std::chrono::steady_clock::now();

    for (long int i=0; i<Npoints; ++i) 
    {
        x = dist(dre);
        y = dist(dre);

        if (x * x + y * y <= 1.0)
            ++N_in;
    }

    // Time
    auto t2             = std::chrono::steady_clock::now();
    double elapsed_time = std::chrono::duration_cast<duration>(t2-t1).count();
    time_per_thread.insert(time_per_thread.begin() +  thread_int_id, elapsed_time);

    Nin_per_thread.insert(Nin_per_thread.begin()  + thread_int_id, N_in);
}

int main(int argc, char* argv[]) {

    cout.precision(15);
    long int N_total = 10000;
    int num_thread   = 1;
    int seed         = 0;

    // =========================================================================
    // Command Line Arguments
    // =========================================================================
    if (argc >= 3)
        num_thread = atoi(argv[2]);

    if (argc >= 2)
        N_total = atoi(argv[1]);

    // =========================================================================
    // Load assignment for each thread
    // =========================================================================
    long int avg_N_point_per_thread = int(N_total/num_thread);
    long int extra_N_point          = N_total % num_thread;
    long int N_point_curr;

    vector <thread> threads; 

    for (int id=0; id < num_thread; ++id)
    {
        Nin_per_thread .insert(Nin_per_thread.begin()  + id, 0);
        time_per_thread.insert(time_per_thread.begin() + id, 0.0);

        // If the N_total number is not perfectly divisible, add extra to the last one
        if (id == num_thread-1)
            N_point_curr = avg_N_point_per_thread + extra_N_point;
        else
            N_point_curr = avg_N_point_per_thread;

        // Start a thread
        cout << "Starting: "<< id << " with " << N_point_curr << " points" << endl;
        threads.emplace_back(get_Nin_per_thread, N_point_curr, seed, id);
    }

    // =========================================================================
    // Final Pi calculation
    // =========================================================================
    int id = 0;
    // has to be a reference for a thread
    for(auto &t : threads)
    {
        if(t.joinable() )
        {
        	t.join();
            cout << "Joined: "<< id << " Time: " << time_per_thread[id]/1e+6 << " ms" << endl;
            ++id;
        }
    }

    // =========================================================================
    // Final Pi calculation
    // =========================================================================
    long double pi;
    long int N_in_sum = 0;

    for (int id= 0; id < num_thread; ++id)
        N_in_sum  += Nin_per_thread[id];

    pi = 4.0 * (long double)N_in_sum/(long double)N_total;

    cout << "After " << N_total << " iterations, calculated value of pi = " << pi << endl;

    return 0;

}
