/**
*manipulator.cppfile
*/

# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include "manipulator.h"

int MTNELL004::convertToInt(std::string str){
	int i;
	std::istringstream is(str);
	is >> i;
	return i;
}

void MTNELL004::differenceMap(int i,int j, std::string file_name){
	std::cout << "Difference Map\n";
}

void MTNELL004::extract(int i, std::string file_name){
	std::cout << "Extract\n";
}

void MTNELL004::noOptionBuild(void){
	std::cout << "No optional flags provided\n";

}

void MTNELL004::rowExtract(int i){
	std::cout << "Row Extract\n";
}

void MTNELL004::getHeaderFileInfo(std::string base){
	//get file name by appending ".dat" to the base
	std::stringstream file;
	file << base << ".data";
	std::string file_name = file.str();

	//open the file
	std::ifstream myfile;
	myfile.open(file_name);
	if(!myfile){
		std::cerr << "Header file not found\n";
	}
	else{
		int width, height, num_images;
		myfile >> width >> std::ws >> height >> std::ws >> num_images >> std::ws;

	}
	myfile.close();
}

void MTNELL004::loadImage(void){
	std::cout << "Number of images: \nNumber of bytes required:\n";
}