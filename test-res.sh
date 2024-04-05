#!/bin/sh
echo "Give path of c file"
read path
cd $path
gcc -pthread -o main p3190164-p3190114-res.c
./main 100 1000 
