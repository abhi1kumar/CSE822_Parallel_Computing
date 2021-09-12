# Homework 1: Branch Prediction

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
Pre-sorting shows performance improvements only for large arrays (>= 4096). In other words, array sizes matter when the code optimization is off. 
Array sizes do not matter when the optimization is on. 

3. **Is the “Primary Loop” faster if we pre-sort the array? If so, why, if not then speculate as to why not.**
Not always. When the code optimization is on, the branch statement is converted to non-branch statement which makes the array faster.
