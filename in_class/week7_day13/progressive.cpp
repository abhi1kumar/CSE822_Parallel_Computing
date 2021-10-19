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
  if (argc != 4)
    cout << "Need a thread count, iterations, chunk_size" << endl;
  else {
    int t_cnt = atoi(argv[1]);
    int iters = atoi(argv[2]);
    int chunk = atoi(argv[3]);

    int repeat = 10;

    double static_time_sum, static_time_avg;
    double dynamic_time_sum, dynamic_time_avg;
    double guided_time_sum, guided_time_avg;

    double result, t1, t2;

    //==========================================================================
    // Static
    //==========================================================================
    for (int i=0; i < repeat; ++i)
    {
        result = 0.0;
        t1 = omp_get_wtime();
        # pragma omp parallel for schedule (static, chunk) num_threads(t_cnt) reduction(+: result)
            for(int i=0; i<iters; ++i)
	          result  += f(i);
        
        t2 = omp_get_wtime();
        static_time_sum += (t2-t1);
        static_time_avg = static_time_sum/repeat;
    }
    cout << "Static  Num_threads= " << t_cnt << " Iterations= " << iters << " Chunk= " << chunk << " Repeat= " << repeat << " Elapsed= " << static_time_avg << endl;


    //==========================================================================
    // Dynamic
    //==========================================================================
    for (int i=0; i < repeat; ++i)
    {
        result = 0.0;
        t1 = omp_get_wtime();
        # pragma omp parallel for schedule (dynamic, chunk) num_threads(t_cnt) reduction(+: result)
            for(int i=0; i<iters; ++i)
	          result  += f(i);
        
        t2 = omp_get_wtime();
        dynamic_time_sum += (t2-t1);
        dynamic_time_avg = dynamic_time_sum/repeat;
    }
    cout << "Dynamic Num_threads= " << t_cnt << " Iterations= " << iters << " Chunk= " << chunk << " Repeat= " << repeat << " Elapsed= " << dynamic_time_avg << endl;


    //==========================================================================
    // Guided
    //==========================================================================
    for (int i=0; i < repeat; ++i)
    {
        result = 0.0;
        t1 = omp_get_wtime();
        # pragma omp parallel for schedule (guided, chunk) num_threads(t_cnt) reduction(+: result)
            for(int i=0; i<iters; ++i)
	          result  += f(i);
        
        t2 = omp_get_wtime();
        guided_time_sum += (t2-t1);
        guided_time_avg = guided_time_sum/repeat;
    }
    cout << "Guided  Num_threads= " << t_cnt << " Iterations= " << iters << " Chunk= " << chunk << " Repeat= " << repeat << " Elapsed= " << guided_time_avg << endl << endl;


   }
}
