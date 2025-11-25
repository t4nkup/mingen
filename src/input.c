#include "../include/mingen.h"

//
//  READ:  parses the input state from GLFW
//

void _input_read()
{
    fn.input.A.pressed = false; fn.input.A.up = false;

    if (glfwGetKey(fn.gfx.window, GLFW_KEY_A) == GLFW_PRESS) {
        fn.input.A.timer += fn.loop.delta;
        fn.input.A.down = true; fn.input.A.up = false;
    } else {
        if (fn.input.A.timer > 0 && fn.input.A.timer < 0.2) { fn.input.A.pressed = true; }
        fn.input.A.timer = 0;
        fn.input.A.down = false; fn.input.A.up = true;
    }
}

//
//  INPUT.C:  collects all keyboard/mouse and gamepad input
//

void _init_input()
{
    fn.input.read = &_input_read;
}