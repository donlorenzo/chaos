#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include "allegro.h"

using namespace std;

/*
 *	LORENTZ-Attractor
 *	x' = -ax + ay
 *	y' = cx - y - xz
 *	z' = -bz + xy
 *	with the following parameters
 *		a = 10
 *		b = 8/3
 *		c = 28
 * 	Attractor is approximately at
 *		x = +/-8.4f;
 *		y = +/-8.4f;
 *		z = 27.0f;
 */

// GLOBALS
// LOG file
std::ofstream LOG ( "log.txt" );


void lorentz_it( double xn, double yn, double zn, double &xfn, double &yfn, double &zfn, double a, double b, double c )
{
	zfn = -b*zn + xn*yn;
	yfn = c*xn - yn - zn*xn;
	xfn = a*(yn-xn);

	return;
}


int lorentz( BITMAP* bmp )
{
	// declare the variables
//	double x, y, z, old_x, old_y, old_z, a, b, c, temp_x, temp_y, dt, dt2;
	double old_x, old_y, old_z, a, b, c, dt, dt2;
	double xn, yn, zn, xn0, yn0, zn0, xfn, yfn, zfn, xfn0, yfn0, zfn0, xmax, ymax, xmin, ymin, scalex, scaley;
	double alpha;
	alpha = M_PI/4;
	long long unsigned int cnt;
	int old_mouse_x, old_mouse_y;
	// initialize them
	//set Attractor parameters
	a = 10.0f;
	b = 8.0f/3.0f;
	c = 28;

	//set view
	xmax = 46/sqrt(2.);
	xmin = -46/sqrt(2.);
	ymax = 48;
	ymin = 1;
	scalex = SCREEN_W/double(xmax-xmin);
	scaley = SCREEN_H/double(ymax-ymin);
	
	//set start point
	xn = -2.1f;
	yn = -3.0f;
	zn = 10.1f;
	
	//set resolution
	dt = 0.008f;//0.0002f;
	dt2 = dt/2.0f;
	
	//misc Variables
	cnt = 0;
	while( !key[KEY_ESC] )
	{
		// here goes the LORENTZ-Attractor...
		old_x = xn;
		old_y = yn;
		old_z = zn;
		lorentz_it( xn, yn, zn, xfn, yfn, zfn, a,b,c );
		xn0 = xn;
		yn0 = yn;
		zn0 = zn;
		xfn0 = xfn;
		yfn0 = yfn;
		zfn0 = zfn;
		xn = xn0 + dt*xfn0;
		yn = yn0 + dt*yfn0;
		zn = zn0 + dt*zfn0;
		lorentz_it( xn, yn, zn, xfn, yfn, zfn, a,b,c );
		xn = xn0 + dt2*(xfn + xfn0 );
		yn = yn0 + dt2*(yfn + yfn0 );
		zn = zn0 + dt2*(zfn + zfn0 );
		// ...LORENTZ-Attractor is finished
		cnt++;

		// play nice with CPU every now and then
		if( cnt % 500 == 0 )
			rest(1);
		// START color stuff //
		int color_r, color_g, color_b;
		// distance from the closest attractor
		double dist = (fabs(MIN(((xn+8.4)*(xn+8.4) + (yn+8.4)*(yn+8.4) + (zn-27.5)*(zn-27.5)), ((xn-8.4)*(xn-8.4) + (yn-8.4)*(yn-8.4) + (zn-27)*(zn-27)))));
		// largest possible distance
		double max = MAX(abs(xmax/3.),MAX(abs(xmin/3.),MAX(abs(ymax/2.),abs(ymin/2.))));
		max = max * max;
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
		// END color stuff //
		
		// PLOT!!!
/*	BACKUP
 *	int x1 = int(scalex*(old_x+old_y-xmin));
 *	int y1 = SCREEN_H + int(scaley*(ymin-old_z));
 *	int x2 = int(scalex*(xn+yn-xmin));
 *	int y2 = SCREEN_H + int(scaley*(ymin-zn));
 */
 		int x1 = int(scalex*(cos(alpha)*old_x+sin(alpha)*old_y-xmin));
		int y1 = SCREEN_H + int(scaley*(ymin-old_z));
		int x2 = int(scalex*(cos(alpha)*xn+sin(alpha)*yn-xmin));
		int y2 = SCREEN_H + int(scaley*(ymin-zn));
 
		line( screen, x1, y1, x2, y2, makecol(color_r,color_g,color_b) );
//		putpixel( screen, int( scalex*(xn+yn-xmin) ), SCREEN_H + int( scaley*(ymin-zn) ), makecol(color_r,color_g,color_b) );

		// misc stuff
		// START mouse //
		if( old_mouse_x != mouse_x || old_mouse_y != mouse_y )
		{
			vline( screen, old_mouse_x, old_mouse_y-5, old_mouse_y+5, makecol(0,0,0) );
			hline( screen, old_mouse_x-5, old_mouse_y, old_mouse_x+5, makecol(0,0,0) );				
			old_mouse_x = mouse_x;
			old_mouse_y = mouse_y;
			vline( screen, old_mouse_x, old_mouse_y-5, old_mouse_y+5, makecol(255,255,255) );
			hline( screen, old_mouse_x-5, old_mouse_y, old_mouse_x+5, makecol(255,255,255) );
		}
		if( mouse_b&1 )
		{
			old_x = xn = ( mouse_x/scalex + xmin )/2.;
			old_y = yn = ( mouse_x/scalex + xmin )/2.;
			old_z = zn = (SCREEN_H - mouse_y)/scaley + ymin;
		}
		// END mouse //
			
		// START user input //
		if( key[KEY_RIGHT] )	// rotate the attractor to the right
		{
			alpha += M_PI/360;
			clear_bitmap( screen );
			line( screen, SCREEN_W/2, 1+SCREEN_H/2, SCREEN_W/2 + int(cos(alpha)*10), 1+SCREEN_H/2, makecol( 255,0,0 ) );
			line( screen, SCREEN_W/2, SCREEN_H/2, SCREEN_W/2 + int(sin(alpha)*10), SCREEN_H/2, makecol( 0,0,255 ) );
			textprintf_right_ex( screen, font, SCREEN_W-10, 10, makecol(255,255,255), 0, "alpha = %.2f", alpha*180/M_PI );
		}
		if( key[KEY_LEFT] )	// rotate the attractor to the left
		{
			alpha -= M_PI/360;
			clear_bitmap( screen );
			line( screen, SCREEN_W/2, 1+SCREEN_H/2, SCREEN_W/2 + int(cos(alpha)*10), 1+SCREEN_H/2, makecol( 255,0,0 ) );
			line( screen, SCREEN_W/2, SCREEN_H/2, SCREEN_W/2 + int(sin(alpha)*10), SCREEN_H/2, makecol( 0,0,255 ) );
			textprintf_right_ex( screen, font, SCREEN_W-10, 10, makecol(255,255,255), 0, "alpha = %.2f", alpha*180/M_PI );
		}
		if( alpha > 2*M_PI )
			alpha -= 2*M_PI;
		if( alpha < 0 )
			alpha += 2*M_PI;


		if( key[KEY_UP] && dt > 0.00001f) // increase resolution
		{
			dt /= 1.1f;
			dt2 = dt/2.0f;
			textprintf_ex( screen, font, 10, 10, makecol(255,255,255), 0, "dt = %1.7f", dt );
			rest(50);
		}
		if( key[KEY_DOWN] && dt < 0.05f )	// decrease resolution
		{
			dt *= 1.1f;
			dt2 = dt/2.0f;
			textprintf_ex( screen, font, 10, 10, makecol(255,255,255), 0, "dt = %1.7f", dt );
			rest(50);
		}
		if( key[KEY_ENTER] )
			clear_bitmap( screen );
		// END user input //
	}

	return 0;
}


BITMAP* init( void )
{
	allegro_init();
	install_timer();
	install_keyboard();
	install_mouse();
	set_color_depth( 24 );
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
	LOG << "LOG-File from Lorentz.exe" << endl << endl;
  BITMAP* buffer = init();
	if( buffer == NULL )
  	return 1;
  
  lorentz( buffer );
  
  destroy_bitmap( buffer );
	LOG << "save exit... good bye!" << endl << endl;
  return 0;
}END_OF_MAIN()
