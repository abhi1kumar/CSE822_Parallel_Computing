#include<iostream>
using namespace std;
using std::cout; using std::endl;

#include<cstdlib>
#include<omp.h>

int main (int argc, char *argv[])
{
    if (argc != 2)
    cout << "Need a thread count arg" << endl;
    else 
    {
        int thrd_cnt = atoi(argv[1]);
        omp_set_num_threads(thrd_cnt);
        cout << "Max number of threads: "<< omp_get_max_threads() << endl;
        int tsum=0;
        #pragma omp parallel
        {
            if (omp_get_thread_num() == 0)
                cout << "I'm the prime node, I'm special "<< endl;
            else
                cout << "I'm worker " << omp_get_thread_num() << endl;
            tsum += omp_get_thread_num();
        }
        cout << "Sum is " << tsum << endl;
    }
    return 0;
}

