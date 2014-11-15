#include "automat.hpp"

c_automat::c_automat( BITMAP* _bmp )
{
//    LOG << "c_automat: constructor" << endl;
    bmp = _bmp;
    quit = false;
    delay = 1;
    current_field = 0;
    current_rule = RULE_NONE;
    field[0] = (bool*) malloc( (bmp->w*bmp->h)*sizeof( bool ) );
    field[1] = (bool*) malloc( (bmp->w*bmp->h)*sizeof( bool ) );
    cnt = 0;    
    show_info = 0;
    step_by_step = false;
    return;
}

c_automat::~c_automat( void )
{
//    LOG << "c_automat: destructor" << endl;
    free( field[0] );
    free( field[1] );
    return;
}

void c_automat::kill_all( void )
{
    for( int x=0; x<bmp->w; x++ ) {
        for( int y=0; y<bmp->h; y++ ) {
            field[0][y*bmp->w+x] = field[1][y*bmp->w+x] = DEAD;
        }
    }

    return;
}

void c_automat::seed_life( int x, int y )
{
    field[current_field][y*bmp->w+x] = ALIVE;
    return;
}

void c_automat::distribute_life( void )
{
    for( int x = 0; x < bmp->w; x++ ) {
        for( int y = 0; y < bmp->h; y++ ) {
            field[current_field][y*bmp->w+x] = (rand()%2?ALIVE:DEAD);
        }
    }
    return;
}




void c_automat::change_rule( int rule )
{
    kill_all();
    clear_bitmap( bmp );
    cnt = 0;
    switch( rule )
    {
    case RULE_NONE:
        rule_name = "Save haven...";
        step_by_step = false;
        break;
    case RULE_GAME_OF_LIFE:
        distribute_life();
        rule_name = "GAME OF LIFE";
        break;
    case RULE_MAJORITY:
        distribute_life();
        rule_name = "MAJORITY RULE";
        break;
    case RULE_ONE_OF_EIGHT:
        seed_life( (bmp->w>>1), (bmp->h>>1) );
        rule_name = "ONE OF EIGHT";
        break;
    case RULE_PARITY:
        for( int x = (bmp->w/2)-4; x<(bmp->w/2)+4; x++ ) {
            for( int y = (bmp->h/2)-4; y<(bmp->h/2)+4; y++ ) {
                seed_life( x, y );
            }
        }
        rule_name = "PARITY RULE";
        break;
    case RULE_PASCAL:
        seed_life( 1, 1 );
        rule_name = "PASCAL";
        break;
    default:
        allegro_message( "ERROR: unknown rule requested in \"c_automat::change_rule\": %d", rule );
        current_rule = RULE_NONE;
        return;
    }
    current_rule = rule;
    return;
}

