main: main.c
	gcc main.c -o main -lpthread

main2: main2.c
	gcc main2.c -o main2 -lpthread

main3: main3.c
	gcc main3.c -o main3 -lpthread

main4: main4.c
	gcc main4.c -o main4 -lpthread

client: client.c
	gcc client.c -o client -lpthread

attacker: attacker.c
	gcc attacker.c -o attacker -lpthread -lm

all: main.c main2.c main3.c main4.c client.c attacker.c
	gcc main.c -o main -lpthread
	gcc main2.c -o main2 -lpthread
	gcc main3.c -o main3 -lpthread
	gcc main4.c -o main4 -lpthread
	gcc client.c -o client -lpthread
	gcc attacker.c -o attacker -lpthread -lm

clean:
	rm main -f
	rm main2 -f
	rm main3 -f
	rm main4 -f
	rm client -f
	rm attacker -f
	rm server_output_time_aggregated -f