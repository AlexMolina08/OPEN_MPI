#!/bin/bash

for ((N=65536;N<67108865;N *= 2));do
    echo "---tam = $N---"
    ./sumavectores $N
done


