#include "../../include/mingen.h"

//
//  NEW:  creates a cube shape struct and returns a void pointer for it
//

static void* _shape_cube_new(int material, int orientation)
{
    shape* s = malloc(sizeof(shape));
    s->type = 1;
    s->material = 0;
    s->orientation = 0;
    return (void*)s;
}

//
//  BUILD:  builds the shape geometry.. vertices, indices, uvs, etc
//

static void _shape_cube_build()
{

}

//
//  CUBE.C:  a "cube" shape is a regular cube
//

void _init_shape_cube()
{
    fn.shape.cube.new = &_shape_cube_new;
    fn.shape.cube.build = &_shape_cube_build;
}