#!/bin/bash

echo "-- Ejecucion Secuencial --"
./pmm-secuencial 109
./pmm-secuencial 552
./pmm-secuencial 1104
./pmm-secuencial 1500

export OMP_NUM_THREADS=2
echo "\n-- Ejecucion paralela con 2 hebras: "

./pmm-OpenMP 109
./pmm-OpenMP 552
./pmm-OpenMP 1104
./pmm-OpenMP 1500

export OMP_NUM_THREADS=3
echo "\n-- Ejecucion paralela con 3 hebras: "

./pmm-OpenMP 109
./pmm-OpenMP 552
./pmm-OpenMP 1104
./pmm-OpenMP 1500

export OMP_NUM_THREADS=4
echo "\n-- Ejecucion paralela con 4 hebras: "

./pmm-OpenMP 109
./pmm-OpenMP 552
./pmm-OpenMP 1104
./pmm-OpenMP 1500




