#ifndef HASH_MAP
#define HASH_MAP


#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"


// TODO: define a struct like
    // struct { float key; char value; } *hash = NULL;
//  to define 

struct {long int key; int value;} *hash = NULL; // need to decide what to use as the value type, for now int is just for viewing


    // int i=0;
    // hmput(hash, i, 12);
    // printf("AT KEY %d is %d\n",i,hmget(hash,i));

#endif