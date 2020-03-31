#!/bin/bash

for (( i = 65536; i <= 67108864 ; i*=2 )); do
    time ./$1 $i
done
