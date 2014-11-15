#include "main.hpp"


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
//	LOG << "LOG-File from spiel_des_lebens.exe" << endl << endl;
    BITMAP* buffer = init();
	if( buffer == NULL )
        return 1;
  
	c_automat* automat = new c_automat( buffer );
	automat->run();	
	
	delete( automat );
	if( buffer != NULL )
        destroy_bitmap( buffer );
//	LOG << "save exit... good bye!" << endl << endl;
    return 0;
}END_OF_MAIN()
