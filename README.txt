Name: Elle Mouton
Student Number: MTNELL004
CSC3022H (CSC3023F) Tutorial 2
________________________________________________________________________________________
CONTENT:
1. How to compile and run the program
2. Description of each of the files used in the program
________________________________________________________________________________________

1. Compiling and running:

To compile the files, navigate into the project folder and type 'make' in the terminal.
To run the program, use tho following command:

	./volimage <imageBase> [-d i j output_file_name][-x i output_file_name][-g i output_file_name]


2. Description of each file

___________
volimg.cpp
-----------

This is the driver file of the program and thus contains the "main()" function. In the main function, the command line arguments are read in.
A Volimg object is created form the main file and based on the options provided by the user, different functions are called on the object.

_______________
manipulator.cpp
---------------

This file contains all the method definitions associated with manipulating the Volimg object. This includes the constructor and destructor as well as the method for reading in image data and all the methods necessary to execute the various options that the user might choose. All the functions in this file are defined within the namespace: MTNELL004.

_____________
manipulator.h
-------------

This file contains all the function and class declarations that are used in the manipulator.cpp file. All the declarations are declared within the namespace: MTNELL004.


_________
Makefile:
----------

The Makefile contains various dependency rules required for compilation. It also a 'clean' rule.

