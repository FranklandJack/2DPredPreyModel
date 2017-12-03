#include "updateGrid.hpp"

void updateGrid(Grid* currentGrid, Grid* updatedGrid, double r, double a, double b, double m, double k, double l, double deltaT)
{

    // Then just iterate through the old grid, and place the updated cells into the new grid.
    for(int j = 1; j <= currentGrid->getRows(); ++j)
    {
        for(int i = 1; i <= currentGrid->getColumns(); ++i)
        {

            // Only need to consider updating the dry cells, since the wet cells do not contain any predator or prey. 
            if((*currentGrid)(i,j).getState() == Cell::Dry)
            {
            int     dryNeighbours  = currentGrid->dryNeighbours(i,j);

            // This is the implementation of the differential equations provided in the coursework development pdf.
            double newPreyDensity = (*currentGrid)(i,j).getDensity(Cell::Prey) + deltaT * ( r * (*currentGrid)(i,j).getDensity(Cell::Prey) - a * (*currentGrid)(i,j).getDensity(Cell::Prey) * (*currentGrid)(i,j).getDensity(Cell::Predator) +
                               k * ( ( (*currentGrid)(i-1,j).getDensity(Cell::Prey) + (*currentGrid)(i+1,j).getDensity(Cell::Prey) + (*currentGrid)(i,j-1).getDensity(Cell::Prey) + (*currentGrid)(i,j+1).getDensity(Cell::Prey) ) -
                                   dryNeighbours * (*currentGrid)(i,j).getDensity(Cell::Prey) )  );

            double newPredDensity = (*currentGrid)(i,j).getDensity(Cell::Predator) + deltaT * ( b * (*currentGrid)(i,j).getDensity(Cell::Prey) * (*currentGrid)(i,j).getDensity(Cell::Predator) - m * (*currentGrid)(i,j).getDensity(Cell::Predator) +
                               l * ( ( (*currentGrid)(i-1,j).getDensity(Cell::Predator) + (*currentGrid)(i+1,j).getDensity(Cell::Predator) + (*currentGrid)(i,j-1).getDensity(Cell::Predator) + (*currentGrid)(i,j+1).getDensity(Cell::Predator) ) -
                                   dryNeighbours * (*currentGrid)(i,j).getDensity(Cell::Predator) )  );

            (*updatedGrid)(i,j).setDensity(Cell::Prey,newPreyDensity);
            (*updatedGrid)(i,j).setDensity(Cell::Predator,newPredDensity);
        }
        }   
    }
}