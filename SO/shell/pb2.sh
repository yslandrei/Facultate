#!/bin/bash
files=`find ./dir -name *.c`
i=0
for file in $files; do
  if [ $i == 2 ]; then
    break
  fi

  lines=`cat $file | wc -l`
  if [ $lines -gt 500 ] 
  then
    echo $file
    i=$(($i+1))
  fi
done
