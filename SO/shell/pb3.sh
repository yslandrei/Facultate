#!/bin/bash

logs=`find ./dir -name *.log`

for log in $logs; do
  txt="`cat $log | sort`"
  echo "$txt" > $log
done
