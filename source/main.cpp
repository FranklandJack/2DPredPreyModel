//main method of the 2D predator prey simulation


#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>


//implementing the grid
#include "Grid.hpp"
#include "updateGrid.hpp"

using namespace std;


int main(int argc, char const *argv[])
{

    //clock_t begin_time = clock();
    auto start = std::chrono::system_clock::now();

	
    unsigned int seed = static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count());
    default_random_engine generator(seed);

   
    //parameter input
    double r, a, b, m, k, l, deltaT;
    unsigned int T;

    ifstream input_par("./input/input_parameters.txt", ios::in);

    if (input_par.is_open())
    {
        input_par >> r >> a >> b >> m >> k >> l >> deltaT >> T;
        input_par.close();
    }
       
    else
    {
           cerr << "input/input_parameters.txt could not be opened for reading." << endl;
           exit(1);
    }
                
    
    
    
    // Take the first command line argument as the landscape input file.
    ifstream input_Landscape(argv[1], ios::in);


    // Initialize values to hold the input landscape data.
    int columns = 0;
    int rows    = 0;
    int **statesData = nullptr;
    
    // Check to make sure the file has been opened for input
    if(input_Landscape.is_open())
    {
        // First line of file should contain two integers. The first being the number of columns, the second being the number of rows. 
        // We need to check that this is the case. 

        input_Landscape >> columns >> rows;

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

    
    
    //construct grid from the data in the input file using our constructor designed for this purpose
    Grid grid(input_Landscape);
    grid(2,2).setPredDensity(1.0);
    //grid.setUniformPreyDistribution(5.0, generator);
    


    

     int t=50;
     int num_iterations=int(t/deltaT);
     int step_average=10;
     char outputfile[50];
    
     for(int iter = 1; iter <= num_iterations; ++iter)
     {
        grid = updateGrid(grid,r,a,b,m,k,l,deltaT);
        if(0 == iter % step_average)
            std::cout<<grid.predDensity()<< ' ' << grid.preyDensity()<<std::endl;
        if(0 == iter % T)
            
         // print output
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
                cout<<"Output file could not open!"<<endl;
    }

    }
    
    /*
    clock_t end_time = clock();
    double time_total = double(end_time - begin_time)/CLOCKS_PER_SEC;   
    cout<<"Execution time: "<<time_total<<" seconds"<<endl;
    */
   
   auto end = std::chrono::system_clock::now();
   auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
   cout << "Time take to execute (us):   " << elapsed.count() << endl;

    return 0;
}
