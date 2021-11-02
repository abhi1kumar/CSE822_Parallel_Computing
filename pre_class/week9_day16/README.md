# Day 16 (Pre- class): Receive and Send

Abhinav Kumar, A61240809

### Questions
**[ElijPP] how can you get deadlock in point-to-point communication?**

When two process need to exchange data, and both of them execute the send call, then both of them will wait for other to issue the send call corresponding to their wait call. This is deadlock.

```c
other = 1-mytid; /* if I am 0, other is 1; and vice versa */
receive(source=other);
send(target=other);
```
**[ElijPP] what is the “eager” limit?**

Sometimes deadlock does not occur. This happens because MPI implementations sometimes send small messages regardless of whether the receive has been posted. This relies on the availability of some amount of available buffer space. The size under which this behavior is used is the eager limit. 

Reference:
https://pages.tacc.utexas.edu/~eijkhout/pcse/html/mpi-ptp.html
