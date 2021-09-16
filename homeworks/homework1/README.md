# Homework 1: Branch Prediction
Take a look at what is purported to be the [most viewed stack overflow post](https://stackoverflow.com/questions/11227809/why-is-processing-a-sorted-array-faster-than-processing-an-unsorted-array). We are interested in the timing of the loop labeled “Primary Loop”. 

1. If we sort the array before running that loop, does that loop run faster.We are only interested in that loop. It is true that sorting the array will take more time, but we are ignoring that. We are only timing that loop
2. Write that code using the supplied random number and timing code. Do **not** use `rand` in your code. Use the `mt19937_64 prng` we discussed in class.
3. Time the “Primary Loop” under the following conditions:
With optimization (something like `-O2`) turned on and turned off (`-O0`).
With a larger or smaller array (try some different sizes, see if it matters).
4. Is it true? Is the “Primary Loop” faster if we pre-sort the array? If so, why, if not then speculate as to why not.

Turn in your code, and a brief write-up (in plain text or markdown) addressing the above questions and discussing your results. Your final write-up and code are due in one week, on 9/16.

### Requirements
1. g++

### Compilation and Running
Navigate to the current directory and then run
```bash
chmod +x main.sh
./main.sh | tee output.log
```

### Results 
Results are in [ouput.log](output.log)

### Discussions
1. **With optimization (something like `-O2`) turned on and turned off (`-O0`)**
Pre-sorting shows performance improvement for large arrays (>= 4096) when the code optimization is turned off. 
Pre-sorting does not show performance improvement for any of the array when the code optimization is turned on.

2. **With a larger or smaller array (try some different sizes, see if it matters)**
Pre-sorting shows performance improvements only for large arrays (>= 4096). In other words, array sizes matter when the code optimization is off. The overheads in smaller arrays possibly hide the improvements. Array sizes do not matter when the code optimization is on. 

3. **Is the “Primary Loop” faster if we pre-sort the array? If so, why, if not then speculate as to why not.**
Not always. 
When the code optimization is off, randomization makes the primary loop slow (sorting makes primary loop fast) because the branch prediction being useless. Reference: [answer](https://stackoverflow.com/a/11227902). 
When the code optimization is on, the branch statement is converted to non-branch statement which makes the array faster.
