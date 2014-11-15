#include "allegro.h"
#include <list>

using namespace std;

list<double> values;
long int k;
double x, x0, x1;
double scale_x, scale_y, a=3.0f;
int right, bottom;
BITMAP* buffer;

inline int rndint( double x ){ return( int(x+0.5f) ); }




void draw_curve( void )
{
	double j;
	for( int i=10; i<right; i++ )
	{
		j = (i-10)/scale_x;
		putpixel( buffer, i, rndint(bottom - scale_y*(a*j*(1-j))), 15 );
	}
}


void draw_grid( void )
{
	line( buffer, 10, bottom, right, bottom, 15 );
	line( buffer, 10, bottom, 10, 10, 15 );
	line( buffer, 10, bottom, right, 10, 15 );
	draw_curve();
}




void draw_next( bool update )
{
	if( update )
	{
		k = 0;
		clear_bitmap( buffer );
		draw_grid();
		x0 = x;
		x1 = a*x0*(1-x0);
		vline( buffer, 10 + rndint(scale_x*x0), bottom, bottom - rndint(scale_x*x1), 4 );
		hline( buffer, 10 + rndint(scale_x*x1), bottom - rndint(scale_y*x1), 10 + rndint(scale_x*x0), 4 );
		textprintf_ex( buffer, font, 10, SCREEN_H-8, 15, 0, "x0 = %1.5f", x );
	}else
	{
		x1 = a*x0*(1-x0);
		hline( buffer, 10 + rndint(scale_x*x0), bottom - rndint(scale_y*x1), 10 + rndint(scale_y*x1), 4 );
		vline( buffer, 10 + rndint(scale_x*x0), bottom - rndint(scale_x*x0), bottom - rndint(scale_y*x1), 4 );
		textprintf_right_ex( buffer, font, right, SCREEN_H-8, 15, 0, "a = %1.3f", a );
		textprintf_centre_ex( buffer, font, SCREEN_W/2, SCREEN_H-8, 15, 0, "  x%ld = %1.5f  ", k, x0 ); 
	}
	x0 = x1;
	k++;
}

void feigenbaum( void )
{
	clear_bitmap( screen );
	double old_x, old_a;
	old_x = x;
	old_a = a;
	bool abort = false;
	
	line( screen, 10, bottom, right, bottom, 15 );
	line( screen, 10, bottom, 10, 10, 15 );
	textprintf_ex( screen, font, 1, bottom-8, 15, 0, "0" );
	textprintf_ex( screen, font, 1, 10, 15, 0, "1" );
	textprintf_ex( screen, font, 10, bottom+2, 15, 0, "1" );
	textprintf_ex( screen, font, right, bottom+2, 15, 0, "4" );
	textprintf_centre_ex( screen, font, 10 + rndint((2*scale_x)/3.0f), bottom+2, 15, 0, "3" );
	textprintf_centre_ex( screen, font, 10 + rndint((2.5699456*scale_x)/3.0f), bottom+2, 15, 0, "s" );
	textprintf_centre_ex( screen, font, 10 + rndint(((old_a-1)*scale_x)/3.0f), bottom+2, 7, 0, "a" );
	vline( screen, 10 + rndint(((old_a-1)*scale_x)/3.0f), bottom+2, bottom - 5, 7 );
	vline( screen, 10 + rndint((2*scale_x)/3.0f), bottom+1, 10, 7 );
	vline( screen, 10 + rndint((2.5699456*scale_x)/3.0f), bottom+1, 10, 7 );
	for( int i=10; i<right; i++ )
	{
		values.clear();
		x0 = 0.5f;
		a = 1.0f+(3.0f*(i-10)/scale_x);
		textprintf_ex( screen, font, 100, 100, 15, 0, "progress: %3d%%", rndint(double(100*(i-10))/double(right-10) ) );
		
		for( k=0; k<1000; k++ )
		{
			if( key[KEY_ESC] )
			{
				abort = true;
				break;
			}
			x0 = a*x0*(1-x0);
			if( k>500 )
				values.push_back( x0 );
		}
		if( abort )
			break;
		values.sort();
		values.unique();
		for( list<double>::iterator it = values.begin(); it != values.end(); ++it )
			putpixel( screen, i, bottom - rndint(scale_y*(*it)), 4 );
	}
	
	x = old_x;
	a = old_a;
	clear_keybuf();
	if( !abort ) 
		while( !keypressed() );
	return;
}


void run( void )
{
	x = 0.324f;
	double step = 0.01f;
	draw_grid();
	bool update;
	draw_next(true);
	while( !key[KEY_ESC] )
	{
		update = false;
		if( key[KEY_LEFT] && x-(1/scale_x) >=0 )
		{
			x -= 1.0f/scale_x;
			update = true;
		}
		if( key[KEY_RIGHT] && x+(1/scale_x) <=1 )
		{
			x += 1.0f/scale_x;
			update = true;
		}
		if( key[KEY_UP] && a+step <= 4.0f )
		{
			a += step;
			update = true;
		}
		if( key[KEY_DOWN] && a-step >= 1.0f )
		{
			a -= step;
			update = true;
		}
		if( key[KEY_F] )
		{
			feigenbaum();
			update = true;
			while( key[KEY_ESC] );
		}
		draw_next( update );
		blit( buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
	}
	return;
}

static void init( void )
{
	allegro_init();
	install_keyboard();
	install_mouse();
	if( set_gfx_mode( GFX_AUTODETECT_WINDOWED, 600, 600, 0, 0 ) )
		exit( 1 );
	buffer = create_bitmap( SCREEN_W, SCREEN_H );
	right = SCREEN_W-10;
	bottom = SCREEN_H-10;
	scale_x = double(right-10);
	scale_y = double(bottom-10);
	return;
}

int main( void )
{
	init();
	run();
	destroy_bitmap( buffer );
	return 0;
}END_OF_MAIN()
