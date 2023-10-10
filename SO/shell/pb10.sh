#!/bin/bash

#date=`date | awk '{print $2}'`
date="Mar"
lastPr=`cat last.fake | awk -v d=$date '$5 ~ d {print $1}' | sort | uniq -c | sort -n -r`
echo "$lastPr"
