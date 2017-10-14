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
    //remembering to start indexing from top since first entry will be at largest y-coordinate
    for(int j = m_rows; j >= 1; --j)
    {
        for(int i = 1; i <= m_columns; ++i)
        {
            //create local variable to hold whether state of this cell will be land or not
            bool state = 0;
            // take the input and put it into land
            inputFile >> state;
            
            // make the particlular array entry wet/dry accordingly
            (*this)(i,j).setState(state);
        }
    }


    
}

Grid::Grid(const Grid& sourceGrid): m_rows(sourceGrid.m_rows),
                                    m_columns(sourceGrid.m_columns)
{
    //because m_rows and m_columns are not dynamically allocated we can just shallow copy them
    
    //m_cellArray is a dynamically allocated pointer, we need to deep copy if it is non-null
    if(sourceGrid.m_cellArray)
    {
        //remembering we need to pad our grid with the boundary of water
        int totalArraySizeIncBufffer = (m_rows+2)*(m_columns+2);

        // allocate the memory for the new array
        m_cellArray = new Cell[totalArraySizeIncBufffer];

        // do the copy using our overloaded () operator and using the index system provided in the example grid

        for(int j = 1; j <= m_rows; ++j)
        {
            for (int i = 1; i <= m_columns; ++i)
            {
                (*this)(i,j) = sourceGrid(i,j);
            }
        }

    }
    // if we are copying from a grid with a null-pointer in its array member variable we just make our new array null too
    else
    {
        m_cellArray = nullptr;
    }

}

// move constructor
Grid::Grid(Grid&& sourceGrid): m_rows(sourceGrid.m_rows), 
                               m_columns(sourceGrid.m_columns),
                               m_cellArray(sourceGrid.m_cellArray)
{
    // transfer ownership of sourceGrid.m_cellArray to the new grid
    // remove ownership of memory from the sourceGrid 

    sourceGrid.m_rows    = 0;
    sourceGrid.m_columns = 0;

    sourceGrid.m_cellArray = nullptr;


}

Grid& Grid::operator=(const Grid& sourceGrid)
{
    // check against self assignment
    if(this == &sourceGrid)
    {
        return *this;
    }

    // if we assign a grid we need to dellocate the memory in its pointer otherwise we will get a memory leak when we assign a new location to the pointer 
    // however if we hadn't first check for self assignment ew could have deleted the memory, then set the pointer to point at the dealoccated memory which would
    // cause a crash if we derefenced it since it is no longer owned by the program

    delete [] m_cellArray;

    // because m_rows and m_columns are not dynamically allocated we can just copy them as normal
    m_rows    = sourceGrid.m_rows;
    m_columns = sourceGrid.m_columns;

    // m_cellArray is a dynamically allocated pointer, so we need to do a deep copy if it is non-null
    if(sourceGrid.m_cellArray)
    {
        //remembering we need to pad our grid with the boundary of water
        int totalArraySizeIncBufffer = (m_rows+2)*(m_columns+2);

        // do the copy using our overloaded () operator and using the index system provided in the example grid

        for(int i = 1; i <= m_columns;++i)
        {
            for (int j = 1; j <= m_rows; ++j)
            {
                (*this)(i,j) = sourceGrid(i,j);
            }
        }

    }
    // if we are copying from a grid with a null-pointer in its array member variable we just make our new array null too
    else
    {
        m_cellArray = nullptr;
    }
    // return *this so we can chain the assingment operator
    return *this;

}


 // move assignment operator

Grid& Grid::operator=(Grid&& sourceGrid)
{
    //check for self assignment
    if(&sourceGrid == this)
    {
        return *this;
    }

    // release memory currently in the grid
    delete [] m_cellArray;

    // copy over the numbers of rows and columns 
    m_rows    = sourceGrid.m_rows;
    m_columns = sourceGrid.m_columns;

    // transfer ownership of the m_cellArray
    m_cellArray = sourceGrid.m_cellArray;

    // remove ownership of the memory from sourceGrid

    sourceGrid.m_rows      = 0;
    sourceGrid.m_columns   = 0;
    sourceGrid.m_cellArray = nullptr;

    // returh *this so we can chain the assignment operator
    return *this;


}
Grid::~Grid()
{
    delete [] m_cellArray;
}

