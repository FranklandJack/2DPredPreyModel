#include "Grid.hpp"


Grid::Grid()
{
    m_columns   = 0;
    m_rows      = 0;
    m_cellArray = nullptr;
}

Grid::Grid(int columns, int rows , int ** const data):m_columns(columns), m_rows(rows)
{
    /*
     * To include the halo the number of rows and columns need to be increased by 2
     * so that there is an extra row on the top and bottom and extra column on either side.
     */
    int arraySizeIncBufffer = (m_columns+2)*(m_rows+2);


    // The actual array size doesn't include the halo.
    int arraySize           = m_columns*m_rows;


    // The 1-D array of Cells is allocated dynamically from the heap and includes the halo.
    m_cellArray = new Cell[arraySizeIncBufffer];


    for(int cellIndex = 0; cellIndex < arraySizeIncBufffer; ++cellIndex)
    {
        /*
         * Initially a Wet cell with predator and prey densities of zero is copied into every 
         * entry in the Grid Cell array including the halo cells.
         */
        Cell::State  initialState       = Cell::Wet;
        double       initialPredDensity = 0.0;
        double       initialPreyDensity = 0.0;

        m_cellArray[cellIndex] = Cell(initialState, initialPreyDensity, initialPreyDensity);
    }


    
     
    // Then the non-halo cells have their state set according to the landscape provided to the constructor
    for(int j = 1; j <= m_rows; ++j)
    {
        for(int i = 1; i <= m_columns; ++i)
        {
            /* 
             * Since the state is an enum which has two possible values Wet (= 0) and Dry (= 1), and  and each value in the input 
             * data array is 0 (for wet) or 1 (for dry) each array entry can be converted into the State data type.
             *
             * The data from the input is indexed from 0, however the actual landscape data is indexed from 1, in line with the specification
             * therefore a shift by -1 is required in the x and y directions in the input data to match the coordinates correctly.
             */
             Cell::State state = static_cast<Cell::State>(data[i-1][j-1]);   


            // The state of the cell is then set using the operator() overload since this ensures the indexing is correct and consistent. 
            (*this)(i,j).setState(state);
        }
    }



}

Grid::Grid(const Grid& sourceGrid): m_rows(sourceGrid.m_rows),
                                    m_columns(sourceGrid.m_columns)
{
    // Because m_rows and m_columns are not dynamically allocated we can just shallow copy them.
    
    // m_cellArray is a dynamically allocated pointer, we need to deep copy if it is non-null.
    if(nullptr != sourceGrid.m_cellArray)
    {
        /*
         * To include the halo the number of rows and columns need to be increased by 2
         * so that there is an extra row on the top and bottom and extra column on either side.
         */
        int arraySizeIncBufffer = (m_rows+2)*(m_columns+2);

        // The 1-D array of Cells is allocated dynamically from the heap and includes the halo.
        m_cellArray = new Cell[arraySizeIncBufffer];

        // The cells are copied and placed in the newly allocated array, including the halo. 
        for(int j = 0; j < m_rows + 2; ++j)
        {
            for (int i = 0; i < m_columns + 2; ++i)
            {
                (*this)(i,j) = sourceGrid(i,j);
            }
        }

    }

    // If copying from a grid with a null-pointer in its array member variable the new array is made null as well.
    else
    {
        m_cellArray = nullptr;
    }

}


Grid::Grid(Grid&& sourceGrid): m_rows(sourceGrid.m_rows), 
                               m_columns(sourceGrid.m_columns),
                               m_cellArray(sourceGrid.m_cellArray)
{
    /*
     * Ownership of member variables in sourceGrid is transferred to the new grid. 
     *
     * Ownership of the member variables is then removed from the sourceGrid. 
     * Technically since m_columns and m_cellArray are just Integer variables that are non-dynamic they do not need to 
     * have their ownership by the sourceGrid removed, it is only done here for completeness. 
     */
    sourceGrid.m_rows    = 0;
    sourceGrid.m_columns = 0;
    sourceGrid.m_cellArray = nullptr;

}

