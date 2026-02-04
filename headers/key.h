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

#endif