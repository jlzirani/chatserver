CC=gcc
CFLAGS=-Wall -pedantic -g

all: bin/chatserver

clean:
	rm -fr bin/chatserver obj/*.o

bin/chatserver: obj/main.o obj/log.o obj/socket.o obj/chatroom.o
	$(CC) obj/*.o -o bin/chatserver $(CFLAGS)

obj/log.o: src/log.h src/log.c
	$(CC) -c src/log.c -o obj/log.o $(CFLAGS)

obj/main.o: src/main.c src/log.h
	$(CC) -c src/main.c -o obj/main.o $(CFLAGS)

obj/socket.o: src/socket.h src/socket.c src/log.h
	$(CC) -c src/socket.c -o obj/socket.o $(CFLAGS)

obj/chatroom.o: src/chatroom.h src/chatroom.c src/log.h src/socket.h
	$(CC) -c src/chatroom.c -o obj/chatroom.o $(CFLAGS)

