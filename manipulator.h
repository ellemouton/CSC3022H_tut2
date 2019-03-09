/**
*manipulator.h file
*/

#ifndef MANIPULATOR_H
#define MANIPULATOR_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

namespace MTNELL004{
	int convertToInt(string str);

	class VolImage{
		private: 
			int width, height; // width and height of image stack
			vector<unsigned char**> slices; // data for each slice, in order

		public: 
			VolImage(); // default constructor - define in .cpp
			~VolImage(); // destructor - define in .cpp file
			
			// populate the object with images in stack and set member variables define in .cpp
			bool readImages(string baseName);
			// compute difference map and write out; define in .cpp
			void diffmap(int sliceI, int sliceJ, string output_prefix);
			// extract slice sliceId and write to output - define in .cpp
			void extract(int sliceId, string output_prefix);
			// extract row rowID - define in .cpp
			void rowExtract(int sliceId, string output_prefix);
			// number of bytes uses to store image data bytes and pointers (ignore vector<> container, dims etc)
			int volImageSize(void); // define in .cpp
	};
}

#endif