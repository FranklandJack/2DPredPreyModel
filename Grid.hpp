
//header guard
#ifndef Grid_hpp
#define Grid_hpp

//cell included since the Grid will contain an array of cells
#include "Cell.hpp"
//fstream included since the grid constructor will take a file stream
//from the input file to construct its cells
#include <fstream>
//cassert for assert in bounds checking on arrarys
#include <cassert>

class Grid
{
	private:
		//pointer to Cell, cells will be dynamically allocated since there may be a larger number of them
		// memorywise most efficient to allocate a 1-d array and index it using (i,j) operator
		// instead of an array of arrays due to padding
		Cell *m_cellArray;
		//m_columns holds number of columns in the grid
		int m_columns;
		//m_rows holds number of rows in the grid
		int m_rows;

	public:
		// TODO: constructor will take the input file 
		Grid(std::ifstream& inputFile);
		// TODO: destructor will need to be implemented since memory will be dynamically allocated
		~Grid();

		//function to return predator density over whole grid
		double predDensity() const;

		//function to return prey denisty over whole grid
		double preyDensity() const;

		//function to return total number of predator in grid
		int totalPred() const;

		//function to return total number of prey in grid
		int totalPrey() const ;

		//overload () operator to return cell at i,j th position in grid, 
		// i is the x coordinate and j is the y coordinate, indexed from 1
		//this is to match the figure given in section 2.1 in the pdf
		Cell& operator()(int i, int j);
	
};

#endif /* Grid_hpp */