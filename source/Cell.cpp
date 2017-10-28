#include "Cell.hpp"

Cell::Cell(Cell::State state, double predDensity, double preyDensity):m_state(state)
{
    /*
     * If the cell is wet it can't contain any predators or prey. Even if the densities 
     * have been provided to the constructor they will still be set to zero if it is Wet.
     *
     */
    if(m_state == Wet)
    {
        m_predDensity = 0;
        m_preyDensity = 0;
    }
    else
    {
        m_predDensity = predDensity;
        m_preyDensity = preyDensity;
    }
}

Cell::~Cell(){}

double        Cell::getPredDensity() const {return m_predDensity;}
double        Cell::getPreyDensity() const {return m_preyDensity;}
Cell::State   Cell::getState()       const {return m_state;}

void Cell::setPredDensity(double predDensity)
{
    /*
     * 
     * If the predDensity < 0 or the Cell is Wet, then the m_predDensity will just be set to zero regardless
     * of the value of predDensity, since in these two cases the density is unphysical. 
     *
     */
    if(predDensity < 0.0 || Wet == m_state)
    {
    m_predDensity = 0.0;
    }

    else
    {
        m_predDensity = predDensity;
    }
}

void Cell::setPreyDensity(double preyDensity)
{
    /*
     * 
     * If the preyDensity < 0 or the Cell is Wet, then the m_preyDensity will just be set to zero regardless
     * of the value of predDensity, since in these two cases the density is unphysical. 
     *
     */
    if(preyDensity < 0.0 || Wet == m_state) m_preyDensity = 0.0;
    else
        m_preyDensity = preyDensity;
}

void Cell::setState(Cell::State state){m_state = state;}

