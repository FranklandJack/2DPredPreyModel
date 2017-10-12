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

	grid(4,5).setPredDensity(800000);

	

	std::cout<<grid.predDensity(false)<<std::endl;
	

	return 0;
}