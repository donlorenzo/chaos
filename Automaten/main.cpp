#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "allegro.h"


using namespace std;

#define ALIVE 1
#define DEAD	0
// GLOBALS
// LOG file
std::ofstream LOG ( "log.txt" );

inline void set_bit( char &byte, int bit )
{
	byte |= (1<<bit);
}
inline bool get_bit( char byte, int bit )
{
	return( byte & (1<<bit) );
}
inline void clear_bit( char &byte, int bit )
{
	byte &= ~(1<<bit);
}



// MEHRHEITS REGEL
void mehrheit( BITMAP* bmp )
{
	int x, y;
	bool* field[2];
	field[0] = (bool*) malloc( (bmp->w*bmp->h)*sizeof( bool ) );
	field[1] = (bool*) malloc( (bmp->w*bmp->h)*sizeof( bool ) );
	int current_field = 0;

	// distribute LIFE!!!
	for( x=0; x<bmp->w; x++ )
		for( y=0; y<bmp->h; y++ )
			field[0][y*bmp->w+x] = field[1][y*bmp->w+x] = rand()%2;
			
	while( !key[KEY_ESC] )
	{
		rest( 1 );
		clear_bitmap( bmp );
		for( x=0; x<bmp->w; x++ )
			for( y =0; y<bmp->h; y++ )
				if( field[current_field][y*bmp->w+x] == ALIVE )
					putpixel( bmp, x, y, 15 );
		textprintf_centre_ex( bmp, font, bmp->w>>1,  5, 0, 0, "           " );
		textprintf_centre_ex( bmp, font, bmp->w>>1, 15, 0, 0, "           " );
		textprintf_centre_ex( bmp, font, bmp->w>>1, 10, 4, 0, " Mehrheit! " );
		blit( bmp, screen, 0, 0, 0, 0, bmp->w, bmp->h );
		for( x=1; x<bmp->w-1; x++ )
			for( y=1; y<bmp->h-1; y++ )
			{
				int sum = field[current_field][(y-1)*bmp->w+x-1] + 
									field[current_field][(y-1)*bmp->w+x] + 
									field[current_field][(y-1)*bmp->w+x+1] + 
									field[current_field][y*bmp->w+x-1] + 
									field[current_field][y*bmp->w+x] + 
									field[current_field][y*bmp->w+x+1] + 
									field[current_field][(y+1)*bmp->w+x-1] + 
									field[current_field][(y+1)*bmp->w+x] + 
									field[current_field][(y+1)*bmp->w+x+1];
				if( sum > 4 )
					field[!current_field][y*bmp->w+x] = ALIVE;
				else
					field[!current_field][y*bmp->w+x] = DEAD;
			}
		current_field = !current_field;
		rest(100);
//		while( !key[KEY_SPACE] );
//		while( key[KEY_SPACE] );
	}
	free( field[0] );
	free( field[1] );
	return;
}
// MEHRHEITS REGEL ENDE


