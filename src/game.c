#include "../include/mingen.h"

static game* _game_new(char* name)
{
    game* g = malloc(sizeof(game));
    fn.utility.uid(g->ID);
    g->name = name;
    g->maps = fn.list.new(10);
    return g;
}

static void _game_load()
{

}

static void _game_unload()
{
    
}

//
//  GAME.C:     handles all of our utility/maintenance for a "game" object
//              which is a "minigame" that a user creates with mingen
//

void _init_game()
{
    fn.game.new = &_game_new;
    fn.game.load = &_game_load;
    fn.game.unload = &_game_unload;
}