#include "../include/mingen.h"

//
//  NEW:  creates a new chunk in memory
//

static chunk* _chunk_new(FN* fn, int x, int y, int z)
{
    chunk* c = malloc(sizeof(chunk));
    c->busy = 0;
    c->loaded = 0;
    c->x = x;
    c->y = y;
    c->z = z;
    c->mesh = fn->mesh.new(fn);
    return c;
}

//
//  BUILD:  builds a chunk mesh from its block data
//

static void _chunk_build(FN* fn, chunk* chunk)
{
    mesh* m = chunk->mesh;

    fn->array.set(m->vertex, 0, 12, (float[]){
        -0.5f, -1.5f, 0.0f, 
        -0.5f,  7.5f, 0.0f,  
         0.5f,  0.5f, 0.0f,  
         0.5f, -3.5f, 0.0f  
    });

    // update our VBO with the new data
    glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m->vertex->length * sizeof(float), m->vertex->data);
}

//
//  DRAW:  draws the chunk onto the frame
//

static void _chunk_draw(FN* fn, chunk* c)
{
    fn->mesh.draw(fn, c->mesh);
}

//
//  CHUNK.C:    a chunk represents a 10x10x10 block of nodes in a game
//              it is the "level geometry" or terrain of a world
//

void _init_chunk(FN* fn)
{
    fn->chunk.new = &_chunk_new;
    fn->chunk.draw = &_chunk_draw;
    fn->chunk.build = &_chunk_build;
}