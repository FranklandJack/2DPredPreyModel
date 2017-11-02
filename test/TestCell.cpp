#include "TestCell.hpp"
CPPUNIT_TEST_SUITE_REGISTRATION(TestCell);

void TestCell::setUp()
{

    dryPosDens = new Cell(Cell::Dry, 2.0, 1.0);
    wetPosDens = new Cell(Cell::Wet, 1.0, 2.0);
    dryNegDens = new Cell(Cell::Dry, -2.0, -1.0);
    wetNegDens = new Cell(Cell::Wet, -1.0, -2.0);

}

void TestCell::tearDown()
{

    delete dryPosDens;
    delete wetPosDens;
    delete wetNegDens;

}

void TestCell::testInit()
{

    CPPUNIT_ASSERT(Cell::Wet == wetNegDens->m_state);

}

void TestCell::testGetPredDensity()
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, dryPosDens->getPredDensity(), precision);
}

void TestCell::testGetPreyDensity()
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dryPosDens->getPreyDensity(), precision);
}

void TestCell::testGetState()
{
    CPPUNIT_ASSERT(Cell::Dry == dryPosDens->getState());
}

void TestCell::testSetState()
{

    wetPosDens->setState(Cell::Dry);
    CPPUNIT_ASSERT(Cell::Dry == wetPosDens->m_state);

}

void TestCell::testSetPreyDensity()
{
    dryPosDens->setPreyDensity(5.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, dryPosDens->m_preyDensity, precision);
}

void TestCell::testSetPredDensity()
{
    dryPosDens->setPredDensity(5.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, dryPosDens->m_predDensity, precision);

}

void TestCell::testConstructorWet()
{
        const Cell::State stateWet = Cell::Wet;
        const double predDensityWet = 0.0;
        const double preyDensityWet = 0.0;
        Cell CellWet(stateWet,predDensityWet,preyDensityWet);
        CPPUNIT_ASSERT_EQUAL( stateWet, CellWet.getState());
        CPPUNIT_ASSERT_DOUBLES_EQUAL( predDensityWet, CellWet.getPredDensity(), precision);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( preyDensityWet, CellWet.getPreyDensity(), precision);
}

void TestCell::testConstructorDry()
{
    const Cell::State stateDry = Cell::Dry;
    const double predDensityDry = 3.45;
    const double preyDensityDry = 1.23;
    Cell CellDry(stateDry,predDensityDry,preyDensityDry);
    CPPUNIT_ASSERT_EQUAL( stateDry, CellDry.getState());
    CPPUNIT_ASSERT_DOUBLES_EQUAL( predDensityDry, CellDry.getPredDensity(), precision);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( preyDensityDry, CellDry.getPreyDensity(), precision);
}

void TestCell::testConstructorDryNegative()
{
    const Cell::State stateDryNegative = Cell::Dry;
    const double predDensityDryNegative = -1.23;
    const double preyDensityDryNegative = -4.56;
    const double densityWet = 0.0;

    Cell CellDryNegative(stateDryNegative,predDensityDryNegative,preyDensityDryNegative);

    CPPUNIT_ASSERT_EQUAL( stateDryNegative, CellDryNegative.getState());
    CPPUNIT_ASSERT_DOUBLES_EQUAL( densityWet, CellDryNegative.getPredDensity(), precision);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( densityWet, CellDryNegative.getPreyDensity(), precision );
}



