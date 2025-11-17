#include "../include/mingen.h"

static void _utility_log(char *message) { printf("%s\n", message); }
static void _utility_logint(int value) { printf("%d\n", value); }
static void _utility_logfloat(float value) { printf("%f\n", value); }

static void _utility_logarray(array *array, array_type type)
{
    if (type == INT) { int *arr = (int*) array->data; for(int i = 0; i < array->length; i++) { _utility_logint(arr[i]); } }
    if (type == FLOAT) { float *arr = (float*) array->data; for(int i = 0; i < array->length; i++) { _utility_logfloat(arr[i]); } }
}

static char* _utility_readfile(char* filename)
{
    // open the file
    FILE *file = fopen(filename, "rb");
    char *data;
    long size;

    // get the filesize
    fseek(file, 0L, SEEK_END); 
    size = ftell(file); 
    rewind(file);

    // allocate our string, we need to add an extra byte
    // to the end so we can nul terminate the string
    data = (char *)malloc(size + 1);

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

void _init_utility(FN *fn)
{
    fn->util.log = &_utility_log;
    fn->util.logint = &_utility_logint;
    fn->util.logfloat = &_utility_logfloat;
    fn->util.logarray = &_utility_logarray;
    fn->util.readfile = &_utility_readfile;
}