#include <stdio.h>
#include <string.h>

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

/*
 * This code is taken from https://github.com/softwaresaved/build_and_test_examples/blob/master/cpp/test/cppunit_test_driver.cc
 * since it will work with any test suites.
 *
 * Set up and run tests.
 *
 * @return 0 if successful else 1.
 */
int main() 
{
  // Set up result collection.
  CppUnit::TestResult controller; 
  CppUnit::TestResultCollector result; 
  controller.addListener(&result); 
  CppUnit::BriefTestProgressListener progressListener;
  controller.addListener(&progressListener);

  std::ofstream xmlout("TestResults.xml"); 
  CppUnit::XmlOutputter xmlOutputter (&result, xmlout); 
  CppUnit::TextOutputter consoleOutputter (&result, std::cout); 

  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry &registry =
    CppUnit::TestFactoryRegistry::getRegistry();
  runner.addTest(registry.makeTest());

  runner.run(controller); 
  
  xmlOutputter.write(); 
  consoleOutputter.write(); 

  return result.wasSuccessful() ? 0 : 1; 
}