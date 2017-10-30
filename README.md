# 2DPredPreyModel

[![Build Status](https://travis-ci.org/FranklandJack/2DPredPreyModel.svg?branch=master)](https://travis-ci.org/FranklandJack/2DPredPreyModel)


Model of the interaction of predator-prey in two-dimensional landscape.

https://github.com/FranklandJack/2DPredPreyModel

Authors: 
- Denitsa Bankova s1319505
- Jack Frankland  s1404032

## Introduction
This program simulates the evolution of a system of predator(pumas) and prey(hares) densities across a 2D landscape which includes land and water. Neither the predators nor prey are considered able to swim so in wet areas density is always zero. The evolution of the system is goverened by differential equations provided in the coursework development pdf:

∂H/∂t = rH - aHP + k (∂^2H/∂x^2 + ∂^2H/∂y^2)

∂P/∂t = bHP - mP + l (∂^2P/∂x^2 + ∂^2P/∂y^2)

where: 

- H is the density of hares (prey).
- P is the density of pumas (predators).
- r is the birth rate of hares.
- a is the predation rate at which pumas eat hares.
- b is the birth rate of pumas per one hare eaten.
- m is the pumas mortality rate.
- k is the diffusion rate for hares. 
- l is the diffusion rate for pumas.

## Instructions
- To build the code run: ``` make ```  

- To run the code run: ```./PredPrey YOURINPUTLANDSCAPEDATA.dat ```  

- To run the tests:  run ```!!!!!!!!!!!!!```  

- To generate the dat files for input from any .pnm files you have to just place your pnm files in the landscapes directory and run: ```make dats``` which will generate the .dats files and place them in the main 2DPredPreyModel directory. 

- To generate complete documentation run: ```doxygen Doxyfile```  

- For a full list of make functionality run: ```make help```  

## Input Formatting

The program takes as its input: 
1. A .txt file containing the various parameters for the differential equation which evolves the system. 
2. A .dat file which contains the landscape of the system. 

The location of the input parameters is hard coded into the main method, so its name should not be changed, however the user can feel free to change the values of the parameters in the file input/input_parameters.txt.

The format of the input_patameters.txt file **MUST** be:

1. birth rate of hares 
2. predation rate at which pumas eat hares
3. birth rate of pumas per one hare eaten
4. puma mortality rate
5. diffusion rate for hares
6. diffusion rate for pumas
7. size of timestep
8. the number of timesteps between output of plain .pnm file
9. total time of simulation

With each value seperated by a newline.

The .dat file is provided as the only command line argument to the executible and **MUST** be of the format:

number columns number rows  
X X X X X X X X ...... X X X X  
X X X X X X X X ...... X X X X  
. . . . . . . . ...... . . . .  
. . . . . . . . ...... . . . .  
. . . . . . . . ...... . . . .  
X X X X X X X X ...... X X X X  

where X=0 if the cell in the landscape is Wet and X=1 if the cell in the landscape is dry. 



