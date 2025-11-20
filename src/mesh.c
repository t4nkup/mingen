#include "../include/mingen.h"

//
//  NEW:  creates a new mesh in memory and creates a VAO for it
//

static mesh* _mesh_new(FN* fn)
{
    mesh* m = malloc(sizeof(mesh));
    m->vertex = fn->array.new(0, sizeof(float));
    m->index = fn->array.new(0, sizeof(int));
    m->uv = fn->array.new(0, sizeof(float));

    fn->array.add(m->vertex, 12, (float[]){
        -0.5f, -1.5f, 0.0f,  // bottom-left
        -0.5f,  0.5f, 0.0f,  // top-left
         0.5f,  0.5f, 0.0f,  // top-right
         0.5f, -0.5f, 0.0f   // bottom-right
    });

    fn->array.add(m->index, 6, (int[]){
        0, 1, 2,
        0, 2, 3
    });

    // create our openGL buffer objects and assign their IDs to our mesh
    glGenVertexArrays(1, &m->VAO);
    glGenBuffers(1, &m->VBO);
    glGenBuffers(1, &m->EBO);

    // bind our new VAO, we have to bind to it first before working with it
    glBindVertexArray(m->VAO);

    fn->util.logint(m->VAO);

    // fill our VBO with our vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
    glBufferData(GL_ARRAY_BUFFER, m->vertex->length * sizeof(float), m->vertex->data, GL_DYNAMIC_DRAW);
    // fill our EBO with our index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->index->length * sizeof(int), m->index->data, GL_DYNAMIC_DRAW);

    // setup our attribute pointer for our VBO
    // this tells openGL how it can read our VBO data (position, color, uv, normal, etc etc)
    // our EBO doesn't need one since its just pure ints
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // tells openGL to use the attribute pointer with ID 0 that we just created
    glEnableVertexAttribArray(0);
    // now our shader will have access to the data we provided in our VBO

    // unbind our mesh VAO so its not overridden elsewhere
    glBindVertexArray(0);

    return m;
}

//
//  DRAW:  draws the mesh using openGL
//

static void _mesh_draw(FN* fn, mesh* m)
{
    glBindVertexArray(m->VAO);
    glDrawElements(GL_TRIANGLES, m->index->length, GL_UNSIGNED_INT, 0);
}

//
//  FREE:  frees up the mesh memory
//

static void _mesh_free(FN* fn, mesh* m)
{
    fn->array.free(m->vertex);
    fn->array.free(m->index);
    fn->array.free(m->uv);
    free(m);
}

//
//  MESH.C:  utility functions for our mesh struct
//

void _init_mesh(FN* fn)
{
    fn->mesh.new = &_mesh_new;
    fn->mesh.draw = &_mesh_draw;
    fn->mesh.free = &_mesh_free;
}