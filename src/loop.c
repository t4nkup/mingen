#include "../include/mingen.h"

static void _loop_start(FN *fn)
{
    fn->loop.isPaused = 0;
}

static void _loop_stop(FN *fn)
{
    fn->loop.isPaused = 1;
}

static void _loop_tick(FN *fn)
{
    // process input

    // process logic

    // render graphics
    fn->gfx.render(fn);
}

void _init_loop(FN *fn)
{
    fn->loop.start = &_loop_start;
    fn->loop.stop = &_loop_stop;
    fn->loop.tick = &_loop_tick;
}