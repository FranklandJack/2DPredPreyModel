#ifndef updateGrid_hpp
#define updateGrid_hpp
#include "Grid.hpp"
/** 
 *
 * \file 
 *
 *
 * \brief Updates the grid by one time step.
 *
 * Function to update the densities of predator and prey in a grid instance according 
 * to the differential equation  specified in the coursework pdf.
 *
 * \param grid Grid reference instance to be updated.
 * 
 * \param r double instance representing the birth rate of hares (prey).
 *
 * \param a double instance representing the predation rate at which pumas (predators).
 *
 * \param b double instance representing the birth rate of pumas (predators) per one hare (prey) eaten.
 *
 * \param m double instance representing the puma (predator) mortality rate.
 *
 * \param k double instance representing the diffusion rate for hares (prey).
 *
 * \param l double instance representing the diffusion rate for pumas (predators).
 *
 * \param deltaT double instance representing the time step value.
 *
 * \return Grid instance which is the original grid updated by one time step.
 *
 */
Grid updateGrid(Grid& grid, double r, double a, double b, double m, double k, double l, double deltaT);
#endif