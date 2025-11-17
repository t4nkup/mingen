#include "../include/mingen.h"

//
//  NEW:  creates a new chunk in memory
//

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

//
//  BUILD:  builds a chunk mesh from its block data
//

static void _chunk_build(FN *fn, chunk *chunk)
{
    // chunk->mesh.vertices[9] = {
    //     -1.0f, -1.0f, 0.0f,  
    //      1.5f, -0.5f, 0.0f,  
    //      0.0f,  0.5f, 0.0f  
    // };
}

//
//  CHUNK.C:    a chunk represents a 10x10x10 block of nodes in a game
//              it is the "level geometry" or terrain of a world
//

void _init_chunk(FN *fn)
{
    fn->chunk.new = &_chunk_new;
    fn->chunk.build = &_chunk_build;
}