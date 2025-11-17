#include "../include/mingen.h"

static game* _game_new(FN *fn, int ID, char *name)
{
    game *g = malloc(sizeof(game));
    g->ID = ID;
    g->name = name;
    g->mapIDs = fn->array.new(0, sizeof(int));
    g->maps = fn->array.new(0, sizeof(map));
    return g;
}

static void _game_load(FN *fn)
{

}

static void _game_unload(FN *fn)
{
    
}

//
//  GAME.C:     handles all of our utility/maintenance for a "game" object
//              which is a "minigame" that a user creates with mingen
//

void _init_game(FN *fn)
{
    fn->game.new = &_game_new;
    fn->game.load = &_game_load;
    fn->game.unload = &_game_unload;
}