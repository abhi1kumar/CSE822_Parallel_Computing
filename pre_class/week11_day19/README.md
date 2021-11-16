# Day 19 (Pre- class): Collectives

Abhinav Kumar, A61240809

### Questions
**The book discusses the “random number problem”, in particular finding the largest random number on an array of random numbers. Describe, in words, two algorithms using collectives you could use to solve this problem.”**

- MPI_Reduce: Reduce to a root.
 One process can generate or read in the initial data for a program run. This then needs to be communicated to all other processes.
At the end of a program run, often one process needs to output some summary information. 
  We could use MPI_MAX

- MPI_Scan: Using exclusive scan and propagate the max of the numbers and the final processor contains the max of all the numbers
