CFLAGS = -ggdb
DEFINES = -DDEBUGGA
INCLUDES = gnuplot-iostream.h
LIBS = -lstdc++ -lboost_iostreams -lboost_system -lboost_filesystem
MAIN = main.o
CC=g++

.cc.o:
	$(CC) -c $(CFLAGS) $(DEFINES) $(INCLUDES) $<

all::	main

gnuplot_i.o:	
main.o:	main.cpp

main: $(MAIN)
	$(CC) -o $@ $(CFLAGS) $(MAIN) $(LIBS)

clean: 
	rm -f $(MAIN) main
