#include "TestUpdateGrid.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(TestUpdateGrid);

void TestUpdateGrid::setUp()
{
    // All test landscapes will be of 3x3.
    const int columnCount = 3;
    const int rowCount    = 3;

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

            // In the realistic landscape we will set the (1,1) and (2,1) cells to be wet, since this is a realistic scenario.
            if((1 == columnIndex || 2 == columnIndex) && 1 == rowIndex)
            {
                realisticLandscape[columnIndex][rowIndex] = wet;
            }

            else
            {
                realisticLandscape[columnIndex][rowIndex] = dry;
            }
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
                // Since the whole grid is wet, every grid cell should have zero predator density... 
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, (*wetGrid)(columnIndex, rowIndex).getPredDensity(), precision);
                
                // ... and zero prey density.
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, (*wetGrid)(columnIndex, rowIndex).getPreyDensity(), precision);
                
            }
        }

    }
    

    CPPUNIT_ASSERT(!hasFailed);
}


void TestUpdateGrid::testZeroDensityGridUpdated()
{
    // Value will change if the function fails to update correctly on any iteration.
    bool hasFailed = false;

    updateGrid(*zeroDensityGrid, r, a, b, m, k, l, deltaT);

    // Do the specified number of iterations, checking on each one that the densities match the expected values.
    for(int iteration = 1; iteration <= numberTestIterations; ++iteration)
    {

        for(int columnIndex = 1; columnIndex <= zeroDensityGrid->getColumns(); ++columnIndex)
        {
            for(int rowIndex = 1; rowIndex <= zeroDensityGrid->getRows(); ++rowIndex)
            {
                // Since the grid intially had zero density, every grid cell should still have zero predator and prey density after each update. 
                if(0.0 != (*zeroDensityGrid)(columnIndex, rowIndex).getPredDensity() || 0.0 != (*zeroDensityGrid)(columnIndex, rowIndex).getPreyDensity())
                {
                    hasFailed = true;
                }
            }
        }

    }
    

    CPPUNIT_ASSERT(!hasFailed);
}


void TestUpdateGrid::testRealisticGridUpdated()
{
    CPPUNIT_ASSERT(true);
}

void 
TestGrid::updateFunctionGrid()
{
     const double r = 0.02;
	 const double a = 0.04;
	 const double b = 0.6;
	 const double m = 0.3;
	 const double k = 0.4;
	 const double l = 0.15;
	 const double deltaT = 0.8;

	 const int numberColumns = 2;
     const int numberRows = 1;
     const int landStates [numberColumns][numberRows]={{1},{1}};
     const Cell::State stateWet = Cell::Wet;
     const Cell::State stateDry = Cell::Dry;
     const int cellStates [numberColumns][numberRows]={{stateDry},{stateDry}};
	 const double predDensityWet = 0.0;
     const double preyDensityWet = 0.0;
     const double preyDensityDry1 = 7.96;
	 const double predDensityDry1 = 2.38;
	 const double preyDensityDry2 = 5.28;
	 const double predDensityDry2 = 6.34;
     

	 //I have to change that!!!!
     const int **inputStates = &landStates;
     Grid oldGrid(numberColumns, numberRows, inputStates);

	 oldGrid(numberColumns-1, numberRows).setPreyDensity(preyDensityDry1);
	 oldGrid(numberColumns-1, numberRows).setPredDensity(predDensityDry1);
	 oldGrid(numberColumns, numberRows).setPreyDensity(preyDensityDry2);
	 oldGrid(numberColumns, numberRows).setPredDensity(predDensityDry2);

	 double newPreyDensity1 = preyDensityDry1 + deltaT * ( r * preyDensityDry1 - a * preyDensityDry1 * predDensityDry1 +
                               k * ( preyDensityDry2 - preyDensityDry1 ) );
	 
     double newPredDensity1 = predDensityDry1 + deltaT * ( b * preyDensityDry1 * predDensityDry1 - m * predDensityDry1 +
                               l * ( predDensityDry2 - predDensityDry1)  );

	 double newPreyDensity2 = preyDensityDry2 + deltaT * ( r * preyDensityDry2 - a * preyDensityDry2 * predDensityDry2 +
                               k * ( preyDensityDry1 - preyDensityDry2 ) );

	 double newPredDensity2 = predDensityDry2 + deltaT * ( b * preyDensityDry2 * predDensityDry2 - m * predDensityDry2 +
                               l * ( predDensityDry1 - predDensityDry2)  );

	 newGrid = updateGrid(oldGrid, r, a, b, m, k, l, deltaT);

	 CPPUNIT_ASSERT_DOUBLES_EQUAL( newPreyDensity1, newGrid(numberColumns-1, numberRows).getPreyDensity() , precision);
	 CPPUNIT_ASSERT_DOUBLES_EQUAL( newPredDensity1, newGrid(numberColumns-1, numberRows).getPredDensity() , precision);
	 CPPUNIT_ASSERT_DOUBLES_EQUAL( newPreyDensity2, newGrid(numberColumns, numberRows).getPreyDensity() , precision);
	 CPPUNIT_ASSERT_DOUBLES_EQUAL( newPredDensity2, newGrid(numberColumns, numberRows).getPredDensity() , precision);
}


