#include <iostream>
#include <stdlib.h>
#include "allegro.h"

using namespace std;

BITMAP* buffer;
//BITMAP* buffer[2];
//int current_page=0;

//	This will display the hénon-attractor with the following forumla:
//	H(x,y) = (y + 1 - a*x^2, b*x)
//	or
//	(x_n+1, y_n+1) = (y_n + 1 - a*x_n^2, b*x_n) 
//	usualy with a=1.4 and b=0.3

double delta_x = 3.0f;
double delta_y = 0.8f;


void draw_coord( BITMAP* bmp )
{
	vline( bmp, bmp->w>>1, 0, bmp->h, 7 );
	hline( bmp, 0, bmp->h>>1, bmp->w, 7 );
	int grid_x = 6;
	int grid_y = 8;
	for( int i=1; i<grid_x; i++ )
	{
		if( i == (grid_x>>1) )
			continue;
		vline( bmp, i*(bmp->w/grid_x), (bmp->h>>1) - 10, (bmp->h>>1) + 10, 7 );
		textprintf_centre_ex( bmp, font, i*(bmp->w/grid_x), (bmp->h>>1) + 12, 7, 0, "%.3f", double(i*delta_x)/double(grid_x) - (delta_x/2) );
	}
	for( int i=1; i<grid_y; i++ )
	{
		if( i == (grid_y>>1) )
			continue;
		hline( bmp, (bmp->w>>1) - 10, i*bmp->h/grid_y, (bmp->w>>1) + 10, 7 );
		textprintf_right_ex( bmp, font, (bmp->w>>1) - 12, i*bmp->h/grid_y - 4, 7, 0, "%.3f", (delta_y/2) - double(i*delta_y)/double(grid_y) );
	}
	return;
}

void henon( void )
{
	BITMAP* bmp = buffer;
//	BITMAP* bmp = buffer[current_page];
//	int display_level = 3;
	double x, y, old_x, old_y;
	double a, b;
	bool show_coord = false;
	int cnt, total;
	cnt = total = 0;
	a = 1.4f;			//	standard: 1.4f
	b = 0.3f;			//	standard: 0.3f
	old_x = 0;
	old_y = 0;
	while( !key[KEY_ESC] )
	{
		x = old_y+1-a*old_x*old_x;
		y = b*old_x;
		old_x=x;
		old_y=y;
		putpixel( bmp, int(x*800/delta_x)+400, 300-int(y*600/delta_y), 15 );
		cnt++;
		total++;

		if( key[KEY_SPACE] )
		{
			if( !show_coord )
			{
				show_coord = true;
				draw_coord( screen );
			}
		}else
		{
			if( show_coord )
			{
				show_coord = false;
				clear_bitmap( screen );
			}
		}

		if( cnt >= 1000 )
		{
			rest(1);
			textprintf_right_ex( bmp, font, bmp->w-5,  5, 7, 16, "number of points: %d", total );
			masked_blit( bmp, screen, 0, 0, 0, 0, bmp->w, bmp->h );
			cnt = 0;
		}
	}
	return;
}








int init( void )
{
	allegro_init();
	install_timer();
	install_keyboard();
	if( set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0 ) )
		return 1;
	clear_bitmap( screen );

	buffer = create_bitmap( SCREEN_W, SCREEN_H );	
	clear_bitmap( buffer );
//	buffer[0] = create_video_bitmap( SCREEN_W, SCREEN_H );
//	buffer[1] = create_video_bitmap( SCREEN_W, SCREEN_H );
//	clear_bitmap( buffer[0] );
//	clear_bitmap( buffer[1] );
	
	return 0;
}


int main(int argc, char *argv[])
{
  if( init() )
  	return 1;
  
  henon();
  
  destroy_bitmap( buffer );
//	destroy_bitmap( buffer[0] );
//	destroy_bitmap( buffer[1] );
  return 0;
}END_OF_MAIN()
