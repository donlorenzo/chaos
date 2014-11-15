#ifndef _FRAKTAL_HPP
#define _FRAKTAL_HPP

#include <allegro.h>
#include "logger.h"
#include <cmath>

using namespace std;


typedef struct position {
	float startx, starty;
 	float endx, endy;    
};  

typedef struct koch_line {
	position pos;
	float length;
 	float angle;
	koch_line *next;
	koch_line *prev;
};    


class c_fraktal {
    public:
        c_fraktal( void );
        ~c_fraktal( void );
        int create_fraktal();
        void calculate( int depth );
        int line_cnt;
        BITMAP* show( void );
    private:
    
	protected:
	    void redraw();
		void insert( koch_line *koch_kurve );
        int how_many( void );
        void clean_up( void );
	    BITMAP* img;
		koch_line *koch_kurve;
};


#endif

