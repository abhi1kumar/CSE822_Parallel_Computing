


```C++
vector<long> f()
{

    return (v); // copy while return so compiler can throw the function out of memory
}

vector <long> x = f()  // copy at equal
```

Although return value optimization (RVO) can fix thix, it is better to explicitly say to compiler to not make a copy and play with memory.

```
v.push_back(27);
v.emblace_back();
```