// EINS-AUS-ACHT-REGEL
void eins_aus_acht( BITMAP* bmp )
{
	int x, y;
	bool* field[2];
	field[0] = (bool*) malloc( (bmp->w*bmp->h)*sizeof( bool ) );
	field[1] = (bool*) malloc( (bmp->w*bmp->h)*sizeof( bool ) );
	int current_field = 0;

	for( x=0; x<bmp->w; x++ )
		for( y=0; y<bmp->h; y++ )
			field[0][y*bmp->w+x] = field[1][y*bmp->w+x] = DEAD;
			
	// seed life!
	field[0][bmp->w*(bmp->h>>1)+(bmp->w>>1)] = field[1][bmp->w*(bmp->h>>1)+(bmp->w>>1)] = ALIVE;

	while( !key[KEY_ESC] )
	{
		rest( 1 );
		clear_bitmap( bmp );
		for( x=0; x<bmp->w; x++ )
			for( y =0; y<bmp->h; y++ )
				if( field[current_field][y*bmp->w+x] == ALIVE )
					putpixel( bmp, x, y, 15 );
		textprintf_centre_ex( bmp, font, bmp->w>>1,  5, 0, 0, "               " );
		textprintf_centre_ex( bmp, font, bmp->w>>1, 15, 0, 0, "               " );
		textprintf_centre_ex( bmp, font, bmp->w>>1, 10, 4, 0, " Eins aus Acht " );
 		blit( bmp, screen, 0, 0, 0, 0, bmp->w, bmp->h );
		for( x=1; x<bmp->w-1; x++ )
			for( y=1; y<bmp->h-1; y++ )
			{
				int sum = field[current_field][(y-1)*bmp->w+x-1] + 
									field[current_field][(y-1)*bmp->w+x] + 
									field[current_field][(y-1)*bmp->w+x+1] + 
									field[current_field][y*bmp->w+x-1] + 
//									field[current_field][y*bmp->w+x] + 
									field[current_field][y*bmp->w+x+1] + 
									field[current_field][(y+1)*bmp->w+x-1] + 
									field[current_field][(y+1)*bmp->w+x] + 
									field[current_field][(y+1)*bmp->w+x+1];
				if( sum == 1 )
					field[!current_field][y*bmp->w+x] = ALIVE;
//				else
//					field[!current_field][y*bmp->w+x] = DEAD;
			}
		current_field = !current_field;
		memcpy( field[!current_field], field[current_field], (bmp->w*bmp->h)*sizeof(bool) );
//		rest(100);
//		while( !key[KEY_SPACE] );
//		while( key[KEY_SPACE] );
	}
	free( field[0] );
	free( field[1] );
	return;
}
// EINS-AUS-ACHT-REGEL


// SPIEL DES LEBENS
void spiel( BITMAP* bmp )
{
	int x, y;
	bool* field[2];
	field[0] = (bool*) malloc( (bmp->w*bmp->h)*sizeof( bool ) );
	field[1] = (bool*) malloc( (bmp->w*bmp->h)*sizeof( bool ) );
	int current_field = 0;

	for( x=0; x<bmp->w; x++ )
		for( y=0; y<bmp->h; y++ )
			field[0][y*bmp->w+x] = field[1][y*bmp->w+x] = rand()%2;
			
	// seed life!
	field[0][bmp->w*(bmp->h>>1)+(bmp->w>>1)] = field[1][bmp->w*(bmp->h>>1)+(bmp->w>>1)] = ALIVE;

	while( !key[KEY_ESC] )
	{
		rest( 1 );
		clear_bitmap( bmp );
		for( x=0; x<bmp->w; x++ )
			for( y =0; y<bmp->h; y++ )
				if( field[current_field][y*bmp->w+x] == ALIVE )
					putpixel( bmp, x, y, 15 );
		textprintf_centre_ex( bmp, font, bmp->w>>1,  5, 0, 0, "                  " );
		textprintf_centre_ex( bmp, font, bmp->w>>1, 15, 0, 0, "                  " );
		textprintf_centre_ex( bmp, font, bmp->w>>1, 10, 4, 0, " Spiel des Lebens " );
 		blit( bmp, screen, 0, 0, 0, 0, bmp->w, bmp->h );
		for( x=1; x<bmp->w-1; x++ )
			for( y=1; y<bmp->h-1; y++ )
			{
				int sum = field[current_field][(y-1)*bmp->w+x-1] + 
									field[current_field][(y-1)*bmp->w+x] + 
									field[current_field][(y-1)*bmp->w+x+1] + 
									field[current_field][y*bmp->w+x-1] + 
//									field[current_field][y*bmp->w+x] + 
									field[current_field][y*bmp->w+x+1] + 
									field[current_field][(y+1)*bmp->w+x-1] + 
									field[current_field][(y+1)*bmp->w+x] + 
									field[current_field][(y+1)*bmp->w+x+1];
				if( sum == 3 )
					field[!current_field][y*bmp->w+x] = ALIVE;
				if( sum > 3 || sum < 2 )
					field[!current_field][y*bmp->w+x] = DEAD;
			}
		current_field = !current_field;
		memcpy( field[!current_field], field[current_field], (bmp->w*bmp->h)*sizeof(bool) );
//		rest(100);
//		while( !key[KEY_SPACE] );
//		while( key[KEY_SPACE] );
	}
	free( field[0] );
	free( field[1] );
	return;
}
// SPIEL DES LEBENS ENDE

