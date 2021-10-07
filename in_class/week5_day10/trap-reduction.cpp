#include<iostream>
using std::cout; using std::endl;
#include "omp.h"

// Remember?
// dx = (b-a)/n
// area = dx/2 * ( f(a) + 2*f(x_1) + 2*f(x_2) + ... + 2*f(x_n-1) + f(x_n) )
// x_i = a + i*dx

double f(double x){
  return 1/((x-3)*(x-3) + 0.01) + 1/((x-2)*(x-2) + 0.05) + 2;
}

double sq(double x){
  return x*x;
}

double trap_interval_return(double a, double b, int n){
  int t_cnt = omp_get_num_threads();
  int my_rank = omp_get_thread_num();
  
  double dx = (b-a)/n;
  double x = 0.0;
  int slice = n/t_cnt;
  double left = a + my_rank * slice * dx;
  double right = left + slice * dx;

  double result = (f(left) + f(right)) / 2.0;
  for (int i=1; i<slice-1; ++i){
    x = left + i*dx;
    result += f(x);
  }
  result *= dx;
  // cout << my_rank <<":"<<left<<":"<<right<<" got "<< result << endl;
  return result;
}
  
int main (int argc, char* argv[]){
  if (argc != 5)
    cout << "need thread cnt, left, right and number of traps argument";
  else{
    double global_result=0.0;
    int t_cnt = atoi(argv[1]);
    double left = atoi(argv[2]);
    double right = atoi(argv[3]);
    int trap_cnt = atoi(argv[4]);

    double start = omp_get_wtime();
#pragma omp parallel num_threads(t_cnt) reduction(+: global_result)
    global_result += trap_interval_return(left, right, trap_cnt);
    double end = omp_get_wtime();
    
    cout << left << " to "<< right <<" area is: "<<global_result<< " elapsed: "<<end-start<<endl;
  }
}
    
      
  
  
