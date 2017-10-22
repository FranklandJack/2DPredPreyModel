
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

// for use in the overloading of << operator
#include<iostream>

// for use in random number generation for assigning pred/prey distributions
#include<random>

// for seeding random nubmber generators
#include<chrono> 

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


        // getter for the number of colummns in the grid
        int getColumns() const;

        // getter for the number of rows in the grid
        int getRows() const;
        

        // function to set predator distriubtion across grid, since it will initially be zero everywhere
        // takes a number and will set the pred. density in each cell to be somewhere between 0 and this value with uniform probablity
        // needs a random generator which will come from the main method
        void setUniformPredDistribution(double uppperBound, std::default_random_engine &generator);

        // function to set prey distriubtion across grid, since it will initially be zero everywhere
        // takes a number and will set the prey. density in each cell to be somewhere between 0 and this value with uniform probablity
        void setUniformPreyDistribution(double upperBound, std::default_random_engine &generator);

        // function to set both predator and prey uniform distribution across whole grid
        void setUniformDistribution(double predUpperBound, double preyUpperbound, std::default_random_engine &generator);

        
        //function to return predator density over whole grid
        //bool argument is so that we can customize the function to calculate average over all grid cells including the wet ones where there are no predators or prey
        //or just the dry cells, defaults to include all cells
        double predDensity(bool includeWetCells = true) const;

        //function to return prey denisty over whole grid
        //bool argument is so that we can customize the function to calculate average over all grid cells including the wet ones where there are no predators or prey
        //or just the dry cells, defaults to include all cells
        double preyDensity(bool includeWetCells = true ) const;


        //overload () operator to return cell at i,j th position in grid, 
        // i is the x coordinate and j is the y coordinate, indexed from 1
        //this is to match the figure given in section 2.1 in the pdf
        Cell& operator()(int i, int j);

        // second overload to return a const reference for a constant grid
        const Cell& operator()(int i, int j) const;

        // function to calculate the number of dry neighbours of a cell, where neighbours are only considered to be non-diagonal
        int dryNeighbours(int i, int j) const;

        // overload << operator so we can easily print our grid into a file or the command line in the same format it was input in
        friend std::ostream&  operator<<(std::ostream& out, const Grid& grid);

        // function to print out the grid with each cell as its density (pred,prey) pair
        void printDensities() const;

    
};

#endif /* Grid_hpp */