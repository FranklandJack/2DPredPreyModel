#include "updateGrid.hpp"

void updateGrid(Grid& grid, double r, double a, double b, double m, double k, double l, double deltaT)
{
    // first we will copy the original grid so we have a grid into which we can place the updated cells
    Grid updatedGrid = grid;

    for(int j = 1; j <= grid.getRows(); ++j)
    {
        for(int i = 1; i <= grid.getColumns(); ++i)
        {
            int    dryNeighbours  = grid.dryNeighbours(i,j);

            double h_old_i_j       = grid.getPreyDensity(i,j);
            double h_old_iMinus1_j = grid.getPreyDensity(i-1,j);
            double h_old_iPlus1_j  = grid.getPreyDensity(i+1,j);
            double h_old_i_jMinus1 = grid.getPreyDensity(i,j-1);
            double h_old_i_jPlus1  = grid.getPreyDensity(i,j+1);
            
            double p_old_i_j       = grid.getPredDensity(i,j);
            double p_old_iMinus1_j = grid.getPredDensity(i-1,j);
            double p_old_iPlus1_j  = grid.getPredDensity(i+1,j);
            double p_old_i_jMinus1 = grid.getPredDensity(i,j-1);
            double p_old_i_jPlus1  = grid.getPredDensity(i,j+1);


            double h_new_i_j = h_old_i_j + deltaT * ( r * h_old_i_j - a * h_old_i_j * p_old_i_j +
                               k * ( ( h_old_iMinus1_j + h_old_iPlus1_j + h_old_i_jMinus1 + h_old_i_jPlus1 ) -
                                   dryNeighbours * h_old_i_j )  );

            double p_new_i_j = p_old_i_j + deltaT * ( b * h_old_i_j * p_old_i_j - m * p_old_i_j +
                               l * ( ( p_old_iMinus1_j + p_old_iPlus1_j + p_old_i_jMinus1 + p_old_i_jPlus1 ) -
                                   dryNeighbours * p_old_i_j )  );

            updatedGrid(i,j).setPreyDensity(h_new_i_j);
            updatedGrid(i,j).setPredDensity(p_new_i_j);
        }   
    }

    grid = updatedGrid;
}