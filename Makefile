#makefile for the 2D-Pred-Prey Simulation

SRC_DIR=source

SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC_FILES))

EXE_FILE=PredPrey

## all  : compile sourcefiles and create an executible

.PHONY : all
all : $(EXE_FILE)

$(EXE_FILE) : $(OBJ_FILES)
	g++ $^ -o $@



## objs  : create object files
.PHONY : objs
objs : $(OBJ_FILES)

%.o : $(SRC_FILES)
	g++ -c $^

## clean : remove auto generated files
.PHONY : clean
clean :
	rm -f $(OBJ_FILES)
	rm -f $(EXE_FILE)

## variables : Print variables
.PHONY :variables
variables:
	@echo SRC_DIR:   $(SRC_DIR)
	@echo SRC_FILES: $(SRC_FILES)
	@echo OBJ_FILES: $(OBJ_FILES)


## help : Print help
.PHONY : help
help : Makefile
	@sed -n 's/^##//p' $<