// PARITÄT
void paritaet( BITMAP* bmp )
{
	int x, y;
	bool* field[2];
	field[0] = (bool*) malloc( (bmp->w*bmp->h)*sizeof( bool ) );
	field[1] = (bool*) malloc( (bmp->w*bmp->h)*sizeof( bool ) );
	int current_field = 0;

	for( x=0; x<bmp->w; x++ )
		for( y=0; y<bmp->h; y++ )
			field[0][y*bmp->w+x] = field[1][y*bmp->w+x] = DEAD;
			
	// seed life!
	for( x = (bmp->w/2)-4; x<(bmp->w/2)+4; x++ )
		for( y = (bmp->h/2)-4; y<(bmp->h/2)+4; y++ )
			field[0][y*bmp->w+x] = ALIVE;
	
//	field[0][bmp->w*(bmp->h>>1)+(bmp->w>>1)] = field[1][bmp->w*(bmp->h>>1)+(bmp->w>>1)] = ALIVE;

	while( !key[KEY_ESC] )
	{
		rest( 1 );
		clear_bitmap( bmp );
		for( x=0; x<bmp->w; x++ )
			for( y =0; y<bmp->h; y++ )
				if( field[current_field][y*bmp->w+x] == ALIVE )
					putpixel( bmp, x, y, 15 );
		textprintf_centre_ex( bmp, font, bmp->w>>1,  5, 0, 0, "         " );
		textprintf_centre_ex( bmp, font, bmp->w>>1, 15, 0, 0, "         " );
		textprintf_centre_ex( bmp, font, bmp->w>>1, 10, 4, 0, " Parität " );
 		blit( bmp, screen, 0, 0, 0, 0, bmp->w, bmp->h );
		for( x=1; x<bmp->w-1; x++ )
			for( y=1; y<bmp->h-1; y++ )
			{
				int sum = field[current_field][(y-1)*bmp->w+x] + 
									field[current_field][y*bmp->w+x-1] + 
									field[current_field][y*bmp->w+x] + 
									field[current_field][y*bmp->w+x+1] + 
									field[current_field][(y+1)*bmp->w+x];
				field[!current_field][y*bmp->w+x] = sum%2;
			}
		current_field = !current_field;
		memcpy( field[!current_field], field[current_field], (bmp->w*bmp->h)*sizeof(bool) );
//		rest(100);
//		while( !key[KEY_SPACE] );
//		while( key[KEY_SPACE] );
	}
	free( field[0] );
	free( field[1] );
	return;
}
// PARITÄT ENDE


BITMAP* init( void )
{
	srand(time(0));
	allegro_init();
	install_timer();
	install_keyboard();
	install_mouse();
//	set_color_depth( 24 );
	if( set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0 ) )
		return NULL;
	clear_bitmap( screen );
	show_mouse( NULL );

	BITMAP* buffer = create_bitmap( SCREEN_W, SCREEN_H );	
	clear_bitmap( buffer );
	
	return buffer;
}

int main(int argc, char *argv[])
{
	LOG << "LOG-File from spiel_des_lebens.exe" << endl << endl;
  BITMAP* buffer = init();
	if( buffer == NULL )
  	return 1;
  
  mehrheit( buffer );
	while( key[KEY_ESC] );
	eins_aus_acht( buffer );
	while( key[KEY_ESC] );
	spiel( buffer );  
	while( key[KEY_ESC] );
	paritaet( buffer );
	
	  
  destroy_bitmap( buffer );
	LOG << "save exit... good bye!" << endl << endl;
  return 0;
}END_OF_MAIN()
