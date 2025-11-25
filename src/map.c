#include "../include/mingen.h"

static map* _map_new(int ID, char* name)
{
    map* m = malloc(sizeof(map));
    m->ID = ID;
    m->name = name;
    m->chunks = fn.list.new(100);
    return m;
}

static void _map_load()
{

}

static void _map_unload()
{

}

static void _map_mapgen()
{

}

void _init_map()
{
    fn.map.new = &_map_new;
    fn.map.load = &_map_load;
    fn.map.unload = &_map_unload;
    fn.map.mapgen = &_map_mapgen;
}