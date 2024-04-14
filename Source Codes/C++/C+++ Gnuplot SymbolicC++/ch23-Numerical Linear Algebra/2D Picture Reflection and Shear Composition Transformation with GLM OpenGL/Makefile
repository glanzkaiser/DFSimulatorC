CFLAGS = -ggdb
DEFINES = -DDEBUGGA
INCLUDES = 
LIBS = -lstdc++ -lSOIL -lGLEW -lsfml-graphics -lsfml-window -lsfml-system -lGL
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
