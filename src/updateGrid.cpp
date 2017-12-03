#include "updateGrid.hpp"

Grid updateGrid(Grid& grid, double r, double a, double b, double m, double k, double l, double deltaT)
{
    // First copy the original grid so there is a grid into which we can place the updated cells. This means are new and old
    // grids will have the same wet and dry cells. 
    Grid updatedGrid = grid;


    // Then just iterate through the old grid, and place the updated cells into the new grid.
    for(int j = 1; j <= grid.getRows(); ++j)
    {
        for(int i = 1; i <= grid.getColumns(); ++i)
        {

            // Only need to consider updating the dry cells, since the wet cells do not contain any predator or prey. 
            if(grid(i,j).getState() == Cell::Dry)
            {
            int     dryNeighbours  = grid.dryNeighbours(i,j);

            // This is the implementation of the differential equations provided in the coursework development pdf.
            double newPreyDensity = grid(i,j).getDensity(Cell::Prey) + deltaT * ( r * grid(i,j).getDensity(Cell::Prey) - a * grid(i,j).getDensity(Cell::Prey) * grid(i,j).getDensity(Cell::Predator) +
                               k * ( ( grid(i-1,j).getDensity(Cell::Prey) + grid(i+1,j).getDensity(Cell::Prey) + grid(i,j-1).getDensity(Cell::Prey) + grid(i,j+1).getDensity(Cell::Prey) ) -
                                   dryNeighbours * grid(i,j).getDensity(Cell::Prey) )  );

            double newPredDensity = grid(i,j).getDensity(Cell::Predator) + deltaT * ( b * grid(i,j).getDensity(Cell::Prey) * grid(i,j).getDensity(Cell::Predator) - m * grid(i,j).getDensity(Cell::Predator) +
                               l * ( ( grid(i-1,j).getDensity(Cell::Predator) + grid(i+1,j).getDensity(Cell::Predator) + grid(i,j-1).getDensity(Cell::Predator) + grid(i,j+1).getDensity(Cell::Predator) ) -
                                   dryNeighbours * grid(i,j).getDensity(Cell::Predator) )  );

            updatedGrid(i,j).setDensity(Cell::Prey,newPreyDensity);
            updatedGrid(i,j).setDensity(Cell::Predator,newPredDensity);
        }
        }   
    }

    return updatedGrid;
}