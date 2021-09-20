/*
    Sample Run:
    ./a.out sort array_size repeat
    ./a.out 0  32768 1000
*/

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <iomanip>
#include <chrono>

using namespace std;

int main(int argc, char* argv[])
{
    int seed             = 0;
    int MAX_VAL_IN_ARRAY = 256;
    int PRECISION        = 8;

    bool do_sort         = true;
    unsigned array_size  = 32768;
    int repeat           = 100000;

    std::mt19937_64 dre(seed);
    uniform_int_distribution<int> dist(0, MAX_VAL_IN_ARRAY-1);

    // =========================================================================
    // Command Line Arguments
    // =========================================================================
    if (argc >= 4)
        repeat = atoi(argv[3]);

    if (argc >= 3)
        array_size = atoi(argv[2]);

    if (argc >= 2)
    {        
        if (atoi(argv[1]) == 1)
            do_sort = true;
        else
            do_sort = false;
    }

    // =========================================================================
    // Generate data
    // =========================================================================

    //const unsigned array_size = 32768;
    //int data[array_size];

    // If we want a variable length or dynamically sized array in C++, we have to
    // dynamically allocate memory ourself:
    int *data = new int[array_size];

    for (unsigned c = 0; c < array_size; ++c)
        //data[c] = rand() % MAX_VAL_IN_ARRAY;
        data[c] = dist(dre);

    if (do_sort)    
        // !!! With this, the next loop runs faster.
        sort(data, data + array_size);

    // =========================================================================
    // Time now
    // =========================================================================
    // clock_t start = clock();
    using duration = chrono::milliseconds;
    auto t1        = chrono::steady_clock::now();

    long long sum = 0;
    for (unsigned i = 0; i < repeat; ++i)
    {
        for (unsigned c = 0; c < array_size; ++c)
        {   // Primary loop
            if (data[c] >= 128)
                sum += data[c];
        }
    }

    // double elapsedTime = static_cast<double>(clock()-start) / CLOCKS_PER_SEC;
    auto t2            = chrono::steady_clock::now();
    double elapsedTime = chrono::duration_cast<duration>(t2-t1).count();

    // Delete the dynamic array
    delete [] data;


    cout << "Sort= " << do_sort << " Array_size = " << array_size << " " << "Repeat= " << repeat << " ";
    cout.setf(ios::fixed);
    cout << "Sum= " << sum << " Time_avg= " << setprecision(PRECISION) << elapsedTime/repeat << " Time_total= " << setprecision(PRECISION) << elapsedTime << "\n";
}