Grid& Grid::operator=(const Grid& sourceGrid)
{
    // Check against self assignment using memory addresses.
    if(this == &sourceGrid)
    {
        /*
         * If self assignment has occurred then the method can return early since there is nothing to do. 
         * Return *this so assignment operations can be chained together.
         */
        return *this;
    }


    /*
     * Current memory held by the m_cellArray must be deallocated to avoid a memory leak. 
     * The same memory cannot be reused since more or less might be required.
     */
    delete [] m_cellArray;

    // Because m_rows and m_columns are not dynamically allocated they are just shallow copied.
    m_rows    = sourceGrid.m_rows;
    m_columns = sourceGrid.m_columns;

    // m_cellArray is a dynamically allocated pointer, we need to deep copy if it is non-null.
    if(nullptr != sourceGrid.m_cellArray)
    {
        /*
         * To include the halo the number of rows and columns need to be increased by 2
         * so that there is an extra row on the top and bottom and extra column on either side.
         */
        int arraySizeIncBufffer = (m_rows+2)*(m_columns+2);

        // The 1-D array of Cells is allocated dynamically from the heap and includes the halo.
        m_cellArray = new Cell[arraySizeIncBufffer];

        // The cells are copied and placed in the newly allocated array, including the halo.
        for(int j = 0; j < m_rows + 2; ++j)
        {
            for (int i = 0; i < m_columns + 2; ++i)
            {
                (*this)(i,j) = sourceGrid(i,j);
            }
        }

    }

    // If copying from a grid with a null-pointer in its array member variable the new array is made null as well.
    else
    {
        m_cellArray = nullptr;
    }

    // Return *this so assignment operations can be chained together. 
    return *this;

}




Grid& Grid::operator=(Grid&& sourceGrid)
{
    // Check against self assignment using memory addresses.
    if(&sourceGrid == this)
    {
        // If self assignment has occurred then the method can return early since there is nothing to do.
        return *this;
    }

    /*
     * Current memory held by the m_cellArray must be deallocated to avoid a memory leak. 
     * The same memory cannot be reused since more or less might be required.
     */
    delete [] m_cellArray;


    // Ownership of member variables in sourceGrid is transferred to the new grid. 
    m_rows    = sourceGrid.m_rows;
    m_columns = sourceGrid.m_columns;
    m_cellArray = sourceGrid.m_cellArray;

    /*
     * Ownership of the member variables is then removed from the sourceGrid. 
     * Technically since m_columns and m_cellArray are just Integer variables that are non-dynamic they do not need to 
     * have their ownership by the sourceGrid removed, it is only done here for completeness. 
     */
    sourceGrid.m_rows      = 0;
    sourceGrid.m_columns   = 0;
    sourceGrid.m_cellArray = nullptr;

    // Return *this so assignment operations can be chained together.
    return *this;


}

Grid::~Grid()
{
    // Release memory held by m_cellArray.
    delete [] m_cellArray;
}

int Grid::getColumns() const {return m_columns;}

int Grid::getRows()    const {return m_rows;}


Cell::State Grid::getCellState(int columnIndex, int rowIndex) const
{
    return (*this)(columnIndex,rowIndex).getState();
}


void Grid::setUniformPredDistribution(double upperBound, std::default_random_engine &generator)
{
    // Create a uniform distribution of random numbers between 0.0 and upper bound.
    std::uniform_real_distribution<double> distribution(0.0,upperBound);

    // Loop through the entire grid not including the halo, hence only index from 1 to m_row and 1 to m_column.
    for(int j = 1; j <= m_rows; ++j)
    {
        for(int i = 1; i <= m_columns; ++i)
        {             
            // Acting on the generator with the distribution produces a new pseudo random number in the range (0.0, upperBound) according to the uniform distribution.
            double randomDensity = distribution(generator);

            // Set each cell to have a random density. 
            ((*this)(i,j)).setPredDensity(randomDensity);
        }
    }
}


