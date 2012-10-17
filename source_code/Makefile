#makefile for nekoware based SDL Program

INCLUDE = 
LIBDIR  = 

COMPILERFLAGS =  `sdl-config --cflags --libs`

CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lSDL

all:  soccer

soccer : soccer.o
	$(CC) $(CFLAGS) -o soccer $(LIBDIR) soccer.o $(LIBRARIES)  
clean:
	rm soccer *.o


