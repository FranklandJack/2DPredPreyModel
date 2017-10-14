//main method of the 2D predator prey simulation

//implementing the grid
#include "Grid.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char const *argv[])
{
    using namespace std;
    
    //parameter imput
    double r, a, b, m, k, l, deltaT;
    unsigned int T;
    ifstream input_par("./input/input_parameters.txt", ios::in);
	if (input_par.is_open())
	 {
		input_par >> r >> a >> b >> m >> k >> l >> deltaT >> T;
		input_par.close();
	 }
	else
		cout<<"Input file could not open!"<<endl;
    // test just for now
    cout<<r<<endl<<a<<endl<<b<<endl<<m<<endl<<k<<endl<<l<<endl<<deltaT<<endl<<T<<endl;
    
    
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
