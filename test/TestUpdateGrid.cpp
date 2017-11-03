#include "TestUpdateGrid.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(TestUpdateGrid);

void TestUpdateGrid::setUp()
{
    // All test landscapes will be of 3x3.
    const int columns = 2;
    const int rows    = 1;

    // 0 in input corresponds to wet cell, 1 corresponds to dry.
    const int wet = 0;
    const int dry = 1;

    int** wetLandscape          = new int*[columns];
    int** zeroDensityLandscape  = new int*[columns];
    int** realisticLandscape    = new int*[columns];
     
    for(int i = 0; i < columns; ++i)
    {
        wetLandscape[i]         = new int[rows];
        zeroDensityLandscape[i] = new int[rows];
        realisticLandscape[i]   = new int[rows]; 
    }

    
    for(int i = 0; i < columns; ++i)
    {
        for(int j = 0; j < rows; ++j)
        {   
            // Wet landscape needs to be wet everywhere.
            wetLandscape[i][j] = wet;

            // Zero density landscape will be dry everywhere, since we are testing densities 
            // at zero, and they will always be zero in wet cells anyway.
            zeroDensityLandscape[i][j] = dry;

            // In the realistic landscape we will set both cells to be dry.
           realisticLandscape[i][j] = dry;
        }   

    }  






    wetGrid         = new Grid(columns, rows, wetLandscape);
    zeroDensityGrid = new Grid(columns, rows, zeroDensityLandscape);
    realisticGrid   = new Grid(columns, rows, realisticLandscape);



    for(int i = 0; i < columns; ++i)
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

    for(int i = 1; i <= wetGrid->getColumns(); ++i)
    {
        for(int j = 1; j <= wetGrid->getRows(); ++j)
            {
                // Since the whole grid is wet, every grid cell should have zero predator density... 
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, (*wetGrid)(i, j).getPredDensity(), precision);
                
                // ... and zero prey density after each update.
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, (*wetGrid)(i, j).getPreyDensity(), precision);   
            }
        }
}


void TestUpdateGrid::testZeroDensityGridUpdated()
{
    
    updateGrid(*zeroDensityGrid, r, a, b, m, k, l, deltaT);

    for(int i = 1; i <= zeroDensityGrid->getColumns(); ++i)
        {
            for(int j = 1; j <= zeroDensityGrid->getRows(); ++j)
            {
                // Since the grid intially had zero density, every grid cell should still have zero predator density... 
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, (*wetGrid)(i, j).getPredDensity(), precision);
                
                // ... and zero prey density after each update.
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, (*wetGrid)(i, j).getPreyDensity(), precision);
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
     for(int i = 0; i < numberColumns; ++i)
     {
        landStates[i] = new int[numberRows]; 
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