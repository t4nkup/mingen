#include "../include/mingen.h"

//
//  NEW:  creates a new camera in memory
//

static camera* _camera_new(int x, int y, int z)
{
    camera* c = malloc(sizeof(camera));
    c->type = CAMERA;
    fn.utility.memory += sizeof(camera);
    return c;
}

//
//  CAMERA.C:   blah blah
//

void _init_camera()
{
    fn.camera.new = &_camera_new;
}