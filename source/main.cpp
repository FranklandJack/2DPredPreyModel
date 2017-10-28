// For any command line IO.
#include <iostream>


// For reading data to and from files.
#include <fstream>


// For seeding random number generatrion and timing. 
#include <chrono>


// For random number generation.
#include <random> 
//#include <ctime>


// For implementing the landscape.
#include "Grid.hpp"


// For updating the landscape.
#include "updateGrid.hpp"


// Lots of use of standard library in this file means its much cleaner to use the std namespace. 
using namespace std;



// Main method begins. 
int main(int argc, char const *argv[])
{

    //clock_t begin_time = clock();


    /// Record a start time so we can time the code.
    auto start = chrono::system_clock::now();


	// Seed the psuedo random number generation.
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());


    // Create a generator which is fed to any random distributions to produce psuedo random numbers. By using the same
    // generator for all random number generation, we will only have a single chain of random numbers, which makes them 
    // reproducbile if seeded by a constant value.
    default_random_engine generator(seed);

   
    // Parameter input for differential equation implementation.
    double r, a, b, m, k, l, deltaT;
    unsigned int T;

    // To handel any errors in the parameter input we will throw exceptions and handel them accordingly.
    

    ifstream input_par("./input/input_parameters.txt", ios::in);

    if (input_par.is_open())
    {
        input_par >> r >> a >> b >> m >> k >> l >> deltaT >> T;
        input_par.close();
    }

    /*
    else
    {
           cerr << "input/input_parameters.txt could not be opened for reading." << endl;
           exit(1);
    }
                
    */
    
    
    // Take the first command line argument as the landscape input file.
    ifstream input_Landscape(argv[1], ios::in);


    // Initialize values to hold the input landscape data.
    int columns = 0;
    int rows    = 0;
    int **statesData = nullptr;
    /*
    // Check to make sure the file has been opened for input
    if(input_Landscape.is_open())
    {
        // First line of file should contain two integers. The first being the number of columns, the second being the number of rows. 
        // We need to check that this is the case. 

        input_Landscape >> columns >> rows;

        // Since we know know the dimensions of the landscape we can read the array in element by element.
        // We will be starting at the top left of the landscape, so we need to read it in top to bottom and left to right.

        // First we need to allocate the memory for the array now we know it's size.



        

        /*
        // Need to check that the input suceeded and is meaningful, i.e. is positive integer
        // Check for failed extaction 
        if(input_Landscape.fail())
        {
            // Clear the buffer
            input_Landscape.clear();

            // Remove the bad input
            input_Landscape.ignore(32767, '\n');

            // Exit with an appropriate error message 
            cerr << argv[1] << " contains erroneous data in #columns or #rows." << endl;
            exit(1);

        }


        // Check that the number of columns and rows are positive
        if(columns < 0 || rows < 0)
        {
            cerr << argv[1] << " has negative column or row numbers." << endl;
            exit(1);
        }
    }
    
    else
    {
        cerr << argv[1] << " could not be opened for reading." << endl;
        exit(1);
    }
    */

    // Try block ends here since at this point all input is complete. 
    


    // Construct grid from the data in the input file using our constructor designed for this purpose.
    Grid grid(input_Landscape);


    grid(2,2).setPreyDensity(1.0);
    //grid.setUniformPreyDistribution(5.0, generator);
    


    
     // Total time for simulation. 
     int t = 50;


     // Total number of iterations for the simulation.
     int num_iterations = int(t/deltaT);

     // Invterval at which to print the predator and prey densities to the command line. 
     int step_average = 10;

     // TODO: why does this have size 50?
     char outputfile[50];
    
     for(int iter = 1; iter <= num_iterations; ++iter)
     {
        grid = updateGrid(grid,r,a,b,m,k,l,deltaT);


        if(0 == iter % step_average)
        {

            cout << grid.predDensity() << " " << grid.preyDensity() << endl;

        }

        
        if(0 == iter % T)
        {  
         // print output
        }
    {
    //file directory has to be changed
         sprintf(outputfile,"./output/output_densities%d.txt",iter/T);
        
        ofstream output_den(outputfile, ios::out);
        
        if (output_den.is_open())
         {
                grid.printDensities(output_den);
                output_den.close();
         }
        else
                cout << "Output file could not open!" << endl;
    }

    }
    
    /*
    clock_t end_time = clock();
    double time_total = double(end_time - begin_time)/CLOCKS_PER_SEC;   
    cout<<"Execution time: "<<time_total<<" seconds"<<endl;
    */
   
   // Register that the program has completed.
   auto end = chrono::system_clock::now();


   // Calculate the elapsed time to an appropriate order. 
   auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);


   // Ouput the time taken to run the code to the command line. 
   cout << "Time take to execute (us):   " << elapsed.count() << endl;

   return 0;
}
