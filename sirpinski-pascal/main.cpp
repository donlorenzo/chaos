#include <iostream>
#include <stdlib.h>
#include "allegro.h"

using namespace std;

void sirpinski( BITMAP* bmp )
{
//	bmp = screen;
	int field[bmp->w][bmp->h];
	for( int i=0; i<bmp->w; i++ )
		for( int j=0; j<bmp->h; j++ )
			field[i][j] = 0;
	for( int i=1; i<bmp->h; i++ )
		field[1][i] = 1;
	for( int x=2; x<bmp->w; x++ )
		for( int y=1; y<bmp->h; y++ )
		{
			if( key[KEY_ESC] ) return;
			field[x][y] = field[x-1][y] + field[x][y-1];
//			if( field[x][y]%16 != 0 )
//				putpixel( bmp, x,y, makecol(0,0,255) );
//			if( field[x][y]%8 != 0 )
//				putpixel( bmp, x, y, makecol(0,255,0) );
//			if( field[x][y]%4 != 0 )
//				putpixel( bmp, x, y, makecol(255,0,0) );
			if( field[x][y]%2 != 0 )
				putpixel( bmp, x, y, 15 );
		}
	if( bmp != screen )
		blit( bmp, screen, 0, 0, 0, 0, bmp->w, bmp->h );
	while( !key[KEY_ESC] );
	return;
}


BITMAP* init( void )
{
	allegro_init();
	install_timer();
	install_keyboard();
	if( set_gfx_mode( GFX_AUTODETECT_WINDOWED, 1000, 400, 0, 0 ) )
		return NULL;
	clear_bitmap( screen );

	BITMAP* buffer = create_bitmap( SCREEN_W, SCREEN_H );	
	clear_bitmap( buffer );
	
	return buffer;
}


int main(int argc, char *argv[])
{
	BITMAP* buffer;
	buffer = init();
	if( buffer == NULL )
  	return 1;
  
  sirpinski( buffer );

  destroy_bitmap( buffer );
  return 0;
}END_OF_MAIN()
