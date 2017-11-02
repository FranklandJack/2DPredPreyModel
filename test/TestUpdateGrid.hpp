#ifndef TestUpdateGrid_hpp
#define TestUpdateGrid_hpp

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include "Grid.hpp"
#include "updateGrid.hpp"
/*
*
* A test case that is designed to produce
* example errors and failures
*
*/
class TestUpdateGrid : public CPPUNIT_NS::TestFixture
{

        // Establish the test suit of TestCell
        CPPUNIT_TEST_SUITE(TestUpdateGrid);

        CPPUNIT_TEST(TestUpdated);

        // Finish the process
        CPPUNIT_TEST_SUITE_END();

    public:

        // Precision value for comparing doubles in any assert statments.
        const double precision = 0.0001;

        // Overide setUp(), init data etc
        void setUp();

        // Overide tearDown(), free allocated memory,etc
        void tearDown();
        
     

    protected:

        void TestUpdated();

        

        

    private:

        // Three instances of Grid for test
    Grid *emptyGrid , *zeroDensityGrid, *realisticGrid;
};

#endif /* TestUpdateGrid_hpp */