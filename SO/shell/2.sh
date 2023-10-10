#!/bin/bash

for X in $*; do
  if file "$X" | grep -q "ASCII"; then
    echo "$X e fisier text"
  elif test -f "$X"; then
    echo "$X e fisier"
  elif test -d; then
    echo "$X e director"
  elif echo "$X" | grep -q -E "^[0-9]+"; then
    echo "$X e nr natural"
  else
    echo "$X e altceva"
  fi
done

