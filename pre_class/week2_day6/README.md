# Day 6 (In class): Threads

Abhinav Kumar, A61240809

### Requirements
1. g++

### Compilation and Running
Navigate to the current directory and then run
```bash
chmod +x main.sh
./main.sh | tee output.log
```

### Questions and SUggest


1. **What is the difference between a `.join` or `a .detach`on a thread?**
When we call `join()` is called, the calling thread will block until the thread of execution has completed. Basically, this is one mechanism that can be used to know when a thread has finished. When `join()` returns, the OS thread of execution has completed and the C++ thread object can be destroyed.

The `thread::detach()` is called, the thread of execution is "detached" from the thread object and is no longer represented by a thread object

Reference: [Stackoverflow](https://stackoverflow.com/a/37021767) 

2. **By default everything passed to a thread is a copy. How might we get around this?**
The solution to this involves passing by reference


3. **you cannot copy a thread, only move it? Why do you suppose that is**

4. **what does it mean to “move” a thread?**



