# Day 21 (Pre- class): Cuda

Abhinav Kumar, A61240809

### Questions

1. **Difference between C’s `malloc`, C++’s `new`, cuda’s `cudaMalloc` and `cudaMallocManaged`**

C’s `malloc`, C++’s `new` allocate memory on DRAM of CPU.

|`malloc()` | `new`
---------------------------
Constructor Call | No | Yes
Type | Function | Operator
Return | `void*` | Data type
Return on Failure | `NULL` | `bad_alloc` exception
Size calculation | Programmer | Compiler


cuda’s `cudaMalloc()` and `cudaMallocManaged()` allocate memory on  GDDRx memory/ Video RAM that is connected to, visible to and only addressable by the GPU.
cudaMalloc() is very similar to cudaMallocManaged() and takes the same arguments. 

|`cudaMalloc()` | `cudaMallocManaged()`
----------------------------------------
Access | GPU memory only | Both CPU + GPU (Cuda unified) memory
Preferrable | Yes | No

References:
- GeeksforGeeks - https://www.geeksforgeeks.org/malloc-vs-new/
- Quora - https://qr.ae/pGmSWy
- Timing Cuda - http://selkie.macalester.edu/csinparallel/modules/TimingCUDA/build/html/0-Introduction/Introduction.html

2. **Synchronize the GPU and CPU? Do you have to?**

Sometimes synchronization is required such as for debugging. At that time, it may be convenient to force the device to finish any outstanding activity. `cudaDeviceSynchronize()` is used while running on the CPU when we want CPU activity wait on the completion of any pending GPU activity. In many cases it's not necessary to do this explicitly, as GPU operations issued to a single stream are automatically serialized, and certain other operations like `cudaMemcpy()` have an inherent blocking device synchronization built into them.
