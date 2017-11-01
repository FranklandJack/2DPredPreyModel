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
	$(CXX) -o $@ -std=c++11  $^ $(INC) 

predprey-cppunittests: $(HEADERS) $(CPPUNITTESTS)  CppunitTestDriver.o
	$(CXX) -std=c++11 -o $@  $^ -L$(INC) $(OBJ_FILES) $(CPPUNITLDFLAGS) 


%.o : $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) -std=c++11 -c $< -o $@ -L$(INC) 

%.o : $(TEST_DIR)/%.cpp $(HEADERS)
	$(CXX) -std=c++11 -c $< -o $@ -L$(INC) 

.PHONY : test
test : predprey-cppunittests
	./$<
