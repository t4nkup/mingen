#include "../include/mingen.h"

//
//  MAIN.C: starting point of our program
//

FN fn;

int main()
{
    // initialize our modules
    _init_array();
    _init_chunk();
    _init_data();
    _init_game();
    _init_graphics();
    _init_grid();
    _init_input();
    _init_loop();
    _init_list();
    _init_map();
    _init_mesh();
    _init_network();
    _init_sound();
    _init_table();
    _init_utility();

    // initialize our shapes
    _init_shape_cube();
    _init_shape_ramp();

    // initialize our graphics
    fn.gfx.setup();

    // // create a new game and a map to go with it
    // game* g = fn.game.new("test");
    // map* m = fn.map.new("test");
    // fn.list.add(g->maps, m);

    // // create a new chunk for the map
    // chunk* c = fn.chunk.new(0, 0, 0);
    // fn.list.add(m->chunks, c);

    // fn.data.game = g;
    // fn.data.map = m;

    // start our game loop
    fn.loop.start();

    // cleanup
    fn.gfx.unload();

    return 0;
}