# 2DPredPreyModel

[![Build Status](https://travis-ci.org/FranklandJack/2DPredPreyModel.svg?branch=master)](https://travis-ci.org/FranklandJack/2DPredPreyModel)

Model of the interaction of predator-prey in two-dimensional landscape.

Authors: - Denitsa Bankova s1319505
		 - Jack Frankland  s1404032


This program simulates the evolution of a system of predator(pumas) and prey(hares) densities across a 2D landscape which includes land and water. Neither the predators nor prey are considered able to swim so in wet areas density is always zero. The evolution of the system is goverened by differential equations provided in the coursework development pdf.

The program takes as its input: 1. A .txt file containing the various parameters for the differential equation which evolves the system. 2. A .dat file which contains the landscape of the system. 

The location of the input parameters is hard coded into the main method, so its name should not be changed, however the user can feel free to change the values of the parameters in the file input/input_parameters.txt.

The format of the input_patameters.txt file MUST be:

birth rate of hares 
predation rate at which pumas eat hares
birth rate of pumas per one hare eaten
puma mortality rate
diffusion rate for hares
diffusion rate for pumas
size of timestep


With each value seperated by a newline.

The .dat file is provided as the only command line argument to the executible and MUST be of the format:

number columns number rows
X X X X X X X X ...... X X X X
X X X X X X X X ...... X X X X
. . . . . . . . ...... . . . .
. . . . . . . . ...... . . . .
. . . . . . . . ...... . . . .
X X X X X X X X ...... X X X X

where X=0 if the cell in the landscape is Wet and X=1 if the cell in the landscape is dry. 


To build the code; run make
To Run the code;   run ./PredPrey YOURINPUTLANDSCAPEDATA.dat

To generate the dat files for input from any .pnm files you have just place your pnm files in the landscapes directory and run; make dats which will generate the .dats files and place them in the main 2DPredPreyModel directory. 
