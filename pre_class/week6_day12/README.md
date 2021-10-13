# Day 12 (Pre- class): Critical section vs Atomic vs Reduction for

Abhinav Kumar, A61240809

### Questions
**Exercise 23.1 asks about doing a critical section vs an atomic vs a reduction for the for loop. Which do you think would be more efficient and why? What would the drawbacks be?**

Here is a table comparing the three approaches

Method | Operations Supported | Locks Needed |Overhead
-------|------------------|-----------------|--------
Critical Section | Arbitrary Block | Yes | Big
Reduction for    | Arbitrary for   | Yes | Big
Atomic           | Limited         | No  | Small

I assume efficiency refers to smallest overhead. Therefore, atomic operations are the most efficient.

References
1. [omp-reduction](https://pages.tacc.utexas.edu/~eijkhout/pcse/html/omp-reduction.html)
2. [stack-overflow](https://stackoverflow.com/a/7798994)
