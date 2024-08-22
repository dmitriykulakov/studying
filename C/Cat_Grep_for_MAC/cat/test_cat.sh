#!/bin/bash

COUNT_SUCCESS=0
COUNT_FAIL=0
COUNT_ALL=0
DIFF_RES=""
TEST_FILE="test_file.txt"

processing()
{
  MAIN_TEST="$VAR $TEST_FILE"
  ./s21_cat $MAIN_TEST > s21_cat_test.txt
  cat $MAIN_TEST > cat_test.txt
  DIFF_RES="$(diff -s s21_cat_test.txt cat_test.txt)"
  (( COUNT_ALL++ ))
  if [ "$DIFF_RES" == "Files s21_cat_test.txt and cat_test.txt are identical" ]
  then
      (( COUNT_SUCCESS++ ))
      echo "$MAIN_TEST\033[32m SUCCESS\033[0m"
      else
          echo "$MAIN_TEST\033[31m FAIL\033[0m"
          (( COUNT_FAIL++ ))
  fi
  rm s21_cat_test.txt cat_test.txt
}

for var in -b -e -n -s -t -v
do
  VAR="$var"
  processing
done

for var in -b -e -n -s -t -v
do
  for var2 in -b -e -n -s -t -v
  do
    if [ $var != $var2 ]
      then
        VAR="$var $var2"
        processing
    fi
  done
done

for var in -b -e -n -s -t -v
do
  for var2 in -b -e -n -s -t -v
  do
    for var3 in -b -e -n -s -t -v
    do
      if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          VAR="$var $var2 $var3"
          processing
      fi
    done
  done
done

for var in -b -e -n -s -t -v
do
  for var2 in -b -e -n -s -t -v
  do
    for var3 in -b -e -n -s -t -v
    do
      for var4 in -b -e -n -s -t -v
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

echo "\033[31mFAIL: $COUNT_FAIL\033[0m"
echo "\033[32mSUCCESS: $COUNT_SUCCESS\033[0m"
echo "\033[34mALL: $COUNT_ALL\033[0m"