void Grid::setUniformPreyDistribution(double upperBound, std::default_random_engine &generator)
{
    // Create a uniform distribution of random numbers between 0.0 and upper bound.
    std::uniform_real_distribution<double> distribution(0.0,upperBound);

    // Loop through the entire grid not including the halo, hence only index from 1 to m_row and 1 to m_column.
    for(int j = 1; j <= m_rows; ++j)
    {
        for(int i = 1; i <= m_columns; ++i)
        {
            // Acting on the generator with the distribution produces a new pseudo random number in the range (0.0, upperBound) according to the uniform distribution.
            double randomDensity = distribution(generator);

            // Set each cell to have a random density. 
            ((*this)(i,j)).setPreyDensity(randomDensity);
        }
    }
}


void Grid::setUniformDistribution(double predUpperBound, double preyUpperbound, std::default_random_engine &generator)
{
    setUniformPredDistribution(predUpperBound, generator);
    setUniformPreyDistribution(preyUpperbound, generator);
}

double Grid::predDensity(bool includeWetCells) const
{
    double totalPredDensity = 0.0;
    int    totalNumbWetCells = 0;
    int    totalNumberCells = m_rows * m_columns;

   // Loop through the entire grid not including the halo, hence only index from 1 to m_row and 1 to m_column.
    for(int j = 1; j <= m_rows; ++j)
    {
        for(int i = 1; i <= m_columns; ++i)
        {
            // Add the predator densities of each cell up.
            totalPredDensity += (*this)(i,j).getPredDensity();

            // Total up the number of Wet cells as well.
            if(Cell::Wet == !((*this)(i,j).getState()))
            {
                ++totalNumbWetCells;
            }

        }


    } 

    // In the case that the caller specified to include Wet cells in the average use all Cells. 
    if(true == includeWetCells)
    {
        return totalPredDensity/totalNumberCells;
    }

    // In the case that the caller specified not to include Wet cells in the average use all Cells only use dry cells.
    else
    {   
        // Since cells are either Wet or Dry totalNumbWetCells + totalNumbDryCells = totalNumberCells. 
        return totalPredDensity/(totalNumberCells - totalNumbWetCells);
    }

}


double Grid::preyDensity(bool includeWetCells) const
{

    double totalPreyDensity = 0.0;
    int    totalNumbWetCell = 0;
    int    totalNumberCells = m_rows * m_columns;

    // Loop through the entire grid not including the halo, hence only index from 1 to m_row and 1 to m_column.
    for(int j = 1; j <= m_rows; ++j)
    {
        for(int i = 1; i <= m_columns; ++i)
        {
            // Add the prey densities of each cell up.
            totalPreyDensity += (*this)(i,j).getPreyDensity();

            /// Total up the number of Wet cells as well.
            if(!((*this)(i,j).getState()))
            {
                ++totalNumbWetCell;
            }

        }


    } 

    // In the case that the caller specified to include Wet cells in the average use all Cells. 
    if(true == includeWetCells)
    {
        return totalPreyDensity/totalNumberCells;
    }

    // In the case that the caller specified not to include Wet cells in the average use all Cells only use dry cells.
    else
    {
        // Since cells are either Wet or Dry totalNumbWetCells + totalNumbDryCells = totalNumberCells. 
        return totalPreyDensity/(totalNumberCells - totalNumbWetCell);
    }
}


Cell& Grid::operator()(int i, int j)
{
    
    /*
     * This formula accounts for the fact that m_cellArray is a "2D-landscape" being stored as a 1-D array. 
     * It allows the caller, and anyone using the function to continue thinking of the data as a 2-D array
     * of 0 (water) and 1 (land), which simplifies access. The index system is chosen to be consistent with 
     * the specification document which is described in detail in the class summary. Note that this means that 
     * the 0th row and 0th column and m_columns + 1 and m_rows + 1 rows correspond to the halo of water that bounds
     * the grid.
     */
    return m_cellArray[i + (m_rows + 1 - j) * (m_columns+2)];
}


const Cell& Grid::operator()(int i, int j) const
{
    // See the non-constant version of this overload for the implementation explanation. 
    return m_cellArray[i + (m_rows + 1 - j) * (m_columns+2)];
}

