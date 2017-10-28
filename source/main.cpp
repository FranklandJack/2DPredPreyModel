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

    // Record a start time so we can time the code.
    auto start = std::chrono::system_clock::now();


	// Seed the psuedo random number generation.
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());


    default_random_engine generator(seed);

   
    // Parameters for differential equation implementation.
    double r, a, b, m, k, l, deltaT;
    int outputSteps;

    
    // The parameters are collected from the parameter input file.
    ifstream input_par("./input/input_parameters.txt", ios::in);

    /*
     *
     * It needs to be checked that for each parameter the input has been sucessfully read in, i.e. it is of the right type
     * and it needs to be checked that the input is physical, which in all cases here just corresponds to it being non-negative. 
     * If either of these conditions fail the program exits with an appropraite message, since it is most likley the user made an
     * error with their input values, and so wouldn't want the code to run anyway. 
     *
     */
    try
    {
    if (input_par.is_open())
    {
        /*
         * As specified in the devlopment pdf:
         * r is the birth rate of hars
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

        
        if(r <= 0.0 || a <= 0.0 || b <= 0.0 || m <= 0.0 || k <= 0.0 || l <= 0.0 || deltaT <= 0.0 || outputSteps < 1)
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
                


    // This is the grid that is used in the simulation.
    Grid grid;
    
    // Take the first command line argument as the landscape input file.
    ifstream input_Landscape(argv[1], ios::in);


    try
    {

    // Construct grid from the data in the input file using the constructor designed for this purpose. This will throw an exception if the input is invalid.
    grid = Grid(input_Landscape);

    }

    catch(exception &exception)
    {
        cerr << "Standard Exception: " << exception.what() << endl;
        return 1;
    }
    

    



    grid(3,3).setPredDensity(2.0);
    grid.setUniformPreyDistribution(2.0, generator);
    
    

    
     // Total time for simulation. 
     int t = 50;


     // Total number of iterations for the simulation.
     int numIterations = int(t/deltaT);

     // Invterval at which to print the predator and prey densities to the command line. 
     int averageDenOutputFreq = 10;

     // No file name will be longer than 50 characters. 
     char outputfile[50];



     // Print the column titles for the standard output. 
     cout << "Pred Density " << "Prey Density" << endl;

     for(int iter = 1; iter <= numIterations; ++iter)
     {
        grid = updateGrid(grid,r,a,b,m,k,l,deltaT);


        if(0 == iter % averageDenOutputFreq)
        {

            cout << grid.predDensity() << " " << grid.preyDensity() << endl;

        }

        
        if(0 == iter % outputSteps)
        {  
        
        
    {
    //file directory has to be changed
         sprintf(outputfile,"./output/output_densities%d.txt",iter/outputSteps);
        
        ofstream output_den(outputfile, ios::out);
        
        if (output_den.is_open())
         {
                grid.printDensities(output_den);
                output_den.close();
         }
        else
                cout << "Output file could not open." << endl;
    }
    }

    }
    
    
   
   // Register that the program has completed.
   auto end = chrono::system_clock::now();


   // Calculate the elapsed time to an appropriate order. 
   auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);


   // Ouput the time taken to run the code to the command line. 
   cout << "Time take to execute (us):   " << elapsed.count() << endl;

   return 0;



   
}
