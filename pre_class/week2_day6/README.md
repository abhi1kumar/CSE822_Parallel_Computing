# Day 6 (Pre- class): Threads

Abhinav Kumar, A61240809

### Questions


1. **What is the difference between a `.join` or `a .detach`on a thread?**

When we call `join()`, the calling thread will block until the thread of execution has completed. Basically, this is one mechanism that can be used to know when a thread has finished. When `join()` returns, the OS thread of execution has completed and the C++ thread object can be destroyed.

When we call `thread::detach()`, the thread of execution is "detached" from the thread object and is no longer represented by a thread object. Basically, it can continue running on its own.

Reference: [Stackoverflow](https://stackoverflow.com/a/37021767) 

2. **By default everything passed to a thread is a copy. How might we get around this?**

The solution to this involves passing by reference using `std::ref`

```C++

#include<iostream>
using std::cout; using std::endl;

#include<thread>
using std::thread;

#include<string>
using std::string; using std::to_string;

void thread_fun(long start, long stop, string &outs)
{
  int even=0, odd=0;
  for(int i=start; i<stop; i++)
    if (i%2 == 0)
      even++;
    else
      odd++;
  outs = "Even:" + to_string(even) + ", Odd:" + to_string(odd);
}

int main ()
{
  string s;
  thread t(thread_fun, 100, 1000, std::ref(s));
  t.join();
  cout << s << endl;
}
```


3. **you cannot copy a thread, only move it? Why do you suppose that is**

A thread of execution can only be associated with one `std::thread` object at a time, so `std::thread` is not copyable

Reference: [justsoftwaresolutions](https://www.justsoftwaresolutions.co.uk/threading/managing_threads_with_a_vector.html)

4. **what does it mean to “move” a thread?**

Thread is movable — means the ownership of a thread of execution can be transferred between objects, and we can return `std::thread` objects from functions.

Reference: [justsoftwaresolutions](https://www.justsoftwaresolutions.co.uk/threading/managing_threads_with_a_vector.html)
