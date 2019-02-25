# include <iostream>
# include <string>

# include "manipulator.h"

int main(int argc, char * argv[]){
	//get info from command line arguments

	if(argc>1){
		std::string base = argv[1];

		//get header file info
		MTNELL004::getHeaderFileInfo(base);
		MTNELL004::loadImage();

		//determine which option the user is choosing
		int i;
		int j;
		std::string file_name;

		switch(argc){
			case 2:
				MTNELL004::noOptionBuild();
				break;

			case 6:
				i = MTNELL004::convertToInt(std::string(argv[3]));
				j = MTNELL004::convertToInt(std::string(argv[4]));
				file_name = std::string(argv[5]);
				MTNELL004::differenceMap(i,j,file_name);
				break;

			case 5:
				i = MTNELL004::convertToInt(std::string(argv[3]));
				file_name = std::string(argv[4]);
				MTNELL004::extract(i, file_name);
				break;

			case 4:
				i = MTNELL004::convertToInt(std::string(argv[3]));
				MTNELL004::rowExtract(i);
				break;

			default:
				std::cout << "invalid number of arguments\n";
		}
	}
	else{
		std::cout << "invalid number of arguments\n";
	}

	return 0;
}

