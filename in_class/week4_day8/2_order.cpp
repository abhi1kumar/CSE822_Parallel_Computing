/*
    Order of m1 and m2 matters
    Two ways-
    1. Programmer discipline --> Unlock in the same order in the order it is locked.
    2. Use scoped_mutex
*/

#include<iostream>
using std::cout; using std::endl;
#include<mutex>
using std::mutex;
#include<thread>
using std::thread;

int main() {
  mutex m1;
  mutex m2;
  thread t1([&m1, &m2] {
    cout << "1: Trying to get m1." << endl;
    m1.lock();
    cout << "1: Got m1." << endl;    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    cout << "1: Trying to get m2." << endl;
    m2.lock();
    cout << "1: Got m2." << endl;        
  });
  thread t2([&m1, &m2] {
    cout << "2: Trying to get m2." << endl;
    m2.lock();
    cout << "2: Got m2." << endl;            
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    cout << "2: Trying to get m1." << endl;
    m1.lock();
    cout << "2: Got m1." << endl;        
  });
  
  t1.join();
  t2.join();
}
