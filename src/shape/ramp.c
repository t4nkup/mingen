#include "../../include/mingen.h"

//
//  BUILD:  builds the shape geometry.. vertices, indices, uvs, etc
//

static void _shape_ramp_build(FN *fn)
{

}

//
//  RAMP.C:  the ramp shape is a cube cut in half diagonally
//

void _init_shape_ramp(FN *fn)
{
    fn->shape.ramp.build = &_shape_ramp_build;
}