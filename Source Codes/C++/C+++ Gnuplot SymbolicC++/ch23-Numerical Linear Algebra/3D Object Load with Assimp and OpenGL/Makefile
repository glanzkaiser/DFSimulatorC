CFLAGS = -ggdb
DEFINES = -DDEBUGGA
INCLUDES = 
LIBS = /root/SourceCodes/CPP/src/glad.c -lstdc++  -lassimp -lglfw -lGL
MAIN = main.o
CC=g++

.cc.o:
	$(CC) -c $(CFLAGS) $(DEFINES) $(INCLUDES) $<

all::	main

gnuplot_i.o:	gnuplot_i.hpp
main.o:	main.cpp

main: $(MAIN)
	$(CC) -o $@ $(CFLAGS) $(MAIN) $(LIBS)

clean: 
	rm -f $(MAIN) main
