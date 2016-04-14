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
  double sum[nthreads];

  for (int i = 0; i < nthreads; i++)
    sum[i] = 0.0;

  step = 1.0 / (double) num_steps;

  pi = 0.0;
