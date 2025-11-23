#include "../include/mingen.h"

//
//  MAIN.C: starting point of our program
//

int main()
{
    // declare our "manager" struct
    FN fn; 

    // initialize our modules
    _init_array(&fn);
    _init_chunk(&fn);
    _init_data(&fn);
    _init_free(&fn);
    _init_game(&fn);
    _init_graphics(&fn);
    _init_grid(&fn);
    _init_input(&fn);
    _init_loop(&fn);
    _init_list(&fn);
    _init_map(&fn);
    _init_mesh(&fn);
    _init_network(&fn);
    _init_sound(&fn);
    _init_table(&fn);
    _init_utility(&fn);

    // initialize our shapes
    _init_shape_cube(&fn);
    _init_shape_ramp(&fn);

    // initialize our graphics
    fn.gfx.setup(&fn);

    // create a new game and a map to go with it
    game* g = fn.game.new(&fn, 0, "test");
    map* m = fn.map.new(&fn, 0, "test");
    fn.list.add(g->maps, m);

    // create a new chunk for the map
    chunk* c = fn.chunk.new(&fn, 0, 0, 0);
    fn.list.add(m->chunks, c);

    fn.data.game = g;
    fn.data.map = m;


    // start our game loop
    fn.loop.start(&fn);

    // cleanup
    fn.gfx.unload(&fn);

    return 0;
}