#ifndef Cell_hpp
#define Cell_hpp

// Forward declare the test class so we can friend it to the cell and then the test class will have access to the member variables.
class TestCell;


/**
 *
 * \file
 *
 * \class Cell
 *
 * \brief Models a single cell
 *
 * A cell forms a single "square" in the landscape and is considered to have three properties
 * a predator density, a prey density and whether or not the cell is land (so dry) or water (so wet)
 */
class Cell
{
    public:

        /**
        * \enum State
        *
        * \brief Enum that represents a value that can be either wet or dry.
        */
        enum State { Wet, Dry};

    private:

        /// Floating point member variable representing the predator density in the given cell as #predator in the cell.
        double m_predDensity;

        /// Floating point member variable representing the prey density in the given cell as #prey in the cell.
        double m_preyDensity;

        /**
        * \brief Member variable representing the state of the Cell as either being Wet(water) or Dry(land)
        *
        * This is implemented using the user defined enum State rather than a simple true/false bool since it provides 
        * far more clarity in terms or function arguments and conditional statements regarding the state of the Cell to 
        * work with the State variable which is explicitly Wet/Dry. Wet cells cannot contain predator or prey, so their 
        * densities will always be zero in a wet cell.
        */
        State m_state;

        /** 
         * 
         * \brief Test class for the Cell.
         * 
         * Declare a TestCell friend member variable to allow access to private member variables in test class.
         *
         */
        friend class TestCell;


    public:

        /** 
        * \brief Creates a Cell
        *
        *  Standard constructor to initialize the member variables of the Cell object.
        *  If no arguments are provided the Cell defaults to be Wet with predator and
        *  prey densities of zero.
        * 
        * \param state a Cell::State value that is either Wet or Dry setting the state
        * of the cell. Defaults to Wet.
        *
        * \param predDensity a floating point value setting the density of the predators
        * in the cell. Defaults to 0.
        *
        * \param preyDensity a floating point value setting the density of the prey in the
        * cell. Defaults to 0.
        */
        Cell(State state = Wet, double predDensity = 0.0, double preyDensity = 0.0);


        /// Default destructor; no dynamic memory allocation is required for this class.
        ~Cell();


        /** 
        * \brief Getter for the predator density in the cell.
        *
        * \return The value of m_predDensity.
        */
        double getPredDensity() const;


        /** 
        * \brief Getter for the prey density in the cell.
        *
        * \return The value of m_preyDensity.
        */
        double getPreyDensity() const;


        /** 
        * \brief Getter for the state of the cell.
        *
        * \return The value of m_state.
        */
        State getState() const;


        /**
        * \brief Setter for the predator density in the cell
        *
        * \param predDensity a floating point value setting the density of the predators in 
        * the cell. Defaults to 0.
        */
        void setPredDensity(double predDensity = 0.0);


        /**
        * \brief Setter for the prey density in the cell
        *
        * \param predDensity a floating point value setting the density of the prey in the 
        * cell. Defaults to 0.
        */
        void setPreyDensity(double preyDensity = 0.0);

        /**
        * \brief Setter for the state of the cell
        *
        * \param state a Cell::State enum value setting the state of the cell to be either 
        * Wet or Dry. Defaults to Wet.
        */
        void setState(State state = Wet);
        
};

#endif /* Cell_hpp */