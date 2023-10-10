#!/bin/bash

virus=$1
pids=`cat ps.fake | grep -E 'migration' | awk '{print $2}'`
for pid in $pids; do
  kill $pid
done
