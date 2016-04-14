#!/bin/bash

names=(
    pi_serial
    pi_omp_false
    pi_omp_critical
    pi_omp_reduction
)

for name in ${names[@]}; do
    g++ -fopenmp -o ${name}.x ${name}.cpp
    echo "${name}.x"
    OMP_NUM_THREADS=4 time ./${name}.x
done
