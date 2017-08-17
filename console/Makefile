all: ponto_que_move

console.o: console.c console.h
	gcc -Wall -c console.c

main.o: main.c
	gcc -Wall -c main.c

tela.o: tela.c tela.h
	gcc -Wall -c tela.c

ponto_que_move: console.o main.o tela.o
	gcc -Wall -o ponto_que_move console.o main.o tela.o

clean:
	rm -f *.o

cleanall:
	make clean
	rm -f ponto_que_move
