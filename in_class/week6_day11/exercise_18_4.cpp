
#include<iostream>
using namespace std;
using std::cout; using std::endl;

#include<cmath>
#include<sstream>

#include "omp.h"

void f() 
{
    int t_cnt         = omp_get_num_threads();
    int thread_int_id = omp_get_thread_num();
    
    #pragma omp for
    for (int i=0; i< 2; ++i)
    {
        stringstream s;
        s << "Hello Thread= " << thread_int_id << " Index= " << i << endl;
        cout << s.str();
    }
}

int main (int argc, char* argv[])
{
    if (argc != 2)
        cout << "need thread cnt" << endl;
    else
    {
        int t_cnt = atoi(argv[1]);
        cout << "Thread cnt = " << t_cnt << endl;

        cout << "===============================" << endl;
        cout << "Func inside parallel region" << endl;
        cout << "===============================" << endl;
        
        #pragma omp parallel num_threads(t_cnt)
        {
            cout << "Before parallel\n";
            f();
        }

        cout << "===============================" << endl;
        cout << "Func outside parallel region" << endl;
        cout << "===============================" << endl;
        f();
    }
        return 0;
}
