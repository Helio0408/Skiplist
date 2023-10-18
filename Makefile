all: src/main.c slist.o
	gcc src/main.c slist.o -Wall -Wextra -std='c99' -o programa

slist.o: src/slist.c
	gcc -c src/slist.c -o slist.o

run:
	./programa

clean:
	rm -rf *.o
	clear
