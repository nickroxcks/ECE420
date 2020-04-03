#! /bin/bash
# Test to run main programs.
# 5300
# 13000
# 18789
# Usage:
#	bash ./test.sh <process> <Main_number>
#

rm data_input_link
rm data_input_meta
num_nodes=5300
./datatrim -b $num_nodes

for i in {1..10};
do
    ./main1 >> /home/user/ECE420/DATA/serial_$num_nodes.txt
done

rm data_input_link
rm data_input_meta
num_nodes=13000
./datatrim -b $num_nodes

for i in {1..10};
do
    ./main1 >> /home/user/ECE420/DATA/serial_$num_nodes.txt
done

rm data_input_link
rm data_input_meta
num_nodes=18789
./datatrim -b $num_nodes

for i in {1..10};
do
    ./main1 >> /home/user/ECE420/DATA/serial_$num_nodes.txt
done




