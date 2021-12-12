# Homework 11: Matrix Vector Multiplication

Group 4: 
- Abhinav Kumar
- Avrajit Ghosh
- Siddhant Gautam
- Trevor Fush

### Matrix Vector Multiplication

Mutiply a matrix times a column vector (yielding a vector) and then add a vector to the result to generate a vector. 

Assume the matrix as square and having the sizes be “correct” for the operation (no need to check). I think it might be wise to use known values for A, B and C to make sure it works. After you are sure it is right, then you can play with larger sizes and increased performance.

#### Outline
Plots of how much we can speed it up vs. a regular CPU run (of the same size). Please try to vary the block sizes (and subsequent thread counts) and make a plot of how that affects speed.


### Requirements
1. nvcc 
2. g++
3. python 3.6

### Compilation and Running
Navigate to the current directory and then run
```bash
chmod +x main.sh
./main.sh | tee output/output.log

```

For plotting, use
```bash
python function/plot_graph.py
```


### Results 
Results are in [output.log](output/output.log)

### Discussions
1. **Vary the block sizes (and subsequent thread counts) and make a plot of how that affects speed.**

We keep the size of the vectors to be `512` while those of the matrix to be `512 x 512`.
We vary the blocks from `1 to 512` (and subsequently thread counts). 
We show the nvprof results of varying the block size in the figure below.

![Time_taken](output/time_vs_num_blocks.png?raw=true "Title")

We see that `MemCpy` takes the same time when we vary the block size. However, the computation time `matrixMulAdd` increases a lot beyond 64 blocks. 

2. **Speedup vs. a regular CPU run (of the same size)**

With block size of `<32`, the GPU provides a speedup of `6` compares to the regular CPU run.
