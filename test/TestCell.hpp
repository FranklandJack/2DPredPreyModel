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

        /// Add test method to test the predator density setter.
        CPPUNIT_TEST(testSetPredDensity);

        // Add test method to test the prey density setter.
        CPPUNIT_TEST(testSetPreyDensity);

        // Add test method to test the state setter.
        CPPUNIT_TEST(testSetState);

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

        // Test method testGetPredatorDensity
        void testGetPredDensity();
    
        // Test method testGetPreyDensity
        void testGetPreyDensity();

        // Test method testGetState
        void testGetState();

        // Test method testSetPredatorDensity
        void testSetPredDensity();

        // Test method testSetPreyDensity
        void testSetPreyDensity();

        // Test method testSetState
        void testSetState();


       //new tests
        void testConstructorWet();
        void testConstructorDry();
        void testConstructorDryNegative();

    private:

    /// Three test cases for the fixture. 

    /// Test case for a dry cell with positive predator and prey densities. 
    Cell *dryPosDens;

    /// Test case for a wet cell with positive predator and prey densities. 
    Cell *wetPosDens;
    
    /// Test case for a dry cell with negative densities.
    Cell *dryNegDens;

    /// Test case for a wet cell with negative densities. 
    Cell *wetNegDens;


    // Delta value within which doubles are considered equal.
    const double precision = 0.0001;
};

#endif /* TestCell_hpp */
