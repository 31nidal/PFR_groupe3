bin/prog.out: lib/main.o
	gcc lib/main.o -o bin/prog.out

lib/main.o: src/main.c
	gcc -c src/main.c -o lib/main.o -Wall

clean:
	rm -rf lib/*.o bin/prog.out
