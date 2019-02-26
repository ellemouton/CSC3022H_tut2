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

// populate the object with images in stack and set member variables
bool MTNELL004::VolImage::readImages(std::string baseName){

	//get file name by appending ".dat" to the base
	std::stringstream file;
	file << baseName << ".data";
	std::string file_name = file.str();

	//open the file
	std::ifstream myfile;
	myfile.open(file_name);
	if(!myfile){
		std::cerr << "Header file not found\n";
		myfile.close();
		return false;
	}

	//read in dimensions and use them to set class variables
	int w, h, num_images;
	myfile >> w >> std::ws >> h >> std::ws >> num_images >> std::ws;
	width = w;
	height = h;

	//close header file
	myfile.close();

	//use base name to find images and num_images to iterate through all the images and build the image slices
	for(int i=0; i<num_images; i++){

		//get the .raw file name using the base name
		std::stringstream file;
		file << baseName <<i<< ".raw";
		std::string raw_file = file.str();
	
		std::ifstream myfile;
		myfile.open (raw_file,  std::ios::in | std::ios::binary);
		if(!myfile){
			std::cout << raw_file << " not found\n";
			return false;
		}


		// get length of file:
	    myfile.seekg (0, myfile.end);
	    int length = myfile.tellg();
	    myfile.seekg (0, myfile.beg);

	    char* img = new char[length];

	    myfile.read (img,length);

	    

	    delete[] img;

		myfile.close();

	}

	

	return true;
}

int MTNELL004::VolImage::volImageSize(void){
	return width;
} 
