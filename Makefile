all:
	gcc -o main src/fibonacci.c src/file.c src/matrix.c src/main.c -lm
	./main

clean:
	rm all main