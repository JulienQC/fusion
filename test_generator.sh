#!/bin/bash

echo -e "$1 \c" > $2

tmp=0
for i in `seq 1 $1`
do
    tmp=$((tmp + $((RANDOM % 10))))
    echo -e "$tmp \c" >> $2
done

tmp=$1
for i in `seq 1 $1`
do
    tmp=$((tmp + $((RANDOM % 10))))
    echo -e "$tmp \c" >> $2
done

echo -e "\n\c" >> $2
