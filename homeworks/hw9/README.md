# Homework 9: Three point average

Group 4: 
- Abhinav Kumar
- Avrajit Ghosh
- Siddhant Gautam
- Trevor Fush

### Latency hiding in three-point average

[threepoint](https://msu-cmse-courses.github.io/cmse822-FS21/assignments/threepoint.cpp) implements a blocking ghost zone exchange for a 1D vector assuming periodic boundary conditions. The operation performed in parallel on the vector is a simple three-point rolling averaging.

1. With your group, come up with a design plan for how to adapt this code to implement “latency hiding.” By this we mean to overlap communication and calculation by posting non-blocking communication calls, then instead of waiting for those calls to complete, going ahead and perform all calculations that do not depend on the data being communicated.

2. Now, go ahead with implementing a latency-hiding version of the three point averaging function. Check that your code works and gives the correct result on 1, 2, and 4 processors.

3. Compare the performance of the non-blocking version of the code to the blocking version of the code for up to 200 ranks keeping the array size per-rank fixed.


### Requirements
1. g++
2. python 3.6

### Compilation and Running
Navigate to the current directory and then run
```bash
chmod +x main.sh
./main.sh | tee output/output.log

```


### Results 
Results are in [output.log](output/output.log)

### Discussions
1. ** Design Plan**
We will carry out the average of the stuff we have after the send. Once the ghost entries have been filled, we then average out the stuff containing ghost entries. 

2. **Table that compares runs for 1, 2 and 4 processors for the original blocking and non-blocking code for various array sizes.**

All times are in 10^-6 seconds

Array Size per rank = 100

  n | Non-Blocking | Non Blocking
 --| -- | ---
 1 | 1.81 | 1.76
 2 | 178 | 105.64
 4 | 322.71 | 1771.60


Array Size per rank = 200

 n | Non-Blocking | Non Blocking
 --| -- | ---
 1 | 2.57 | 2.48
 2 | 115.1 | 1232
 4 | 236.2 | 1190




