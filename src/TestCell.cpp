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
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, a->m_preyDensity, 0.0001);
}

void TestCell::testSetPredDensity()
{
    a->setPredDensity(5.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, a->m_predDensity, 0.0001);

}
void 
TestCell::testConstructorWet()
{
  	const Cell::State stateWet = Cell::Wet;
	const double predDensityWet = 0.0;
	const double preyDensityWet = 0.0;
	Cell CellWet(stateWet,predDensityWet,preyDensityWet);
	CPPUNIT_ASSERT_EQUAL( stateWet, CellWet.getState() );
    CPPUNIT_ASSERT_EQUAL( predDensityWet, CellWet.getPredDensity() );
	CPPUNIT_ASSERT_EQUAL( preyDensityWet, CellWet.getPreyDensity() );
  }
void 
TestCell::testConstructorDry()
{
  	const Cell::State stateDry = Cell::Dry;
	const double predDensityDry = 3.45;
	const double preyDensityDry = 1.23;
	Cell CellDry(stateDry,predDensityDry,preyDensityDry);
	CPPUNIT_ASSERT_EQUAL( stateDry, CellDry.getState() );
    CPPUNIT_ASSERT_EQUAL( predDensityDry, CellDry.getPredDensity() );
	CPPUNIT_ASSERT_EQUAL( preyDensityDry, CellDry.getPreyDensity() );
  }
void 
TestCell::testConstructorDryNegative()
{
  	const Cell::State stateDryNegative = Cell::Dry;
	const double predDensityDryNegative = -1.23;
	const double preyDensityDryNegative = -4.56;
	Cell CellDryNegative(stateDryNegative,predDensityDryNegative,preyDensityDryNegative);
	CPPUNIT_ASSERT_EQUAL( stateDryNegative, CellDryNegative.getState() );
    CPPUNIT_ASSERT_EQUAL( 0.0, CellDryNegative.getPredDensity() );
	CPPUNIT_ASSERT_EQUAL( 0.0, CellDryNegative.getPreyDensity() );
  }



