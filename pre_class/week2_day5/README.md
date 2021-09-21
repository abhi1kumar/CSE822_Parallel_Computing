# Day 5 (In class): Matrix Multiplication


### Requirements
1. g++

### Compilation and Running
Navigate to the current directory and then run
```bash
chmod +x main.sh
./main.sh | tee output.log
```

### Discussions
1. **What happens if you try to `.join` a thread that has ended.**
When a thread has ended i.e. thread object goes out of scope and it is in joinable state, the program is terminated with the following message
```bash
terminate called without an active exception
```
Reference: [stackoverflow](https://stackoverflow.com/a/7989043)

2. **What happens if you try to `.join` a thread you have already joined**
```bash
terminate called after throwing an instance of 'std::system_error'
what():  Invalid argument
```

3. **What method can help you avoid this problem?**
We should use `joinable()` method

4. **What happens to any thread after the main program ends?**
If the `detach()` function is called inside the main, the thread keeps running. After calling detach *this no longer owns any thread. 

Reference: [cppreference.com](https://en.cppreference.com/w/cpp/thread/thread/detach)

5. **What values can you return from a thread call?**
We cannot return a value from a thread

Reference: [Threads: Slide 29](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week3/threads1.pdf)
