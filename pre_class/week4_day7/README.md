# Day 7 (Pre- class): Concurrency

Abhinav Kumar, A61240809

### Questions


1. **What is a way one can help avoid a race condition?**
To avoid race condition, we need Mutual Exclusion. If one process is using a shared variable or file, Mutual Exclusion makes sure that all other processes will be excluded from doing the same things. In other words, if we could ensure that no more than a single process is in the critical section of the code at the 
same time instant, we could avoid race conditions.

Avoiding race condition is not sufficient for having parallel processes cooperate correctly and efficiently using shared data.

Reference: [Race condition](http://www.idc-online.com/technical_references/pdfs/information_technology/Race_Condition_and_Avoiding_Race_Conditions.pdf)


2. **Give two things you can do to avoid deadlock**

- Avoid Hold and Wait: Processes must be prevented from holding one or more resources while simultaneously waiting for one or more others. There are several possibilities for this: 
    1. Require that all processes request all resources at one time. Wastes system resources if a process needs one resource early in its execution and doesn't need some other resource until much later.
    2. Require that processes holding resources must release them before requesting new resources, and then re-acquire the released resources along with the new ones in a single new request. This can be a problem if a process has partially completed an operation using a resource and then fails to get it re-allocated after releasing it.

- Pre-emption of resources: When a resource is requested and not available, then the system looks to see what other processes have those resources and are themselves blocked waiting. If such a process is found, then some of their resources may get preempted and added to the list of resources for which the process is waiting.

Reference: [Deadlocks](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/7_Deadlocks.html)
 
3. **How can you find a race condition (what are the symptoms)**

Race condition refers to the unpredictability in the order in which the threads execute. Therefore, the most common symptom of a race condition is the unpredictability of values of the shared variables. Sometimes execution works correctly, while at other times it works incorrectly. Moreover, if we execute each thread separately, the shared variable value is correct.

Reference: [Race condition deadlocks](https://docs.microsoft.com/en-us/troubleshoot/dotnet/visual-basic/race-conditions-deadlocks)
