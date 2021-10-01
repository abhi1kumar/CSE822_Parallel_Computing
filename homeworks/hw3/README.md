# Homework 3: Monte Carlo Algorithm

Group 4: 
- Abhinav Kumar
- Avrajit Ghosh
- Siddhant Gautam
- Trevor Fush

We are going to thread a Monte Carlo algorithm to calculate `π`. A word about this. This is a terrible algorithm if your goal is to actually calculate `π`. It converges very slowly, requiring 100’s of millions of points to get even minimal accuracy. However, for testing parallel algorithms it is quite wonderful. It is numeric, it is tunable and it is “pleasantly parallel”, meaning that no shared memory is required to make the calculation. We’ll use it as our “Hello World” for writing a parallel programs.
1. First, write an outline, in words, of how to do it. Yes, actual words! Could be just a list. Be smart about how computationally expensive it is.
2. Next, write a serial version of the algorithm. When you write the algorithm, use command line arguments where the argument is the number of iterations of the algorithm. It will be useful if you make the calculation a function, as it will be easier to time and easier to thread.
3. Finally, write a threaded version of the algorithm. In this code, the command line arguments should represent the number of iterations (in total) and the number of threads used.
        The total iterations should be divided among the threads evenly (more or less).
4. For the system you are running on, list how many cores (and hyper-threads if that is available) you have on your system.
  - run the threaded algorithm with various core counts, starting with the single and running up to well beyond the number of cores/hyperthreads of the system.
  - make a graph of the per-thread time for the various thread counts.

Again, remember that to get anything resembling an accurate `π` you are going to have to run 100’s of millions (or more) total iterations.

### Requirements
1. g++
2. python3

### Compilation and Running
Navigate to the current directory and then run
```bash
chmod +x main.sh
./main.sh | tee output/output.log
```


### Results 
Results are in [output.log](output/output.log)

1. **Outline**

Serial Version
  - Sample a point `[0,1] x [0,1]` inside the first quadrant.
  - The ratio of points inside the circle/ total point equals the ratio of areas of quadrant / area of rectangele = `π/4` which means `π = 4 * N_in/ N_total`

Parallel Version

  - Divide the `N_tot` among the threads
  - Make two shared array which keeps the `N_in` and `N_tot` passed to each thread
  - Make each thread call the serial function and write to its id location in the shared array.
  - Call `join` 
  - Use `N_in` and `N_tot` to get the final version of `π`
       
4. **Cores in the System and Plot of per-thread time of various thread counts**

The cores in the system is 120 and we ran it for 2048 threads.

![Per-thread time vs Thread Count](output/per_thread_time_vs_thread_time.png?raw=true "Title")
