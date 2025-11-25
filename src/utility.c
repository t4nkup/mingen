#include "../include/mingen.h"

//
//  DELETE:  takes a void pointer to one of our objects and frees
//           its memory based off its type
//

void _utility_delete(void* data)
{
    if (data == NULL) { return; }

    // read the first byte of our void pointer and cast it to its enum type
    type t = *(type*)data;

    switch(t)
    {
        case ARRAY:
            array* a = (array*) data;
            free(a->data);
        break;
        case CHUNK:
        break;
        case ENTRY:
        break;
        case GAME:
        break;
        case GRID:
        break;
        case LIST:
            list* l = (list*) data;
            for (int i = 0; i < l->count; i++) {
                void* d = (char*)l->data + i * l->size;
                _utility_delete(d);
            }
        case MAP:
        break;
        case MESH:
            mesh* m = (mesh*) data;
            _utility_delete(m->vertex);
            _utility_delete(m->uv);
            _utility_delete(m->index);
        break;
        case SHAPE:
        break;
        case TABLE:
        break;
        case TRANSFORM:
        break;
        default: break;
    }

    free(data);
}

//
//  LOG:  prints our data for a type to console for debugging
//

static void _utility_log(void* data, const char* file, int line)
{
    if (data == NULL) { return; }

    // read the first byte of our void pointer and cast it to its enum type
    type t = *(type*)data;

    // log what file and line # this log came from
    printf("%s, %d: ", file, line);

    switch(t)
    {
        case ARRAY:
            array* _array = (array*) data;
            switch(_array->value)
            {
                case BOOL:      printf("ARRAY\n- Type: BOOL\n"); break;
                case INT:       printf("ARRAY\n- Type: INT\n"); break;
                case FLOAT:     printf("ARRAY\n- Type: FLOAT\n"); break;
                case STRING:    printf("ARRAY\n- Type: STRING\n"); break;
                case UID:       printf("ARRAY\n- Type: UID\n"); break;
                default: break;
            }
            printf("- Count: %d\n", _array->count);
            printf("- Size: %d\n", _array->size);
            for (int i = 0; i < _array->count; i++) {
                void* e = (char*)_array->data + i * _array->byte;
                switch (_array->value) {
                    case BOOL: printf("[%d] %s\n", i, (*(bool*)e ? "true" : "false")); break;
                    case INT:  printf("[%d] %d\n", i, *(int*)e); break;
                    case FLOAT: printf("[%d] %f\n", i, *(float*)e); break;
                    case STRING: printf("[%d] %s\n", i, *(char**)e); break;
                    case UID:   uint8_t* id = (uint8_t*)e; printf("[%d] ", i);
                                for (int j = 0; j < 16; j++) { printf("%02x", id[j]); }
                                printf("\n"); break;
                    default: break;
                }
            }
        break;
        case CHUNK:
        break;
        case GAME:

        break;
        case GRID:
            grid* _grid = (grid*) data;
            printf("GRID\n- Size: %d", _grid->size);
        break;
        case LIST:

        break;
        case MAP:
        break;
        case MESH:

        break;
        case TABLE:

        break;
        default: 
            char* s = (char*)data;
            for (int i = 0; s[i] != '\0'; i++) { putchar(s[i]); }
            printf("\n");
        break;
    }
}

//
//  LOAD:  reads a data file and returns a string of its characters
//

static char* _utility_load(char* filename)
{
    // open the file
    FILE* file = fopen(filename, "rb");
    char* data;
    long size;

    // get the filesize
    fseek(file, 0L, SEEK_END); 
    size = ftell(file); 
    rewind(file);

    // allocate our string, we need to add an extra byte
    // to the end so we can nul terminate the string
    data = (char*)malloc(size + 1);

    // read the file and nul terminate the end
    size = fread(data, 1, size, file); 
    data[size] = '\0';

    // close the file
    fclose(file);
    
    // send the string back:  we need to make sure
    // to free the string from wherever we are sending it
    // to avoid memory leak
    return data;
}

//
//  UID:  generates a random 16 byte uid
//

void _utility_uid(uid id)
{
    static uint32_t counter = 0;
    counter++;

    static uint32_t prng_state = 0;
    if (prng_state == 0) { prng_state = (uint32_t)time(NULL); }

    uint32_t x = prng_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    prng_state = x;
    uint64_t t = (uint64_t)time(NULL);
    for (int i = 0; i < 8; i++) { id[i] = (t >> (56 - i*8)) & 0xFF; }
    for (int i = 0; i < 4; i++) { id[8 + i] = (counter >> (24 - i*8)) & 0xFF; }
    for (int i = 0; i < 4; i++) { id[12 + i] = (x >> (24 - i*8)) & 0xFF; }
    id[6] = (id[6] & 0x0F) | 0x40;
    id[8] = (id[8] & 0x3F) | 0x80;
}

//
//  UTILITY.C:  a helper module for various functions that dont fit elsewhere
//

void _init_utility()
{
    fn.utility.delete = &_utility_delete;
    fn.utility.log = &_utility_log;
    fn.utility.load = &_utility_load;
    fn.utility.uid = &_utility_uid;
}