#include "Cell.hpp"

Cell::Cell(int numberPred, int numberPrey, bool dry):m_nPredator(numberPred),m_nPrey(numberPrey),m_dry(dry){}
Cell::~Cell(){}

int Cell::getNumbPred() const {return m_nPredator;}
int Cell::getNumbPrey() const {return m_nPrey;}
bool Cell::isDry() const	    {return m_dry;}

void Cell::setNumbPred(int numberPred){m_nPredator = numberPred;}
void Cell::setNumbPrey(int numberPrey){m_nPrey     = numberPrey;}
void Cell::setDry() 				  {m_dry = true;}
void Cell::setWet()					  {m_dry = false;}

