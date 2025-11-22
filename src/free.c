#include "../include/mingen.h"

//
//  FREE:  takes a void pointer to one of our objects and frees
//         its memory based off its type
//

void _free(void* data)
{
    if (data == NULL) { return; }

    // read the first byte of our void pointer and cast it to its enum type
    type type = *((unsigned char*)data);

    switch(type)
    {
        case ARRAY:
        break;
        case BUTTON:
        break;
        case CHUNK:
        break;
        case ENTRY:
        break;
        case FLOAT3:
        break;
        case GAME:
        break;
        case GRID:
        break;
        case INT3:
        break;
        case MAP:
        break;
        case MESH:
        break;
        case SHAPE:
        break;
        case TABLE:
        break;
        case TRANSFORM:
        break;
        case UID:
        break;
        default: break;
    }

    free(data);
}

//
//  FREE.C:    a helper module for freeing memory and preventing leaks
//

void _init_free(FN* fn)
{
    fn->free = &_free;
}