#include <iostream>
#include <fstream>
#include <chrono>
#include <random> 
#include <stdexcept>
#include <string>
#include <sstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include "Grid.hpp"
#include "updateGrid.hpp"

using namespace std;
namespace po = boost::program_options;

int main(int argc, char const *argv[])
{

    /**************************************************************************************************
     ******************************************* SET UP ***********************************************
     **************************************************************************************************/

    // Record a start time so we can time the code.
    auto start = std::chrono::system_clock::now();

    cout << "Setting up simulation..." << '\n' << '\n';
    // Create an output directory for the output files based on run time and date.
    time_t startTime = chrono::system_clock::to_time_t(start);
    string outputName = ctime(&startTime);
    std::transform(outputName.begin(), outputName.end(), outputName.begin(), [](char ch) {return ch == ' ' ? '_' : ch;});
    std::transform(outputName.begin(), outputName.end(), outputName.begin(), [](char ch) {return ch == ':' ? '-' : ch;});
    outputName.erase(std::remove(outputName.begin(), outputName.end(), '\n'), outputName.end());
    boost::filesystem::path outPath = outputName;
    
    // Since the directory name is unique only up to the second it is created in be can append a number if the program is
    // run more than once in a second. We assume that the rate a user can call the program is less than 
    // 10 times a second.
    for(int i = 2; boost::filesystem::exists(outPath) && i < 10; ++i)
    {
        stringstream ss;
        ss << outPath << "(" << i << ")";
        outPath = ss.str();
    }
    boost::filesystem::create_directory(outPath);

	// Seed the pseudo random number generation using the system clock.
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());

    // Create a generator that is fed to the distributions to provide the psuedo random numbers.
    default_random_engine generator(seed);


    /**************************************************************************************************
     ******************************************** INPUT ***********************************************
     **************************************************************************************************/

    /***************************  Input for the differential equation *********************************/

    // Parameters for differential equation implementation.
    double r, a, b, m, k, l, deltaT, totalTime;
    int outputSteps;
    bool includeWater = false;

    // Set up optional command line argument.
    po::options_description desc("Options for hmc oscillator program");

    desc.add_options()
        
        ("prey-birth-rate,r", po::value<double>(&r)->default_value(0.08), "Prey birth rate")
        ("predation-rate,a", po::value<double>(&a)->default_value(0.04), "Predation rate at which predators eat prey")
        ("predator-birth-rate,b", po::value<double>(&b)->default_value(0.02), "Birth rate for preadtors per one prey eaten")
        ("predator-mortality-rate,m", po::value<double>(&m)->default_value(0.06), "Predator mortality rate")
        ("prey-diffusion-rate,k", po::value<double>(&k)->default_value(0.2), "Diffusion rate of prey")
        ("predator-diffusion-rate,l", po::value<double>(&l)->default_value(0.2), "Diffusion rate of predators")
        ("time-step-size,t", po::value<double>(&deltaT)->default_value(0.4), "Time evolution step size")
        ("total-time,T", po::value<double>(&totalTime)->default_value(500.0), "Total run time")
        ("ppm-output-frequency,f", po::value<int>(&outputSteps)->default_value(10), "Output frequency in time steps of plain .ppm file")
        ("include-water,i", "Include water in average calulations over landscape")
        ("help,h", "produce help message");

    po::variables_map vm;
    po::store(po::parse_command_line(argc,argv,desc), vm);
    po::notify(vm);

    // If the user asks for help display it then exit.
    if(vm.count("help"))
    {
        cout << desc << "\n";
        return 1;
    }

    if(vm.count("include-water"))
    {
        includeWater = true;
    }

    // Inform user of their input parameters since they may want to check they are correct before running a long simulation.
    int outputColumnWidth = 30;
    cout << "Input Parameters..." << '\n';
    cout << setw(outputColumnWidth) << setfill(' ') << left << "Prey Birth Rate: " << right << r << '\n';
    cout << setw(outputColumnWidth) << setfill(' ') << left << "Predation Rate: " << right << a << '\n';
    cout << setw(outputColumnWidth) << setfill(' ') << left << "Predator Mortality Rate: " << right << b << '\n';
    cout << setw(outputColumnWidth) << setfill(' ') << left << "Prey Diffusion Rate: " << right << m << '\n';
    cout << setw(outputColumnWidth) << setfill(' ') << left << "Predator Diffusion Rate: " << right << k << '\n';
    cout << setw(outputColumnWidth) << setfill(' ') << left << "Time Step Size: " << right << l << '\n';
    cout << setw(outputColumnWidth) << setfill(' ') << left << "Time Step Size: " << right << deltaT << '\n';
    cout << setw(outputColumnWidth) << setfill(' ') << left << "Total Simulation Time: " << right << totalTime << '\n';
    cout << setw(outputColumnWidth) << setfill(' ') << left << "Output .PPM Frequency: " << right << outputSteps << '\n';
    cout << setw(outputColumnWidth) << setfill(' ') << left << "Include Water in Averages: " << right << (includeWater ? "Yes" : "No") << '\n' << '\n';




                
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
    double upperBound = 5.0;
	
    grid.setUniformDistribution(Cell::Prey, upperBound, generator);
    grid.setUniformDistribution(Cell::Predator, upperBound, generator);


    // Total number of iterations for the simulation.
    int numIterations = int(totalTime/deltaT);

    // Interval at which to print the predator and prey densities to the command line. 
    int averageDenOutputFreq = 10;

    // Initial maximal colour number for the PPM output files. 
    int maxNumberPPM;
	
    // Minimal number for the maximal colour number for the PPM output files.
    int minLimit = 10;
	
    // Changing maxNumberPPM when needed
    double scaleFactor = 2.0;
	
    // Scaling densities before printing them in the PPM output files.
    double scaling;
	
    // Evaluating scaling and maxNumberPPM
    if ( upperBound > minLimit)
    {
	    scaling = 1.0;
	    maxNumberPPM = static_cast<int>(scaleFactor * upperBound);
    }
     
    else
    {
	    scaling = minLimit/upperBound;
	    maxNumberPPM = static_cast<int>(scaleFactor * minLimit);
    }
    

    // Name of output file for average densities
    string averageDensitiesOutput(outputName + "/Average_Densities.txt");


    // Create an output file for the average densities.
    ofstream output_avrg_dens(averageDensitiesOutput, ios::out);


    if(output_avrg_dens.is_open())
    {
        // Print the column titles for the average density outputs
        output_avrg_dens << "Time    Pred Dens.    Prey Dens." << endl;
    }

    // Total number of output .ppm files.
    int totalPPMcount = numIterations/outputSteps;
    int outputDigits  = 0;
    int ppmCount      = totalPPMcount; 
    while(ppmCount != 0) 
        { 
            ppmCount/=10; 
            ++outputDigits;
        }

    // The densities of the cells in the grid are printed before any updates of the grid.
    // Iteration number numIterations allows printing values after numIterations updates, although one more update is made after that.

    Grid grid2 = grid;
    Grid* currentGrid = &grid;
    Grid* updatedGrid = &grid2;
    Grid* tempGrid;

    // Inform user we have started simulation.
    cout << "Starting Simulation..." << endl;
    for(int iter = 0; iter <= numIterations; ++iter)
    {
        // Calulate how far through simulation we are.
        double percentageComplete = 100*static_cast<double>(iter)/numIterations;
        int    basePercentage     = static_cast<int>(percentageComplete);
        int    decimalPercentage  = static_cast<int>(100 * (percentageComplete-basePercentage));
        int    numBars            = static_cast<int>(percentageComplete/2);
        string bars(numBars, '=');
        ostringstream barStringStream;
        barStringStream << setw(50) << setfill(' ') << left << bars;

        ostringstream percentageBaseStream;
        percentageBaseStream << setw(2) << setfill('0') << basePercentage; 

        ostringstream percentageDecimalStream;
        percentageDecimalStream << setw(2) << setfill('0') << decimalPercentage;

        string percentage = percentageBaseStream.str() + '.' + percentageDecimalStream.str();
        cout << '\r' << "Progress: " <<  percentage <<  "% " << '[' << barStringStream.str() << ']' << flush;


        
        
        if(0 == iter % averageDenOutputFreq)
        {

            output_avrg_dens << iter * deltaT << "       " << grid.averageDensity(Cell::Predator, includeWater) << "       " << grid.averageDensity(Cell::Prey,includeWater) << endl;

        }

        
        if(0 == iter % outputSteps)
        {  
            {
                int outFileNum = iter/outputSteps;
                ostringstream ss;
                ss << setw(outputDigits) << setfill('0') << outFileNum;
                string outputfile(outputName + "/output" + ss.str() +".ppm");
                //Creates different names for each output file in the output folder, called output
                //sprintf(outputfile,"./output/output%d.ppm",iter/outputSteps);
                
                ofstream outputPPM(outputfile, ios::out);
        
                if (outputPPM.is_open())
                {
                    maxNumberPPM = grid.printPPM(outputPPM, maxNumberPPM, scaling, scaleFactor);
                    outputPPM.close();
                }
                else
                {
                    cout << "Output .ppm file could not open." << endl;
                    cout << "Check that the specified output directory exists" << endl;
                }
            }




        }

        updateGrid(currentGrid,updatedGrid,r,a,b,m,k,l,deltaT);
        tempGrid    = currentGrid;
        currentGrid = updatedGrid; 
        updatedGrid = tempGrid;


    }
    output_avrg_dens.close();


   /**************************************************************************************************
    *************************************** TIDYING UP ***********************************************
    **************************************************************************************************/
     
   cout << "Simulation complete!..." << endl; 
   // Print the destination of output files.
   cout << "Average densities have been printed to " << averageDensitiesOutput << endl; 

   
   // Register that the program has completed.
   auto end = std::chrono::system_clock::now();


   // Calculate the elapsed time to an appropriate order. 
   auto elapsed = std::chrono::duration_cast<chrono::milliseconds>(end - start);


   // Output the time taken to run the code to the command line. 
   cout << "Time take to execute (ms):   " << elapsed.count() << endl;

   return 0;
}
