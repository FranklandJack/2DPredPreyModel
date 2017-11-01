#include "TestGrid.hpp"
const double precision=0.0001;

CPPUNIT_TEST_SUITE_REGISTRATION(TestGrid);


void 
TestGrid::testConstructor()
{
        const int landStates [2][3]={{0,1,1},{0,1,1}};
        const int **inputStates = &landStates;
        const int numberColumns = 2;
        const int numberRows = 3;
        Grid NewGrid(numberColumns,numberRows,**inputStates);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( numberColumns, NewGrid.getColumns(), precision);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( numberRows, NewGrid.getRows(), precision);
        //Is there an easy way to check the cell states of NewGird?
/*      for(int i=0; i<=1; ++i){
              for(int j=0; j<=2; ++j){
                 CPPUNIT_ASSERT_EQUAL( landStates[i][j], NewGrid.?());
              }
        }
  */
  }


