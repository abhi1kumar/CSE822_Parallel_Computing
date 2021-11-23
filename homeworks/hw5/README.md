# Homework 5: Composite Simpson Rule

Group 4: 
- Abhinav Kumar
- Avrajit Ghosh
- Siddhant Gautam
- Trevor Fush

### Integration

Our first OpenMP program! We looked at various implementations of the trapezoid rule. Let’s redo that with a slightly different example. Let’s use [Composite Simpson](https://en.wikipedia.org/wiki/Simpson%27s_rule#Composite_Simpson's_rule)’s to do integration. Let’s use the `humps` and `sinc` functions in the trapezoid code for testing.

Composite Simpsons gives you the opportunity to do more than one parallel region, take advantage of that. Also, no results vectors, use mutual exclusion, reduction or the like to do the total area update.


### Requirements
1. g++
2. python 3.6

### Compilation and Running
Navigate to the current directory and then run
```bash
chmod +x main.sh
./main.sh | tee output/output.log

# Generate graphs
python function/plot_graph.py
```


### Results 
Results are in [output.log](output/output.log)

### Discussions
1. **More than one parallel region**
We saw that even and odd terms get multiplied by different numbers and therefore, we were able to use parallelized for to split between even and odd terms.

2. **Graph of the area under the curve as the number of elements is increased**

![Area vs Num points](output/area_vs_num_points.png?raw=true "Title")

3. **Do two graphs here of time vs thread: .**

a. Strong scaling. Constant number of trapezoids but increasing threads (less trapezoids/thread)

Number of trapezoids was fixed to 16384

![Time vs Threads](output/strong_scaling_time_vs_num_threads.png?raw=true "Title")

b. Weak scaling. Increasing number of threads but the same number of trapezoids/thread (increasing trapezoids overall as thread number increases)

![Time vs Threads](output/weak_scaling_time_vs_num_threads.png?raw=true "Title")
