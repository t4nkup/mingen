#ifndef MINGEN
#define MINGEN

//
//  MINGEN.H:   our mega header which we will use throughout the program
//

// standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// included libraries
#include "../lib/GLAD/glad.h"
#include "../lib/GLFW/glfw3.h"

// game modules
#include "_/enum.h"
#include "_/defs.h"
#include "_/comp.h"
#include "_/fn.h"
#include "array/array.h"
#include "chunk/chunk.h"
#include "collection/collection.h"
#include "data/data.h"
#include "game/game.h"
#include "graphics/graphics.h"
#include "input/input.h"
#include "loop/loop.h"
#include "map/map.h"
#include "mesh/mesh.h"
#include "network/network.h"
#include "shapes/shapes.h"
#include "sound/sound.h"
#include "utility/utility.h"

// block shapes
#include "shapes/solid/solid.h"
#include "shapes/ramp/ramp.h"

#endif