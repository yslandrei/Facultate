#!/bin/bash

names="`cat ./pb7.txt`"

n=`echo "$names" | wc -l`
echo $n

i=1
for name in $names; do
  if [ $i == $n ]; then
    echo ${name}@scs.ubbcluj.ro
  else
    echo -n "${name}@scs.ubbcluj.ro, "
  fi
    i=$(($i+1))
done
