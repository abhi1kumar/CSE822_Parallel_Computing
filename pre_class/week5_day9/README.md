# Day 9 (Pre- class): Task Parallelism

Abhinav Kumar, A61240809

### Questions


1. **What’s the default launch flag for an `async` function template?**
The function template can behave either of the two flags /policies . In other words, it behaves the same as `async(std::launch::async | std::launch::deferred, f, args...)`. In other words, `f` may be executed in another thread or it may be run synchronously when the resulting `std::future` is queried for a value.

Reference: [Async reference](https://en.cppreference.com/w/cpp/thread/async)


2. **Give two advantages of the future data structure**

- A `future` data structure is the way to return an object from the `async` function call.
- The `.get()` method of a `future` data structure functions like a `join`.
- Also handles exceptions. If the underlying thread throws an error which is not handled by the thread, the caller gets to handle the exception at the point of the `.get()`.
 
3. **Can you find some discussion online concerning challenges associated with async?**

There are a couple of issues associated with `async` which are taken from [Stackoverflow](https://stackoverflow.com/a/12510731)

- `std::async` without a launch policy lets the runtime library choose whether to start a new thread or run the task in the thread that called `get()` or `wait()` on the future. 

- Using a policy of `std::launch::deferred` doesn't actually run the task until you explicitly call `get()` or `wait()`. This is almost never what you want, so don't do that.

- Using a policy of `std::launch::async` starts a new thread. If we don't keep track of how many threads we've got, this leads to too many threads running.

- The behaviour of the `std::future` destructor, which is supposed to wait for the task to complete, doesn't wait because of a MSVC2012 bug.


Online discussions:
- [Stackoverflow](https://stackoverflow.com/a/12510731)
- [Medium](https://clightning.medium.com/why-you-should-care-about-std-async-8f7714d112d0)
