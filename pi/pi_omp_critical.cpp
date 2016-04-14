#include <cstdio>
#include <iostream>

#include <omp.h>

using namespace std;

int main()
{

  int num_steps = 10000000;

  double step;
  double pi;

  int nthreads = omp_get_max_threads();
  // double sum = 0.0;

  step = 1.0 / (double) num_steps;

  pi = 0.0;

#pragma omp parallel
  {
    int i;
    double x;
    double sum = 0.0;
    int id = omp_get_thread_num();
    int start = id * (num_steps/nthreads);
    int end = (id + 1) * (num_steps/nthreads);
    for (i = start; i < end; i++) {
      x = (i + 0.5) * step;
      sum += 4.0/(1.0 + x * x);
    }
#pragma omp critical
    pi += step*sum;
  }

  printf("pi: %f\n", pi);

  return 0;

}
