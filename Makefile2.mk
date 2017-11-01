CXX=c++
LDFLAGS=-lcunit

CPPUNITLDFLAGS=-lcppunit


SRC_DIR=src
TEST_DIR=test
INC=-I$(SRC_DIR) -I$(TEST_DIR) -I$(HOME)/include

HEADERS=$(wildcard $(SRC_DIR)/*.hpp)
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC_FILES))

CPPUNITTESTS=TestCell.o


predprey: $(OBJ_FILES) $(HEADERS)
	g++ -std=c++11  $^ $(INC) -o $@

predprey-cppunittests: $(HEADERS) $(CPPUNITTESTS) CppunitTestDriver.o
	g++ -std=c++11  $^ $(INC) $(CPPUNITLDFLAGS) -o $@


%.o : $(SRC_DIR)/%.cpp $(HEADERS)
	g++ -std=c++11 -c $< $(INC) -o $@

%.o : $(TEST_DIR)/%.cpp $(HEADERS)
	g++ -std=c++11 -c $< $(INC) -o $@

.PHONY : test
test : predprey-cppunittests
	./$<