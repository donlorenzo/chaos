#ifndef _SYSTEM_HPP
#define _SYSTEM_HPP

#include <string>
#include <allegro.h>
#include "fraktal.hpp"

using namespace std;

class c_system {
	public:
	    c_system( volatile long int* _sys_timer );
	    ~c_system( void );
		void run( void );

 	private:
		bool quit_flag;
		int create_fraktal( string fraktal );
		BITMAP* buffer;
		BITMAP* info_scr;
		c_fraktal *koch;
		int depth;
		bool update_screen;

		void update_gfx( BITMAP* bmp );
		volatile long int *sys_timer;
		long int old_timer;
};


#endif

