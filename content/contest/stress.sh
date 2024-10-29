#!/bin/bash
[ "$#" -ne 3 ] && echo "Usage: $0 test_file brute_file mycode_file" && exit 1
g++ -O2 $1 -o test && g++ -O2 $2 -o brute && g++ -O2 $3 -o mycode
for i in {1..10000}; do
  ./test > tests.txt
  ./brute < tests.txt > correct.txt
  ./mycode < tests.txt > myans.txt
  diff -q correct.txt myans.txt >/dev/null || { echo -e "\e[31mTest $i: WA\e[0m"; cat tests.txt; break; }
  echo -e "\e[32mTest $i: AC\e[0m"
done
