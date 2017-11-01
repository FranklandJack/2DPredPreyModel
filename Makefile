# Makefile for the 2D-Pred-Prey Simulation

SRC_DIR=src
HEADERS=$(wildcard $(SRC_DIR)/*.hpp)
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC_FILES))


TEST_DIR=test
TEST_HEADERS=$(wildcard $(TEST_DIR)/*.hpp)
TEST_SRC_FILES=$(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ_FILES=$(patsubst $(TEST_DIR)/%.cpp, %.o, $(TEST_FILES))


PNM_DIR=landscapes
OUT_DIR=output
PNM_FILES=$(wildcard $(PNM_DIR)/*.pnm)
DAT_FILES=$(patsubst $(PNM_DIR)/%.pnm, %.dat, $(PNM_FILES))
OUT_FILES=$(wildcard $(OUT_DIR)/*)



CXX=c++
LDFLAGS=-lcunit
CPPUNITLDFLAGS=-lcppunit
INC=-I$(SRC_DIR) -I$(TEST_DIR) -I$(HOME)/include


CPPUNITTESTS=TestCell.o

EXE_FILE=predprey
EXE_TEST=predprey-cppunittests


$(EXE_FILE): $(OBJ_FILES) 
	$(CXX) -std=c++11 -o $@  $^ 

$(EXE_TEST): $(TEST_OBJ_FILES)
	$(CXX) -std=c++11 -o $@  $^ $(INC) $(CPPUNITLDFLAGS) 

## objs      : create object files
.PHONY : objs
objs : $(OBJ_FILES)

%.o : $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) -std=c++11 -c $< -o $@ $(INC) 

%.o : $(TEST_DIR)/%.cpp $(HEADERS)
	$(CXX) -std=c++11 -c $< -o $@ $(INC) 



.PHONY : test
test : predprey-cppunittests
	./$<


include config.mk
## dats      : create .dats files for input 
.PHONY : dats
dats : $(DAT_FILES)

%.dat : $(PNM_DIR)/%.pnm $(CONVERT_EXE)
	$(CONVERT_EXE) $< $@



## clean     : remove auto generated files
.PHONY : clean
clean :
	rm -f $(OBJ_FILES)
	rm -f $(TEST_OBJ_FILES)

	rm -f $(EXE_FILE)
	rm -f $(EXE_TEST)

	rm -f $(OUT_FILES)
	rm -f $(DAT_FILES)

## variables : Print variables
.PHONY :variables
variables:
	@echo SRC_DIR:        $(SRC_DIR)
	@echo SRC_FILES:      $(SRC_FILES)
	@echo OBJ_FILES:      $(OBJ_FILES)

	@echo TEST_DIR:       $(TEST_DIR)
	@echo TEST_SRC_FILES: $(TEST_SRC_FILES)
	@echo TEST_OBJ_FILES: $(TEST_OBJ_FILES)

	@echo OUT_DIR:        $(OUT_DIR)
	@echo OUT_FILES:      $(OUT_FILES)

	@echo PNM_DIR:        $(PNM_DIR)
	@echo PNM_FILES:      $(PNM_FILES)


## help      : Print help
.PHONY : help
help : Makefile
	@sed -n 's/^##//p' $<
