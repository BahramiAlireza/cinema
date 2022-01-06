 
CC = g++
 
all: main.o events.o ticket.o

main.o: main.cpp events.h ticket.h
	$(CC) -c main.cpp
 
events.o: events.h ticket.h
	$(CC) -c events.h
 
ticket.o: ticket.h
	$(CC) -c ticket.h
