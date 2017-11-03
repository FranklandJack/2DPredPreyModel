# 2DPredPreyModel

[![Build Status](https://travis-ci.org/FranklandJack/2DPredPreyModel.svg?branch=master)](https://travis-ci.org/FranklandJack/2DPredPreyModel)


Model of the interaction of predator-prey in two-dimensional landscape.

https://github.com/FranklandJack/2DPredPreyModel

Authors: 
- Denitsa Bankova s1319505
- Jack Frankland  s1404032

## Introduction
This program simulates the evolution of a system of predator(pumas) and prey(hares) densities across a 2D landscape which includes land and water. Neither the predators nor prey are considered able to swim so in wet areas density is always zero. The evolution of the system is governed by differential equations provided in the coursework development pdf:

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

## Prerequisites

The source code in this project makes use of C++ move semantics, as such it needs to be compiled under the C++11 standard (or higher) hence the compiler on the user's machine must be C++11 compliant. 

The unit test framework used is cppunit. To download, build and install see [CppUnit](http://www.freedesktop.org/wiki/Software/cppunit/), or do the following:
```
$ wget http://dev-www.libreoffice.org/src/cppunit-1.13.2.tar.gz
$ tar -xvzf cppunit-1.13.2.tar.gz
$ cd cppunit-1.13.2
$ ./configure --prefix=$HOME
$ make
$ make install 
$ ls $HOME/include/cppunit
AdditionalMessage.h          Protector.h           TestResultCollector.h
Asserter.h                   SourceLine.h          TestResult.h
BriefTestProgressListener.h  SynchronizedObject.h  TestRunner.h
CompilerOutputter.h          TestAssert.h          TestSuccessListener.h
config                       TestCaller.h          TestSuite.h
config-auto.h                TestCase.h            TextOutputter.h
Exception.h                  TestComposite.h       TextTestProgressListener.h
extensions                   TestFailure.h         TextTestResult.h
Message.h                    TestFixture.h         TextTestRunner.h
Outputter.h                  Test.h                tools
plugin                       TestLeaf.h            ui
portability                  TestListener.h        XmlOutputter.h
Portability.h                TestPath.h            XmlOutputterHook.h
$ ls $HOME/lib
libcppunit-1.13.so.0      libcppunit.a   libcppunit.so
libcppunit-1.13.so.0.0.2  libcppunit.la
$ ls $HOME/share/cppunit
html
$ export CPLUS_INCLUDE_PATH=$HOME/include:$CPLUS_INCLUDE_PATH
$ export LIBRARY_PATH=$HOME/lib:$LIBRARY_PATH
$ export LD_LIBRARY_PATH=$HOME/lib:$LD_LIBRARY_PATH
```

These instructions were taken from: <https://github.com/softwaresaved/build_and_test_examples/blob/master/cpp/README.md>


## Instructions
- To build the code run: ```$ make ```.  

- To run the code run: ```$ ./predprey YOURINPUTLANDSCAPEDATA.dat ```.

- To build and run the tests run: ```$ make test``` or alternatively check the Travis CI repository [here](https://travis-ci.org/FranklandJack/2DPredPreyModel). Running the tests will produce a summary of success and failures in the command line as well as TestResults.xml file that contains the same information.

- To generate the dat files for input from any .pnm files you have to just place your pnm files in the landscapes directory and run: ```$ make dats``` which will generate the .dats files and place them in the main 2DPredPreyModel directory ready to be run with the executable. 

- For a full list of make functionality run: ```$ make help```.

- To generate the code documentation run: ```$ doxygen Doxyfile```  which will output into the documentation directory two subdirectories called latex and html. To generate the reference manual ```$ mv documentation/latex``` and run ```$ make``` which will create a refman.pdf. The generated html documentation can be viewed by pointing a HTML browser to the index.html file in the html directory.

## Input Formatting

The program takes as its input: 
1. A .txt file containing the various parameters for the differential equation which evolves the system. 
2. A .dat file which contains the landscape of the system. 

The location of the input parameters is hard coded into the main method, so its name should not be changed, however the user can feel free to change the values of the parameters in the file input/input_parameters.txt.

The format of the input_parameters.txt file **MUST** be:

1. birth rate of hares 
2. predation rate at which pumas eat hares
3. birth rate of pumas per one hare eaten
4. puma mortality rate
5. diffusion rate for hares
6. diffusion rate for pumas
7. size of time step
8. the number of time steps between output of plain .pnm file

With each value separated by a newline.

The .dat file is provided as the only command line argument to the executable and **MUST** be of the format:

number columns     number rows  
X X X X X X X X ...... X X X X  
X X X X X X X X ...... X X X X  
. . . . . . . . ...... . . . .  
. . . . . . . . ...... . . . .  
. . . . . . . . ...... . . . .  
X X X X X X X X ...... X X X X  

where X=0 if the cell in the landscape is Wet and X=1 if the cell in the landscape is dry, and number columns and number rows are both positive integers.

## Output 
The program will run from t=0 to t=500 and output the average density of the predators and prey (over the whole grid including wet areas) every 10 time steps into a file called Average_Densities.txt. It will also output a plain ppm file every N time steps called outputM.ppm where N is the number of time steps between output set by the user in the input file, and M is the step number of the output. All output files are created in the output directory. The user should note that since output is always sent to the output directory if they run the simulation more than once they will overwrite their output from the first run. The user can either save the outputs into a different directory, or remove the original outputs by running ``` $ make clean ```.



