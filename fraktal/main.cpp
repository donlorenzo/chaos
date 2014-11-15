#include "allegro.h"
#include "logger.h"
#include "system.hpp"

using namespace std;

// timing
volatile long int sys_timer;

void ttimer(  void )
{
   sys_timer++;
}
END_OF_FUNCTION(ttimer);



int main(int argc, char *argv[])
{
	// init allegro
   allegro_init();

	// init logger
   log_init("log.txt",LOG_TRACE);
   log_info("-------init---------\n");

	// init timer
   install_timer();
	LOCK_VARIABLE( sys_timer );
	LOCK_FUNCTION( ttimer );
	install_int( ttimer, 1 );

	// init input devices
   install_keyboard();
   install_mouse();

	// init variables
	bool quit = false;
	
	// init gfx
   if( set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0 ) )
      if( set_gfx_mode( GFX_AUTODETECT, 640, 480, 0, 0 ) )
      {
         set_gfx_mode( GFX_TEXT, 0, 0, 0, 0);
         allegro_message("ERROR setting gfx mode! aborting...");
         log_error( "Could NOT set gfx mode! aborting...");
         log_close();
         return 1;
      }


	c_system *system = new c_system( &sys_timer );
	// main loop	
	system->run();


	// shutting down
	delete( system );

	log_info( "save exit\n\n\n" );
	log_close();
   allegro_exit();
   return 0;
}
END_OF_MAIN() 
