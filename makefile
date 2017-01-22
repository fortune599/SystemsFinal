all: file

file: server.o client.o networking.o final.o
	gcc -o final server.o client.o networking.o final.o

final.o: final.c
	gcc -c final.c

server.o: server.c networking.h
	gcc -c server.c

client.o: client.c networking.h
	gcc -c client.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
	rm *~