void c_automat::next_step( void )
{
    switch( current_rule )
    {
    case RULE_NONE:
        textprintf_ex( bmp, font, 10,  90, 15, 0, "OPTIONS:" );
        textprintf_ex( bmp, font, 10, 100, 15, 0, "========" );
        textprintf_ex( bmp, font, 10, 110, 15, 0, "0) The Save Haven" );
        textprintf_ex( bmp, font, 10, 120, 15, 0, "1) Game of Life" );
        textprintf_ex( bmp, font, 10, 130, 15, 0, "2) Majority Rule" );
        textprintf_ex( bmp, font, 10, 140, 15, 0, "3) One of Eight" );
        textprintf_ex( bmp, font, 10, 150, 15, 0, "4) Parity Rule" );
        textprintf_ex( bmp, font, 10, 160, 15, 0, "5) Pascal-Sirpinski" );
        textprintf_ex( bmp, font, 10, 175, 15, 0, "ESC) QUIT" );
        textprintf_ex( bmp, font, 10, 250, 15, 0, "You can slow down the process if you increase" );
        textprintf_ex( bmp, font, 10, 260, 15, 0, "the delay by pressing \"DOWN\" and vice versa." );
        textprintf_ex( bmp, font, 10, 270, 15, 0, "Or you can enable the step-by-step option by");
        textprintf_ex( bmp, font, 10, 280, 15, 0, "pressing the \"RIGHT\"-key on your keyboard.");
        textprintf_ex( bmp, font, 10, 290, 15, 0, "With the step-by-step option enabled the next" );
        textprintf_ex( bmp, font, 10, 300, 15, 0, "step will only take place if you press \"RIGHT\"" );
        textprintf_ex( bmp, font, 10, 310, 15, 0, "again." );
        textprintf_ex( bmp, font, 10, 320, 15, 0, "Press \"ENTER\" to disable the step-by-step option." );
        textprintf_ex( bmp, font, (bmp->w>>1)-10, 90, 15, 0, "INFO:" );
        switch( show_info )
        {
        case 0:
            textprintf_ex( bmp, font, bmp->w>>1, 100, 15, 0, "This is sort of the menu." );
            textprintf_ex( bmp, font, bmp->w>>1, 110, 15, 0, "You can view more information about the");
            textprintf_ex( bmp, font, bmp->w>>1, 120, 15, 0, "different options by pressing shift and");
            textprintf_ex( bmp, font, bmp->w>>1, 130, 15, 0, "the number" );
            break;
        case 1:
            textprintf_ex( bmp, font, bmp->w>>1, 100, 15, 0, "The Game of Life was invented by John Horton");
            textprintf_ex( bmp, font, bmp->w>>1, 110, 15, 0, "Conway in the 70s. In the Game each cell is");
            textprintf_ex( bmp, font, bmp->w>>1, 120, 15, 0, "either alive (white) or dead (black).");
            textprintf_ex( bmp, font, bmp->w>>1, 130, 15, 0, "The state of the surrounding cells determine");
            textprintf_ex( bmp, font, bmp->w>>1, 140, 15, 0, "whether the cell will be alive or dead in the");
            textprintf_ex( bmp, font, bmp->w>>1, 150, 15, 0, "next step:");
            textprintf_ex( bmp, font, bmp->w>>1, 160, 15, 0, "It will STAY alive if two or three adjacent");
            textprintf_ex( bmp, font, bmp->w>>1, 170, 15, 0, "   cells are alive" );
            textprintf_ex( bmp, font, bmp->w>>1, 180, 15, 0, "It will BECOME alive if exactly three adjacent");
            textprintf_ex( bmp, font, bmp->w>>1, 190, 15, 0, "   cells are alive" );
            textprintf_ex( bmp, font, bmp->w>>1, 200, 15, 0, "It will DIE if non of the above applys" );
            break;
        case 2:
            textprintf_ex( bmp, font, bmp->w>>1, 100, 15, 0, "The Majority Rule determines the way a cell" );
            textprintf_ex( bmp, font, bmp->w>>1, 110, 15, 0, "behaves as follows:" );
            textprintf_ex( bmp, font, bmp->w>>1, 120, 15, 0, "It will become or stay alive (white) if five" );
            textprintf_ex( bmp, font, bmp->w>>1, 130, 15, 0, "   or more of the nine surrounding cells" );
            textprintf_ex( bmp, font, bmp->w>>1, 140, 15, 0, "   (eight plus it self) are alive" );
            textprintf_ex( bmp, font, bmp->w>>1, 150, 15, 0, "It will die (black) otherwise" );
            textprintf_ex( bmp, font, bmp->w>>1, 160, 15, 0, "This will usually result in a static picture" );
            textprintf_ex( bmp, font, bmp->w>>1, 170, 15, 0, "after some steps. but take a look yourself..." );
            break;
        case 3:
            textprintf_ex( bmp, font, bmp->w>>1, 100, 15, 0, "The One-of-eight-Rule is a very simple rule:" );
            textprintf_ex( bmp, font, bmp->w>>1, 110, 15, 0, "A cell will become white if exactly one of the" );
            textprintf_ex( bmp, font, bmp->w>>1, 120, 15, 0, "   eight adjacent cells are white" );
            break;
        case 4:
            textprintf_ex( bmp, font, bmp->w>>1, 100, 15, 0, "The Parity-Rule is quite simple but not that" );
            textprintf_ex( bmp, font, bmp->w>>1, 110, 15, 0, "easy to explain. It can be described in one" );
            textprintf_ex( bmp, font, bmp->w>>1, 120, 15, 0, "equation:" );
            textprintf_ex( bmp, font, bmp->w>>1, 130, 15, 0, "      M_new = ( M + N + E + S + W ) mod 2" );
            textprintf_ex( bmp, font, bmp->w>>1, 140, 15, 0, "M_new is the new state of the cell it is either" );
            textprintf_ex( bmp, font, bmp->w>>1, 150, 15, 0, "   1 (white) or 0 (black)");
            textprintf_ex( bmp, font, bmp->w>>1, 160, 15, 0, "M is the previous state of the cell" );
            textprintf_ex( bmp, font, bmp->w>>1, 170, 15, 0, "N, E, S and W are the states of the cells to" );
            textprintf_ex( bmp, font, bmp->w>>1, 180, 15, 0, "   the North, East, South and West respective" );
            textprintf_ex( bmp, font, bmp->w>>1, 190, 15, 0, "\"mod 2\" is a mathamatical operation which will" );
            textprintf_ex( bmp, font, bmp->w>>1, 200, 15, 0, "   return 0 if the term parantheses is an even" );
            textprintf_ex( bmp, font, bmp->w>>1, 210, 15, 0, "   number and 1 if it an uneven number." );
            break;
        }
        break;
    case RULE_GAME_OF_LIFE:
        game_of_life( field[current_field], field[!current_field], bmp->w, bmp->h ); break;
    case RULE_MAJORITY:
        majority( field[current_field], field[!current_field], bmp->w, bmp->h ); break;
    case RULE_ONE_OF_EIGHT:
        one_of_eight( field[current_field], field[!current_field], bmp->w, bmp->h ); break;
    case RULE_PARITY:
        parity( field[current_field], field[!current_field], bmp->w, bmp->h ); break;
    case RULE_PASCAL:
        pascal( field[current_field], field[!current_field], bmp->w, bmp->h ); break;
    default:
        allegro_message( "ERROR: unknown rule \"c_automat::next_stage\": %d", current_rule );
        current_rule = RULE_NONE;
        return;
    }
    memcpy( field[current_field], field[!current_field], (bmp->w*bmp->h)*sizeof(bool) );
    current_field = !current_field;
    return;
}

