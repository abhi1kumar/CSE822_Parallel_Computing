#include<iostream>
using namespace std; //using std::cout; using std::endl;

#include<vector>
using std::vector;

#include<thread>
using std::thread;using namespace std::this_thread;

#include<string>
using std::string; using std::to_string;

#include<cstdlib>

void t_function(int id, vector<int>& results)
{
  results[id] = id * id;
}

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Need two arguments";
    }
    else
    {
        int t_cnt = atoi(argv[1]);

        vector<thread> thrds;
        vector<int> results(t_cnt);

        for (int i= 0 ; i< t_cnt; ++i)
        {
            thrds.emplace_back(t_function, i, std::ref(results));
        }

        int id = 0;
        for (auto &t: thrds)
        {
            if (t.joinable())
            {
                t.join();
                cout << "Joined :" << id++ << endl;
            }
        }
        for(int i= 0; i< t_cnt; ++i)
            cout << "Results "<<i<<" are "<<endl;

    }
    cout << "Goodbye from main" << endl;

}


//As soon as the thread writes out to a location, it invalidates the cache sharing.
// Technically this is a false sharing.
//
// Better to pad the stuff
// 0           |8             |16           | 24
// ------------|--------------|-------------|---------------
//
// Another solution
// Have a global variable result instead of vector and make only one thread write to the 
// variable
