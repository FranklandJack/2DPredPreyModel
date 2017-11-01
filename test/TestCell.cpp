#include "TestCell.hpp"
const double precision=0.0001;
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
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, a->getPredDensity(), precision);
}

void TestCell::testGetPreyDensity()
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, a->getPreyDensity(), precision);
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
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, a->m_preyDensity, precision);
}

void TestCell::testSetPredDensity()
{
    a->setPredDensity(5.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, a->m_predDensity, precision);

}
void 
TestCell::testConstructorWet()
{
        const Cell::State stateWet = Cell::Wet;
        const double predDensityWet = 0.0;
        const double preyDensityWet = 0.0;
        Cell CellWet(stateWet,predDensityWet,preyDensityWet);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( stateWet, CellWet.getState(), precision);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( predDensityWet, CellWet.getPredDensity(), precision);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( preyDensityWet, CellWet.getPreyDensity(), precision);
  }
void 
TestCell::testConstructorDry()
{
  	const Cell::State stateDry = Cell::Dry;
	const double predDensityDry = 3.45;
	const double preyDensityDry = 1.23;
	Cell CellDry(stateDry,predDensityDry,preyDensityDry);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( stateDry, CellDry.getState(), precision);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( predDensityDry, CellDry.getPredDensity(), precision);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( preyDensityDry, CellDry.getPreyDensity(), precision);
  }
void 
TestCell::testConstructorDryNegative()
{
  const Cell::State stateDryNegative = Cell::Dry;
        const double predDensityDryNegative = -1.23;
        const double preyDensityDryNegative = -4.56;
	const double densityWet = 0.0;

        Cell CellDryNegative(stateDryNegative,predDensityDryNegative,preyDensityDryNegative);

        CPPUNIT_ASSERT_DOUBLES_EQUAL( stateDryNegative, CellDryNegative.getState(), precision);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( densityWet, CellDryNegative.getPredDensity(), precision);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( densityWet, CellDryNegative.getPreyDensity(), precision );
}


