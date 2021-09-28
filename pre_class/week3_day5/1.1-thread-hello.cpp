#include<iostream>
using std::cout; using std::endl;
#include<thread>
using std::thread;

void a_fun(){
  cout << "Hello World"<<endl;
}

int main(){
  thread thrd(a_fun);
  thrd.join();
}
