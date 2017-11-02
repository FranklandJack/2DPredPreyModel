#include "TestGrid.hpp"
//const double precision = 0.0001;

CPPUNIT_TEST_SUITE_REGISTRATION(TestGrid);

void TestGrid::setUp()
{

    
}

void TestGrid::tearDown()
{

    

}
//test for constructor Grid::Grid()
void TestGrid::testConstructor1()
{
    const int numberColumns = 0;
    const int numberRows = 0;
    Grid initialGrid;
    CPPUNIT_ASSERT_EQUAL(numberColumns, initialGrid.getColumns());
    CPPUNIT_ASSERT_EQUAL(numberRows, initialGrid.getRows());
}

//test for constructor Grid::Grid(int columns, int rows , int ** const data)
void TestGrid::testConstructor2()
{
  
    const int numberColumns = 2;
    const int numberRows = 3;

    int** landStates = new int*[numberColumns];
    for(int columnIndex = 0; columnIndex < numberColumns; ++columnIndex)
    {
        landStates[columnIndex] = new int[numberRows]; 
    }

    landStates[0][0] = 1;
    landStates[0][1] = 0;
    landStates[0][2] = 1;
    landStates[1][0] = 0;
    landStates[1][1] = 1;
    landStates[1][2] = 1;

    
    
    const Cell::State stateWet = Cell::Wet;
    const Cell::State stateDry = Cell::Dry;
    const Cell::State cellStates [2] [3]={ {stateDry, stateWet, stateDry}, {stateWet, stateDry, stateDry} };
	
    Grid newGrid(numberColumns, numberRows, landStates);

    for(int columnIndex = 0; columnIndex < numberColumns; ++columnIndex)
    {
      delete [] landStates[columnIndex];
    } 
    delete [] landStates;  

    CPPUNIT_ASSERT_EQUAL(numberColumns, newGrid.getColumns());
    CPPUNIT_ASSERT_EQUAL(numberRows, newGrid.getRows());

    for(int i=1; i<numberRows; ++i)
    {
       for(int j=1; j<numberColumns; ++j)
       {
          
           CPPUNIT_ASSERT_EQUAL(cellStates[j][i], newGrid(j+1,i+1).getState());
       }
    }
    
    //tests for the halo cells states - checking if the cell states are Wet
     for(int i=0; i<=numberColumns; ++i)
     {
          CPPUNIT_ASSERT_EQUAL(stateWet, newGrid(i,numberRows+1).getState());
          CPPUNIT_ASSERT_EQUAL(stateWet, newGrid(i,0).getState());
     }
   //the states of the 4 egde cells have been checked so j=1; j<numberColumns
    for(int j=1; j<numberRows; ++j)
    {
        CPPUNIT_ASSERT_EQUAL(stateWet, newGrid(0,j).getState());
        CPPUNIT_ASSERT_EQUAL(stateWet, newGrid(numberColumns+1,j).getState());
    }
    
  }

