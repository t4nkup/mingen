#include "../mingen.h"

void _init_shapes(FN *fn)
{
    fn->shapes.solid.build = &_shape_solid_build;
    fn->shapes.ramp.build = &_shape_ramp_build;
}