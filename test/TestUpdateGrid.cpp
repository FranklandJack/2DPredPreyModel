#include "TestUpdateGrid.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(TestUpdateGrid);

void TestUpdateGrid::setUp()
{
    // All test landscapes will be of 3x3.
    const int columnCount = 2;
    const int rowCount    = 1;

    // 0 in input corresponds to wet cell, 1 corresponds to dry.
    const int wet = 0;
    const int dry = 1;

    int** wetLandscape          = new int*[columnCount];
    int** zeroDensityLandscape  = new int*[columnCount];
    int** realisticLandscape    = new int*[columnCount];
     
    for(int i = 0; i < columnCount; ++i)
    {
        wetLandscape[i]         = new int[rowCount];
        zeroDensityLandscape[i] = new int[rowCount];
        realisticLandscape[i]   = new int[rowCount]; 
    }

    
    for(int columnIndex = 0; columnIndex < columnCount; ++columnIndex)
    {
        for(int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
        {   
            // Wet landscape needs to be wet everywhere.
            wetLandscape[columnIndex][rowIndex] = wet;

            // Zero density landscape will be dry everywhere, since we are testing densities 
            // at zero, and they will always be zero in wet cells anyway.
            zeroDensityLandscape[columnIndex][rowIndex] = dry;

            // In the realistic landscape we will set both cells to be dry.
           realisticLandscape[columnIndex][rowIndex] = dry;
        }   

    }  






    wetGrid         = new Grid(columnCount, rowCount, wetLandscape);
    zeroDensityGrid = new Grid(columnCount, rowCount, zeroDensityLandscape);
    realisticGrid   = new Grid(columnCount, rowCount, realisticLandscape);



    for(int i = 0; i < columnCount; ++i)
    {
        delete [] wetLandscape[i];
        delete [] zeroDensityLandscape[i];
        delete [] realisticLandscape[i];
    }

    delete [] wetLandscape;
    delete [] zeroDensityLandscape;
    delete [] realisticLandscape;


    
    

}

void TestUpdateGrid::tearDown()
{

    delete wetGrid;
    delete zeroDensityGrid;
    delete realisticGrid;

}




void TestUpdateGrid::testWetGridUpdated()
{
    updateGrid(*wetGrid, r, a, b, m, k, l, deltaT);

    for(int columnIndex = 1; columnIndex <= wetGrid->getColumns(); ++columnIndex)
    {
        for(int rowIndex = 1; rowIndex <= wetGrid->getRows(); ++rowIndex)
            {
                // Since the whole grid is wet, every grid cell should have zero predator density... 
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, (*wetGrid)(columnIndex, rowIndex).getPredDensity(), precision);
                
                // ... and zero prey density after each update.
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, (*wetGrid)(columnIndex, rowIndex).getPreyDensity(), precision);   
            }
        }
}


void TestUpdateGrid::testZeroDensityGridUpdated()
{
    
    updateGrid(*zeroDensityGrid, r, a, b, m, k, l, deltaT);

    for(int columnIndex = 1; columnIndex <= zeroDensityGrid->getColumns(); ++columnIndex)
        {
            for(int rowIndex = 1; rowIndex <= zeroDensityGrid->getRows(); ++rowIndex)
            {
                // Since the grid intially had zero density, every grid cell should still have zero predator density... 
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, (*wetGrid)(columnIndex, rowIndex).getPredDensity(), precision);
                
                // ... and zero prey density after each update.
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, (*wetGrid)(columnIndex, rowIndex).getPreyDensity(), precision);
            }
        }

}

/*
void TestUpdateGrid::testRealisticGridUpdated()
{
    CPPUNIT_ASSERT(true);
}
*/
void TestUpdateGrid::testRealisticGridUpdated()
{
    
     const int numberColumns = 2;
     const int numberRows = 1;
     const double preyDensityDry1 = 7.96;
     const double predDensityDry1 = 2.38;
     const double preyDensityDry2 = 5.28;
     const double predDensityDry2 = 6.34;
     

	/*
     int** landStates = new int*[numberColumns];
     for(int columnIndex = 0; columnIndex < numberColumns; ++columnIndex)
     {
        landStates[columnIndex] = new int[numberRows]; 
     }
     landStates[0][0] = 1;
     landStates[1][0] = 1;
	
     Grid oldGrid(numberColumns, numberRows, landStates);

     oldGrid(numberColumns-1, numberRows).setPreyDensity(preyDensityDry1);
     oldGrid(numberColumns-1, numberRows).setPredDensity(predDensityDry1);
     oldGrid(numberColumns, numberRows).setPreyDensity(preyDensityDry2);
     oldGrid(numberColumns, numberRows).setPredDensity(predDensityDry2);

    */

    // We can initialise the landscape with some values and explictly calculate the evolution.
    (*realisticGrid)(1, 1).setPredDensity(predDensityDry1);
    (*realisticGrid)(1, 1).setPreyDensity(preyDensityDry1);
    (*realisticGrid)(2, 1).setPredDensity(predDensityDry2);
    (*realisticGrid)(2, 1).setPreyDensity(preyDensityDry2);

    double newPreyDensity1 = preyDensityDry1 + deltaT * ( r * preyDensityDry1 - a * preyDensityDry1 * predDensityDry1 +
                               k * ( preyDensityDry2 - preyDensityDry1 ) );
	 
    double newPredDensity1 = predDensityDry1 + deltaT * ( b * preyDensityDry1 * predDensityDry1 - m * predDensityDry1 +
                               l * ( predDensityDry2 - predDensityDry1)  );

    double newPreyDensity2 = preyDensityDry2 + deltaT * ( r * preyDensityDry2 - a * preyDensityDry2 * predDensityDry2 +
                               k * ( preyDensityDry1 - preyDensityDry2 ) );

    double newPredDensity2 = predDensityDry2 + deltaT * ( b * preyDensityDry2 * predDensityDry2 - m * predDensityDry2 +
                               l * ( predDensityDry1 - predDensityDry2)  );

    Grid newGrid = updateGrid(*realisticGrid, r, a, b, m, k, l, deltaT);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(newPredDensity1, newGrid(1, 1).getPredDensity(), precision);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(newPreyDensity1, newGrid(1, 1).getPreyDensity(), precision);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(newPredDensity2, newGrid(2, 1).getPredDensity(), precision);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(newPreyDensity2, newGrid(2, 1).getPreyDensity(), precision);
     
}