#!/bin/bash

COUNT_SUCCESS=0
COUNT_FAIL=0
COUNT_ALL=0
DIFF_RES=""
TEST_FILE="linux 1.txt 2.txt"

processing()
{
  MAIN_TEST="$VAR $TEST_FILE"
  ./s21_grep $MAIN_TEST > s21_grep_test.txt
  grep $MAIN_TEST > grep_test.txt
  DIFF_RES="$(diff -s s21_grep_test.txt grep_test.txt)"
  (( COUNT_ALL++ ))
  if [ "$DIFF_RES" == "Files s21_grep_test.txt and grep_test.txt are identical" ]
  then
      (( COUNT_SUCCESS++ ))
      echo "$MAIN_TEST\033[32m SUCCESS\033[0m"
      else
          echo "$MAIN_TEST\033[31m FAIL\033[0m"
          (( COUNT_FAIL++ ))
  fi
  rm s21_grep_test.txt grep_test.txt
}

for var in -i -v -l -c -n -s -h -elin/?/x -ffile2.txt -o
do
  VAR="$var"
  processing
done

for var in -i -v -l -c -n -s -h -elinux -ffile2.txt -o
do
  for var2 in -i -v -l -c -n -s -h -elinux -ffile2.txt -o
  do
    if [ $var != $var2 ]
      then
        VAR="$var $var2"
        processing
    fi
  done
done

for var in -i -v -l -c -n -s -h -elinux -ffile2.txt -o
do
  for var2 in -i -v -l -c -n -s -h -elinux -ffile2.txt -o
  do
    for var3 in -i -v -l -c -n -s -h -elinux -ffile2.txt -o
    do
      if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          VAR="$var $var2 $var3"
          processing
      fi
    done
  done
done

for var in -i -v -l -c -n -s -h -elinux -ffile2.txt -o
do
  for var2 in -i -v -l -c -n -s -h -elinux -ffile2.txt -o
  do
    for var3 in -i -v -l -c -n -s -h -elinux -ffile2.txt -o
    do
      for var4 in -i -v -l -c -n -s -h -elinux -ffile2.txt -o
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
          then
            VAR="$var $var2 $var3 $var4"
            processing
        fi
      done
    done
  done
done

for var in -i -v -c -n -o
do
  for var2 in -i -v -c -n -o
  do
    if [ $var != $var2 ] 
      then
        VAR="$var $var2 -f file.txt -f file2.txt"
        processing
    fi
  done
done

for var in -i -v -c -n -o
do
  for var2 in -i -v -c -n -o
  do
    if [ $var != $var2 ] 
      then
        VAR="$var $var2 ^a"
        processing
    fi
  done
done

echo "\033[31mFAIL: $COUNT_FAIL\033[0m"
echo "\033[32mSUCCESS: $COUNT_SUCCESS\033[0m"
echo "\033[34mALL: $COUNT_ALL\033[0m"