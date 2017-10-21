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
    clock_t begin_time = clock();
	
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine generator(seed);
   
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
                cout<<"Input file could not open!"<<endl;
    
    
    
    //take the first command line argument as the input file
    std::ifstream inputFile(argv[1]);
    /*
    //check to make sure the file has been opened for input
    if(!inputFile)
    {
        std::cerr << inputFile << " could not be opened for reading" << std::endl;
        exit(1);
    }
    */
    //construct grid from the data in the input file using our constructor designed for this purpose
    Grid grid(inputFile);
    grid(1,1).setPredDensity(1.0);
    grid.setUniformPreyDistribution(5.0, generator);
    
    grid.printDensities();
    std::cout << std::endl;
    

     int t=500;
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
          sprintf(outputfile,"D:\\output_densities%d.txt",iter/T);
		
	    ofstream output_den(outputfile, ios::out);
        if (output_den.is_open())
         {
           for(int i=1; i<=Nrows; ++i){
             for(int j=1; j<=Ncolumns; ++j){
	 //I hope it works (fingers crossed)
                output_den << i <<" "<< j <<" "<< grid(i,j).getPredDensity() <<" "<< grid(i,j).getPreyDensity()<<endl;
             }
            }
                output_den.close();
         }
        else
                cout<<"Output file could not open!"<<endl;
	}

    }
    
    
    clock_t end_time = clock();
    double time_total = double(end_time - begin_time)/CLOCKS_PER_SEC;	
    cout<<"Execution time: "<<time_total<<" seconds"<<endl;

    return 0;
}
