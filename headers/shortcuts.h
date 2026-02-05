#ifndef SHORTCUTS_H
#define SHORTCUTS_H


#include "custom_string.h" 
#include "key.h"


int calculate_shortcut(StringBuilder* shortcut){

    StringArray tokens = split_string(shortcut,'+');
    int sum = 0;

    for(size_t i = 0; i < tokens.count; i++){
        sum += tokens.items[i].items[0]; // the char will be the 0th element so this is fine
    }

    return  (sum > 0) ? sum : -1; // cant figure it out, return error code
}

int calculate_shortcut_with_keys(keyPresses* keys){
    int mask = 0;

    for(size_t i = 0; i < keys->count; i++){
        mask |= keys->items[i].keyCode; // the char will be the 0th element so this is fine
    }

    return mask;
}



int calculate_shortcut_and_free(StringBuilder* shortcut){

    int return_code = calculate_shortcut(shortcut);
    free((*shortcut).items);

    return return_code; 
}



#endif