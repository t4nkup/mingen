#include "../include/mingen.h"

//
//  START:  starts the loop
//

static void _loop_start(FN *fn)
{
    fn->loop.isPaused = 0;
}

//
//  STOP:  stops the loop
//

static void _loop_stop(FN *fn)
{
    fn->loop.isPaused = 1;
}

//
//  TICK:  represents a frame
//

static void _loop_tick(FN *fn)
{
    // process input

    // process logic

    // render graphics
    fn->gfx.render(fn);
}

//
//  LOOP.C:  our main game loop
//

void _init_loop(FN *fn)
{
    fn->loop.start = &_loop_start;
    fn->loop.stop = &_loop_stop;
    fn->loop.tick = &_loop_tick;
}