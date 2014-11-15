/*	THE CELLULAR AUTOMATE
    by Lorenz "DonLorenzo" Quack (Freiburg i.Br., Germany the 25.2.2005)
      
    This program simulates all cellular automates which depende on exactly 3
    other cells. you can determine if a cell lives or dies by applying different
    rules. because the status depends on 3 cells there are 2³ differnt posible
    situations ("1"represents alive and "0" dead):
       0        1        2        3        4        5        6        7
    |1|1|1|; |0|1|1|; |1|0|1|; |0|0|1|; |1|1|0|; |0|1|0|; |1|0|0|; |0|0|0|
    now you can say if a cell lives or dies in a given situation by creating a
    bitmask and converting it into a 8-Bit Character.
    Example:
      you want a cell to live in the situation 1,3,5 and 6!
      1) you convert that into a bitmask:
          0101 0110
      2) now you convert that into a 8-Bit Character:
          0101 0110 -> 86
      3) finished! 86 is the rule you want!
    one more example:
      you want a cell to live in the situations 0,2,3,6 and 7!
      1) bitmask: 1011 0011
      2) Char:  1011 0011 -> 179
      3) go ahaed and try rule #179.
    
    NOTE: if you don't know how to convert a binary bitmask to an integer go and
      google it up or try to figure it out with a scientific calculator...
      
    some rules which will generate the sirpinski triangle:
      18, 22, 26, 82,90, 146, 154, 210, 218 
    invers sirpinski:
      182
    sirpinski which gets disturbed:
      126, 129, 161, 167
    some other stuff:
      30, 45, 50, 57, 60, 73, 105, 150(!), 151, 153, 169
    of cours there are much mor stuff like pure black (8), pure white (255),
    vertical line (4) and many more... enjoy!

    4 more things:
      1) the new cell is in the middle of the three it depends on and exactly
         one row below.
      2) the seed will be placed in the top row in the middle of the screen
      3) rule# 0 will quit the programm
      4) you have to enter the rule in the console and switch to the gfx window
         to see the result. I know this is a pain in the ass but so is
         programming an input interface with allegro!
*/

#include <iostream>
#include "allegro.h"

using namespace std;

#define WIDTH   (400)
#define HEIGHT  (300)


// GLOBAL STUFF
bool* field = (bool*)malloc( sizeof( bool )*WIDTH*HEIGHT );

inline void setBit( unsigned char &byte, unsigned char bit )
{ byte |= (1<<bit); }
inline void clearBit( unsigned char &byte, unsigned char bit )
{ byte &= ~(1<<bit); }
inline bool getBit( unsigned char byte, unsigned char bit )
{ return( (byte & (1<<bit)?true:false) ); }
inline void writeBit( unsigned char &byte, unsigned char bit, bool value ) {
  // https://graphics.stanford.edu/~seander/bithacks.html#ConditionalSetOrClearBitsWithoutBranching
  unsigned char mask = (1<<bit);
  byte = (byte & ~mask) | (-value & mask);
/*
  if( value )
    setBit( byte, bit );
  else
    clearBit( byte, bit );
*/
}


// sets up allegro
void init( void )
{
  allegro_init();
  install_keyboard();
  set_color_depth( 8 );
  set_gfx_mode( GFX_AUTODETECT_WINDOWED, WIDTH, HEIGHT, 0, 0 );
  
  return;
}

// does all the work
void run( unsigned char automat )
{
  BITMAP* bmp = create_bitmap( SCREEN_W, SCREEN_H );
  clear_bitmap( bmp );
  // reset bitfield
  memset (field, 0, sizeof(bool)*SCREEN_W * SCREEN_H);  
  // Seed
  field[SCREEN_W/2] = 1;
  putpixel( bmp, SCREEN_W/2, 0, 15 );

  // here we go...
  for( int y = 1; y< SCREEN_H; y++ ) {
    for( int x=1; x<SCREEN_W-1; x++ ) {
      // figure out in which situation we are
      unsigned char situation = 0;
      writeBit( situation, 0, field[(y-1)*SCREEN_W+x-1] );
      writeBit( situation, 1, field[(y-1)*SCREEN_W+x] );
      writeBit( situation, 2, field[(y-1)*SCREEN_W+x+1] );
      // look how we're supposed to react and react!
      if( getBit( automat, situation ) ) {
        field[y*SCREEN_W+x] = 1;
        putpixel( bmp, x, y, 15 );
      } else {
        field[y*SCREEN_W+x] = 0;
      }
    }
  }
  blit( bmp, screen, 0, 0, 0, 0, bmp->w, bmp->h );
  allegro_message( "rule# %d", automat );
  destroy_bitmap( bmp );
  return;
}

// entry point
int main( void )
{
  init();
  unsigned char automat = 1;
  while( automat != 0 ) {
    int temp = 0;
    cin >> temp;
    automat = (unsigned char)temp;
    if( automat != 0 )
      run( automat );
  }
  // go through ALL rules
//  for( int a=0; a<256; a++ )
//    run( a );

  // clean up
  free( field );
  return 0;
}END_OF_MAIN()