void c_automat::run( void )
{
    int x, y;
    kill_all();
    change_rule( RULE_NONE );
    while( !quit )
    {
        // play nice and slow down
        rest(delay);
        
        // START user input
        if( key[KEY_ESC] ) {
            quit = true;
        }
        for( int i=27; i<=32; i++ ) {
            if( key[i] ) {
                if( key_shifts & KB_SHIFT_FLAG ) {
                    show_info = i - 27;
                } else {
                    switch( i )
                    {
                    case KEY_0:
                        change_rule( RULE_NONE ); break;
                    case KEY_1:
                        change_rule( RULE_GAME_OF_LIFE ); break;
                    case KEY_2:
                        change_rule( RULE_MAJORITY ); break;
                    case KEY_3:
                        change_rule( RULE_ONE_OF_EIGHT ); break;
                    case KEY_4:
                        change_rule( RULE_PARITY ); break;
                    case KEY_5:
                        change_rule( RULE_PASCAL ); break;
                    default:
                        allegro_message( "ERROR: unknown rule requested: %d", i );
                    }
                }
            }
        }
        if( key[KEY_UP] && delay > 1 ) {
            delay--;
        }
        if( key[KEY_DOWN] ) {
            delay++;
        }
        if( key[KEY_RIGHT] && current_rule != RULE_NONE ) {
            step_by_step = true;
            next_step();
            cnt++;
            while( key[KEY_RIGHT] );
        }
        if( key[KEY_ENTER] ) {
            step_by_step = false;
        }
        while( key[KEY_SPACE] );
        // END user input
        
        // START output
        clear_bitmap( bmp );
        for( x=0; x<bmp->w; x++ )
            for( y =0; y<bmp->h; y++ )
                if( field[current_field][y*bmp->w+x] == ALIVE )
                    putpixel( bmp, x, y, makecol(255,255,255) );
        textprintf_centre_ex( bmp, font, bmp->w>>1,  5, 0, 0, " %s ", rule_name.c_str() );
        textprintf_centre_ex( bmp, font, bmp->w>>1, 15, 0, 0, " %s ", rule_name.c_str() );
        textprintf_centre_ex( bmp, font, bmp->w>>1, 23, 0, 0, " %s ", rule_name.c_str() );
        textprintf_centre_ex( bmp, font, bmp->w>>1, 10, 4, 0, " %s ", rule_name.c_str() );
        if( current_rule != RULE_NONE )
            textprintf_centre_ex( bmp, font, bmp->w>>1, 18, 15, 0, " step %d ", cnt );

        textprintf_ex( bmp, font, 10,  5,  0, 0, " delay: %d ", delay );
        textprintf_ex( bmp, font, 10, 15,  0, 0, " delay: %d ", delay );
        textprintf_ex( bmp, font, 10, 10, 15, 0, " delay: %d ", delay );

        textprintf_right_ex( bmp, font, bmp->w-10,  5,  0, 0, " step-by-step: %s ", (step_by_step?"on":"off") );
        textprintf_right_ex( bmp, font, bmp->w-10, 15,  0, 0, " step-by-step: %s ", (step_by_step?"on":"off") );
        textprintf_right_ex( bmp, font, bmp->w-10, 10, 15, 0, " step-by-step: %s ", (step_by_step?"on":"off") );
        // END output
        
        if( !step_by_step )
        {
            next_step();
            cnt++;
        }

        blit( bmp, screen, 0, 0, 0, 0, bmp->w, bmp->h );
        
    }
    return;
}



