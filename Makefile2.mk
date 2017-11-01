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


predprey: $(OBJ_FILES) 
	$(CXX) -std=c++11 -o $@  $^ 

predprey-cppunittests: $(HEADERS) $(CPPUNITTESTS) Cell.o CppunitTestDriver.o
	$(CXX) -std=c++11 -o $@  $^ $(INC) $(CPPUNITLDFLAGS) 


%.o : $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) -std=c++11 -c $< -o $@ $(INC) 

%.o : $(TEST_DIR)/%.cpp $(HEADERS)
	$(CXX) -std=c++11 -c $< -o $@ $(INC) 

.PHONY : test
test : predprey-cppunittests
	./$<
