#!/bin/bash

while true; do
  read -p "Dati un string: " X
  if test "$X" == "stop"; then
    break
  fi
  echo "=== $X"
done
