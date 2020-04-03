all: Main1.c Main2.c serialtester.c datatrim.c Lab4_IO.c
	gcc Main1.c Lab4_IO.c -o main1 -lm 
	mpicc -g Main2.c Lab4_IO.c -o main2 -lm
	gcc -g serialtester.c Lab4_IO.c -o serialtester -lm 
	gcc datatrim.c -o datatrim
datatrim:
	gcc datatrim.c -o datatrim
Main1:
	gcc Main1.c Lab4_IO.c -o main1 -lm
Main2:
	mpicc -g Main2.c Lab4_IO.c -o main2 -lm
serialtester: serialtester.c
	gcc -g serialtester.c Lab4_IO.c -o serialtester -lm
clean:
	rm datatrim data_input_link data_input_meta data_output main1 main2 serialtester
