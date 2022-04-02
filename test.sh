#!/bin/bash

testing_with_valgrind=0

if [[ $# -ne 2 ]]
then
  echo "Wrong argument count. Expected three"
  exit
fi

program=`realpath "$1"`
directory=`realpath "$2"`

temporary_out=$(mktemp)
temporary_err=$(mktemp)

for test_file in "$directory/"*.in
do
  exitcode=0
  echo Testing file: "$(basename "$test_file")"

  if [ "$testing_with_valgrind" == 1 ]
  then
    valgrind --error-exitcode=3180 --log-file=valgrind.log --tool=memcheck
     --leak-check=full --show-leak-kinds=all --track-origins=yes -s
     $program < "$test_file" >"$temporary_out" 2>"$temporary_err"
    exitcode="$?"
  else
  ($program < "$test_file") > "$temporary_out" 2>"$temporary_err"
  fi

  test_file=$(echo "$test_file" | cut -f 1 -d '.')

  if  diff -q "$temporary_out" "$test_file.out"
  then
    echo "Out: Correct"
  else
    echo "Out: Incorrect XXXXXXX"
  fi

  if  diff -q "$temporary_err" "$test_file.err"
    then
      echo "Error: Correct"
    else
      echo "Error: Incorrect XXXXXXX"
  fi

  if [ "$testing_with_valgrind" == 1 ]
  then
    if [ "$exitcode" == 3180 ]
    then
      echo "Mem erorr"
    else
      echo "No mem errors"
    fi
  fi

done