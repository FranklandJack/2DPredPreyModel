#makefile for the 2D-Pred-Prey Simulation



SRC_DIR=source
PNM_DIR=landscapes

SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC_FILES))

PNM_FILES=$(wildcard $(PNM_DIR)/*.pnm)
DAT_FILES=$(patsubst $(PNM_DIR)/%.pnm, %.dat,$(PNM_FILES))



EXE_FILE=PredPrey

## all       : compile sourcefiles and create an executible

.PHONY : all
all : $(EXE_FILE)

$(EXE_FILE) : $(OBJ_FILES)
	g++ $^ -o $@

include config.mk

## objs      : create object files
.PHONY : objs
objs : $(OBJ_FILES)

%.o : $(SRC_DIR)/%.cpp
	g++ -c $<

## dats      : create .dats files for input 
.PHONY : dats
dats : $(DAT_FILES)

%.dat : $(PNM_DIR)/%.pnm $(CONVERT_SRC)
	$(CONVERT_EXE) $< $@

## clean     : remove auto generated files
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


## help      : Print help
.PHONY : help
help : Makefile
	@sed -n 's/^##//p' $<