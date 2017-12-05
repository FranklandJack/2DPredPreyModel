#include "Cell.hpp"

Cell::Cell(Cell::State state, double predDensity, double preyDensity):m_state(state)
{
    /*
     * If the cell is wet it can't contain any predators or prey. Even if the densities 
     * have been provided to the constructor they will still be set to zero if it is Wet.
     */
    if(m_state == Wet)
    {
        for(int animal = 0; animal < static_cast<int>(Cell::MAX_ANIMAL); ++animal)
        {
            m_animalDensities[animal] = 0.0;
        }
    }
    else
    {
        // If the constructor tries to set either density to a negative value, it will automatically be set to zero.
        m_animalDensities[Predator] = (predDensity < 0.0) ? 0.0 : predDensity;
        m_animalDensities[Prey]     = (preyDensity < 0.0) ? 0.0 : preyDensity;
    }
}

Cell::~Cell(){}

double Cell::getDensity(Cell::Animal animal) const 
{ 
    return m_animalDensities[animal];
}

Cell::State Cell::getState() const { return m_state;}

void Cell::setDensity(Cell::Animal animal, double density)
{
    /*
     * If the predDensity < 0 or the Cell is Wet, then the m_predDensity will just be set to zero regardless
     * of the value of predDensity, since in these two cases the density is unphysical. 
     */
    if(density < 0.0 || Wet == m_state)
    {
        density = 0.0;
    }

    m_animalDensities[animal] = density;
    
}



void Cell::setState(Cell::State state){ m_state = state; }

