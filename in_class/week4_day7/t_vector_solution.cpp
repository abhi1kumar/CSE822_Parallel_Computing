#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<thread>
using std::thread;
#include<cstdlib>

#include <mutex>

std::mutex printMutex;  // enable synchronized output with print()
long total = 0;

void t_function(int id)
{
    std::lock_guard<std::mutex> l(printMutex);  
    total += id * id;
}

int main (int argc, char *argv[])
{
    if (argc != 2)
        cout << "Need thread count argument" << endl;
    else
    {
        int t_cnt = atoi(argv[1]);
        vector<thread> thrds;

        for(int i=0; i<t_cnt; ++i)
        {
            thrds.emplace_back(t_function, i);
            cout << "starting: "<<i<<endl;
        }

        int id=0;
        // has to be a reference for a thread
        // If we do not join, it throws an error.
        for(auto &t : thrds)
        {
            if(t.joinable())
            {
                t.join();
                cout << "Joined: "<< id++ << endl;
            }
        }
        cout << "Total: "<<total << endl;
    } // of else
}
