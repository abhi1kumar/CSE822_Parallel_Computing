/*
 pop has lock_guard and locks it.
 pop calls empty which again checks for lock_guard, but lock_guard is locked. So, the program waits

 Possible Solutions:
 1. mutex --> recursive mutex
 2. two lockguards one for empty and one for all other functions
 3. Create private unsafe empty()  and call unsafe empty from pop so that lock_guard is used once.
*/
#include<mutex>
using std::mutex; using std::lock_guard; using std::recursive_mutex;
#include<vector>
using std::vector;
#include<thread>
using std::thread;

class Stack{
private:
  size_t sz;  
  vector<long> data;
  mutex_m;
  //recursive_mutex m;

public:
  Stack(size_t s=10) : sz(s), data(s) {};
  void pop();
  bool empty();
  void push(long);
  long top();
};

void Stack::pop(){
  lock_guard<mutex> lk(m);
  //lock_guard<recursive_mutex> lk(m);

  if (! empty() )
    data.pop_back();
}

bool Stack::empty(){
  lock_guard<mutex> lk(m);
  //lock_guard<recursive_mutex> lk(m);

  return data.empty();
}

void Stack::push(long i){
  lock_guard<mutex> lk(m);
  //lock_guard<recursive_mutex> lk(m);

  data.push_back(i);
}

long Stack::top(){
  lock_guard<mutex> lk(m);
  //lock_guard<recursive_mutex> lk(m);

  return data.back();
}

void push_and_pop(Stack &s, long id){
  for (int i=0; i<10; ++i){
    s.push(id);
    s.pop();
  }
}

int main (){
  Stack s;  
  thread t1 (push_and_pop, std::ref(s), 1 );
  //thread t2 (push_and_pop, std::ref(s), 2 );
  t1.join();
  //t2.join();
}
    
