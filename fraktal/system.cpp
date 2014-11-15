#include "system.hpp"


c_system::c_system( volatile long int* _sys_timer ) {
	quit_flag = false;
    sys_timer = _sys_timer;
    buffer = create_bitmap( SCREEN_W, SCREEN_H );
    clear_bitmap( buffer );
    info_scr = create_bitmap( SCREEN_W, 50 );
    clear_bitmap( info_scr );
	update_screen = true;
	
	koch = new c_fraktal;
	depth = 1;
	log_info( "... c_system constructor DONE\n" );
}    

c_system::~c_system( void ) {
    if( buffer != NULL )
    	destroy_bitmap( buffer );
}    

void c_system::update_gfx( BITMAP* bmp )
{
	clear_bitmap( info_scr );
	
	if( update_screen ) {
	    clear_bitmap( bmp );
		blit( koch->show(), bmp, 0, 0, 0, 0, SCREEN_W, SCREEN_H );
		update_screen = false;
	}    

	textprintf_ex( info_scr, font, 10, 10, 15, 0, "depth: %d", depth );
	textprintf_ex( info_scr, font, 10, 20, 15, 0, "lines: %d", koch->line_cnt );
	textprintf_ex( info_scr, font, 200, 10, 15, 0, "timeing: %d", old_timer );
	textprintf_ex( info_scr, font, 200, 20, 15, 0, "Timer: %d", *sys_timer );

	
	blit( info_scr, bmp, 0, 0, 0, 0, info_scr->w, info_scr->h );
	blit( bmp, screen, 0, 0, 0, 0, bmp->w, bmp->h );
}


void c_system::run( void ) {
    old_timer = *sys_timer;
 	koch->calculate( depth );
	old_timer = *sys_timer-old_timer;
	while( !quit_flag ) {
	    update_gfx( buffer );
	    if( key[KEY_UP] ) {
	        depth++;
		    old_timer = *sys_timer;
	        koch->calculate( depth );
			old_timer = *sys_timer-old_timer;
			update_screen = true;
	        while( key[KEY_UP] )
         		update_gfx( buffer );
	    }
     	if( key[KEY_DOWN] && depth > 0) {
      	    depth--;
		    old_timer = *sys_timer;
	        koch->calculate( depth );
			old_timer = *sys_timer-old_timer;
			update_screen = true;
   	        while( key[KEY_DOWN] )
         		update_gfx( buffer );
	    }
	    if( key[KEY_ESC] )
    		quit_flag = true;
		rest( 1 );
	}
  	return;
}

