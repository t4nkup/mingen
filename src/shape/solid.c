#include "../../include/mingen.h"

static void _shape_solid_build(FN *fn)
{

}

void _init_shape_solid(FN *fn)
{
    fn->shape.solid.build = &_shape_solid_build;
}