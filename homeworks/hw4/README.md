# Homework 4: ATM Machine

Group 4: 
- Abhinav Kumar
- Avrajit Ghosh
- Siddhant Gautam
- Trevor Fush

### ATM

Let’s work a little with concurrency. Let’s make a simple ATM system. Only one class, the ATM

The `ATM` maintains a list of accounts by a customer id. Associated with each id is a monetary amount (only one account per id).

- `constructor()` is in the prototype. Adds a customer:cash pair to the ATM to start things off

The ATM provides the following methods for access:

- `query(id)`: returns the amount presently in the account of the `id` passed. If the `id` is unknown, returns 0 and prints an error message.
- `deposit(id, amount)`: deposit the indicated amount into the account at `id`. return is a Boolean indicating success (true) or failure (false) of deposit, print an error message on failure.
- `withdraw(id, amount)`: returns the amount withdrawn. If the `id` is unknown or the `amount` is unavailable, then return 0 and print a message.

#### Workstreams

You need to make a workstream, a sequence of events that occur at our ATM. For this we make a function(s) that perform ATM operations. We want to thread these workstreams, so each workstream gets a reference to our ATM instance and performs operations on the ATM. We should have multiple threads running workstreams (maybe the same stream, maybe not). I leave it to you to design some tests to see.

#### Overall.

Obviously access to the ATM via our methods are going to need to be handled so they can be concurrent. That is what you have to do, write those methods and provide a workstream(s) that tests that they are concurrent. 
- To start with, allow one method to run in your ATM. 
- Improve upon that by having multiple readers but only 1 writer (which method(s) is/are the writer). Something to think about at least.

#### Hints

- The workstream functions ran so fast that one thread will have done all the work before another starts. You might wait them, or make the workstream crazy long.
- The shared_mutex requires `-std=c++17`, perhaps other elements also require it.


### Requirements
1. g++

### Compilation and Running
Navigate to the current directory and then run
```bash
chmod +x main.sh
./main.sh | tee output/output.log
```


### Results 
Results are in [output.log](output/output.log)

### Discussions
1. **Which method(s) is/are the writer**

`query()` is the reader while `deposit()` and `withdraw()` are both writers.

2. **Why you think the workstreams you designed tested concurrency.**

We use mutex and shared_mutex to handle concurrency.

The first version of our [atm](function/atm.cpp) uses `lock_guard<mutex> lk(m);` for handling concurrency. However, a drawback of using lock-guard is it makes read and writes sequential.

The [second version](function/atm_shared.cpp) uses `shared_lock lock(mutex_);` feature of `shared_mutex` to allow for multiple reads at the same time. This version uses `unique_lock lock(mutex_);` to avoid concurrent writes. A drawback of this version is obvious. Whenever, one of the person withdraws from/ deposits from his account, everyone else waits.

A more better version should uses `deque` of mutex to only lock the array position belonging to the person. `vector` cannot be used here because `mutex` are not movable.
