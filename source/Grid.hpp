
#ifndef Grid_hpp
#define Grid_hpp

//cell included since the Grid will contain an array of cells
#include "Cell.hpp"

//fstream included since the grid constructor will take a file stream
//from the input file to construct its cells
#include <fstream>

//cassert for assert in bounds checking on arrarys
#include <cassert>

// for use in the overloading of << operator
#include<iostream>

// for use in random number generation for assigning pred/prey distributions
#include<random>

// for seeding random nubmber generators
#include<chrono> 


/**
 * \class Grid
 *
 * \brief Models a 2D landscape of cells.  
 *
 * A Grid consists of a (2D) array of cells that can either be land or water and each have a predator
 * and prey density. The actual array is implemented with a "halo" of Wet cells, this means that the 
 * densities of predators and prey in these cells is zero. This is very useful for implementing any 
 * differential equations where we may inadvertently check the #columns + 1 or #rows + 1, so rather than 
 * introducing bounds checking, we can introduce this boundary. 
 */

class Grid
{

    private:


        /**
         * \brief Cell* member variable that holds an array of Cell objects that represent the landscape.
         *
         * This is implmented as a 1-D pointer. This is because first of all we do not know how big the landscape 
         * and therefore array of Cells will need to be until runtime, and array sizes must be determined at compiletime, 
         * therefore we will use dynamic memory allocation. Secondly for very large landscapes there might not be enough 
         * memory on the stack for the appropriate number of Cells, hence dynamic memory allocation from the heap is needed
         * for this reason as well. Finally the member variable is implemented as a 1-D dynamic array, rather than a 2-D array.
         * This is because of the memory padding that is involved in allocating a 2-D array; it is far more memory efficient
         * to allocate a 1-D array with the same number of elements as the 2-D array and use the overloaded operator() to access
         * the 1-D array as if it was a 2D array.
         */       
        Cell *m_cellArray;


        /** 
         * \brief Integer member variable that holds number of columns in the grid.
         *
         * This member variable hold the number of columns on the grid which is the discritization of the x-axis of the landscape. 
         * It holds the actual number of columns in the landscape, without any halo/buffer surrounding the landscape.
         */
        int m_columns;


         /** 
         * \brief Integer member variable that holds number of rows in the grid.
         *
         * This member variable hold the number of rows on the grid which is the discritization of the y-axis of the landscape. 
         * It holds the actual number of rows in the landscape, without any halo/buffer surrounding the landscape.
         */
        int m_rows;

        

    public:
        
        // constructor to take the input file and construct whole grid
        Grid(std::ifstream& inputFile);

        // overload copy constructor since the class has dynamic memory allocation so we need to do deep copying
        Grid(const Grid& sourceGrid);

        // we implement a move constructor since this is more performant for certain operations
        // such as returning a grid from a function, which we will need to do when we update the grid
        Grid(Grid&& sourceGrid);

        // destructor is implemented since memory will be dynamically allocated
        ~Grid();

        // overload assignment operator since class has dynamic memory allocation so need to do deep copying
        Grid& operator=(const Grid& sourceGrid);

        // we implement a move assignment operator as well to go with out move constructor
        Grid& operator=(Grid&& sourceGrid);


        /**
         * \brief Getter for the number of actual columns in the grid.
         *
         * \return The value of m_columns, the actual number of columns in the grid without a halo of water.
         *
         */
        int getColumns() const;


        /**
         * \brief Getter for the number of actual rows in the grid.
         *
         * \return The value of m_rows, the actual number of rows in the grid without a halo of water.
         *
         */
        int getRows() const;
        

        /**
         * \breif Sets uniform random predator distribution in each grid cell.
         *
         * Intially predator density will be zero in each cell since the constructors do no intialization of 
         * densities. This function sets the density of predators in every Dry grid cell to a random number 
         * between 0 and upperBound according to a uniform distribution. i.e. If upperBound = 5.0, then each 
         * dry cell will be assigned a density between 0.0 and 5.0 according to a uniform distribution.
         * 
         * \param upperBound floating point value that provides the upper bound for the random number 
         * distriubtion. 
         * 
         * \param generator a default_random_engine refernece from the std library <random> class. This is used 
         * to generate the random number from the distriubtion which is a local variable within the function. The 
         * generator should be provided by the main method so that chains of random predator densities can be 
         * reproduced if required for debugging. The generator is passed as a reference so that if any other functions
         * which makes use of the same distribution are called from the main method, they do not 
         * produce the same chain of random numbers, rather they act on the next random number given by the generator.
         */
        void setUniformPredDistribution(double uppperBound, std::default_random_engine &generator);

        /**
         * \breif Sets uniform random prey distribution in each grid cell.
         *
         * Intially prey density will be zero in each cell since the constructors do no intialization of 
         * densities. This function sets the density of predators in every Dry grid cell to a random number 
         * between 0 and upperBound according to a uniform distribution. i.e. If upperBound = 5.0, then each 
         * dry cell will be assigned a density between 0.0 and 5.0 according to a uniform distribution.
         * 
         * \param upperBound floating point value that provides the upper bound for the random number 
         * distriubtion. 
         * 
         * \param generator a default_random_engine refernece from the std library <random> class. This is used 
         * to generate the random number from the distriubtion which is a local variable within the function. The 
         * generator should be provided by the main method so that chains of random prey densities can be 
         * reproduced if required for debugging. The generator is passed as a reference so that if any other functions
         * which makes use of the same distribution are called from the main method, they do not 
         * produce the same chain of random numbers, rather they act on the next random number given by the generator.
         */
        void setUniformPreyDistribution(double upperBound, std::default_random_engine &generator);

