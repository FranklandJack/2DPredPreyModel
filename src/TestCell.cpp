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

void TestCell::testInit()
{

    CPPUNIT_ASSERT(Cell::Wet == c->m_state);

}

void TestCell::testGetPredDensity()
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, a->getPredDensity(), 0.0001);
}

void TestCell::testGetPreyDensity()
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, a->getPreyDensity(), 0.0001);
}

void TestCell::testGetState()
{
    CPPUNIT_ASSERT(Cell::Dry == a->getState());
}

void TestCell::testSetState()
{

    b->setState(Cell::Wet);
    CPPUNIT_ASSERT(Cell::Dry == b->m_state);

}

void TestCell::testSetPreyDensity()
{
    a->setPreyDensity(5.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, a->getPreyDensity(), 0.0001);
}

void TestCell::testSetPredDensity()
{
    a->setPredDensity(5.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, a->getPredDensity(), 0.0001);

}



