#ifndef TestGrid_hpp
#define TestGrid_hpp

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include "Grid.hpp"
/**
 *
 * \file
 *
 * \class TestGrid
 *
 * \brief Tests the Grid class.  
 *
 * This test class is written using the CppUnit test framework and tests the various methods of the Grid class.
 *
 *
 */
class TestGrid : public CPPUNIT_NS::TestFixture
{

        /// Establish the test suit of TestCell
        CPPUNIT_TEST_SUITE(TestGrid);

        CPPUNIT_TEST(testConstructor1);
        CPPUNIT_TEST(testConstructor2);

        // Finish the process
        CPPUNIT_TEST_SUITE_END();

    public:

        

        // Overide setUp(), init data etc
        void setUp();

        // Overide tearDown(), free allocated memory,etc
        void tearDown();
        
        void testConstructor1();
        void testConstructor2();

    protected:

        // Test method testInit
        //void testInit();

        

    private:

    // Three instances of Grid for test
    Cell *a , *b, *c;

    // Delta value within which doubles are considered equal.
    const double precision = 0.0001;
};

#endif /* TestCell_hpp */
