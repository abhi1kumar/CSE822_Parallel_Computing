# Day 13 (Pre- class): Chunk Size of 1 is Bad

Abhinav Kumar, A61240809

### Questions
**[ElijPP] Exercise 19.6. Why is a chunk size of 1 typically a bad idea?**

Because of cache coherence problem called false sharing. Chunk size of 1 means the thread chunks operate on nearby locations. Therefore, there is a high probability of these locations being adjacent and therefore, being on same cachelines. As a result, the threads write to the nearby locations and therefore, invalidate the cacheline(s) frequently. Thus the code performance would be slower.
