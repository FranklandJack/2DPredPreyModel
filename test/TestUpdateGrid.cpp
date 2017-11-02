#include "TestUpdateGrid.hpp"
const double precision=0.0001;
const int    numberTestIterations = 10;

CPPUNIT_TEST_SUITE_REGISTRATION(TestUpdateGrid);

void TestUpdateGrid::setUp()
{
    // All test landscapes will be of 3x3.
    const int columnCount = 3;
    const int rowCount    = 3;

    // 0 in input corresponds to wet cell, 1 corresponds to dry.
    const int wet = 0;
    const int dry = 1;

    int** wetLandscape;
    wetLandscape = new int*[columnCount];
    for(int i = 0; i < columnCount; ++i)
    {
        wetLandscape[i] = new int[rowCount]; 
    }


    for(int columnIndex = 0; columnIndex < columnCount; ++columnIndex)
    {
        for(int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
        {
            wetLandscape[columnIndex][rowIndex] = 0;
        }   

    }          




    wetGrid         = new Grid(columnCount, rowCount, wetLandscape);
    zeroDensityGrid = new Grid();
    realisticGrid   = new Grid();



    for(int i = 0; i < columnCount; ++i)
    {
        delete [] wetLandscape[i];
    }

    delete [] wetLandscape;


    
    

}

void TestUpdateGrid::tearDown()
{

    delete wetGrid;
    delete zeroDensityGrid;
    delete realisticGrid;

}




void TestUpdateGrid::testWetGridUpdated()
{
    // Value will change if the function fails to update correctly on any iteration.
    bool hasFailed = false;

    updateGrid(*wetGrid, r, a, b, m, k, l, deltaT);

    // Do the specified number of iterations, checking on each one that the densities match the expected values.
    for(int iteration = 1; iteration <= numberTestIterations; ++iteration)
    {

        for(int columnIndex = 1; columnIndex <= wetGrid->getColumns(); ++columnIndex)
        {
            for(int rowIndex = 1; rowIndex <= wetGrid->getRows(); ++rowIndex)
            {
                // Since the whole grid is wet, every grid cell should have zero predator and prey density.
                if(0.0 != (*wetGrid)(columnIndex, rowIndex).getPredDensity() || 0.0 != (*wetGrid)(columnIndex, rowIndex).getPreyDensity())
                {
                    hasFailed = true;
                }
            }
        }

    }
    

    CPPUNIT_ASSERT(!hasFailed);
}