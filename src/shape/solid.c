#include "../../include/mingen.h"

//
//  BUILD:  builds the shape geometry.. vertices, indices, uvs, etc
//

static void _shape_solid_build(FN* fn)
{

}

//
//  SOLID.C:  a "solid" shape is a regular cube
//

void _init_shape_solid(FN* fn)
{
    fn->shape.solid.build = &_shape_solid_build;
}