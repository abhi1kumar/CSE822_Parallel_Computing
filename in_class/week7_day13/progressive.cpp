#include<iostream>
using std::cout; using std::endl;
#include<cmath>
#include<omp.h>

double f (int iters){
  double result = 0.0;

  for (int j = -iters; j<= iters; ++j)
    result += sqrt(atan(j));

  return result;
}

int main (int argc, char* argv[]){
  if (argc != 3)
    cout << "Need a thread count and iterations" << endl;
  else {
    int t_cnt = atoi(argv[1]);
    int iters = atoi(argv[2]);
    double result = 0.0;
    
    double t1 = omp_get_wtime();
# pragma omp parallel for num_threads(t_cnt) reduction(+: result)
    for(int i=0; i<iters; ++i)
	  result  += f(i);
    double t2 = omp_get_wtime();

    cout << "Elapsed: " << t2-t1 << endl;
   }
}
