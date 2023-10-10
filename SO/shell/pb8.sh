#!/bin/bash

mounted=`df | awk '{if ($2 < 10000000){printf("%d\n", $6);}}'`
echo $mounted
