#include <cstdio>
#include <iostream>

#include <omp.h>

int main()
{

  int num_steps = 10000000;

  int i;
  double step;
  double pi = 0.0;
  double sum = 0.0;

  step = 1.0 / (double) num_steps;

#pragma omp parallel for reduction(+:sum)
  for (i = 0; i < num_steps; i++) {
    double x = (i + 0.5) * step;
    sum += 4.0/(1.0 + x * x);
  }

  pi = step * sum;

  printf("pi: %f\n", pi);

  return 0;

}
