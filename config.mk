# convert .pnm file to .dat file for input to our program
CONVERT_SRC=pnm2datConvertor/pnmreader.c
CONVERT_EXE=pnm2datConvertor/pnm2dat

$(CONVERT_EXE) : $(CONVERT_SRC)
	gcc $< -o $@