All:
	gcc datagen.c Lab3IO.c -o datagen
	gcc Main.c Lab3IO.c -o  main -lm
	gcc Main2.c Lab3IO.c -o main2 -lm -fopenmp
	gcc Main3.c Lab3IO.c -o main3 -lm -fopenmp
	gcc Main4.c Lab3IO.c -o main4 -lm -fopenmp
	gcc Main5.c Lab3IO.c -o main5 -lm -fopenmp
Main:
	gcc Main.c Lab3IO.c -o  main -lm
Main2:
	gcc Main2.c Lab3IO.c -o main2 -lm -fopenmp
Main3:
	gcc Main3.c Lab3IO.c -o main3 -lm -fopenmp
Main4:
	gcc Main4.c Lab3IO.c -o main4 -lm -fopenmp
Main5:
	gcc Main5.c Lab3IO.c -o main5 -lm -fopenmp
datagen:
	gcc datagen.c Lab3IO.c -o datagen
clean:
	rm main main2 main3 main4 main5 datagen data_input data_output