        /**
         * \breif Sets uniform random predator and prey distribution in each grid cell.
         *
         * This function works by just calling the setUniformPredDistribution() and setUniormPreyDistribution() functions with
         * their respective upper bounds. For a more in depth discussion of the functionality plesae see those functions where
         * the implementation is explained in full.
         * 
         * \param predUpperBound floating point value that provides the upper bound for the random number 
         * distriubtion of the predators. 
         * \param preyUpperBound floating point value that provides the upper bound for the random number 
         * distriubtion of the prey.   
         *
         * 
         * \param generator a default_random_engine refernece from the std library <random> class. 
         */
        void setUniformDistribution(double predUpperBound, double preyUpperbound, std::default_random_engine &generator);

        
        /**
         * \brief Calulates average predator density across the grid.
         *
         * Calulates the average value of the predator density across the entire grid, not included the halo of Wet cells. However, 
         * the average can be taken over just the Dry cells in the grid, or over the Dry and Wet cells in the grid if the
         * corresponding argument is provided.
         *
         * \param includeWetCells bool value that represents whether the user wants to include the Wet cells in the grid
         * as the well as the Dry cells, as the total number of cells to take the average over. This value defaults to true i.e. 
         * the default behaviour is to average over all cells in the grid including the Wet ones where predator/prey densities will
         * be zero.
         *        
         * \return Floating point value representing the average predator density across the grid either including or not including the 
         * Wet cells, depending on how the function was called.
         *
         */
        double predDensity(bool includeWetCells = true) const;

        /**
         * \brief Calulates average prey density across the grid.
         *
         * Calulates the average value of the prey density across the entire grid, not included the halo of Wet cells. However, 
         * the average can be taken over just the Dry cells in the grid, or over the Dry and Wet cells in the grid if the
         * corresponding argument is provided.
         *
         * \param includeWetCells bool value that represents whether the user wants to include the Wet cells in the grid
         * as the well as the Dry cells, as the total number of cells to take the average over. This value defaults to true i.e. 
         * the default behaviour is to average over all cells in the grid including the Wet ones where predator/prey densities will
         * be zero.
         *        
         * \return Floating point value representing the average prey density across the grid either including or not including the 
         * Wet cells, depending on how the function was called.
         *
         */
        double preyDensity(bool includeWetCells = true ) const;


        /**
         * \breif Operator overload to access the Cell stored at the (i,j)th coordinates of the grid.
         * Since the 2-D landscape is implemeted as a 1-D array with the same number of elements for memory reasons, this opertor provides a way of acessing
         * the elements of the 1-D array with two indicies (i,j) as if it were a 2D-array. This operator should be used whenever direct acess to the grid cells 
         * is needed and extensive use of it is made in the constructors.
         * 
         * The indexing system for this operator and therefore the Grid itself follows that given in the specification document for this project in the figure 
         * in section 2.1. i.e. (i,j) corresponds to x (column number) and y coordinates (row number) where the orgin is taken to be in the bottom left corner.
         * This is not the same as matrix notation. For example (3,4) would return the cell in the 3rd column of the 4th row. 
         * 
         * \param i column number/x-coordinate of cell.
         * \param j row/y-coordinate of cell.
         *
         * \return Cell reference to the cell at the (i,j) coordinate. 
         */
        Cell& operator()(int i, int j);


        /**
        * \brief Second operator overload to acess the Cell stored at the (i,j)th coordinate if the grid is a constant variable.
        *
        * This function behaves in exactly the same way as its non-constant counterpart. However the non-constant operator() overload will not work with any constant 
        * grid objects, since it returns a reference, it would be able to edit contents of the constant Cells m_cellArray member. For an explanation of the indexing 
        * system please see the non-constant overload. 
        *
        * \param i column number/x-coordinate of cell.
        * \param j row/y-coordinate of cell.
        *
        * \return Constant Cell reference to the cell at the (i,j) coordinate, so that the main method cannot edit the contents of a constant Grid.  
        */
        const Cell& operator()(int i, int j) const;


        /**
        * \brief Calulates number of Dry neighbours of a given cell.
        * 
        * Neighbours are only considered to be non-diagonal, so this function counts the number of Dry cells directly above/below and to the left/right of the specified
        * cell.
        *
        * \param i column number/x-coordinate of cell.
        * \param j row number/y-corrdinate of cell.
        *
        * \return Integer value representing number of Dry neighbours of the cell. 
        */
        int dryNeighbours(int i, int j) const;


        /**
        * \brief Operator overload for outputting the grid
        *
        * Outputs the Grid into an ouput stream in the format: 
        * #columns #rows
        * x x ..... x
        * x x ..... x
        * . . ..... .
        * . . ..... .
        * . . ..... .
        * x x ..... x
        * where x take on the values of 0 or 1 depending on whether the corresponding (i,j)th cell measure from the bottom left corner is Wet or Dry respivtively.
        * 
        * This is a friend function since the first operand (argument on left of operator) is not the Cell
        *
        * \param out std::ostream reference which is the output.
        * \param grid const Grid reference which is the grid to be sent into the output stream.
        *
        * \return std::ostream reference that is the same as the out parameter, this is so one can put this opearator in a chain of output operators. 
        */
        friend std::ostream&  operator<<(std::ostream& out, const Grid& grid);


        /**
        * \brief Outputs predator and prey densities to output stream.
        * 
        * Outputs densities of predator and prey for each cell in the format:
        * i j predator density prey density 
        * and repeats this for all cells in the grid.
        *
        * \param out std::ostream reference which is the output stream. This will also work for fstream since it inherits from ostream.
        *
        */
        void printDensities(std::ostream& out) const;

    
};

#endif /* Grid_hpp */