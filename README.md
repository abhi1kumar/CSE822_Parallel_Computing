# CSE822/CMSE822 Parallel Computing

Homeworks/Pre-class/In-class assignments of [CSE822 Parallel Computing](https://msu-cmse-courses.github.io/cmse822-FS21/) taken by [Prof William (Bill) Punch](https://www.egr.msu.edu/~punch/) at Michigan State University (MSU) in Fall 2021

### Schedule
1. Lectures - Tuesday/Thursday 10:20-11:40 AM in Room EB1230
2. Office Hours - Monday/Wednesday 3:00-5:00 PM on [Zoom 9299924290](https://msu.zoom.us/j/9299924290?pwd=WGY0WkRVTis2UUhjSE5GdlR1NTR4QT09)/395525

### Requirements
1. Ubuntu 18.04
2. C++
3. MSU HPCC Access

Other platforms have not been tested.

### Books

1. Intro to HPC - Victor Eijkhout, Edmond Chow, Robert van de Geijn [pdf](https://web.corral.tacc.utexas.edu/CompEdu/pdf/stc/EijkhoutIntroToHPC.pdf), [html](https://pages.tacc.utexas.edu/~eijkhout/istc/html/index.html)
2. Parallel  Programming for Science and Engineering - Victor Eijkhout [pdf](https://web.corral.tacc.utexas.edu/CompEdu/pdf/pcse/EijkhoutParallelProgramming.pdf), [html](https://pages.tacc.utexas.edu/~eijkhout/pcse/html/index.html)


### Lectures

Date  | Wk/Day | Pre-class Slides| Video  |Book | Submit | In-class Topics | Slides    | Homework 
----- |--   | ----------------|--------|-----|--------|-----------------| ----------| -----
02-09 | [0/1](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week0/Day0) |                 |        |     |        | Introduction, Logistics | [Intro](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week0/Day0-slides.pdf)
07-09 | [1/1](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week1/Day1) | [Pointers](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week1/ptrs.pdf)|| | [PointerCode](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week1/ptr.cpp)| HPCC Usage |
09-09 | [1/2](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week1/Day2) | | [CPU](https://www.youtube.com/watch?v=o_WXTRS2qTY) | 1.2 | Exer 1.1 | Branching | | [HW1](https://msu-cmse-courses.github.io/cmse822-FS21/assignments/hw1) Released
14-09 | [2/3](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week2/Day3) | [C-arrays](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week2/c-arrays.pdf), [2D-arrays](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week2/2Darray.pdf) | [Cache](https://www.youtube.com/watch?v=TV6AtNbmLBE), [VM](https://www.youtube.com/watch?v=muLn57VrGAA) | 1.3-1.4| Exer 1.12 | Cache | [Cache](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week2/Day3-cache.pdf)
16-09 | [2/4](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week2/Day4) |  | | 1.6, 1.7.1- 1.7.4, 2.1- 2.5 | Exer 1.18, 2.3, 2.10, 2.16 |Arithmetic Intensity, Amdahl Law, Scalability |[Roofline](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week2/Day4-theory.pdf) | [HW2](https://msu-cmse-courses.github.io/cmse822-FS21/assignments/hw2) Released
21-09 | [3/5](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week3/Day5) | [Command line args](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week3/commandLineArgs.pdf) | [Thread](https://www.youtube.com/watch?v=F6Ipn7gCOsY&t=415s) till 12:30 | | Effect of `.join`| Threads1 | [Threads1](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week3/threads1.pdf)
23-09 | [3/6](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week3/Day6) | | [Thread](https://www.youtube.com/watch?v=F6Ipn7gCOsY&t=415s) 12:30 to 28:30 || `.join`/`.detach`, copy/move | Threads2 | [Threads2](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week3/threads2.pdf) | [HW3](https://msu-cmse-courses.github.io/cmse822-FS21/assignments/hw3) Released
27-09 | [4/7](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week4/Day7) | | | |Avoid race, deadlock, detect race | Concurrency1 | [Concurrency1](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week4/Concurrency1.pdf) |
29-09 | [4/8](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week4/Day8) | | [Concurrency](https://www.youtube.com/watch?v=F6Ipn7gCOsY) from 28:30 | | | Concurrency2 | [Concurrency2](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week4/Concurrency2.pdf) | [HW4](https://msu-cmse-courses.github.io/cmse822-FS21/assignments/hw4) Released
05-10 | [5/9](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week5/Day9) | | | | `async` default, `future` advantages | OpenMP | [Tasks](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week5/task_parallelism.pdf) | |
07-10 | [5/10](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week5/Day10) | | [OpenMP Intro](https://www.youtube.com/watch?v=x0HkbIuJILk),[False sharing example](https://www.youtube.com/watch?v=OuzYICZUthM) | Chap 17 | PP Exer 17.3 | OpenMP | [OpenMP](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week5/OpenMP1.pdf) | [HW5](https://msu-cmse-courses.github.io/cmse822-FS21/assignments/hw5) Released | 
12-10 | [6/11](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week6/Day11) | | [For loops](https://www.youtube.com/watch?v=iPb6OLhDEmM) | Chap 18, 19,20 | `stringstream`, thread local | OpenMP | [OpenMP2](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week6/OpenMP2.pdf) |  | 
14-10 | [6/12](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week6/Day12) | | [OpenMP Sync](https://www.youtube.com/watch?v=WcPZLJKtywc&t=0s&index=9&list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG) | Chap 23 till 23.3.1 | Critical/Atomic/Reduction | OpenMP Sync | [OpenMP Sync](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week6/OpenMPsync.pdf) | [HW6](https://msu-cmse-courses.github.io/cmse822-FS21/assignments/hw6) [HW7](https://msu-cmse-courses.github.io/cmse822-FS21/assignments/hw7) Released |
19-10 | [7/13](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week7/Day13) | | [Worksharing](https://www.youtube.com/watch?v=4MiXzs0d1eE&ab_channel=ArgonneInternalChannel) 29:00-38:00 [Tasks](https://www.youtube.com/watch?v=AioeS_Jo0Yg&ab_channel=OpenMP) | PP 19.3 21.1 24 | PP Exer 19.3 | OpenMP Schedule Task | [OpenMP3](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week7/OpenMP3.pdf) |  | 
21-10 | [7/14](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week7/Day14) | | [Git](https://www.youtube.com/playlist?list=PLqPfbT7gwVP_AlE6HeDQUJsG4nUbGyeh3) |  | Add Func Template | Func Templates | [Func Templates](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week7/funs.pdf) |  |
19-11 | [11/20](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week11/Day20) | | | - | Cuda compile on HPCC | Cuda | [GPU](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week11/gpu-background.pdf) | 
23-11 | [12/21](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week12/Day21) | | [Vector_add](https://www.youtube.com/watch?v=1cHx1baKqq0)| - | Diff between C `malloc`, C++ `new`, cuda `cudaMalloc`, `cudaMallocManaged`; sync GPU + CPU| Cuda | [Cuda](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week12/cuda1.pdf) | 
25-11 | | | Thanksgiving break |
30-11 | [13/22](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week13/Day23) | | [Vector_add](https://www.youtube.com/watch?v=1cHx1baKqq0)| - | `nvprof` on `profile.cu`| More Cuda | [More Cuda](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week13/more_cuda.pdf) | [HW 11](https://msu-cmse-courses.github.io/cmse822-FS21/assignments/hw11) released
02-12 | [13/23](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week13/Day22) | | [Tiled Matrix_Mul](https://www.youtube.com/watch?v=3xfyiWhtvZw&ab_channel=CoffeeBeforeArch)| - | `nvvp ./a.out` | Cuda Matrix Mul | [Mat Mul](https://msu-cmse-courses.github.io/cmse822-FS21/Weekly/Week13/matmul.pdf) | 

### Debugging Segmentation Fault

1. [gdb](https://stackoverflow.com/a/3719031)

- Compile your application with `-g`, then you'll have debug symbols in the binary file.
```bash
g++ -g cpp_file.cpp -o binary.o
```
- Use `gdb` to open the `gdb` console.
- Type 
```bash 
file binary.o
```
- Type 
```bash
run argument1 argument2
``` 
- Do something to cause a Segmentation Fault.
- Type `bt` to get a stack trace of the Segmentation Fault.



### HPCC Stuff
1. [HPCC Access](https://wiki.hpcc.msu.edu/display/ITH/How+to+Access+HPCC)
2. [SLURM scheduling](https://wiki.hpcc.msu.edu/display/ITH/Job+Scheduling+by+SLURM) and [SLURM job management](https://wiki.hpcc.msu.edu/display/ITH/Job+Management+by+SLURM)
3. [Module basics](https://wiki.hpcc.msu.edu/display/ITH/Common+Module+Commands)
4. [HPCC Tutorial Series](https://wiki.hpcc.msu.edu/display/ITH/HPC+Tutorial+Series)
5. [HPCC Video Series](https://wiki.hpcc.msu.edu/display/TEAC/HPCC+video+tutorials)
