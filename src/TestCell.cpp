#include "TestCell.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestCell);

void TestCell::setUp()
{

    a = new Cell(Cell::Dry, 2.0, 1.0);
    b = new Cell(Cell::Wet, 1.0, 2.0);
    c = new Cell(Cell::Wet, -1.0, -2.0);

}

void TestCell::tearDown()
{

    delete a;
    delete b;
    delete c;

}
/*
void TestCell::testInit()
{

    CPPUNIT_ASSERT(a->realPart==1.0);

}
*/
void TestCell::testGetPredDensity()
{
    CPPUNIT_ASSERT(2.0 == a->getPredDensity());
}

void TestCell::testGetPreyDensity()
{
    CPPUNIT_ASSERT(1.0 == a->getPreyDensity());
}

void TestCell::testGetState()
{
    CPPUNIT_ASSERT(Cell::Dry == a->getState());
}

void TestCell::testSetPreyDensity()
{
    a->setPreyDensity(5.0);
    CPPUNIT_ASSERT(5.0 == b->m_preyDensity);
}

void TestCell::testSetPredDensity()
{
    a->setPredDensity(5.0);
    CPPUNIT_ASSERT(5.0 == b->m_predDensity);

}

void TestCell::testSetState()
{

    a->setState(Cell::Dry);
    CPPUNIT_ASSERT(State::Dry == b->getState());

}

