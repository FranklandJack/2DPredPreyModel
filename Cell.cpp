#include "Cell.hpp"

Cell::Cell(int numberPred, int numberPrey, bool dry):m_nPredator(numberPred),m_nPrey(numberPrey),m_dry(dry){}
Cell::~Cell(){}

int Cell::getNumbPred(){return m_nPredator;}
int Cell::getNumbPrey(){return m_nPrey;}

void Cell::setNumbPred(int numberPred){m_nPredator = numberPred;}
void Cell::setNumbPrey(int numberPrey){m_nPrey     = numberPrey;}