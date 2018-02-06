# Makefile
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic -ansi $(DEBUG)
LFLAGS = -Wall $(DEBUG)

programs: wfseq lexdriver

# uses Lexer to check whether a sequence of tokens is well-formed
wfseq: Lexer.o wfseq.cpp
	$(CC) $(LFLAGS) Lexer.o wfseq.cpp -o wfseq

# only uses Lexer to test the Lexer class
lexdriver : Lexer.o lexdriver.cpp
	$(CC) $(CFLAGS) Lexer.o lexdriver.cpp -o lexdriver

# error handling routines make use of terminal control routines
error_handling.o : error_handling.h error_handling.cpp
	$(CC) -c $(CFLAGS) error_handling.cpp

# the Lexer is fairly independent
Lexer.o : Lexer.h Lexer.cpp
	$(CC) -c $(CFLAGS) Lexer.cpp


clean:
	rm -f *.o a.out wfseq lexdriver
