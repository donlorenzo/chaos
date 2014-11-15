#ifndef REGELN_HPP
#define REGELN_HPP

#include "_base.hpp"

#define ALIVE 1
#define DEAD	0

void game_of_life( bool* old_field, bool* new_field, int width, int height );
void majority( bool* old_field, bool* new_field, int width, int height );
void one_of_eight( bool* old_field, bool* new_field, int width, int height );
void parity( bool* old_field, bool* new_field, int width, int height );
void pascal( bool* old_field, bool* new_field, int width, int height );


#endif // REGELN_HPP
