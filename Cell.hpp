
//header guard
#ifndef Cell_hpp
#define Cell_hpp

class Cell
{
	private:
		// m_nPredator holds number of predators in cell
		int m_nPredator;
		// m_nPrey holds number of prey in cell
		int m_nPrey;
		/*
		/* m_dry tells us whether the cell is land or not
		/* true = land/dry
		/* false = wet/water
		*/
		bool m_dry;

	public:
		/*
		/* constructor that takes: number of predators
		/*						   number of prey 
		/*						   bool representing whether the cell is land or water
		/* if no arguments provided number of predators and defaults to 0 and cell is assumed to be wet
		*/
		Cell(bool dry = false,int numberPred = 0, int numberPrey = 0);
		// default destructor; no dynamic memory allocation
		~Cell();

		// getter for number of predators in cell
		int getNumbPred() const;
		// getter for number of prey in cell
		int getNumbPrey() const;
		/*
		/* getter for determining whether it is wet or dry
		/* returns true if it is dry/land false if wet/water
		*/
		bool isDry() const;

		//setter for number of predators in cell
		void setNumbPred(int numberPred = 0);
		//setter for number of prey in cell
		void setNumbPrey(int numberPrey = 0);
		//setter for making cell dry/land
		void setDry();
		//setter for making cell wet/watter, used instead of giving setDry() an argument
		void setWet();
};

#endif /* Cell_hpp */