int Grid::dryNeighbours(int i, int j) const
{
    int totalDry = 0;
    // Check the cell to the right of the cell in question.
    if(Cell::Dry == (*this)(i+1,j).getState()) ++totalDry;

    // Check the cell to the left of the cell in question.
    if(Cell::Dry == (*this)(i-1,j).getState()) ++totalDry;

    // Check the cell above the cell in question. 
    if(Cell::Dry == (*this)(i,j+1).getState()) ++totalDry;

    // Check the cell below the cell in question.
    if(Cell::Dry == (*this)(i,j-1).getState()) ++totalDry;

    return totalDry;
}

std::ostream& operator<<(std::ostream& out, const Grid& grid)
{

    out << grid.m_columns <<" "<< grid.m_rows << "\n";

    /*
     * Output works from the top of the grid first i.e. the largest y-coordinate so that the grid is not 
     * output upside down. So output goes from "top" to "bottom"  and "left" to "right" and doesn't include
     * the halo of Wet cells since these are not part of the actual grid. 
     */
    for(int j = grid.m_rows; j >= 1; --j)
    {
       
        for(int i = 1; i <= grid.m_columns; ++i)
        {
            /* 
             * The state should be converted into an integer so it can be printed. Since it is an enum with only two 
             * states Wet (= 0) and Dry (= 1) a cast will give the correct 0s and 1s representing the states in the grid. 
             */
            Cell::State state = grid(i,j).getState();
            int stateOutput = static_cast<int>(state);
            out << stateOutput << " ";
        }

        // Print a newline at the end of each column for the correct format.
        out<<"\n";
    }

    // Return the output stream so we can chain together outputs 
    return out;
}


void Grid::printDensities(std::ostream& out) const
{

    for(int j = m_rows; j >= 1; --j)
    {
        for (int i = 1; i <= m_columns; ++i)
        {
            // Print column number, then row number, followed by predator density, then prey density. 
            out << i << " " << j << " " << (*this)(i,j).getPredDensity() << " " << (*this)(i,j).getPreyDensity() << std::endl;
        }
    }
}


int Grid::printPPM(std::ofstream &file, int maxNumberPPM, double scaling, double scaleFactor) const
{
    double rounding = 0.5;
    double maxDensity;
    // Print the header which identifies it as a plain PPM file.
    file << "P3" << std::endl;

    // Print the width and heigh of the image in pixels.
    file << m_columns << " " << m_rows << std::endl;

    // Print the maximum value any colour can take into the file since this is part of the format.
    file << maxNumberPPM << std::endl;

    for(int j = m_rows; j >= 1; --j)
    {
        for(int i = 1; i <= m_columns; ++i)
        {
            // The first value in the RGB triple will just be zero, which means that the density dependency in the colours will be goverened only by the 
            // G and B values. 
            int rValue = 0;

            // The green value will be determined by the rounded predator density.
            int gValue = static_cast<int>(scaling * (*this)(i,j).getPredDensity() + rounding);

            // The blue value will be deterined by the rounded prey density. 
            int bValue = static_cast<int>(scaling * (*this)(i,j).getPreyDensity() + rounding);
            
            if (gValue > maxNumberPPM)
                gValue = maxNumberPPM;
            
            if (bValue > maxNumberPPM)
                bValue = maxNumberPPM;
            
            file << rValue << " " << gValue << " " << bValue;
            
            // Print each pixel to a new line since at most any line can be 70 characters long.
            file << std::endl;
            
            //Finds the higher density and changes maxNumberPPM so that for the next output maxNumberPPM is a high enough number.
            maxDensity = ( ((*this)(i,j).getPredDensity()) > ((*this)(i,j).getPreyDensity()) ? ((*this)(i,j).getPredDensity()) : ((*this)(i,j).getPreyDensity()) );
            while(maxNumberPPM < scaleFactor * maxDensity * scaling)
             {
                maxNumberPPM = static_cast<int>(scaleFactor * maxNumberPPM);
             }
        }
    }
    
    return maxNumberPPM;
}
