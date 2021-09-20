# Homework 2: Matrix Multiplication Prediction

With your group, write a program that multiplies two matrices together. See [Matrix Multiplication](http://mathworld.wolfram.com/MatrixMultiplication.html).

1. For a given matrix size ```N``, what is the total number of floating point operations performed by this operator?

2. Compute the performance in Mflop/s of the matrix-matrix multiply for N=100. Be sure to perform enough repeat calculations of the timing to overcome any statistical noise in the measurement.

3. For the system you are running on, determine the clock speed of the processor and the cache size/layout. On Linux the command ```lscpu``` can be helpful for this. Assuming that the processor is capable of one flop per clock cycle, how does the performance you measures in (3) compare to the theoretical peak performance of your system?

4. Now repeat the performance measurement for a range of matrix size ```N``` from 1 to 10,000,000. Make a plot of the resulting measured Gflop/s vs. ```N```. On this plot place a horizontal line representing the theoretical peak performance based upon your system’s clock speed.

5. How does the measured performance for multiple N’s compare to peak? Are there any “features” in your plot? Explain them in the context of the hardware architecture of your system. Include in your write-up a description of your system’s architecture (processor, cache, etc.).


### Requirements
1. g++

### Compilation and Running
Navigate to the current directory and then run
```bash
chmod +x main.sh
./main.sh | tee output.log
```

### Results 
Results are in [output.log](output.log)

### Discussions
1. **Total number of floating point operations performed by this operator**
It is `2N^3`

2. **Performance in Mflop/s of the matrix-matrix multiply for `N=100`**


3. **Is the “Primary Loop” faster if we pre-sort the array? If so, why, if not then speculate as to why not.**
Not always. 
When the code optimization is off, randomization makes the primary loop slow (sorting makes primary loop fast) because the branch prediction being useless. Reference: [answer](https://stackoverflow.com/a/11227902). 
When the code optimization is on, the branch statement is converted to non-branch statement which makes the array faster.
