all:
	gcc -W -Wall -pedantic -std=c99 neander.c -o neander

run: all
	clear
	./neander a_vezes_-b.mem

clean:
	rm -f neander
