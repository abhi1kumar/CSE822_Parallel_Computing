# Homework 2: Matrix Multiplication

Group 4: 
- Abhinav Kumar
- Avrajit Ghosh
- Siddhant Gautam
- Trevor Fush

With your group, write a program that multiplies two matrices together. See [Matrix Multiplication](http://mathworld.wolfram.com/MatrixMultiplication.html).

1. For a given matrix size `N` (which is number of rows times number of columns), what is the total number of floating point operations performed by this operator?

2. Compute the performance in Mflop/s of the matrix-matrix multiply for `N=100`. Be sure to perform enough repeat calculations of the timing to overcome any statistical noise in the measurement.

3. For the system you are running on, determine the clock speed of the processor and the cache size/layout. On Linux the command ```lscpu``` can be helpful for this. Assuming that the processor is capable of one flop per clock cycle, how does the performance you measures in (3) compare to the theoretical peak performance of your system?

4. Now repeat the performance measurement for a range of matrix size ```N``` from 1 to 10,000,000. Make a plot of the resulting measured Gflop/s vs. ```N```. On this plot place a horizontal line representing the theoretical peak performance based upon your system’s clock speed.

5. How does the measured performance for multiple N’s compare to peak? Are there any “features” in your plot? Explain them in the context of the hardware architecture of your system. Include in your write-up a description of your system’s architecture (processor, cache, etc.).


### Requirements
1. g++
2. python3

### Compilation and Running
Navigate to the current directory and then run
```bash
chmod +x main.sh
./main.sh | tee output.log
```

### Results 
Results are in [output.log](output/output.log)

### Discussions
1. **Total number of floating point operations performed by this operator**
It is `2R^3` where `R= sqrt(N)` is the number of rows of the matrix.

2. **Performance in Mflop/s of the matrix-matrix multiply for `N=100`**
It is `623.053`. We repeated it `100` times to remove the statistical noise.

3. **Determine clock speed and the cache size/layout. How does performance compare with the theoretical peak performance.**

```bash
CPU Speed Max:       4000MHz
L1d cache:           32K
L1i cache:           32K
L2 cache:            256K
L3 cache:            8192K
```
Assuming one flop per sec, the peak CPU performance amounts to 4000 MFlops/s. Clearly, the speed achieves is less than the peak performance.

4. **Plot performance with varying `N`**
![GFlops vs N](output/gflops_vs_tot_elem.png?raw=true "Title")


5. **Measured performance for multiple `N`’s compare to the peak. Are there any “features” in your plot? Explain them in the context of the hardware architecture of your system. Include in your write-up a description of your system’s architecture (processor, cache, etc.).**

We see that GFlops performance is maximum at rows=`64` which corresponds to matrix size of `64x64`. The double data type corresponds to 8 bytes of storage and therefore, total size of the matrix `= 64 x 64 x 8` bytes `= 32` kB which is the L1d cache size. Beyond this matrix size, the performance goes down.
