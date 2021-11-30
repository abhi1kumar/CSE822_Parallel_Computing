# Day 22 (Pre- class): Cuda nvprof

Abhinav Kumar, A61240809

### Compilation

```bash
nvcc profile.cu
nvprof ./a.out
```


### Ouptut

The log is in [output.log](output/output.log)

### Questions

1. **What does nvprof tell you about that simple code?**

It shows that `cudaMalloc` takes the maximum time out of all operations. The second highest time consuming operations is `cudaMemcpy`
