#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

using namespace std;


int main(int argc, char* argv[])
{
    int seed             = 0;
    int MAX_VAL_IN_ARRAY = 256;
    int REPEAT           = 1000;
    bool do_sort         = true;

    std::mt19937_64 dre(seed);
    uniform_int_distribution<int> dist(0, MAX_VAL_IN_ARRAY-1);

    // =========================================================================
    // Command Line Arguments
    // =========================================================================
    if (argc >= 3)
        REPEAT = atoi(argv[2]);

    if (argc >= 2)
    {        
        if (atoi(argv[1]) == 1)
            do_sort = true;
        else
            do_sort = false;
    }
    cout << "Sort= " << do_sort << "\t" << "Repeat= " << REPEAT << "\n";

    // =========================================================================
    // Generate data
    // =========================================================================
    const unsigned arraySize = 32768;
    int data[arraySize];

    for (unsigned c = 0; c < arraySize; ++c)
        //data[c] = rand() % MAX_VAL_IN_ARRAY;
        data[c] = dist(dre);

    if (do_sort)    
        // !!! With this, the next loop runs faster.
        sort(data, data + arraySize);

    // =========================================================================
    // Time now
    // =========================================================================
    clock_t start = clock();
    long long sum = 0;
    for (unsigned i = 0; i < REPEAT; ++i)
    {
        for (unsigned c = 0; c < arraySize; ++c)
        {   // Primary loop
            if (data[c] >= 128)
                sum += data[c];
        }
    }

    double elapsedTime = static_cast<double>(clock()-start) / CLOCKS_PER_SEC;

    cout << "Sum= " << sum << " Elapsed Time: Avg= " << elapsedTime/REPEAT << " Total= " << elapsedTime << "\n";
}
