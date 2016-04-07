#!/bin/bash

names=(
    # pi_serial
    # pi_omp
    pi_omp_proper
    # pi_omp_slide
)

for name in ${names[@]}; do
    g++ -fopenmp -o ${name}.x ${name}.cpp
    echo "${name}.x"
    ./${name}.x
done
