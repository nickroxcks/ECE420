#! /bin/bash
# Compiles programs, Genertate data input then runs main and compares output with serial tester
# 
# 
# Usage:
#	./generate_data.sh
#
node2IP=192.168.1.205
node3IP=192.168.1.51
node4IP=192.168.1.77
path=~/Lab4/Code
executables=("main1" "main2")
nodeIPs=("192.168.1.205" "192.168.1.51" "192.168.1.77")
meta=./data_input_meta
link=./data_input_link


clear
make clean
make

# Upload executables to hosts
for IP in ${nodeIPs[@]}; do
    for executable in ${executables[@]}; do
        scp -q $executable $IP:$path
    done 
done

# Lists
bounds=(5300 13000 18789)
hosts=("onehost" "twohost" "threehost" "fourhost")
processors=(1 2 4 6 8 16)
iterations=10

# # Get Serial Implementation Data
echo "Running main1"
# Run With Various Martix bounds
for bound in ${bounds[@]}; do
	echo "Testing bound =  $bound"
	./datatrim -b $bound
	# Upload data_input files to hosts


	# Run with Various Thread Counts
	for ((i=0; i < $iterations; i++)) do
		./main1
	done
done

mv data/*.csv data/serial

# Loop Through main
echo "Running main"
# Run With Various Martix bounds
for hostfile in ${hosts[@]}; do
	echo "Testing for $hostfile"
	for bound in ${bounds[@]}; do
		echo "Testing bound =  $bound"
		./datatrim -b $bound
			for IP in ${nodeIPs[@]}; do
				scp -q $link $IP:$path
				scp -q $meta $IP:$path
			done
		# Run with Various Thread Counts
		for process_count in ${processors[@]}; do
			echo "Testing processor =  $process_count"
			for ((i=0; i < $iterations; i++)) do
				mpirun -np $process_count -f $hostfile ./main2
			done
		done
	done
	mv data/*.csv data/$hostfile
done