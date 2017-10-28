#ifndef updateGrid_hpp
#define updateGrid_hpp
#include "Grid.hpp"

/**
 *
 * Function to update the densities of predator and prey in grid object according 
 * to the differential equation  specified in the development pdf.
 *
 */
Grid updateGrid(Grid& grid, double r, double a, double b, double m, double k, double l, double deltaT);
#endif