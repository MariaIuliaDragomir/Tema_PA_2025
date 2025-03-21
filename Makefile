build: main


main: *.c
	gcc *.c -g -o main

clean:
	rm main