# Homework 6: 1D Heat Transfer

Group 4: 
- Abhinav Kumar
- Avrajit Ghosh
- Siddhant Gautam
- Trevor Fush

### 1D Heat Transfer

Imagine we have an `nxn` metal plate which is at an equilibrium temperature of 0 at all locations. We then instantaneously heat the 4 central cells of the grid to some temperature `T` and the heat source removed. We would like to know the temperature of the cells of the plate at some time point in the future from the initial heating.

![Heatplate](output/heatplate.jpg?raw=true "Title")

We can do this iteratively by stepping forward in time. At some time `t` we can calculate the temperature of a cell by averaging the temperature of the 4 cardinal direction cells. We wish to do the calculation in parallel using OpenMP.

#### Outline

- Takes in 5 command line arguments
    the dimension `n`, the size of the square plate
    the number of threads
    the inital temp of the 4 central cells (all cells are initialized to 0 except for those 4 cells)
    the number of timesteps to take.
    a tolerance
- the top and bottom rows, as well as the leftmost and rightmost columns, will be missing 1 neighbor. The 4 corners will be missing 2 neighbors. Assume all missing neighbors have a temp 0 for the duration of the simulation.
- timestep vs tolerance: The maximum number of timesteps to take is provided as an argument. However, if the tolerance criteria is reached before the timestep limit, the calculation ends. The tolerance criteria is achieved when the largest difference between two cells in the simulation (between time steps) is equal or less than the tolerance.


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
1. **For a single thread (and starting conditions) how long (in time) the simulation took and did it ever reach equilibrium first. If it reached equilibrium, what was the tolearance?**

We saw that even and odd terms get multiplied by different numbers and therefore, we were able to use parallelized for to split between even and odd terms.

2. **Repeat with different thread counts (up to twice the number of cores on your computer), reporting time taken (iterations should be the same?)**


