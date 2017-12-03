#include "Cell.hpp"

Cell::Cell(Cell::State state, double predDensity, double preyDensity):m_state(state)
{
    /*
     * If the cell is wet it can't contain any predators or prey. Even if the densities 
     * have been provided to the constructor they will still be set to zero if it is Wet.
     */
    if(m_state == Wet)
    {
        m_predDensity = 0;
        m_preyDensity = 0;
    }
    else
    {
        // If the constructor tries to set either density to a negative value, it will automatically be set to zero.
        m_predDensity = (predDensity < 0.0) ? 0.0 : predDensity;
        m_preyDensity = (preyDensity < 0.0) ? 0.0 : preyDensity;
    }
}

Cell::~Cell(){}

double        Cell::getDensity(Cell::Animal animal) const 
{ 
    switch(animal)
    {
        case Cell::Predator:
            return m_predDensity;

        case Cell::Prey:
            return m_preyDensity;

        default:
            return 0;
    }
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

    switch(animal)
    {
        case Cell::Predator:
            m_predDensity = density;
            break;

        case Cell::Prey:
            m_preyDensity = density;
            break;

        default:
            break;

    }
    
}



void Cell::setState(Cell::State state){ m_state = state; }

