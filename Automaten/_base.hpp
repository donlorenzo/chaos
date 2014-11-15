#ifndef _BASE_HPP
#define _BASE_HPP

#include <stdlib.h>
#include <fstream>
#include "allegro.h"

using namespace std;

// GLOBAL
// LOG file
//ofstream LOG ( "log.txt" );

inline void set_bit( char &byte, int bit ){ byte |= (1<<bit); }
inline bool get_bit( char byte, int bit ){ return( byte & (1<<bit) ); }
inline void clear_bit( char &byte, int bit ){ byte &= ~(1<<bit); }



#endif // _BASE_HPP
