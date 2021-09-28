/* The following code example is taken from the book
 * "The C++ Standard Library - A Tutorial and Reference, 2nd Edition"
 * by Nicolai M. Josuttis, Addison-Wesley, 2012
 *
 *  Modified by w.f. punch
 */
#include<iostream>
using std::cout; using std::endl;
#include <mutex>
using std::mutex;
#include<thread>
using std::thread;
#include <string>
using std::string;

mutex printMutex;  // enable synchronized output with print()

void print (const string& s){
  printMutex.lock();
    for (char c : s) 
      cout.put(c);
  cout << endl;
  printMutex.unlock();
}

int main(){
  auto t1 = thread(print, "Howdy, this is the first thread");
  auto t2 = thread(print, "Greetings ala second thread");
  t1.join();
  t2.join();
  cout << "Goodbye from the main thread" << endl;
}
