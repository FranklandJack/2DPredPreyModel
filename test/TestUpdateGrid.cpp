#include "TestUpdateGrid.hpp"
const double precision=0.0001;
CPPUNIT_TEST_SUITE_REGISTRATION(TestUpdateGrid);

void TestUpdateGrid::setUp()
{
    // All test landscapes will be of 3x3.
    const int columnCount = 3;
    const int rowCount    = 3;

    // 0 in input corresponds to wet cell, 1 corresponds to dry.
    const int wet = 0;
    const int dry = 1;

    int wetLandscape[columnCount][rowCount] = 
    {
        {wet, wet, wet}, {wet, wet, wet}, {wet, wet, wet}
    }
                                                




    wetGrid         = new Grid(columnCount, rowCount, wetLandscape);
    zeroDensityGrid = new Grid();
    realisticGrid   = new Grid();
    

}

void TestUpdateGrid::tearDown()
{

    delete wetGrid;
    delete zeroDensityGrid;
    delete realisticGrid;

}




void TestUpdateGrid::TestUpdated()
{
    CPPUNIT_ASSERT(true);
}