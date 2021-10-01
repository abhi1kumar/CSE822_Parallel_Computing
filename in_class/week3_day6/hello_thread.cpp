#include<iostream>
using namespace std; //using std::cout; using std::endl;

#include<vector>
using std::vector;

#include<thread>
using std::thread;using namespace std::this_thread;

#include<string>
using std::string; using std::to_string;

void my_func()
{
    cout << "Hello from " << get_id() << endl;
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

        for (int i =0 ; i <t_cnt; ++i)
        {
            //thrds.push_back(my_func); // --> This does not work with threads
            thrds.emplace_back(my_func);
        }

        for (auto &t: thrds)
        {
            if (t.joinable())
                t.join();
        }
    }
    cout << "Goodbye from main" << endl;

}