int Grid::getColumns() const {return m_columns;}

int Grid::getRows()    const {return m_rows;}

double Grid::predDensity(bool includeWetCells) const
{
    //initalize to zero since we will be adding to these values
    double totalPredDensity = 0.0;
    int    totalNumbWetCell = 0;

    int    totalNumberCells = m_rows * m_columns;

    //indexing from 1 since we are following the system in example landscape
    for(int j = 1; j <= m_rows; ++j)
    {
        for(int i = 1; i <= m_columns; ++i)
        {
            totalPredDensity += (*this)(i,j).getPredDensity();

            if(!((*this)(i,j).getState()))
            {
                ++totalNumbWetCell;
            }

        }


    } 

    if(includeWetCells)
    {
        return totalPredDensity/totalNumberCells;
    }

    else
    {
        return totalPredDensity/(totalNumberCells - totalNumbWetCell);
    }

}


double Grid::preyDensity(bool includeWetCells) const
{
    //initalize to zero since we will be adding to these values
    double totalPreyDensity = 0.0;
    int    totalNumbWetCell = 0;

    int    totalNumberCells = m_rows * m_columns;

    //indexing from 1 since we are following the system in example landscape
    for(int j = 1; j <= m_rows; ++j)
    {
        for(int i = 1; i <= m_columns; ++i)
        {
            totalPreyDensity += (*this)(i,j).getPreyDensity();

            if(!((*this)(i,j).getState()))
            {
                ++totalNumbWetCell;
            }

        }


    } 

    if(includeWetCells)
    {
        return totalPreyDensity/totalNumberCells;
    }

    else
    {
        return totalPreyDensity/(totalNumberCells - totalNumbWetCell);
    }
}


Cell& Grid::operator()(int i, int j)
{
    //check indicies are within bounds
    assert(i>=1 && i<=m_columns && j>=1 && j<=m_rows && "indicies out of bounds");
    //this formula accounts for the fact we are storing are 2-D array, in a 1-D array 
    //and takes account of the indexing for that configuration
    return m_cellArray[i + (m_rows + 1 - j) * (m_columns+2)];
}

//  second overload to return a const reference for a constant grid
const Cell& Grid::operator()(int i, int j) const
{
    //check indicies are within bounds
    assert(i>=1 && i<=m_columns && j>=1 && j<=m_rows && "indicies out of bounds");
    //this formula accounts for the fact we are storing are 2-D array, in a 1-D array 
    //and takes account of the indexing for that configuration
    return m_cellArray[i + (m_rows + 1 - j) * (m_columns+2)];
}

int Grid::dryNeighbours(int i, int j) const
{
    int totalDry = 0;
    if((*this)(i+1,j).getState()) ++totalDry;
    if((*this)(i-1,j).getState()) ++totalDry;
    if((*this)(i,j+1).getState()) ++totalDry;
    if((*this)(i,j-1).getState()) ++totalDry;
    return totalDry;
}

std::ostream& operator<<(std::ostream& out, const Grid& grid)
{

    //we will output the grid in the same format it came in with the number of rows and columns in the first line
    out<<grid.m_columns<<' '<<grid.m_rows<<'\n';

    //we will then use our overloaded() operator to access the cells and print there state, 0 or 1, remembering the indexing system 
    //we need to be careful to print out grid the right way round since (1,1) for example will give the cell in the bottom left hand corner we need to 
    //start from the top and work down 
    //start in the top row i.e. largest y coordinate
    for(int j = grid.m_rows; j >= 1 ; --j)
    {
        //work along the columns
        for(int i = 1; i <= grid.m_columns; ++i)
        {
            out << grid(i,j).getState() << ' ';
        }

        //printing a newline at the end of each column
        out<<'\n';
    }

    //return the output stream so we can chain together outputs 

    return out;

}