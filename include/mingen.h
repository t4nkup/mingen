#ifndef MINGEN
#define MINGEN

//
//  MINGEN.H:   our main header which we will use in all our src files
//

// standard libraries
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// included libraries
#include "../lib/GLAD/glad.h"
#include "../lib/GLFW/glfw3.h"

// mingen headers
#include "defs.h"
#include "enum.h"
#include "fn.h"
#include "macro.h"

// module init funcs
void _init_array(FN* fn);
void _init_chunk(FN* fn);
void _init_data(FN* fn);
void _init_game(FN* fn);
void _init_graphics(FN* fn);
void _init_grid(FN* fn);
void _init_hash(FN* fn);
void _init_input(FN* fn);
void _init_loop(FN* fn);
void _init_map(FN* fn);
void _init_mesh(FN* fn);
void _init_network(FN* fn);
void _init_shape_cube(FN* fn);
void _init_shape_ramp(FN* fn);
void _init_sound(FN* fn);
void _init_utility(FN* fn);

#endif