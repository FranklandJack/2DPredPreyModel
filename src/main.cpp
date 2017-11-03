#include <iostream>
#include <fstream>
#include <chrono>
#include <random> 
#include <stdexcept>
#include <string>
#include "Grid.hpp"
#include "updateGrid.hpp"

using namespace std;

int main(int argc, char const *argv[])
{

    /**************************************************************************************************
     ******************************************* SET UP ***********************************************
     **************************************************************************************************/

    // Record a start time so we can time the code.
    auto start = std::chrono::system_clock::now();

	// Seed the pseudo random number generation using the system clock.
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());

    // Create a generator that is fed to the distributions to provide the psuedo random numbers.
    default_random_engine generator(seed);


    /**************************************************************************************************
     ******************************************** INPUT ***********************************************
     **************************************************************************************************/

    /***************************  Input for the differential equation *********************************/

    // Parameters for differential equation implementation.
    double r, a, b, m, k, l, deltaT;
    int outputSteps;

    // The parameters are collected from the parameter input file.
    ifstream input_par("./input/input_parameters.txt", ios::in);

    /*
     *
     * It needs to be checked that for each parameter the input has been successfully read in, i.e. it is of the right type
     * and it needs to be checked that the input is physical, which in all cases here just corresponds to it being non-negative. 
     * If either of these conditions fail the program exits with an appropriate message, since it is most likely the user made an
     * error with their input values, and so wouldn't want the code to run anyway. 
     *
     */
    try
    {
    if (input_par.is_open())
    {
        /*
         * As specified in the development pdf:
         * r is the birth rate of hares 
         * a is the predation rate as which pumas eat hares
         * b is the birth rate of pumas per one hare eaten
         * m is the puma mortality rate
         * k is the diffusion rate of hares
         * l is the diffusion rate of pumas
         * delta T is the size of the time step
         *
         * outputSteps is the number of steps between output
         */
        input_par >> r >> a >> b >> m >> k >> l >> deltaT >> outputSteps;

        
        if(r < 0.0 || a < 0.0 || b < 0.0 || m < 0.0 || k < 0.0 || l < 0.0 || deltaT <= 0.0 || outputSteps < 1)
        {
            throw runtime_error("Input parameters are not all positive.");
            
        }

        if(input_par.fail()) 
        {
            throw runtime_error("One or more parameters are of incorrect type.");
            
        }
        

        input_par.close();
    }

    else
    {
        throw runtime_error("input/input_parameters.txt could not be opened for reading.");    
    }

    }
    catch(exception &exception)
    {
        cerr << "Exception: " << exception.what() << endl;
        return 1;
    }
                

    /************************************* Input for the landscape/grid **********************************************************/

    // Forward declare variables here since they will be unreachable if they are place inside a try block 

    // Grid that is to be updated at each time step.
    Grid grid;

    // Number of columns in the grid.
    int columns = 0;

    // Number of rows in the grid.
    int rows   = 0;

    // 2D array/pointer that represents the landscapeData.
    int** landscapeData;

    try
    {
    // Take the first command line argument as the landscape input file.
    ifstream input_Landscape(argv[1], ios::in);

    // First value in the file should be the number of columns and second value in the file should be the number of rows.
    input_Landscape >> columns >> rows;

    // If extraction fails in columns or rows we need to throw an exception since the grid cannot be constructed. 
    if(input_Landscape.fail()) 
    {
        throw std::runtime_error("#columns or #rows is of incorrect type");
    }

    // Need to make sure the number of columns and rows is physical, i.e. positive definite.
    if(columns <= 0 || rows <= 0) 
    {
        // Throw an exception here since we cannot interpret negative columns or rows, so the code shouldn't run until it is dealt with.
        throw std::runtime_error("#columns or #rows in input is unphysical");

    }

    // The rest of the data in the file is the actual landscape. The landscape data will be temporarily stored in a 2D array. Which will
    // need to be dynamically allocated, since the size is not known at compile time.
    landscapeData = new int*[columns];
    for(int i = 0; i < columns; ++i)
    {
        landscapeData[i] = new int[rows]; 
    }

    /*
     * The rest of the data in the file is the actual landscape. Since the data in the file corresponds to the x-y
     * the first value will correspond to the coordinate (#rows, 1), i.e. it starts at the top of the landscape in the first
     * column and will work down the rows.
     */
    // Starting from the top row and working downwards.
    for(int j = rows - 1; j >= 0; --j)
    {   
        // Starting from the left most column and working rightwards.
        for(int i = 0; i < columns; ++i)
        {
            // Get the next landscape data value from the file.
            int inputState = 0;
            input_Landscape >> inputState;

            if(input_Landscape.fail())
            {
                throw std::runtime_error("anomalous grid entry is of incorrect type");
            }

            // Check to see that the input was of type 0 or 1 and throw an exception otherwise since cannot interpret other integers.
            if(1 != inputState && 0 != inputState)
            {
                throw std::runtime_error("grid entry detected that is neither 0 nor 1");
            }
            landscapeData[i][j] = inputState;
        }
    }


    // Construct the grid object, that models the landscape from this data.
    grid = Grid(columns, rows, landscapeData);
    }
    catch(exception &exception)
    {
        cerr << "Exception: " << exception.what() << endl;

        // Need to make sure we release all the memory that was allocated in the data array since it might not reach the stage where it is 
        // normally released if an exception is thrown.
        for(int i = 0; i < columns; ++i)
        {
            delete [] landscapeData[i];
        }   

        delete [] landscapeData;
        return 1;
    }

    // Now that the data is all stored in the grid the landscape data can be deleted and its memory freed. 
    for(int i = 0; i < columns; ++i)
    {
        delete [] landscapeData[i];
    }

    delete [] landscapeData;





    /**************************************************************************************************
     ************************************ ALGORITHM AND OUTPUT ****************************************
     **************************************************************************************************/
    
    // Set uniform predator and prey distributions between 0 and 5.0 across the whole grid.
    grid.setUniformDistribution(5.0, 5.0, generator);

    
    // Total time for simulation. 
    int t = 500;


    // Total number of iterations for the simulation.
    int numIterations = int(t/deltaT);

    // Interval at which to print the predator and prey densities to the command line. 
    int averageDenOutputFreq = 10;

    // Initial maximal colour value for the PPM output files. 
    int maxNumberPPM = 10;
	
    // No file name will be longer than 50 characters. 
    char outputfile[50];


    // Name of output file for average densities
    string averageDensitiesOutput("./output/Average_Densities.txt");


    // Create an output file for the average densities.
    ofstream output_avrg_dens(averageDensitiesOutput, ios::out);


    if(output_avrg_dens.is_open())
    {
        // Print the column titles for the average density outputs
        output_avrg_dens << "Time    Pred Dens.    Prey Dens." << endl;
    }

    // The densities of the cells in the grid are printed before any updates of the grid.
    // Iteration number numIterations allows printing values after numIterations updates, although one more update is made after that.
    for(int iter = 0; iter <= numIterations; ++iter)
    {
        
        
        if(0 == iter % averageDenOutputFreq)
        {

            output_avrg_dens << iter * deltaT << "       " << grid.predDensity() << "       " << grid.preyDensity() << endl;

        }

        
        if(0 == iter % outputSteps)
        {  
            {
                //Creates different names for each output file in the output folder, called output
                sprintf(outputfile,"./output/output%d.ppm",iter/outputSteps);
                
                ofstream outputPPM(outputfile, ios::out);
        
                if (outputPPM.is_open())
                {
                    maxNumberPPM = grid.printPPM(outputPPM, maxNumberPPM);
                    outputPPM.close();
                }
                else
                {
                    cout << "Output .ppm file could not open." << endl;
                    cout << "Check that the specified output directory exists" << endl;
                }
            }




        }

        grid = updateGrid(grid,r,a,b,m,k,l,deltaT);

    }
    output_avrg_dens.close();


   /**************************************************************************************************
    *************************************** TIDYING UP ***********************************************
    **************************************************************************************************/
     
    
   // Print the destination of output files.
   cout << "Average densities have been printed to " << averageDensitiesOutput << endl; 

   
   // Register that the program has completed.
   auto end = std::chrono::system_clock::now();


   // Calculate the elapsed time to an appropriate order. 
   auto elapsed = std::chrono::duration_cast<chrono::milliseconds>(end - start);


   // Output the time taken to run the code to the command line. 
   cout << "Time take to execute (us):   " << elapsed.count() << endl;

   return 0;
}
