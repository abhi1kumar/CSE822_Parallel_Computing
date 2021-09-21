#include<iostream>
using std::cout; using std::endl;
#include<thread>
using std::thread;

int main(){
  thread thrd(
     [](){cout << "Hello World" << endl;}
  );
  thrd.join();
}
