SFINAE = Substitution Failure Is Not An Error

```c
vector<type> //template
```

There could be pages and pages of error. Just search for that line number

### Arithmetic Complexity

Name | Code | \#Load | \# Write | \#Ops | \#BW | Notes
-----| -----| -------| -------- |----- | -----  | -----
Matrix Vector Product | `Y[j] = Y[j] + A[i][j]*B[i]` | 3 | 1 | 2 | 2/4 
Vector Norm  | `s = s + A[i]*A[i]` | 2* | 1 | 2 | | Scalar `s` is cached somewhere in register.Something between 1 and 2 reads
Inner Product |`s = s + A[i]*B[i]` | 3* | 1 | 2 | 2/4
Inner Product with Indirect Access | `s = s + A[i]*B[K[i]]` | 4* | 1 | 2 | 2/5

### Combo of Instruction and Data

 Combo | Example
-----|----
SISD | CPU
MIMD | Computing Cluster
SIMD | GPU
MISD | Tesla, two CPUs run and if one of them dies, other picks up from there
