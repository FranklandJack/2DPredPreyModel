#ifndef TestGrid_hpp
#define TestGrid_hpp

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include "Grid.hpp"
/*
*
* A test case that is designed to produce
* example errors and failures
*
*/
class TestGrid : public CPPUNIT_NS::TestFixture
{

        // Establish the test suit of TestCell
        CPPUNIT_TEST_SUITE(TestGrid);

        // Add test method testInit
        //CPPUNIT_TEST(testInit);

        //CPPUNIT_TEST( testConstructor );

        // Finish the process
        CPPUNIT_TEST_SUITE_END();

    public:

        // Overide setUp(), init data etc
        void setUp();

        // Overide tearDown(), free allocated memory,etc
        void tearDown();
        
        //void testConstructor();

    protected:

        // Test method testInit
        //void testInit();

        

    private:

        // Three instances of Grid for test
    Cell *a , *b, *c;
};

#endif /* TestCell_hpp */
