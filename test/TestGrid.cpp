#include "TestGrid.hpp"
//const double precision=0.0001;

CPPUNIT_TEST_SUITE_REGISTRATION(TestGrid);

void TestGrid::setUp()
{

    
}

void TestGrid::tearDown()
{

    

}

void 
TestGrid::testConstructor()
{
  /*
	const int numberColumns = 2;
	const int numberRows = 3;
	const int landStates [numberColumns][numberRows]={{0,1,1},{0,1,1}};
	const int **inputStates = &landStates;
	const Cell::State stateWet = Cell::Wet;
	const Cell::State stateDry = Cell::Dry;
  	const int cellStates [numberColumns][numberRows]={{stateWet,stateDry,stateDry},{stateWet,stateDry,stateDry}};
	
	Grid NewGrid(numberColumns, numberRows, inputStates);

	CPPUNIT_ASSERT_EQUAL(numberColumns, NewGrid.getColumns());
    CPPUNIT_ASSERT_EQUAL(numberRows, NewGrid.getRows());

    for(int i=0; i<numberRows; ++i){
        for(int j=0; j<numberColumns; ++j){
            CPPUNIT_ASSERT_EQUAL(cellStates[i][j], NewGrid.getCellState(i+1,j+1));
       }
    }
    //tests for the halo cells states - checking if the cell states are Wet
     for(int i=0; i<=numberRows; ++i){
          CPPUNIT_ASSERT_EQUAL(stateWet, NewGrid.getCellState(i,numberColumns));
          CPPUNIT_ASSERT_EQUAL(stateWet, NewGrid.getCellState(i,0));
     }
   //the states of the 4 egde cells have been checked so j=1; j<numberColumns
    for(int j=1; j<numberColumns; ++j){
        CPPUNIT_ASSERT_EQUAL(stateWet, NewGrid.getCellState(0,j));
        CPPUNIT_ASSERT_EQUAL(stateWet, NewGrid.getCellState(numberRows,j));
    }
    */
  }

