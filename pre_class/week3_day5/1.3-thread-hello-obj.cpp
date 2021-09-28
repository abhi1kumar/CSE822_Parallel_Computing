#include<iostream>
using std::cout; using std::endl;
#include<thread>
using std::thread;
#include<string>
using std::string;

class MyClass{
 private:
  string my_mesg_;
 public:
  MyClass(string s) : my_mesg_(s){};
  void operator()(){
    cout << my_mesg_ << endl;
  }
};

int main(){
  MyClass mc("Hello World");
  thread thrd(mc);
  thrd.join();
}
