
# Makefile for Volumetric Image Manipulation Tool

CC = g++
CCFLAGS = -std=c++11

volimg: volimg.o manipulator.o manipulator.h
	$(CC) $(CCFLAGS) volimg.o manipulator.o -o volimg
	
volimg.o: volimg.cpp manipulator.h
	$(CC) $(CCFLAGS) volimg.cpp -c -o volimg.o

manipulator.o: manipulator.cpp manipulator.h
	$(CC) $(CCFLAGS) manipulator.cpp -c

run:
	./driver

clean:
	rm *.o
