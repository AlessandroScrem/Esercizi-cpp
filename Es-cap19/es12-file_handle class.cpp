/******************************************************************************

12. Define a File_handle class with a constructor that takes a string argument (the file name), 
	opens the file in the constructor, and closes it in the destructor.

******************************************************************************/



#include <iostream>
#include <string>
#include <stdlib.h>

#pragma warning(disable : 4996)


// error() simply disguises throws:
inline void error(const std::string& s)
{
	throw std::runtime_error(s);
}


class FileHandle {
	FILE* f;
public:
	FileHandle(const std::string&  name){
		if (!(f = fopen(name.c_str(), "w"))) {
			error("impossibile aprire il file");
			return;
		}
		std::cout << "opened : " << name << "\n";
	}

	~FileHandle() {
		fclose(f); 
		std::cout << "file closed : " << "\n";
	}
};
             	

int main()
{
	try
	{
		FileHandle File("prova.txt");	
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;           //write error message
	}


   char c;
   std::cin >> c;

}



