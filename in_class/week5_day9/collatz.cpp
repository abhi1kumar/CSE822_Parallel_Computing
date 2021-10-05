#include<iostream>
using std::cout; using std::endl;
#include<future>
using std::future; using std::async;
#include<vector>
using std::vector;
#include<chrono>

long collatz(long num){
  long cnt=0;
  while (num != 1){
    if (num % 2)
      num = 3*num + 1;
    else
      num = num/2;
    ++cnt;
  }
  return cnt;
}


long collatz_len(long start, long stop){
  long max=0;
  long val=0;
  
  for(long i=start; i<stop; ++i){
    long cnt = collatz(i);
    // cout << i <<":"<<cnt<<endl;
    if (cnt > max){
      max = cnt;
      val = i;
    }
  }
  return val;
}

int main (){
  vector<future<long> > f;
  long start=1, len=10000000;
  auto t1 = std::chrono::steady_clock::now();
  for(int i=0; i<8; ++i){
    f.push_back(async(std::launch::async, collatz_len, start, start+len));
    start += len;
  }
  long max=0;
  long l = 0;
  long longest = 0;
  long res = 0;
  for(auto &fut : f){
    res = fut.get();
    if (l = collatz(res) > max){
      longest = res;
      max = l;
    }
  }
  auto t2 = std::chrono::steady_clock::now();  
  cout << "Longest: "<<longest<<" at "<<collatz(longest)<<endl;
  cout << "Took: "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << endl;
  
  //cout << "Longest:"<<longest<<" length:"<<collatz(longest) << endl;
}
