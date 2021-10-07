# Day 10 (Pre- class): Hello World OpenMP

Abhinav Kumar, A61240809

### Requirements
1. gcc

### Compilation and Running
Navigate to the current directory and then run
```bash
chmod +x main.sh
./main.sh
```

### Questions
**Run your program a number of times. Do you see something unexpected? Can you think of an explanation**

We see the race condition. Since the write is not access protected, many threads try to write at the same place resulting in a race.
