#include <cstdio>
#include <iostream>

#include <omp.h>

int main() {
  int N = 100000;
  double pi = 0.0;
  long i;
  double t;
#pragma omp parallel for reduction(+:pi)
  for (i=0; i<N; i++)
  {
    t = (double)((i+0.05)/N);
    pi += 4.0/(1.0+t*t);
  }
  printf(“pi = %f\n”, pi/N);
  return 0;
}
