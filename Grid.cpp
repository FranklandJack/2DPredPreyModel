#include "Grid.hpp"
//TODO: implement
Grid::Grid(std::ifstream& inputFile)
{
	//first two numbers in file are number of coloumns and number of rows
	inputFile>>m_columns;
	inputFile>>m_rows;

	//dynamically allocate the array of size (m_columns+2)*(m_rows+2)
	//remembering to include the buffer of water at the edge

	int totalArraySizeIncBufffer = (m_columns+2)*(m_rows+2);
	int arraySize                = m_columns*m_rows;

	m_cellArray = new Cell[totalArraySizeIncBufffer];

	//initialise grid to be wet everywhere and contain no prey/predators 
	//with cell constructor with no arguments

	for(int cellIndex = 0; cellIndex < totalArraySizeIncBufffer; ++cellIndex)
		m_cellArray[cellIndex] = Cell();

	//rest of data is just the array of ones and zeros
	//whilst there is still data left to read keep reading

	//using operator() function since this takes care of all the indexing
	//remembering it indexes from 1
	for(int column = 1; column <= m_columns; ++column)
	{
		for(int row = 1; row <= m_rows; ++row)
		{
			//create local variable to hold whether this cell will be land or not
			bool land = 0;
			// take the input and put it into land
			inputFile >> land;
			//ignore any empty strings or newlines in the file
			if(land==' ' || land == '\n')
			{
				continue;
			}
			// make the particlular array entry wet/dry accordingly
			(*this)(column,row) = land;
		}
	}


	
}
//TODO: implement 
Grid::~Grid()
{
	delete [] m_cellArray;
}
/*
//TODO:implement
double Grid::predDensity();
//TODO: implement 
double Grid::preyDensity();
//TODO: implement 
int Grid::totalPred();
//TODO: implement 
int Grid::totalPrey();
*/
Cell& Grid::operator()(int i, int j)
{
	//check indicies are within bounds
	assert(i>=1 && i<=m_columns && j>=1 && j<=m_rows && "indicies out of bounds");
	//this formula accounts for the fact we are storing are 2-D array, in a 1-D array 
	//and takes account of the indexing for that configuration
	return m_cellArray[i + (m_rows + 1 - j) * (m_columns+2)];
}