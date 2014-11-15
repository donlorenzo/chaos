#ifndef AUTOMAT_HPP
#define AUTOMAT_HPP

#include "_base.hpp"
#include "regeln.hpp"
#include <string>

#define ALIVE 1
#define DEAD  0

#define RULE_NONE           0
#define RULE_GAME_OF_LIFE   1
#define RULE_MAJORITY       2
#define RULE_ONE_OF_EIGHT   3
#define RULE_PARITY         4
#define RULE_PASCAL         5

class c_automat
{
public:
    c_automat( BITMAP* _bmp );
    ~c_automat();
    void run( void );
private:
    void kill_all( void );
    void seed_life( int x, int y );
    void distribute_life( void );
    void special_seed_life( void );  // required for parity rule
    void change_rule( int rule );
    void next_step( void );
  
    BITMAP* bmp;
    bool quit;
    bool* field[2];
    int current_field;
    int current_rule;
    string rule_name;
    int delay;
    bool step_by_step;
    int show_info;
    int cnt;
};



#endif // AUTOMAT_HPP
