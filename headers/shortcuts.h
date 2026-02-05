#ifndef SHORTCUTS_H
#define SHORTCUTS_H

#include "custom_string.h" 
#include "key.h"


int calculate_shortcut(StringBuilder* shortcut){

    long int mask = 0;

    for(size_t i = 0; i < shortcut->count; i++){
        int bit = shortcut->items[i] - 'a'; // -a to remove
        mask |= (1L << bit);
    }
}

long int calculate_shortcut_with_keys(keyPresses* keys){
    long int mask = 0;

    for(size_t i = 0; i < keys->count; i++){
        int bit = keys->items[i].keyCode - 'a';
        mask |= (1L << bit);
    }

    return mask;
}



int calculate_shortcut_and_free(StringBuilder* shortcut){

    int return_code = calculate_shortcut(shortcut);
    free((*shortcut).items);

    return return_code; 
}



#endif