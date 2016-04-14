#!/bin/bash

names=(
    pi_serial
    pi_omp_false
    pi_omp_critical
    pi_omp_reduction
)

fmt="real: %e user: %U cpu: %P"

for name in ${names[@]}; do
    g++ -fopenmp -o ${name}.x ${name}.cpp
    echo "${name}.x"
    for num_threads in 1 2 4; do
        OMP_NUM_THREADS=${num_threads} command time -f "$fmt" ./${name}.x
    done
done
