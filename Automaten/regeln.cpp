#include "regeln.hpp"

// MEHRHEITS REGEL
void majority( bool* old_field, bool* new_field, int width, int height )
{
    for( int x=1; x<width-1; x++ )
        for( int y=1; y<height-1; y++ )
        {
            int sum = old_field[(y-1)*width+x-1] + 
                old_field[(y-1)*width+x] + 
                old_field[(y-1)*width+x+1] + 
                old_field[y*width+x-1] + 
                old_field[y*width+x] + 
                old_field[y*width+x+1] + 
                old_field[(y+1)*width+x-1] + 
                old_field[(y+1)*width+x] + 
                old_field[(y+1)*width+x+1];
            if( sum > 4 )
                new_field[y*width+x] = ALIVE;
            else
                new_field[y*width+x] = DEAD;
        }
    return;
}
// MEHRHEITS REGEL ENDE


// EINS-AUS-ACHT-REGEL
void one_of_eight( bool* old_field, bool* new_field, int width, int height )
{
    for( int x=1; x<width-1; x++ )
        for( int y=1; y<height-1; y++ )
        {
            int sum = old_field[(y-1)*width+x-1] + 
                old_field[(y-1)*width+x] + 
                old_field[(y-1)*width+x+1] + 
                old_field[y*width+x-1] + 
                old_field[y*width+x+1] + 
                old_field[(y+1)*width+x-1] + 
                old_field[(y+1)*width+x] + 
                old_field[(y+1)*width+x+1];
            if( sum == 1 )
                new_field[y*width+x] = ALIVE;
        }
    return;
}
// EINS-AUS-ACHT-REGEL
 

// SPIEL DES LEBENS
void game_of_life( bool* old_field, bool* new_field, int width, int height )
{
    for( int x=1; x<width-1; x++ )
        for( int y=1; y<height-1; y++ )
        {
            int sum = old_field[(y-1)*width+x-1] + 
                old_field[(y-1)*width+x] + 
                old_field[(y-1)*width+x+1] + 
                old_field[y*width+x-1] + 
                old_field[y*width+x+1] + 
                old_field[(y+1)*width+x-1] + 
                old_field[(y+1)*width+x] + 
                old_field[(y+1)*width+x+1];
            if( sum == 3 )
                new_field[y*width+x] = ALIVE;
            if( sum > 3 || sum < 2 )
                new_field[y*width+x] = DEAD;
        }
    return;
}
// SPIEL DES LEBENS ENDE

// PARITÄT
void parity( bool* old_field, bool* new_field, int width, int height )
{    
    for( int x=1; x<width-1; x++ )
        for( int y=1; y<height-1; y++ )
        {
            int sum = old_field[(y-1)*width+x] + 
                old_field[y*width+x-1] + 
                old_field[y*width+x] + 
                old_field[y*width+x+1] + 
                old_field[(y+1)*width+x];
            new_field[y*width+x] = sum%2;
        }
    return;
}
// PARITÄT ENDE

// PASCAL-SIRPINSKI
void pascal( bool* old_field, bool* new_field, int width, int height )
{
    int field[width][height];
    for( int i=0; i<width; i++ ) {
        for( int j=0; j<height; j++ ) {
            field[i][j] = 0;
        }
    }
    for( int i=1; i<height; i++ ) {
        field[1][i] = 1;
    }
    for( int x=2; x<width; x++ ) {
        for( int y=1; y<height; y++ ) {
            if( key[KEY_ESC] ) {
                return;
            }
            field[x][y] = field[x-1][y] + field[x][y-1];
/*            if( field[x][y]%16 != 0 )
              putpixel( bmp, x,y, makecol(0,0,255) );
              if( field[x][y]%8 != 0 )
              putpixel( bmp, x, y, makecol(0,255,0) );
              if( field[x][y]%4 != 0 )
              putpixel( bmp, x, y, makecol(255,0,0) );
*/           
            if( field[x][y]%2 != 0 ) {
                new_field[y*width+x] = true;
//                putpixel( bmp, x, y, 15 );
            }
        }
    }
//    if( bmp != screen )
//        blit( bmp, screen, 0, 0, 0, 0, bmp->w, bmp->h );
//    while( !key[KEY_ESC] );
    return;
}
// PASCAL-SIRPINSKI ENDE
