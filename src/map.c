#include "../include/mingen.h"

static map* _map_new(FN *fn, int ID, char *name)
{
    map *m = malloc(sizeof(map));
    m->ID = ID;
    m->name = name;
    m->chunks = fn->array.new(0, sizeof(chunk));
    return m;
}

static void _map_load(FN *fn)
{

}

static void _map_unload(FN *fn)
{

}

static void _map_mapgen(FN *fn)
{

}

void _init_map(FN *fn)
{
    fn->map.new = &_map_new;
    fn->map.load = &_map_load;
    fn->map.unload = &_map_unload;
    fn->map.mapgen = &_map_mapgen;
}