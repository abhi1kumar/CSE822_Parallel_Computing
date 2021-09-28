#include<iostream>
using std::cout; using std::endl; using std::flush;
#include<thread>
using std::thread;
#include<random>
using std::mt19937_64; using std::uniform_int_distribution;
#include<chrono>


long global_var = 0;
bool stop = false;

void thread_fun(long inc, int seed, char c){
  mt19937_64 reng(seed);
  uniform_int_distribution<long> dist;
  decltype(dist.param()) small(100,500);
  decltype(dist.param()) large(600,1500);
  if (inc > 0)
    dist.param(small);
  else
    dist.param(large);

  while(!stop){
    cout << c;
    global_var += inc;
    cout << "Global is now:"<<global_var<<endl<<flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(dist(reng)));
  }
}

int main (){
  char c;
  long ms_since_epoch = std::chrono::system_clock::now().time_since_epoch() 
                        / std::chrono::milliseconds(1);
  thread t1(thread_fun, 3, ms_since_epoch, '*');
  ms_since_epoch = std::chrono::system_clock::now().time_since_epoch() 
                        / std::chrono::milliseconds(1);
  thread t2(thread_fun, -3, ms_since_epoch, '-');

  c=getchar();
  stop = true;
  t1.join();
  t2.join();
  cout << "Global result is:"<<global_var << endl;
}
