#include "mingen.h"

#ifndef MACRO
#define MACRO

// macros
#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : \
                      (__builtin_strrchr(__FILE__, '\\') ? __builtin_strrchr(__FILE__, '\\') + 1 : __FILE__))
                      
#define delete(data) fn.utility.delete(data)
#define log(data) fn.utility.log(data, __FILENAME__, __LINE__)
#define load(data) fn.utility.load(data)

#endif