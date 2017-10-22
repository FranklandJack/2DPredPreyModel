/**
 * \class Cell
 *
 * \brief Models a single cell
 *
 * A cell forms a single "square" in the landscape and is considered to have three properties
 * a predator density, a prey density and whether or not the cell is land (so dry) or water (so wet)
 * 
 *
 *
 *
 */


#ifndef Cell_hpp
#define Cell_hpp

class Cell
{
    public:
        //user defined type to hold whether the cell is wet or dry, we will use this instead of true/false as it is clearer
        enum State
        {
            Wet,
            Dry
        };

    private:
        // m_predDensity holds predator density in the cell
        double m_predDensity;
        // m_preyDensity holds prey density in the cell
        double m_preyDensity;
        /*
        /* m_state tells us whether the cell is land or not
        /* true = land/dry
        /* false = wet/water
        */
        State m_state;


    public:
        
        
        /*
        /* constructor that takes: number of predators
        /*                         number of prey 
        /*                         bool representing whether the cell is land or water
        /* if no arguments provided number of predators and defaults to 0 and cell is assumed to be wet
        */
        Cell(State = Wet, double predDensity = 0.0, double preyDensity = 0.0);
        // default destructor; no dynamic memory allocation
        ~Cell();

        // getter for the predator density of the cell
        double getPredDensity() const;

        // getter for the prey density of the cell
        double getPreyDensity() const;
        /*
        /* getter for determining whether it is wet or dry
        /* returns true if it is dry/land false if wet/water
        */
        State getState() const;

        //setter for predator density of the cell
        void setPredDensity(double predDensity = 0.0);

        //setter for prey density of cell
        void setPreyDensity(double preyDensity = 0.0);

        //setter for making cell dry/wet, defaults to wet
        void setState(State = Wet);
        
};

#endif /* Cell_hpp */