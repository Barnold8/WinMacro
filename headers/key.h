#ifndef KEY_H
#define KEY_H

#include "windows.h"

typedef struct{
    
    DWORD keyCode;
    DWORD timePressed;
    

}keyPress;


typedef struct keyPresses
{
    keyPress *items;
    size_t count;
    size_t capacity;

}keyPresses;


char* keyPresses_to_string(keyPresses* keyArray){

    char* string = malloc(sizeof(char)*keyArray->count);

    for(int i = 0; i < keyArray->count; i++){
        string[i] = keyArray->items[i].keyCode;
    }
    return string;
}

#endif