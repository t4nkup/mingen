#include "../include/mingen.h"

//
//  NEW:  creates a new array with a specified size where size = # of bits per element
//

static array* _array_new(int size, type value)
{
    array* a = malloc(sizeof(array));
    a->type = ARRAY;
    a->count = 0;
    a->size = size;
    if (a->size == 0) { a->size = 1; }
    a->value = value;
    switch(value)
    {
        case BOOL:      a->byte = sizeof(bool); break;
        case INT:       a->byte = sizeof(int); break;
        case FLOAT:     a->byte = sizeof(float); break;
        case STRING:    a->byte = sizeof(char*); break;
        case UID:       a->byte = sizeof(uid); break;
        default:        a->byte = sizeof(void*); break;
    }
    a->data = malloc(a->size * a->byte);
    return a;
}

//
//  GROW:  when our array is full we will increase its size
//

static void _array_grow(array* a)
{
    if (a->size < 50) { a->size = 50; }
    a->size *= 2;
    a->data = realloc(a->data, a->size * a->byte);
}

//
//  ADD:  adds more elements to the array resizing it in the process
//

static void _array_add(array* a, int count, void* data)
{
    while (a->count + count > a->size) { _array_grow(a); }
    memcpy((char*)a->data + a->count * a->byte, data, a->byte * count);
    a->count += count;
}

//
//  SET:  assigns a new piece of data at index
//

static void _array_set(array* a, int index, int count, void* data)
{
    if (index < 0 || index + count > a->count) { return; }

    memcpy((char*)a->data + index * a->byte, data, a->byte * count);
}

//
//  GET: returns pointer to element at index
//

static void* _array_get(array* a, int index)
{
    if (index < 0 || index >= a->count) { return NULL; }

    return (char*)a->data + index * a->byte;
}

//
//  REMOVE:  removes an element in the array at index
//

static void _array_remove(array* a, int index, int count)
{
    if (index < 0 || index + count > a->count) { return; }

    char* start = (char*)a->data + index * a->byte;
    char* end   = start + count * a->byte;

    memmove(start, end, (a->count - index - count) * a->byte);
    a->count -= count;
}

//
//  ARRAY.C:  a helper module for managing arrays
//            we can have an array of primitives and also custom types
//

void _init_array()
{
    fn.array.new = &_array_new;
    fn.array.add = &_array_add;
    fn.array.set = &_array_set;
    fn.array.get = &_array_get;
    fn.array.remove = &_array_remove;
}