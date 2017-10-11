//main method of the 2D predator prey simulation

//implementing the grid
#include "Grid.hpp"

//for file IO
#include <fstream>

//for general IO
#include <iostream>

int main(int argc, char const *argv[])
{
	//take the first command line argument as the input file
	std::ifstream inputFile(argv[1]);

	//check to make sure the file has been opened for input
	if(!inputFile)
	{
		std::cerr << inputFile << " could not be opened for reading" << std::endl;
		exit(1);
	}

	//construct grid from the data in the input file using our constructor designed for this purpose
	Grid grid(inputFile);

	//std::cout<<grid(2,2).getState()<<std::endl;

	/*for(int j = grid.getRows(); j >= 1 ; --j)
	{
		//work along the columns
		for(int i = 1; i <= grid.getColumns(); ++i)
		{
			std::cout << grid(i,j).getState() << ' ';
		}

		//printing a newline at the end of each column
		std::cout<<'\n';
	}
*/

	std::cout<<grid<<std::endl;
	

	return 0;
}