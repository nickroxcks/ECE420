All:
	gcc datatrim.c -o datatrim
	gcc Main1.c Lab4_IO.c -o main1 -lm
	mpicc -g -Wall Main2.c Lab4_IO.c -o main2 -lm
clean:

datatrim:
	gcc datagrim.c -o datatrim
Main1:
	gcc Main1.c Lab4_IO.c -o main1 -lm
Main2:
	mpicc -g -Wall Main2.c Lab4_IO.c -o main2 -lm
clean:
	rm datatrim
