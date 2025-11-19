#include "../include/mingen.h"

//
//  MAIN.C: starting point of our program
//

int main()
{
    // declare our "manager" struct, this will be passed around 
    // everywhere by reference so we can easily access our modules
    FN fn; 

    // initialize our modules
    _init_array(&fn);
    _init_chunk(&fn);
    _init_collection(&fn);
    _init_data(&fn);
    _init_game(&fn);
    _init_graphics(&fn);
    _init_input(&fn);
    _init_loop(&fn);
    _init_map(&fn);
    _init_mesh(&fn);
    _init_network(&fn);
    _init_shape_solid(&fn);
    _init_shape_ramp(&fn);
    _init_sound(&fn);
    _init_utility(&fn);

    // initialize our graphics
    fn.gfx.setup(&fn);

    // create a new game and a map to go with it
    game* g = fn.game.new(&fn, 0, "test");
    map* m = fn.map.new(&fn, 0, "test");

    // assign the map to the game
    fn.array.add(g->mapIDs, 1, (int[]) { m->ID });
    fn.array.add(g->maps, 1, (map[]) { *m });

    // create a new chunk for the map
    chunk* c = fn.chunk.new(&fn, 0, 0, 0);

    fn.array.add(m->chunks, 1, (chunk[]){ *c });

    fn.data.game = g;
    fn.data.map = m;


    // start our game loop
    fn.loop.start(&fn);

    // cleanup
    fn.gfx.unload(&fn);

    return 0;
}