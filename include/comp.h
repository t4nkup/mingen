#include "mingen.h"

#ifndef _COMP
#define _COMP

// 
//  COMP:   these are all of our "component" declarations
//          a component is just a piece of data assigned to an object
//

typedef struct shape
{
    char type;
    char orientation;
    char material;
}
shape;

typedef struct transform
{
    float3 position;
    float3 rotation;
    float3 scale;
}
transform;

#endif