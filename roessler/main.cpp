#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "allegro.h"

using namespace std;


/*
 *	ROESSLER-Attractor
 *	x' = -y - z
 *	y' = x + ay
 *	z' = b + xz - cz
 *	with the following parameters
 *		a = 0.2
 *		b = 0.2
 *		c = 5.7 ????!!!
 */

void roessel_it( double xn, double yn, double zn, double &xfn, double &yfn, double &zfn, double a, double b, double c )
{
	xfn = -yn - zn;
	yfn = xn + a* yn;
	zfn = b+xn*zn-c*zn;

	return;
}


int roessler( BITMAP* bmp )
{
	double old_x, old_y, old_z, a, b, c, dt, dt2;
	double xn, yn, zn, xn0, yn0, zn0, xfn, yfn, zfn, xfn0, yfn0, zfn0, xmax, ymax, xmin, ymin, scalex, scaley;
	a = 0.2f;
	b = 0.2f;
	c = 5.7f;
	xn = 0.001;
	yn = 0.001;
	zn = 0.001;
	dt = 0.001f;
	dt2 = dt/2.0f;
	xmax = ymax = xmin = ymin = 0;
	scalex = SCREEN_W/double(xmax-xmin);
	long int cnt = 0;
	while( !key[KEY_ESC] )
	{
		old_x = xn;
		old_y = yn;
		old_z = zn;
		roessel_it( xn, yn, zn, xfn, yfn, zfn, a,b,c );
		xn0 = xn;
		yn0 = yn;
		zn0 = zn;
		xfn0 = xfn;
		yfn0 = yfn;
		zfn0 = zfn;
		xn = xn0 + dt*xfn0;
		yn = yn0 + dt*yfn0;
		zn = zn0 + dt*zfn0;
		roessel_it( xn, yn, zn, xfn, yfn, zfn, a,b,c );
		xn = xn0 + dt2*(xfn + xfn0 );
		yn = yn0 + dt2*(yfn + yfn0 );
		zn = zn0 + dt2*(zfn + zfn0 );
		cnt++;
		if( cnt < 100000 )
		{
			if( xn+1 > xmax )
				xmax = xn+1;
			if( xn-1 < xmin )
				xmin = xn-1;
			if( yn+zn+1 > ymax )
				ymax = yn+zn+1;
			if( yn+zn-1 < ymin )
				ymin = yn+zn-1;
			scalex = SCREEN_W/double(xmax-xmin);
			scaley = SCREEN_H/double(ymax-ymin);
		}else
		{
			int color_r, color_g, color_b;
			double dist = sqrt(xn*xn + yn*yn + zn*zn);
			double max = MAX(abs(xmax/2.),MAX(abs(xmin/2.),MAX(abs(ymax*2./3.),abs(ymin*2./3.))));
			double color = dist*1024/max;
			
			switch( int(color/256) )
			{
				case 0:
					color_r = 255;
					color_g = int( color );
					color_b = 0;
					break;
				case 1:
					color_r = 512 - int( color );
					color_g = 255;
					color_b = 0;
					break;
				case 2:
					color_r = 0;
					color_g = 255;
					color_b = int( color ) - 512;
					break;
				case 3:
					color_r = 0;
					color_g = 1024 - int( color );
					color_b = 255;
					break;
				default:
					color_r = color_g = 0;
					color_b = 255;
			}
			color_r = MID( 0, color_r, 255 );
			color_g = MID( 0, color_g, 255 );
			color_b = MID( 0, color_b, 255 );

			line( screen, int(scalex*(old_x-xmin)), SCREEN_H + int(scaley*(ymin-old_y-old_z)), int(scalex*(xn-xmin)), SCREEN_H + int(scaley*(ymin-yn-zn)), makecol(color_r,color_g,color_b) );
		}

/*		textprintf_ex( screen, font, 10, 10, 15, 0, "x = %f", xn );
		textprintf_ex( screen, font, 10, 20, 15, 0, "y = %f", yn );
		textprintf_ex( screen, font, 10, 30, 15, 0, "z = %f", zn );
*/
//		while( !key[KEY_SPACE] );
//		while( key[KEY_SPACE] );
	}
	
	return 0;
}


BITMAP* init( void )
{
	allegro_init();
	install_timer();
	install_keyboard();
	set_color_depth( 24 );
	if( set_gfx_mode( GFX_AUTODETECT_WINDOWED, 400, 500, 0, 0 ) )
		return NULL;
	clear_bitmap( screen );

	BITMAP* buffer = create_bitmap( SCREEN_W, SCREEN_H );	
	clear_bitmap( buffer );
	
	return buffer;
}

int main(int argc, char *argv[])
{
  BITMAP* buffer = init();
	if( buffer == NULL )
  	return 1;
  
  roessler( buffer );
  
  destroy_bitmap( buffer );
  return 0;
}END_OF_MAIN()
