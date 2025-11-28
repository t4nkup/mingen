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
#include <time.h>

// included libraries
#include "../lib/CGLM/cglm.h"
#include "../lib/GLAD/glad.h"
#include "../lib/GLFW/glfw3.h"

// mingen headers
#include "enum.h"
#include "def.h"
#include "type.h"
#include "fn.h"
#include "macro.h"

// field declarations
extern FN fn;
void _init_array();
void _init_chunk();
void _init_data();
void _init_game();
void _init_graphics();
void _init_grid();
void _init_input();
void _init_loop();
void _init_list();
void _init_map();
void _init_mesh();
void _init_network();
void _init_shape_cube();
void _init_shape_ramp();
void _init_sound();
void _init_table();
void _init_utility();

#endif