#include "../include/mingen.h"

//
//  NEW:  creates a new list with a specified size where size = # of bits per element
//

static list* _list_new(int size)
{
    list* a = malloc(sizeof(list));
    a->count = 0;
    a->size = size;
    a->data = malloc(size * sizeof(void*));
    return a;
}

//
//  GROW:  will reallocate the list whenever it fills up
//

static void _list_grow(list* a)
{
    a->size *= 2;
    a->data = realloc(a->data, sizeof(void*) * a->size);
}

//
//  ADD:  adds an element to the list resizing it in the process
//

static void _list_add(list* a, void* data)
{
    if (a->count >= a->size) { _list_grow(a); }
    ((void**)a->data)[a->count++] = data;
}

//
//  SET:  assigns a new piece of data at index
//

static void _list_set(list* a, int index, void* data)
{
    if (index < 0 || index >= a->count) { return; }
    ((void**)a->data)[index] = data;
}

//
//  GET:  returns pointer to element at index
//

static void* _list_get(list* a, int index)
{
    if (index < 0 || index >= a->count) { return NULL; }
    return ((void**)a->data)[index];
}

//
//  REMOVE:  removes an element in the list at index
//

static void _list_remove(list* a, int index)
{
    if (index < 0 || index >= a->count) { return; }

    void** data = (void**)a->data;
    for (int i = index; i < a->count - 1; i++) { data[i] = data[i + 1]; }

    a->count--;
}

//
//  list.C:  a helper module for managing lists
//            we can have an list of primitives and also custom types
//

void _init_list()
{
    fn.list.new = &_list_new;
    fn.list.add = &_list_add;
    fn.list.set = &_list_set;
    fn.list.get = &_list_get;
    fn.list.remove = &_list_remove;
}