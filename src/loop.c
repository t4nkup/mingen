#include "../include/mingen.h"

//
//  START:  starts the loop
//

static void _loop_start(FN* fn)
{
    fn->loop.isPaused = 0;

    // here we loop until the window is terminated
    while (!glfwWindowShouldClose(fn->gfx.window))
    {
        // tick our game loop
        if (!fn->loop.isPaused) { fn->loop.tick(fn); }

        // process the window events
        glfwPollEvents();
    }
}

//
//  STOP:  stops the loop
//

static void _loop_stop(FN* fn)
{
    fn->loop.isPaused = 1;
}

//
//  TICK:  represents a frame
//

static void _loop_tick(FN* fn)
{
    // process input

    // process logic

    // render graphics
    fn->gfx.render(fn);
}

//
//  LOOP.C:  our main game loop
//

void _init_loop(FN* fn)
{
    fn->loop.start = &_loop_start;
    fn->loop.stop = &_loop_stop;
    fn->loop.tick = &_loop_tick;
}