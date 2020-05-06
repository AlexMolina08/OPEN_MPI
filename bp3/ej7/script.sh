#!/bin/bash
export OMP_SCHEDULE="static"
echo "static y chunk por defecto"
./pmtv-OpenMP 15360
export OMP_SCHEDULE="static,1"
echo "static y chunk 1"
./pmtv-OpenMP 15360

export OMP_SCHEDULE="static,64"
echo "static y chunk 64"
./pmtv-OpenMP 15360
export OMP_SCHEDULE="dynamic"
echo "dynamic y chunk por defecto"
./pmtv-OpenMP 15360
export OMP_SCHEDULE="dynamic,1"
echo "dynamic y chunk 1"
./pmtv-OpenMP 15360
export OMP_SCHEDULE="dynamic,64"
echo "dynamic y chunk 64"
./pmtv-OpenMP 15360
export OMP_SCHEDULE="guided"
echo "guided y chunk por defecto"
./pmtv-OpenMP 15360
export OMP_SCHEDULE="guided,1"
echo "guided y chunk 1"
./pmtv-OpenMP 15360
export OMP_SCHEDULE="guided,64"
echo "guided y chunk 64"
./pmtv-OpenMP 15360
