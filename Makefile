all:
	gcc main.c -o main

run: all
	clear
	./main

clean:
	rm -f main