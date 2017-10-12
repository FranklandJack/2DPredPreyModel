#include "Cell.hpp"

Cell::Cell(bool state,int predDensity, int preyDensity):m_state(state)
{
	//if the cell is wet it can't contain any predators or prey
	if(m_state == false)
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

int Cell::getPredDensity() const {return m_predDensity;}
int Cell::getPreyDensity() const {return m_preyDensity;}
bool Cell::getState() const	     {return m_state;}

void Cell::setPredDensity(int predDensity){m_predDensity = predDensity;}
void Cell::setPreyDensity(int preyDensity){m_preyDensity = preyDensity;}
void Cell::setState(bool state) 		  {m_state = state;}

