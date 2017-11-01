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


PredPrey: $(OBJ_FILES) $(HEADERs)
	$(CXX) -o $@ $^ $(INC)


%.o : $(SRC_DIR)/%.cpp $(HEADER)
	$(CXX) -c $< -o $@ $(INC)
