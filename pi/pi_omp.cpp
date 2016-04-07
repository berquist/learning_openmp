#include <cstdio>
#include <iostream>

#include <omp.h>

using namespace std;

int main()
{

  int num_steps = 16;

  double step;
  double pi;
  printf("pi (d): %d\n", pi);
  printf("pi (f): %f\n", pi);
  printf("pi (e): %e\n", pi);

  int nthreads = omp_get_max_threads();
  double sum[nthreads];

  for (int i = 0; i < nthreads; i++)
    sum[i] = 0.0;

  step = 1.0 / (double) num_steps;

  pi = 0.0;

#pragma omp parallel
  {
    int i;
    double x;
    int id = omp_get_thread_num();
    int start = id * (num_steps/nthreads);
    int end = (id + 1) * (num_steps/nthreads);
    for (i = start; i < end; i++) {
      x = (i + 0.5) * step;
      sum[id] += 4.0/(1.0 + x * x);
    }
    cout << sum[id] << endl;
  }

  for (int i = 0; i < nthreads; i++) {
    cout << i << endl;
    pi += step*sum[i];
  }

  printf("pi: %f\n", pi);

  return 0;

}
