#include "../include/mingen.h"

//
//  START:  starts the loop
//

static void _loop_start()
{
    // set pause state to off
    fn.loop.isPaused = 0;
    // set our previous frame time
    fn.loop.previous = glfwGetTime();

    // here we loop until the window is terminated
    while (!glfwWindowShouldClose(fn.gfx.window))
    {
        // get the current time
        fn.loop.current = glfwGetTime();
        // calculate our delta time for frame
        fn.loop.delta = fn.loop.current - fn.loop.previous;
        // update our previous frame time to current
        fn.loop.previous = fn.loop.current;

        // process the window events
        glfwPollEvents();

        // tick our game loop
        if (!fn.loop.isPaused) { fn.loop.tick(); }

        // replaces the drawn frame with our newly created one
        glfwSwapBuffers(fn.gfx.window);
    }
}

//
//  STOP:  stops the loop
//

static void _loop_stop()
{
    fn.loop.isPaused = 1;
}

//
//  TICK:  represents a frame
//

static void _loop_tick()
{
    // process input
    fn.input.read(fn);

    // process logic
    if (fn.input.A.pressed) { 

        array* a = fn.array.new(5, INT);
        fn.array.add(a, 3, (int[]) { 1, 2, 3 });
        log(a);
        chunk* c = fn.list.get(fn.data.map->chunks, 0);
        log(c->mesh->vertex);
        log(c->mesh->uv);
        log(c->mesh->index);
        logmem();
        delete(a);
        delete(c->mesh->vertex);
        delete(c->mesh->uv);
        delete(c->mesh->index);
        logmem();

        // log("A pressed"); 
    
        // chunk* c = fn.list.get(fn.data.map->chunks, 0);
        // fn.chunk.build(c);
    
        // log(c->mesh->vertex);
    }
    if (fn.input.A.down && fn.input.A.timer > 0.2) { log("A was held"); }

    // render graphics
    fn.gfx.render(fn);
}

//
//  LOOP.C:  our main game loop
//

void _init_loop()
{
    fn.loop.start = &_loop_start;
    fn.loop.stop = &_loop_stop;
    fn.loop.tick = &_loop_tick;
}