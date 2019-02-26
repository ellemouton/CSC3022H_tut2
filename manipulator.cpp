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

MTNELL004::VolImage::VolImage(){
	std::cout<<"constructor called \n";
	width = 0; height = 0;
}

MTNELL004::VolImage::~VolImage(){

}

void MTNELL004::VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix){
	std::cout << "Difference Map\n";
}

void MTNELL004::VolImage::extract(int sliceId, std::string output_prefix){
	std::cout << "Extract\n";
}

void MTNELL004::VolImage::rowExtract(int sliceId){
	std::cout << "Row Extract\n";
}

bool MTNELL004::VolImage::readImages(std::string baseName){
	// populate the object with images in stack and set member variables

	//get file name by appending ".dat" to the base
	std::stringstream file;
	file << baseName << ".data";
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

	std::cout << "Number of images: \nNumber of bytes required:\n";

	return true;
}

int MTNELL004::VolImage::volImageSize(void){
	return 1;
} 
