#!/usr/pkg/bin/bash

# Set to "YES" if you want it to stop execution after error.
STOP_AFTER_ERROR="NO"

function compile_and_execute() {
  echo -n "$1: "
  if clang $1 -O2 -o temp; then
    if ./temp; then
      echo "OK"
      rm ./temp 
      return 0
    else
      echo "FAIL"
    fi
  else
    echo "Compile failure"
  fi
  if [[ $STOP_AFTER_ERROR == "YES" ]]; then
    exit 1
  fi
  # Deleting file if $STOP_AFTER_ERROR != "YES"
  if [[ -e ./temp ]]; then
    rm ./temp  
  fi
}

while read tests; do
  for f in ./$tests/*.c; do
    if [[ -e $f ]]; then
      compile_and_execute $f
    fi
  done
done < tests.txt
