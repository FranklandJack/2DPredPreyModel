CXX=c++
LDFLAGS=-lcunit

CPPUNITLDFLAGS=-lcppunit

CPPUNIT_PATH=$(HOME)/include

tests: TestCell.o CppunitTestDriver.o Cell.o
	g++ -o tests TestCell.o CppunitTestDriver.o Cell.o -L$(CPPUNIT_PATH) -lstdc++ -lcppunit -ldl

Cell.o: src/Cell.cpp src/Cell.hpp
	g++ -c src/Cell.cpp

TestCell.o: test/TestCell.cpp
	g++ -c test/TestCell.cpp -I$(CPPUNIT_PATH)

CppunitTestDriver.o: test/CppunitTestDriver.cpp
	g++ -c test/CppunitTestDriver.cpp -I$(CPPUNIT_PATH)

clean:
	rm -f *.o tests