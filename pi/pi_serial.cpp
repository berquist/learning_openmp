#include <cstdio>

#include <omp.h>

int main()
{

  int num_steps = 100000;

  int i;
  double step;
  double x, pi, sum = 0.0;

  step = 1.0 / (double) num_steps;

  for (i = 0; i < num_steps; i++) {
    x = (i + 0.5) * step;
    sum += 4.0/(1.0 + x * x);
  }

  pi = step * sum;

  printf("pi: %f\n", pi);

  return 0;

}
