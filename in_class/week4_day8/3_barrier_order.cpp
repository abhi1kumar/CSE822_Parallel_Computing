#include<iostream>
using std::cout; using std::endl;
#include<thread>
using std::thread; using std::this_thread;
#include<mutex>
using std::mutex;
#include<barrier>
using std::barrier;
#include<chrono>
using namespace chrono_literals;
// ns, us, ms, s, min, h, d, y
// nano, micro, milli, sec, min, hour, day, year

mutex foo;
barrier bar(3);

void task_a () {
  bar.wait();
  foo.lock();
  cout << "task a\n";
  foo.unlock();
}

void task_b () {
  bar.wait();
  foo.lock();
  cout << "task b\n";
  foo.unlock();
}

void task_c () {
  bar.wait();
  foo.lock();
  cout << "task c\n";
  foo.unlock();
}

int main (){
  thread th1 (task_a);
  thread th2 (task_b);
  thread th3 (task_c);
  th1.join();
  th2.join();
  th3.join();
  this_thread::sleep_for(1s);
}
