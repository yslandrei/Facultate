#!/bin/bash

files=`find ./dir`

for file in $files; do
  if test -L "$file"; then
    echo "Gasit SymboLink"
  else
    echo "Nu e"
  fi
done
