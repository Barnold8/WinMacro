#ifndef MEMORY_H
#define MEMORY_H


#define da_append(xs,x) if (xs.count >= xs.capacity) {\
    do {\
        if (xs.capacity == 0) xs.capcity = 256;\
        else xs.capacity *= 2;\
        xs.items = realloc(xs.items,xs.capacity*sizeof(xs.items))\
    } while(0)\
}

#endif

// all we need above for a dynamic array in C :)

// struct someStruct
// {
//     type *items;
//     size_t count;
//     size_t capacity;
// } someStruct;