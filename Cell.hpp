class Cell
{
	private:
		int m_nPredator;
		int m_nPrey;
		bool m_dry;

	public:

		Cell(int numberPred = 0, int numberPrey = 0, bool dry = true);
		~Cell();

		int getNumbPred();
		int getNumbPrey();

		void setNumbPred(int numberPred = 0);
		void setNumbPrey(int numberPrey = 0);
};