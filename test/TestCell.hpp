#ifndef TestCell_hpp
#define TestCell_hpp

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include "Cell.hpp"

/**
 *
 * \class TestCell
 *
 * \brief Tests the Cell class.  
 *
 * This test class is written using the CppUnit test framework and tests the various methods of the Cell class.
 *
 *
 */
class TestCell : public CPPUNIT_NS::TestFixture
{

        /// Establish the test suit of TestCell
        CPPUNIT_TEST_SUITE(TestCell);

        /// Add test method to test the predator density getter.
        CPPUNIT_TEST(testGetPredDensity);

        /// Add test method to test the prey density getter.
        CPPUNIT_TEST(testGetPreyDensity);

        /// Add test method to test the state getter.
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

        /// Add test method to test whether the constructor creates a wet cell correctly.
        CPPUNIT_TEST(testConstructorWet);

        /// Add test method to test whether the constructor creates a dry cell correctly.
        CPPUNIT_TEST(testConstructorDry);

        /// Add test method to test whether the constructor creates a dry cell correctly when provided with a negative predator density. 
        CPPUNIT_TEST(testConstructorDryNegPredDensity);

        /// Add test method to test whether the constructor creates a dry cell correctly when provided with a negative prey density. 
        CPPUNIT_TEST(testConstructorDryNegPreyDensity);

        /// Add test method to test the default behaviour of the constructor.
        CPPUNIT_TEST(testConstructorDefault);

        /// Finish the process.
        CPPUNIT_TEST_SUITE_END();

    public:

        /// Override setUp(), initialise test cases etc.
        void setUp();

        /// Override tearDown(), free allocated memory in test cases, etc.
        void tearDown();

    protected:



        /**
         *
         * \brief Test method for Cell::getPredDensity() method.
         *
         * Tests that the getter returns the correct predator density for the cell.
         *
         */
        void testGetPredDensity();
    

        /**
         *
         * \brief Test method for Cell::getPreyDensity() method.
         *
         * Tests that the getter returns the correct prey density for the cell.
         *
         */
        void testGetPreyDensity();

        /**
         *
         * \brief Test method for Cell::getState() method.
         *
         * Tests that the getter returns the state for the cell.
         *
         */
        void testGetState();

        /**
         *
         * \brief Test method for Cell::setPredDensity() method.
         *
         * Tests that the setter sets the correct density for positive arguments.
         *
         */
        void testSetPosPredDensity();


        /**
         *
         * \brief Test method for Cell::setPreyDensity() method.
         *
         * Tests that the setter sets the correct density for positive arguments.
         *
         */
        void testSetPosPreyDensity();


        /**
         *
         * \brief Test method for Cell::setPredDensity() method.
         *
         * Tests that the setter sets the correct density for negative arguments.
         *
         */
        void testSetNegPredDensity();


        /**
         *
         * \brief Test method for Cell::setPreyDensity() method.
         *
         * Tests that the setter sets the correct density for negative arguments.
         *
         */
        void testSetNegPreyDensity();


        /**
         *
         * \brief Test method for Cell::setState() method.
         *
         * Tests that the setter sets the correct state for Cell::Dry arguments.
         *
         */
        void testSetStateDry();

        /**
         *
         * \brief Test method for Cell::setState() method.
         *
         * Tests that the setter sets the state for Cell::Wet arguments.
         *
         */ 
        void testSetStateWet();


        /**
         * 
         * \brief Test method for Cell::Cell() method.
         *
         * Tests that the constructor creates a cell with zero densities if it is wet.
         *
         */
        void testConstructorWet();


        /**
         * 
         * \brief Test method for Cell::Cell() method.
         *
         * Tests that the constructor creates a cell with correct densities if it is dry.
         *
         */
        void testConstructorDry();


        /**
         * 
         * \brief Test method for Cell::Cell() method.
         *
         * Tests that the constructor creates a cell with zero predator density if the predator density provided to the constructor 
         * is less than 0.
         *
         */
        void testConstructorDryNegPredDensity();

        /**
         *
         * \brief Test method for Cell::Cell() method.
         *
         * Tests that the constructor creates a cell with zero prey density if the predator density provided to the constructor 
         * is less than 0.
         *
         */
        void testConstructorDryNegPreyDensity();


        /**
         *
         * \brief Test method for Cell::Cell() method.
         *
         * Tests the default behaviour of the constructor i.e. if no arguments provided should create a wet cell with zero densities.
         *
         */
        void testConstructorDefault();

    private:

        /// Test case for a dry cell with positive predator and prey densities. 
        Cell *dryPosDensCell;

        /// Test case for a wet cell with positive predator and prey densities. 
        Cell *wetPosDensCell;

        /// Test case for a dry cell with negative predator density.
        Cell *dryNegPredDensCell;
    
        /// Test case for a dry cell with negative prey density.
        Cell *dryNegPreyDensCell;

        /// Test case for a cell which is constructed via the default constructor.
        Cell *defaultCell;


        /// Delta value within which doubles are considered equal.
        const double precision = 0.0001;

        /// Positive predator density value for initialisation of test case.
        const double posPredDensity = 3.142;

        /// Positive prey density value for initialisation of test case.
        const double posPreyDensity = 2.718;

        /// Negative predator density value for initialisation of test case.
        const double negPredDensity = -0.577;

        /// negative prey density value for initialisation of test case.
        const double negPreyDensity = -4.669;
};

#endif /* TestCell_hpp */
