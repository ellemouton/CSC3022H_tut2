
# include "manipulator.h"

using namespace std;

int main(int argc, char * argv[]){
	//get info from command line arguments

	if(argc>1){
		string base = argv[1];

		//create new VolImage instance
		MTNELL004::VolImage images;

		//read in images and header file
		bool successRead = images.readImages(base);
		
		//if the read was successful, continue
		if(successRead && argc>2){
			//determine which option the user is choosing
			int i;
			int j;
			string file_name;
			
			string s = string(argv[2]);
			
			if(s=="-d"){
				//get slice numbers
				i = MTNELL004::convertToInt(string(argv[3]));
				j = MTNELL004::convertToInt(string(argv[4]));

				//get output file name if provided. else use default name.
				if(argc>4){
					file_name = string(argv[5]);
				}
				else{
					file_name = "output";
				}
				
				images.diffmap(i,j,file_name);
			}
			else if(s=="-x"){
				
				i = MTNELL004::convertToInt(string(argv[3]));
				
				//get output file name if provided. else use default name.
				if(argc>4){
					file_name = string(argv[4]);
				}
				else{
					file_name = "output";
				}

				images.extract(i, file_name);

			}
			else if(s=="-g"){
				i = MTNELL004::convertToInt(string(argv[3]));
				
				//get output file name if provided. else use default name.
				if(argc>4){
					file_name = string(argv[4]);
				}
				else{
					file_name = "output";
				}

				images.rowExtract(i, file_name);
			}
			
		}

	}
	else{
		cout << "invalid arguments\n";
	}

	return 0;
}

