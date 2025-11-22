#include "../include/mingen.h"

//
//  NEW:  creates a new hashtable with a predetermined # of entries
//

static table* _table_new(int max)
{
    table* h = malloc(sizeof(table));
    h->count = 0;
    h->max = max;
    h->entry = calloc(max, sizeof(entry));
    return h;
}

//
//  HASH:  creates a hash from our uid struct
//

static uint32_t _table_hash(uid* uid)
{
    uint32_t hash = 2166136261u; 
    for (size_t i = 0; i < 16; i++) {
        hash ^= uid->data[i];
        hash *= 16777619;
    }
    return hash;
}

//
//  COMPARE:  checks if two uids are equal
//

static int _table_compare(uid* a, uid* b)
{
    return memcmp(a->data, b->data, 16) == 0;
}

//
//  INSERT:  inserts a new entry into the table
//

static void _table_insert(table* table, uid* key, void* data)
{
    uint32_t h = _table_hash(key);
    size_t index = h % table->max;

    for (size_t i = 0; i < table->max; i++) 
    {
        size_t p = (index + i) % table->max;
        entry* e = &table->entry[p];

        // if the entry state is 0 (unused) or -1 (deleted) then we can use it
        if (e->state <= 0) 
        {
            e->key = key;    
            e->data = data;
            e->state = 1;
            table->count++;
            return;
        }

        // if the entry state is 1 (used) then update it with the new value
        if (e->state == 1 && _table_compare(e->key, key)) 
        {
            e->data = data;
            return;
        }
    }

    // check if our table is at 70% capacity and if so resize it
}

//
//  GET:  inserts a new entry into the table
//

static void* _table_get(table* table, uid* key)
{
    uint32_t h = _table_hash(key);
    size_t index = h % table->max;

    for (size_t i = 0; i < table->max; i++) 
    {
        size_t p = (index + i) % table->max;
        entry* e = &table->entry[p];

        if (e->state == 0) return NULL;
        if (e->state == 1 && _table_compare(e->key, key)) { return e->data; }
    }

    return NULL;
}

//
//  REMOVE:  removes an entry from the table
//

static void _table_remove(table* table, uid* key)
{
    uint32_t h = _table_hash(key);
    size_t index = h % table->max;

    for (size_t i = 0; i < table->max; i++) 
    {
        size_t p = (index + i) % table->max;
        entry* e = &table->entry[p];

        if (e->state == 0) return; 
        if (e->state == 1 && _table_compare(e->key, key)) 
        {
            e->state = -1; 
            table->count--;
            return;
        }
    }
}

//
//  TABLE.C:  a hashtable.  lets us store objects by uid to easily retrieve and edit their data
//

void _init_table(FN* fn)
{
    fn->table.new = &_table_new;
    fn->table.hash = &_table_hash;
    fn->table.compare = &_table_compare;
    fn->table.insert = &_table_insert;
    fn->table.get = &_table_get;
    fn->table.remove = &_table_remove;
}