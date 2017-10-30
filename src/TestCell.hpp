#include <cppunit/extensions/HelperMacros.h>
#include "Cell.hpp"
/*
*
* A test case that is designed to produce
* example errors and failures
*
*/
class TestCell : public CPPUNIT_NS::TestFixture
{

// Establish the test suit of TestCell
CPPUNIT_TEST_SUITE(TestCell);

// Add test method testInit
CPPUNIT_TEST(testInit);

// Add test method testGetPredatorDensity
CPPUNIT_TEST(testGetPredDensity);

// Add test method testGetPreyDensity
CPPUNIT_TEST(testGetPreyDensity);

// Add test method testGetState
CPPUNIT_TEST(testGetState);

// Add test method testSetPredatorDensity
CPPUNIT_TEST(testSetPredDensity);

// Add test method testSetPreyDensity 
CPPUNIT_TEST(testSetPreyDensity);

// Add test method testSetState
CPPUNIT_TEST(testGetState);

// Finish the process
CPPUNIT_TEST_SUITE_END();

public:

// Overide setUp(), init data etc
void setUp();

// Overide tearDown(), free allocated memory,etc
void tearDown();

protected:

// Test method testInit
//void testInit();

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

private:

// Three instances of Grid for test
Cell *a , *b, *c;
};