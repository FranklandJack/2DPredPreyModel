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


            double newPreyDensity = grid(i,j).getPreyDensity() + deltaT * ( r * grid(i,j).getPreyDensity() - a * grid(i,j).getPreyDensity() * grid(i,j).getPredDensity() +
                               k * ( ( grid(i-1,j).getPreyDensity() + grid(i+1,j).getPreyDensity() + grid(i,j-1).getPreyDensity() + grid(i,j+1).getPreyDensity() ) -
                                   dryNeighbours * grid(i,j).getPreyDensity() )  );

            double newPredDensity = grid(i,j).getPredDensity() + deltaT * ( b * grid(i,j).getPreyDensity() * grid(i,j).getPredDensity() - m * grid(i,j).getPredDensity() +
                               l * ( ( grid(i-1,j).getPredDensity() + grid(i+1,j).getPredDensity() + grid(i,j-1).getPredDensity() + grid(i,j+1).getPredDensity() ) -
                                   dryNeighbours * grid(i,j).getPredDensity() )  );

            updatedGrid(i,j).setPreyDensity(newPreyDensity);
            updatedGrid(i,j).setPredDensity(newPredDensity);
        }
        }   
    }

    return updatedGrid;
}