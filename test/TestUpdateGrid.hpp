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

        CPPUNIT_TEST(testWetGridUpdated);

        CPPUNIT_TEST(testZeroDensityGridUpdated);

        CPPUNIT_TEST(testRealisticGridUpdated);

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

        // Test to see whether a grid that is wet everywhere remains at zero density everywhere.
        void testWetGridUpdated();


        // Test to see whether a grid that initially has zero density everywhere stays at zero density after updating.
        void testZeroDensityGridUpdated();


        // Test to see whether a realistic grid with non-zero densities updates as expected. 
        void testRealisticGridUpdated();



    
    private:

    // Test parameters for updating the grid will just be default values of 1 for everything since we can easily check these are correct.
    const int r = 1;
    const int a = 1;
    const int b = 1;
    const int m = 1;
    const int k = 1;
    const int l = 1;
    const double deltaT = 1.0;

    // Three instances of Grid for test

    // First is a grid that is wet everywhere, so the densities should be zero everywhere even after updating.
    Grid *wetGrid;

    // Second is a grid with intial predator and prey densities of zero everywhere, this system should stay at zero everywhere, even after updating.
    Grid *zeroDensityGrid;

    // Third is a realistic grid which will have density values set after it is constructed and then its densities after each iteration will be compared to those
    // calulated by hand.
    Grid *realisticGrid;
};

#endif /* TestUpdateGrid_hpp */