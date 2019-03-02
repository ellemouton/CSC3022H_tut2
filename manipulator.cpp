/**
*manipulator.cppfile
*/

# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include <cmath>
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

	//create output file name
	std::stringstream file;
	file << output_prefix <<".raw";
	std::string raw_file = file.str();

	//create and populate new difference image
	unsigned char** diffSlice = new unsigned char* [height];

    for(int r = 0; r<height; r++){
    	diffSlice[r] = new unsigned char[width];
    	for(int c = 0; c< width; c++){
    		diffSlice[r][c] = (unsigned char)(abs((float)slices[sliceI][r][c] - (float)slices[sliceJ][r][c])/2);
    	}
    }

    // get length of output file:
	int length = height*width;

    //create a memory block 
	char* img = new char[length];

	//read from 2D array into 1D array
	int index = 0;
    for(int r = 0; r<height; r++){
    	for(int c = 0; c< width; c++){
    		img[index] = diffSlice[r][c];
    		index++;
    	}
    }

    //create output file
    std::ofstream myfile;
  	myfile.open (raw_file,  std::ios::out | std::ios::binary);
  	myfile.write (img,length);
  	myfile.close();

    delete[] diffSlice;
    delete[] img;
}

void MTNELL004::VolImage::extract(int sliceId, std::string output_prefix){
	std::cout << "Extract\n";

	//create output file name and header file name
	std::stringstream file;
	std::stringstream hFile;
	file << output_prefix <<".raw";
	hFile << output_prefix <<".dat";
	std::string raw_file = file.str();
	std::string header_file = hFile.str();

    // get length of output file:
	int length = height*width;

    //create a memory block 
	char* img = new char[length];

	//read from 2D array into 1D array
	int index = 0;
    for(int r = 0; r<height; r++){
    	for(int c = 0; c< width; c++){
    		img[index] = slices[sliceId][r][c];
    		index++;
    	}
    }

    //create output file
    std::ofstream myfile;
  	myfile.open (raw_file,  std::ios::out | std::ios::binary);
  	myfile.write (img,length);
  	myfile.close();

  	//create header file
  	std::ofstream myHeaderFile;
  	myHeaderFile.open (header_file);
    myHeaderFile << width<<" "<<height<< " 1";
    myHeaderFile.close();

    delete[] img;

}

void MTNELL004::VolImage::rowExtract(int sliceId){
	std::cout << "Row Extract\n";

	//create output file name and header file name
	std::stringstream file;
	std::stringstream hFile;
	file << "output.raw";
	hFile << "output.dat";
	std::string raw_file = file.str();
	std::string header_file = hFile.str();

    // get length of output file:
    int num_images = slices.size();
	int length = num_images*width;

    //create a memory block 
	char* img = new char[length];

	//read from 2D array into 1D array
	int index = 0;
    for(int n = 0; n<num_images; n++){
    	for(int c = 0; c< width; c++){
    		img[index] = slices[n][sliceId][c];
    		index++;
    	}
    }

    //create output file
    std::ofstream myfile;
  	myfile.open (raw_file,  std::ios::out | std::ios::binary);
  	myfile.write (img,length);
  	myfile.close();

  	//create header file
  	std::ofstream myHeaderFile;
  	myHeaderFile.open (header_file);
    myHeaderFile << width<<" "<<num_images<< " 1";
    myHeaderFile.close();

    delete[] img;
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
	    myfile.read (img,length);

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

	std::cout << "Number of images: "<<num_images<<"\n";
	std::cout << "Number of bytes required: "<<"TO-DO"<<"\n";

	return true;
}

int MTNELL004::VolImage::volImageSize(void){
	return width;
} 
