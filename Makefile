# Makefile for the 2D-Pred-Prey Simulation

SRC_DIR=source
PNM_DIR=landscapes
OUT_DIR=output

SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC_FILES))

PNM_FILES=$(wildcard $(PNM_DIR)/*.pnm)
DAT_FILES=$(patsubst $(PNM_DIR)/%.pnm, %.dat, $(PNM_FILES))

OUT_FILES=$(wildcard $(OUT_DIR)/*.txt)



EXE_FILE=PredPrey

## all       : compile sourcefiles, create an executible create the dat files from the pnm files provided. 

.PHONY : all
all : $(EXE_FILE) $(DAT_FILES)

$(EXE_FILE) : $(OBJ_FILES)
	g++ -std=c++11 $^ -o $@



include config.mk

## objs      : create object files
.PHONY : objs
objs : $(OBJ_FILES)

%.o : $(SRC_DIR)/%.cpp
	g++ -std=c++11 -c $<

## dats      : create .dats files for input 
.PHONY : dats
dats : $(DAT_FILES)

%.dat : $(PNM_DIR)/%.pnm $(CONVERT_EXE)
	$(CONVERT_EXE) $< $@

## clean     : remove auto generated files
.PHONY : clean
clean :
	rm -f $(OBJ_FILES)
	rm -f $(EXE_FILE)
	rm -f $(OUT_FILES)
	rm -f $(DAT_FILES)

## variables : Print variables
.PHONY :variables
variables:
	@echo SRC_DIR:   $(SRC_DIR)
	@echo SRC_FILES: $(SRC_FILES)
	@echo OBJ_FILES: $(OBJ_FILES)

	@echo OUT_DIR:   $(OUT_DIR)
	@echo OUT_FILES: $(OUT_FILES)

	@echo PNM_DIR:   $(PNM_DIR)
	@echo PNM_FILES: $(PNM_FILES)


## help      : Print help
.PHONY : help
help : Makefile
	@sed -n 's/^##//p' $<
