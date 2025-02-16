all:
	gcc main.c -o neander

run: all
	clear
	./neander mult_positivo.mem

clean:
	rm -f neander
