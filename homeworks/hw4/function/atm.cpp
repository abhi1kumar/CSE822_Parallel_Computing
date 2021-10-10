// add whatever includes you need. You don't have to use all the ones
// listed here.

#include<iostream>
using std::cout; using std::endl; using std::cin;

#include<map>
using std::map;
#include<initializer_list>
using std::initializer_list;
#include<utility>
using std::pair;

#include<chrono>
using namespace std::chrono_literals;
#include<random>
using std::mt19937_64; using std::uniform_int_distribution; using std::random_device;

#include<thread>
using std::thread;
using namespace std::this_thread;
#include<mutex>
using std::mutex; using std::lock_guard;
#include<shared_mutex>
// using std::shared_mutex;

mt19937_64 prng{random_device()() };
uniform_int_distribution<int> dist(100,500);


//==============================================================================
// ATM class and its member functions
//==============================================================================
class ATM
{
    private:
        // add whatever you need

        map<long, double> accounts;
        mutex m;

    public:
        ATM()=default;

        // Helper functions
        ATM(initializer_list<pair<long, double>>);
        bool is_id_invalid(long);

        // Actual functions
        double query(long);
        bool deposit(long, double);
        double withdraw(long, double);
};

ATM::ATM(initializer_list<pair<long, double>> il)
{
    for(auto &p : il)
    {
        accounts[p.first] = p.second;
    }
}

bool ATM::is_id_invalid(long id)
{
    // Returns id is valid or not
    if (id < 0 or id > accounts.size())
        return true;
    else
        return false;
}


double ATM::query(long id)
{
    // do this
    if (is_id_invalid(id))
    {
        cout<<"\nError!! ID is unknown";
        return -1.0;
    }
    else 
    {
        lock_guard<mutex> lk(m);
        return accounts[id];
    }
}


bool ATM::deposit(long id, double cash)
{
    // do this
    if (is_id_invalid(id))
    {
        cout<<"\nError!! ID is unknown";
        return false;
    }
    else if (cash <= 0)
    {
        cout<<"\nCannot deposit negative cash";
        return false;
    }
    else
    {
        lock_guard<mutex> lk(m);
        accounts[id]+=cash;
        cout<<"\nCash Deposited to ID:"<<id<<"="<<cash;
        cout<<"\nUpdated amount["<< id << "]=" << accounts[id];
        return true;
    }
}

double ATM::withdraw(long id, double cash)
{
    // do this
    if (is_id_invalid(id))
      cout<<"\nError!!! Unknown id"; 
    else
    {
        lock_guard<mutex> lk(m);
        if (accounts[id] - cash < 0) 
        {
            cout<<"\nCannot withdraw more money by [" << id << "]";
            return 0;
        }
        else 
        {
            accounts[id]-=cash;
            cout<<"\nCash Withdrawn by ID="<<id<<"="<<cash;
            cout<<"\nUpdated amount["<< id << "]=" << accounts[id];
            return cash;
        }
    }
}

void work_stream1(ATM &a, bool reverse)
{
    // make a workstream, a stream of atm visits
    // maybe a loop. Could take more params if you like for your testing
    // needs.

    if (reverse)
    {
        //Withdraw before deposit
        for(int i=2;i>=0;--i)
            (&a)->deposit(i+1,50);

        // if you want to have each thread wait, here is a way to get some
        // ms from the prng
        std::chrono::milliseconds wait(dist(prng));
        
        for(int i=2;i>=0;--i)
            (&a)->withdraw(i+1,100 + i);

    }
    else
    {
        for(int i=0;i<3;i++)
            (&a)->deposit(i+1,50);

        // if you want to have each thread wait, here is a way to get some
        // ms from the prng
        std::chrono::milliseconds wait(dist(prng));

        for(int i=0;i<3;i++)
            (&a)->withdraw(i+1,100 + i);
    }
}


//==============================================================================
// Main starts here
//==============================================================================
int main (){
  char c;

  // setup the accounts: {id, money}
  ATM atm({ {1, 100}, {2, 100}, {3, 100} });

  // atm is a shared variable, each thread gets a reference
  thread t1(work_stream1, std::ref(atm), false);
  thread t2(work_stream1, std::ref(atm), true);

  t1.join();
  t2.join();

}
