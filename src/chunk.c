#include "../include/mingen.h"

static chunk* _chunk_new(FN *fn, int x, int y, int z)
{
    chunk *c = malloc(sizeof(chunk));
    c->busy = 0;
    c->loaded = 0;
    c->x = x;
    c->y = y;
    c->z = z;
    c->mesh = malloc(sizeof(mesh));
    c->mesh->vertex = fn->array.new(0, sizeof(float));
    c->mesh->index = fn->array.new(0, sizeof(int));
    c->mesh->uv = fn->array.new(0, sizeof(float));
    return c;
}

static void _chunk_build(FN *fn, chunk *chunk)
{
    // chunk->mesh.vertices[9] = {
    //     -1.0f, -1.0f, 0.0f,  
    //      1.5f, -0.5f, 0.0f,  
    //      0.0f,  0.5f, 0.0f  
    // };
}

void _init_chunk(FN *fn)
{
    fn->chunk.new = &_chunk_new;
    fn->chunk.build = &_chunk_build;
}