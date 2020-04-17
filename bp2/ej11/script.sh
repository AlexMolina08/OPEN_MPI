#!/bin/bash

export OMP_NUM_THREADS=1
for (( i = 100; i <= 40100; i += 1000 )); do
    ./pmv-OpenMP-a2 $i >> tiempos.dat
done

echo -e "\n" >> tiempos.dat
export OMP_NUM_THREADS=2
for (( i = 100; i <= 40100; i += 1000 )); do
    ./pmv-OpenMP-a2 $i >> tiempos.dat
done

echo -e "\n" >> tiempos.dat
export OMP_NUM_THREADS=3
for (( i = 100; i <= 40100; i += 1000 )); do
    ./pmv-OpenMP-a2 $i >> tiempos.dat
done

echo -e "\n" >> tiempos.dat
export OMP_NUM_THREADS=4
for (( i = 100; i <= 40100; i += 1000 )); do
    ./pmv-OpenMP-a2 $i >> tiempos.dat
done
