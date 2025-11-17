#include "../../include/mingen.h"

static void _shape_ramp_build(FN *fn)
{

}

void _init_shape_ramp(FN *fn)
{
    fn->shape.ramp.build = &_shape_ramp_build;
}