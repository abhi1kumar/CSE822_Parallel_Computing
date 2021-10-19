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

    int chunk = 2;
    int repeat = 10;

    double result, t1, t2;


    result = 0.0;
    t1 = omp_get_wtime();
# pragma omp parallel for schedule (static, chunk) num_threads(t_cnt) reduction(+: result)
    for(int i=0; i<iters; ++i)
	  result  += f(i);
    t2 = omp_get_wtime();
    cout << "Num_threads= " << t_cnt << " Iterations= " << iters << " Chunk= " << chunk << " Elapsed= " << t2-t1 << endl;


    result = 0.0;
    t1 = omp_get_wtime();
# pragma omp parallel for schedule (dynamic, chunk) num_threads(t_cnt) reduction(+: result)
    for(int i=0; i<iters; ++i)
	  result  += f(i);
    t2 = omp_get_wtime();
    cout << "Num_threads= " << t_cnt << " Iterations= " << iters << " Chunk= " << chunk << " Elapsed= " << t2-t1 << endl;

    result = 0.0;
    t1 = omp_get_wtime();
# pragma omp parallel for schedule (guided, chunk) num_threads(t_cnt) reduction(+: result)
    for(int i=0; i<iters; ++i)
	  result  += f(i);
    t2 = omp_get_wtime();
    cout << "Num_threads= " << t_cnt << " Iterations= " << iters << " Chunk= " << chunk << " Elapsed= " << t2-t1 << endl;


   }
}
