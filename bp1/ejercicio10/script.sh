#!/bin/bash

for (( i = 16384; i <= 67108864 ; i*=2 )); do
    ./$1 $i
done
