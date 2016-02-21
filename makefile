CC=g++
LD=g++

CFLAGS=-std=c++0x -Wall
LFLAGS=-pthread
srcdir=source
VPATH=source

all: Input

Input: ImageProcessor.o Input.o Cursor.o
	g++ $(CFLAGS) $(LFLAGS)  Input.o ImageProcessor.o Cursor.o   -lopencv_features2d -lraspicam_cv -lopencv_core -lraspicam -o Input `pkg-config --cflags --libs opencv` 

ImageProcessor.o: $(srcdir)/ImageProcessor.cpp $(srcdir)/ImageProcessor.hpp
	g++ $(CFLAGS) -c $(srcdir)/ImageProcessor.cpp

Input.o: $(srcdir)/Input.cpp $(srcdir)/ImageProcessor.hpp
	g++ $(CFLAGS) -c $(srcdir)/Input.cpp

Cursor.o: $(srcdir)/Cursor.cpp $(srcdir)/Cursor.hpp
	g++ $(CFLAGS) -c $(srcdir)/Cursor.cpp

clean:
	rm *.o
