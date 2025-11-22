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
    //c->shapes = fn->grid.new(10);
    //c->shapes->data[0][0][0] = fn->shape.cube.new(0, 0);
    return c;
}

//
//  BUILD:  builds a chunk mesh from its block data
//

static void _chunk_build(FN* fn, chunk* chunk)
{
    mesh* m = chunk->mesh;

    fn->array.add(m->vertex, 12, (float[]){
        -0.5f, -1.5f, 0.0f, 
        -0.5f,  0.5f, 0.0f, 
         0.5f,  0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f 
    });

    fn->array.add(m->index, 6, (int[]){
        0, 1, 2,
        0, 2, 3
    });

    // bind our VBO for the new data
    glBindBuffer(GL_ARRAY_BUFFER, m->VBO);

    if (m->vertex->count * sizeof(float) > m->VBOSize)
    {
        // for chunks we make sure the default size is 50k verts to prevent reallocations every time a shape is changed
        // 48 bytes per vert = 2.4MB a chunk
        int s = 50000 * 48 * sizeof(float); if (s < m->vertex->count * sizeof(float)) { s = m->vertex->count * sizeof(float); }

        // our current buffer is too small for the new data so allocate a new area in GPU memory
        glBufferData(GL_ARRAY_BUFFER, m->vertex->count * sizeof(float), m->vertex->data, GL_DYNAMIC_DRAW);

        // buffer overflow so update the new buffer size
        m->VBOSize = s;
    }
    else
    {
        // our current buffer has sufficient space so we just upload data with no reallocation
        glBufferSubData(GL_ARRAY_BUFFER, 0, m->vertex->count * sizeof(float), m->vertex->data);
    }

    if (m->index->count * sizeof(int) > m->EBOSize)
    {
        // for chunks we make sure the default size is 50k verts to prevent reallocations every time a shape is changed
        int s = 50000 * 36 * sizeof(int); if (s < m->index->count * sizeof(int)) { s = m->index->count * sizeof(int); }

        // our current buffer is too small for the new data so allocate a new area in GPU memory
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->index->count * sizeof(int), m->index->data, GL_DYNAMIC_DRAW);

        // buffer overflow so update the new buffer size
        m->EBOSize = s;
    }
    else
    {
        // our current buffer has sufficient space so we just upload data with no reallocation
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m->index->count * sizeof(int), m->index->data);
    }
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