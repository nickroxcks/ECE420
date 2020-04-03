
#! /bin/bash
# Test to run main programs.
# 5300
# 13000
# 18789
# Usage:
#	bash ./test.sh <process> <Main_number>
#

num_nodes=5300
rm data_input_link
rm data_input_meta
./datatrim -b $num_nodes

for i in {1..10};
do
    mpirun -np 1 ./main2 >> /home/user/ECE420/DATA/p1_$num_nodes.txt
done

for i in {1..10};
do
    mpirun -np 4 ./main2 >> /home/user/ECE420/DATA/p4_$num_nodes.txt
done

for i in {1..10};
do
    mpirun -np 8 ./main2 >> /home/user/ECE420/DATA/p8_$num_nodes.txt
done

for i in {1..10};
do
    mpirun -np 16 ./main2 >> /home/user/ECE420/DATA/p16_$num_nodes.txt
done

num_nodes=13000
rm data_input_link
rm data_input_meta
./datatrim -b $num_nodes

for i in {1..10};
do
    mpirun -np 1 ./main2 >> /home/user/ECE420/DATA/p1_$num_nodes.txt
done

for i in {1..10};
do
    mpirun -np 4 ./main2 >> /home/user/ECE420/DATA/p4_$num_nodes.txt
done

for i in {1..10};
do
    mpirun -np 8 ./main2 >> /home/user/ECE420/DATA/p8_$num_nodes.txt
done

for i in {1..10};
do
    mpirun -np 16 ./main2 >> /home/user/ECE420/DATA/p16_$num_nodes.txt
done

num_nodes=18789
rm data_input_link
rm data_input_meta
./datatrim -b $num_nodes

for i in {1..10};
do
    mpirun -np 1 ./main2 >> /home/user/ECE420/DATA/p1_$num_nodes.txt
done

for i in {1..10};
do
    mpirun -np 4 ./main2 >> /home/user/ECE420/DATA/p4_$num_nodes.txt
done

for i in {1..10};
do
    mpirun -np 8 ./main2 >> /home/user/ECE420/DATA/p8_$num_nodes.txt
done

for i in {1..10};
do
    mpirun -np 16 ./main2 >> /home/user/ECE420/DATA/p16_$num_nodes.txt
done