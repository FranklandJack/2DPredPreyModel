#include "updateGrid.hpp"

Grid updateGrid(Grid& grid, double r, double a, double b, double m, double k, double l, double deltaT)
{
    // first we will copy the original grid so we have a grid into which we can place the updated cells
    Grid updatedGrid = grid;

    for(int j = 1; j <= grid.getRows(); ++j)
    {
        for(int i = 1; i <= grid.getColumns(); ++i)
        {
            int     dryNeighbours  = grid.dryNeighbours(i,j);

            double h_old_i_j       = grid(i,j).getPreyDensity();
            double h_old_iMinus1_j = grid(i-1,j).getPreyDensity();
            double h_old_iPlus1_j  = grid(i+1,j).getPreyDensity();
            double h_old_i_jMinus1 = grid(i,j-1).getPreyDensity();
            double h_old_i_jPlus1  = grid(i,j+1).getPreyDensity();
            
            double p_old_i_j       = grid(i,j).getPredDensity();
            double p_old_iMinus1_j = grid(i-1,j).getPredDensity();
            double p_old_iPlus1_j  = grid(i+1,j).getPredDensity();
            double p_old_i_jMinus1 = grid(i,j-1).getPredDensity();
            double p_old_i_jPlus1  = grid(i,j+1).getPredDensity();


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

    return updatedGrid;
}