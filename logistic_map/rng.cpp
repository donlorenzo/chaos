#include <cstdio>
#include "allegro.h"
#include "rng.hpp"

volatile long unsigned int sys_timer;
long unsigned int old_timer;

void ttimer( void )
{
   sys_timer++;
}
END_OF_FUNCTION(ttimer);


c_rng::c_rng( void )
{
	err_no = ERR_NOERROR;
	if( fegetround() != FE_TONEAREST )
	{
		old_rounding_mode = fegetround();
		if( fesetround( FE_TONEAREST ) )
			err_no = ERR_ROUNDING;
	}else
	{
		old_rounding_mode = FE_TONEAREST;
	}
}

c_rng::~c_rng( void )
{ fesetround( old_rounding_mode ); }

double c_rng::next( void )
{
	if( total%10000 == 0 )
		x += (0.5f-x)*0.0000001f;
	do
	{
		if( x == 0 || x == 1 )
			x += (0.5f-x)*0.0000001f;
		x = 4.0f*x*(1.0f-x);
	}while( fabs( x-0.5f ) >= HW );
	total++;

	return( (x-0.5+HW)/(2*HW) );
}

int c_rng::get_err( void )
{
	return( err_no );
}

void c_rng::seed( long unsigned int number, long int _steps=1000 )
{
	steps = _steps;
	int bytes = sizeof( number );
	number = number<<( (bytes-1)*8 );
	number = number>>( (bytes-1)*8 );
	x = 1/double(number+1);
	for( unsigned int i=0; i<number; i++ )
		x=next();

	return;
}



void c_rng::show_graph( void )
{
	long long unsigned int i;
	long long unsigned int max = 0;
	long long unsigned int total = 0;
	BITMAP* buffer = create_bitmap( SCREEN_W, SCREEN_H );
	clear_bitmap( buffer );
	int old_steps = steps;
	if( steps > SCREEN_W )
		steps = SCREEN_W;
	long unsigned int field[steps];
	for( i=0; i<steps; i++ )
		field[i] = 0;


	while( !key[KEY_ENTER] )
	{
		for( i=0; i<100000; i++ )
		{  
			int num = int(next()*steps);
			field[num]++;
			if( field[num] > max )
				max++;
			total++;
		}

		for( i=0; i<steps; i++ )
			rectfill( buffer, i*SCREEN_W/steps, SCREEN_H, (i+1)*SCREEN_W/steps-1, SCREEN_H-int(field[i]/float(max)*SCREEN_H), 15 );
		textprintf_centre_ex( buffer, font, SCREEN_W/2, SCREEN_H/2, 4, -1, "total number of generated numbers: %lld", total );
		blit( buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
		clear_bitmap( buffer );
	}
	steps = old_steps;
	destroy_bitmap( buffer );
	return;
}

void time_it( c_rng* rng, long int how_many )
{
	int i;
	long unsigned int rand_timer;
	old_timer = sys_timer;
	for( i=0; i<how_many; i++ )
		rng->next();
	old_timer = sys_timer - old_timer;
	rand_timer = sys_timer;
	for( i=0; i<how_many; i++ )
		rand();
	rand_timer = sys_timer - rand_timer;

	allegro_message("%ld random numbers in %ld ms!\nthats an average of: %.2f numbers/sec\nthe compilers rand() did the same task in %ld ms... *coughcough*",\
									how_many, 10*old_timer, 100.0f*double(how_many)/double(old_timer), 10*rand_timer );
	return;
}


void dump( c_rng* rng, int how_many )
{
	FILE* f;
	f = fopen( "output.bin", "w" );

	for( int i=0; i<25000000; i++ )
	{
		int num = int(rng->next()*2147483647);
		putc( num, f );
	}
	allegro_message( "success!" );
	fclose( f );
	return;
}


void run( c_rng* rng )
{
	int pos = 0;
	while( !key[KEY_ESC] )
	{
		if( key[KEY_G] )
		{
			rng->show_graph();
			clear_bitmap( screen );
		}
		if( pos*10 > SCREEN_H-10 )
		{
			clear_bitmap( screen );
			pos = 0;
		}
		textprintf_ex( screen, font, 10, pos*10, 15, 0, "%f", rng->next() );
		pos++;
		
		clear_keybuf();
		while( !keypressed() );
	}
	
	return;
}



static int init( void )
{
	allegro_init();
	install_timer();
	LOCK_VARIABLE( sys_timer );
	LOCK_FUNCTION( ttimer );
	install_int( ttimer, 10 );

	install_keyboard();
	install_mouse();
	if( set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0 ) )
		return 1;
	
	return 0;
} 


int main( void )
{
	srand( time(0) );
	if( init() )
		return 1;	

	c_rng* rng = new c_rng;
	rng->seed( time( NULL ), 2147483647 );

	time_it( rng, 1000000 );
//	dump( rng, 1 );
//	return 0;
	run( rng );
	
	return 0;
}END_OF_MAIN()
