#! /bin/bash
# Test to run main programs.
# 
# 
# Usage:
#	bash ./test.sh <numthreads> <Main_number>
#

if [ $# -lt 2 ]; then
	echo "./test.sh [thread_count] [Main_number]"
	exit -1
fi

thread_count=${1}
main_number=${2}
for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do  
    echo "doing iteration $i" 
    ./main$main_number $thread_count
done
