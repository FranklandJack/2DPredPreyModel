#include "Cell.hpp"

Cell::Cell(bool dry,int numberPred, int numberPrey):m_dry(dry)
{
	if(m_dry == false)
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
bool Cell::isDry() const	    {return m_dry;}

void Cell::setNumbPred(int numberPred){m_nPredator = numberPred;}
void Cell::setNumbPrey(int numberPrey){m_nPrey     = numberPrey;}
void Cell::setDry() 				  {m_dry = true;}
void Cell::setWet()					  {m_dry = false;}

