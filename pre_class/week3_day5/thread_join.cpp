/*
  Reference:
  https://www.cplusplus.com/reference/thread/thread/join/
*/

#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
 
using namespace std;

void pause_thread(int n) 
{
  this_thread::sleep_for (std::chrono::seconds(n));
  cout << "pause of " << n << " seconds ended\n";
  
  // Terminate the thread and then call join
  // Reference: https://stackoverflow.com/a/12207835
  // terminate();
}
 
int main() 
{
  cout << "Spawning 2 threads...\n";
  thread t1 (pause_thread,1);
  thread t2 (pause_thread,2);
  cout << "Done spawning threads. Now waiting for them to join:\n";
  
  t1.join();
  t2.join();
  cout << "All threads joined!\n";

  // cout << "Calling join after threads joined...\n";
  // t2.join();

  return 0;
}
