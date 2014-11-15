#include "math.h"
#include "fenv.h"

#define ERR_NOERROR  0
#define ERR_ROUNDING 1


class c_rng
{
	public:
		c_rng();
		~c_rng();
		void seed( long unsigned int number, long int _steps );
		double next( void );
		void show_graph( void );
		int get_err( void );
	private:
		double x; 												// the current random number
		int total;												// the total amount of numbers created
		static const double HW = .03;//0.01f;		// HalfWidth of the center of the interval [0,1]
		long unsigned int steps;										// in how many discrete steps are we going to split the interval
		int old_rounding_mode;
		int err_no;
};
