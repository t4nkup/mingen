#include "../include/mingen.h"

//
//  LOG:  takes a string and prints it to console
//

static void _utility_log(char* message) { printf("%s\n", message); }

//
//  LOGINT:  takes an int and prints it to console
//

static void _utility_logint(int value) { printf("%d\n", value); }

//
//  LOGFLOAT:  takes a float and prints it to console
//

static void _utility_logfloat(float value) { printf("%f\n", value); }

//
//  LOGARRAY:  takes an array and prints each element to the console
//

static void _utility_logarray(array*array, array_type type)
{
    if (type == INT) { int* arr = (int*) array->data; for(int i = 0; i < array->count; i++) { _utility_logint(arr[i]); } }
    if (type == FLOAT) { float* arr = (float*) array->data; for(int i = 0; i < array->count; i++) { _utility_logfloat(arr[i]); } }
}

//
//  READFILE:  reads a data file and returns a string of its characters
//

static char* _utility_readfile(char* filename)
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
//  UTILITY.C:  a helper module for various functions that dont fit elsewhere
//

void _init_utility(FN* fn)
{
    fn->log = &_utility_log;
    fn->logint = &_utility_logint;
    fn->logfloat = &_utility_logfloat;
    fn->logarray = &_utility_logarray;
    fn->readfile = &_utility_readfile;
}