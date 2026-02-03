#include "windows.h"
typedef struct{
    
    DWORD keyCode;
    DWORD timePressed;
    

}keyPress;


struct keys
{
    keyPress *items;
    size_t count;
    size_t capacity;
}keys;