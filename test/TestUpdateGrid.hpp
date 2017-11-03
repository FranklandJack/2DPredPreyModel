#ifndef TestUpdateGrid_hpp
#define TestUpdateGrid_hpp

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include "Grid.hpp"
#include "updateGrid.hpp"

/**
 *
 * \file
 *
 * \class TestUpdateGrid
 *
 * \brief Tests the updateGrid function.  
 *
 * This test class is written using the CppUnit test framework and tests the function that updates the grid.
 *
 *
 */
class TestUpdateGrid : public CPPUNIT_NS::TestFixture
{

        /// Establish the test suit of TestCell
        CPPUNIT_TEST_SUITE(TestUpdateGrid);

        /// Add test method to test the grid updates correctly for a grid that is wet everywhere.
        CPPUNIT_TEST(testWetGridUpdated);

        /// Add test method to test the grid updates correctly for a grid that initially has zero density everywhere.
        CPPUNIT_TEST(testZeroDensityGridUpdated);

        /// Add test method to test the grid updates correctly for a grid that has realistic (non-zero densities).
        CPPUNIT_TEST(testRealisticGridUpdated);
        
        //CPPUNIT_TEST(updateFunctionGrid);

        /// Finish the process
        CPPUNIT_TEST_SUITE_END();

    public:

        

        /// Override setUp(), initialise test cases etc.
        void setUp();

        /// Override tearDown(), free allocated memory in test cases, etc.
        void tearDown();
        
     

    protected:

        /**
         *
         * \brief Test method for updateGrid() function.
         *
         * Tests that the function correctly updates a grid that is wet everywhere.
         *
         */
        void testWetGridUpdated();


        /**
         *
         * \brief Test method for updateGrid() function.
         *
         * Tests that the function correctly updates a grid that initially has zero densities everywhere.
         *
         */
        void testZeroDensityGridUpdated();


        /**
         *
         * \brief Test method for updateGrid() function.
         *
         * Tests that the function correctly updates a grid that initially has non-zero densities.
         *
         */
        void testRealisticGridUpdated();

        // A different name for testRealisticGridUpdated()
        //void updateFunctionGrid();

    
    private:

    /// Test parameters for updating the grid will just be default values of 1 for everything since we can easily check these are correct.
    const int r = 1;
    const int a = 1;
    const int b = 1;
    const int m = 1;
    const int k = 1;
    const int l = 1;
    const double deltaT = 1.0;

  

    /// First test case is a grid that is wet everywhere, so the densities should be zero everywhere even after updating.
    Grid *wetGrid;

    /// Second test case is a grid with initial predator and prey densities of zero everywhere, this system should stay at zero everywhere, even after updating.
    Grid *zeroDensityGrid;

    /// Third test case is a realistic grid which will have density values set after it is constructed and then its densities after each iteration will be compared to the correct values.
    Grid *realisticGrid;

    /// Delta value within which doubles are considered equal.
    const double precision = 0.0001;
};

#endif /* TestUpdateGrid_hpp */
