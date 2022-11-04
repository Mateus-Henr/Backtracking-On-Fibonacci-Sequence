all:
	gcc src/main.c -o main -lm
	./main

clean:
	rm all main