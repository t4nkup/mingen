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
            array* a = (array*) data;
            free(a->data);
        break;
        case CHUNK:
        break;
        case ENTRY:
        break;
        case GAME:
        break;
        case GRID:
        break;
        case LIST:
            list* l = (list*) data;
            for (int i = 0; i < l->count; i++) {
                void* d = (char*)l->data + i * l->size;
                _free(d);
            }
        case MAP:
        break;
        case MESH:
            mesh* m = (mesh*) data;
            _free(m->vertex);
            _free(m->uv);
            _free(m->index);
        break;
        case SHAPE:
        break;
        case TABLE:
        break;
        case TRANSFORM:
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