#include "Cell.hpp"

Cell::Cell(bool state,int numberPred, int numberPrey):m_state(state)
{
	if(m_state == false)
	{
		m_nPredator = 0;
		m_nPrey = 0;
	}
	else
	{
		m_nPredator = numberPred;
		m_nPrey     = numberPrey;
	}
}
Cell::~Cell(){}

int Cell::getNumbPred() const {return m_nPredator;}
int Cell::getNumbPrey() const {return m_nPrey;}
bool Cell::getState() const	    {return m_state;}

void Cell::setNumbPred(int numberPred){m_nPredator = numberPred;}
void Cell::setNumbPrey(int numberPrey){m_nPrey     = numberPrey;}
void Cell::setState(bool state) 				  {m_state = state;}

