# Day 18 (Pre- class): Receive and Send

Abhinav Kumar, A61240809

### Questions
**what is a “halo” region or “ghost points”**

Ghost points (halo points) are usually part of the local data structure of an MPI process

If an MPI process only uses a subset of the entire data structure, data decomposition should be done
Otherwise, data duplication will be a killing factor. 

Reference - 
- https://www.uio.no/studier/emner/matnat/ifi/INF5620/h12/undervisningsmateriale/para-lecture.pdf

**Define latency hiding in the context of MPI**

Latency hiding means providing each processor with useful work to do as it awaits the completion of memory access requests.

In the context of MPI, latency hiding means  updating the non-boundary cells when the boundary/halo values are in transit. The latency of the communications is overlapped with useful work.

References - 
- https://www.geeksforgeeks.org/multithreading-and-latency-hiding/
- https://www.math.tu-cottbus.de/~kd/parallel/mpi/mpi-course.book_51.html
