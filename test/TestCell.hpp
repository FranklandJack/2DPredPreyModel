#ifndef TestCell_hpp
#define TestCell_hpp

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include "Cell.hpp"
/*
*
* A test case that is designed to produce
* example errors and failures
*
*/
class TestCell : public CPPUNIT_NS::TestFixture
{

        /// Establish the test suit of TestCell
        CPPUNIT_TEST_SUITE(TestCell);

        // Add test method testInit
        CPPUNIT_TEST(testInit);

        /// Add test method to test the predator density getter.
        CPPUNIT_TEST(testGetPredDensity);

        /// Add test method to test the prey density getter.
        CPPUNIT_TEST(testGetPreyDensity);

        /// Add test metho to test the state getter.
        CPPUNIT_TEST(testGetState);

        /// Add test method to test the predator density setter for positive densities.
        CPPUNIT_TEST(testSetPosPredDensity);

        /// Add test method to test the prey density setter for positive densities.
        CPPUNIT_TEST(testSetPosPreyDensity);

        /// Add test method to test the predator density setter for negative densities.
        CPPUNIT_TEST(testSetNegPredDensity);

        // Add test method to test the prey density setter for negative densities.
        CPPUNIT_TEST(testSetNegPreyDensity);

        /// Add test method to test the state setter for dry states.
        CPPUNIT_TEST(testSetStateDry);

        /// Add test method to test the state setter for wet states.
        CPPUNIT_TEST(testSetStateWet);

        //new tests for check
        CPPUNIT_TEST( testConstructorWet );
        CPPUNIT_TEST( testConstructorDry );
        CPPUNIT_TEST( testConstructorDryNegative );
        // Finish the process
        CPPUNIT_TEST_SUITE_END();

    public:

        // Overide setUp(), init data etc
        void setUp();

        // Overide tearDown(), free allocated memory,etc
        void tearDown();

    protected:

        // Test method testInit
        void testInit();

        /**
         *
         * Test method for Cell::getPredDensity() method.
         *
         * Tests that the getter returns the correct predator density for the cell.
         *
         */
        void testGetPredDensity();
    

        /**
         *
         * Test method for Cell::getPreyDensity() method.
         *
         * Tests that the getter returns the correct prey density for the cell.
         *
         */
        void testGetPreyDensity();

        /**
         *
         * Test method for Cell::getState() method.
         *
         * Tests that the getter returns the state for the cell.
         *
         */
        void testGetState();

        /**
         *
         * Test method for Cell::setPredDensity() method.
         *
         * Tests that the setter sets the correct density for positive arguments.
         *
         */
        void testSetPosPredDensity();


        /**
         *
         * Test method for Cell::setPreyDensity() method.
         *
         * Tests that the setter sets the correct density for positive arguments.
         *
         */
        void testSetPosPreyDensity();


        /**
         *
         * Test method for Cell::setPredDensity() method.
         *
         * Tests that the setter sets the correct density for negative arguments.
         *
         */
        void testSetNegPredDensity();


        /**
         *
         * Test method for Cell::setPreyDensity() method.
         *
         * Tests that the setter sets the correct density for negative arguments.
         *
         */
        void testSetNegPreyDensity();


        /**
         *
         * Test method for Cell::setState() method.
         *
         * Tests that the setter sets the correct state for Cell::Dry arguments.
         *
         */
        void testSetStateDry();

        /**
         *
         * Test method for Cell::setState() method.
         *
         * Tests that the setter sets the state for Cell::Wet arguments.
         *
         */ 
        void testSetStateWet();


       //new tests
        void testConstructorWet();
        void testConstructorDry();
        void testConstructorDryNegative();

    private:

        /// Test case for a dry cell with positive predator and prey densities. 
        Cell *dryPosDens;

        /// Test case for a wet cell with positive predator and prey densities. 
        Cell *wetPosDens;
    
        /// Test case for a dry cell with negative densities.
        Cell *dryNegDens;

        /// Test case for a wet cell with negative densities. 
        Cell *wetNegDens;


        /// Delta value within which doubles are considered equal.
        const double precision = 0.0001;
};

#endif /* TestCell_hpp */
