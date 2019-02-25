
# Makefile for Volumetric Image Manipulation Tool

CC = g++
CCFLAGS = -std=c++11

volimg: volimg.o manipulator.o
	$(CC) $(CCFLAGS) volimg.o manipulator.o -o volimg
	
volimg.o: volimg.cpp
	$(CC) $(CCFLAGS) volimg.cpp -c -o volimg.o

manipulator.o: manipulator.cpp
	$(CC) $(CCFLAGS) manipulator.cpp -c

run:
	./driver

clean:
	rm *.o