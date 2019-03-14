/**
*manipulator.cppfile
*/

# include "manipulator.h"

namespace MTNELL004{
	int convertToInt(string str){
		int i;
		istringstream is(str);
		is >> i;
		return i;
	}

	VolImage::VolImage(){
		width = 0; height = 0;
	}

	VolImage::~VolImage(){
		for(int i=0; i< slices.size(); i++){
			for(int j = 0; j<height; j++){
				delete [] slices[i][j];
			}
			delete [] slices [i];
		}
	}

	void VolImage::diffmap(int sliceI, int sliceJ, string output_prefix){
		cout << "Difference Map\n";

		//create output file name
		stringstream file;
		file << output_prefix <<".raw";
		string raw_file = file.str();

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
	    ofstream myfile;
	  	myfile.open (raw_file,  ios::out | ios::binary);
	  	myfile.write (img,length);
	  	myfile.close();

	    delete[] diffSlice;
	    delete[] img;
	}

	void VolImage::extract(int sliceId, string output_prefix){
		cout << "Extract\n";

		//create output file name and header file name
		stringstream file;
		stringstream hFile;
		file << output_prefix <<".raw";
		hFile << output_prefix <<".dat";
		string raw_file = file.str();
		string header_file = hFile.str();

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
	    ofstream myfile;
	  	myfile.open (raw_file,  ios::out | ios::binary);
	  	myfile.write (img,length);
	  	myfile.close();

	  	//create header file
	  	ofstream myHeaderFile;
	  	myHeaderFile.open (header_file);
	    myHeaderFile << width<<" "<<height<< " 1";
	    myHeaderFile.close();

	    delete[] img;

	}

	void VolImage::rowExtract(int sliceId, string output_prefix){
		cout << "Row Extract\n";

		//create output file name and header file name
		stringstream file;
		stringstream hFile;
		file << output_prefix <<".raw";
		hFile << output_prefix <<".dat";
		string raw_file = file.str();
		string header_file = hFile.str();

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
	    ofstream myfile;
	  	myfile.open (raw_file,  ios::out | ios::binary);
	  	myfile.write (img,length);
	  	myfile.close();

	  	//create header file
	  	ofstream myHeaderFile;
	  	myHeaderFile.open (header_file);
	    myHeaderFile << width<<" "<<num_images<< " 1";
	    myHeaderFile.close();

	    delete[] img;
	}

	// populate the object with images in stack and set member variables
	bool VolImage::readImages(string baseName){

		//get file name by appending ".dat" to the base
		stringstream file;
		file << baseName << ".data";
		string file_name = file.str();

		//open the file
		ifstream myfile;
		myfile.open(file_name);
		if(!myfile){
			cerr << "Header file not found\n";
			myfile.close();
			return false;
		}

		//read in dimensions and use them to set class variables
		int w, h, num_images;
		myfile >> w >> ws >> h >> ws >> num_images >> ws;
		width = w;
		height = h;

		//close header file
		myfile.close();

		//use base name to find images and num_images to iterate through all the images and build the image slices
		for(int i=0; i<num_images; i++){

			//get the .raw file name using the base name
			stringstream file;
			file << baseName <<i<< ".raw";
			string raw_file = file.str();
		
			ifstream myfile;
			myfile.open (raw_file,  ios::in | ios::binary);
			if(!myfile){
				cout << raw_file << " not found\n";
				return false;
			}

			// get length of file:
			int length = height*width;

			//create a memory block for it
		    char* img = new char[length];

		    //read in from binary file. "img" pointer points to where it is stored
		    myfile.read (img,length);

		    unsigned char *uimg = (unsigned char *)img;

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
		
		int bytesNeededForImage = num_images*width*height*sizeof(unsigned char);
		int bytesNeededForPointers = sizeof(slices)+ (sizeof(unsigned char*)*num_images*height);
		int totalBytesNeeded = bytesNeededForImage+bytesNeededForPointers;

		cout << "Number of images: "<<num_images<<"\n";
		cout << "Number of bytes required: "<<totalBytesNeeded<<"\n";

		return true;
	}

	int VolImage::volImageSize(void){
		return width;
	} 
}

