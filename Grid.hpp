//cell included since the Grid will contain an array of cells
#include "Cell.hpp"
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
		Grid();
		// TODO: destructor will need to be implemented since memory will be dynamically allocated
		~Grid();

		//function to return predator density over whole grid
		double predDensity();

		//function to return prey denisty over whole grid
		double preyDensity();

		//function to return total number of predator in grid
		int totalPred();

		//function to return total number of prey in grid
		int totalPrey();

		//overload () operator to return cell at i,j th position in grid, 
		Cell operator()(int i, int j);
	
};