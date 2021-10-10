# Day 11 (Pre- class): Thread

Abhinav Kumar, A61240809

### Questions
**page 457 C++ example uses a `stringstream`. What is it and why use it?**

`stringstream` is a Stream class to operate on strings. Without `stringstream` the output lines from the various threads may get mixed up.

Reference: [cplusplus.com](https://www.cplusplus.com/reference/sstream/stringstream/)

**how can you get thread local storage (what do you need to do)?**

Thread local storage is needed for variables such as index of the loop for each thread. Otherwise, all of threads try to initialize and
increment the same shared variable. We use `private` clause for thread local variables.
