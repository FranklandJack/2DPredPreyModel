#include "TestCell.hpp"
CPPUNIT_TEST_SUITE_REGISTRATION(TestCell);

void TestCell::setUp()
{

    dryPosDensCell      = new Cell(Cell::Dry, 2.0, 1.0);
    wetPosDensCell      = new Cell(Cell::Wet, 1.0, 2.0);
    dryNegPredDensCell  = new Cell(Cell::Dry, -2.0, 1.0);
    dryNegPreyDensCell  = new Cell(Cell::Dry, 1.0, -2.0);
    defaultCell         = new Cell();

}

void TestCell::tearDown()
{

    delete dryPosDensCell;
    delete wetPosDensCell;
    delete dryNegPredDensCell;
    delete dryNegPreyDensCell;
    delete defaultCell;

}

void TestCell::testConstructorWet()
{
        // Cell should be wet.
        CPPUNIT_ASSERT(Cell::Wet == wetPosDensCell->m_state);

        // Predator density should be zero.
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, wetPosDensCell->m_predDensity, precision);

        // Prey density should be zero.
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, wetPosDensCell->m_preyDensity, precision);
}

void TestCell::testConstructorDry()
{
        // Cell should be dry.
        CPPUNIT_ASSERT(Cell::Dry == dryPosDensCell->m_state);

        // Predator density should be set to the value given to the constructor.
        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, dryPosDensCell->m_predDensity, precision);

        // Prey density should be set to the value given to the constructor.
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dryPosDensCell->m_preyDensity, precision);
}

void TestCell::testConstructorDryNegPredDensity()
{
    // Cell should be dry.
    CPPUNIT_ASSERT(Cell::Dry == dryNegPredDensCell->m_state);

    // Predator density should be set to 0 since the value given to the constructor was negative.
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dryNegPredDensCell->m_predDensity, precision);

    // Prey density should be set to the value given to the constructor.
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dryNegPredDensCell->m_preyDensity, precision);
}

void TestCell::testConstructorDryNegPreyDensity()
{
    // Cell should be dry.
    CPPUNIT_ASSERT(Cell::Dry == dryNegPreyDensCell->m_state);

    // Predator density should be set to the value given to the constructor.
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dryNegPreyDensCell->m_predDensity, precision);

    // Prey density should be set to 0 since the value given to the constructor was negative.
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dryNegPreyDensCell->m_preyDensity, precision);

}


        
void TestCell::testConstructorDefault()
{
    // Cell should be wet by default.
    CPPUNIT_ASSERT(Cell::Wet == defaultCell->m_state);

    // Predator density should be zero by default.
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, defaultCell->m_predDensity, precision);

    // Prey density should be zero by default.
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, defaultCell->m_preyDensity, precision);

}



void TestCell::testGetPredDensity()
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, dryPosDensCell->getPredDensity(), precision);
}

void TestCell::testGetPreyDensity()
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dryPosDensCell->getPreyDensity(), precision);
}

void TestCell::testGetState()
{
    CPPUNIT_ASSERT(Cell::Dry == dryPosDensCell->getState());
}

void TestCell::testSetPosPredDensity()
{
    dryPosDensCell->setPredDensity(5.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, dryPosDensCell->m_predDensity, precision);

}



void TestCell::testSetPosPreyDensity()
{
    dryPosDensCell->setPreyDensity(5.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, dryPosDensCell->m_preyDensity, precision);
}

void TestCell::testSetNegPredDensity()
{
    dryPosDensCell->setPredDensity(-5.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,dryPosDensCell->m_predDensity, precision);
}

void TestCell::testSetNegPreyDensity()
{
    dryPosDensCell->setPreyDensity(-5.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dryPosDensCell->m_preyDensity, precision);
}


void TestCell::testSetStateDry()
{

    wetPosDensCell->setState(Cell::Dry);
    CPPUNIT_ASSERT(Cell::Dry == wetPosDensCell->m_state);

}

void TestCell::testSetStateWet()
{
    dryPosDensCell->setState(Cell::Wet);
    CPPUNIT_ASSERT(Cell::Wet == dryPosDensCell->m_state);

}











