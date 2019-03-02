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
	for(int i=0; i<slices.size(); i++){
		delete[] slices[i];
	}
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
		int length = height*width;

		//create a memory block for it
	    char* img = new char[length];

	    //read in from binary file. "img" pointer points to wehere it is stored
	    myfile.read (img,1);

	    unsigned char *uimg = (unsigned char *)img;
	    
	    //int h = *( ( int * )(uimg));
	    //std::cout <<h <<"\n";

	    //create a new 2D array
	    unsigned char** newSlice = new unsigned char* [height];
	    int index = 0;

	    for(int r = 0; r<height; r++){
	    	newSlice[r] = new unsigned char[width];
	    	for(int c = 0; c< width; c++){
	    		newSlice[r][c] = uimg[index];
	    		index++;
	    	}
	    }

	    slices.push_back(newSlice);
	    delete[] img;

		myfile.close();

	}

	

	return true;
}

int MTNELL004::VolImage::volImageSize(void){
	return width;
} 
