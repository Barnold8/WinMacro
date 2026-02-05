#include "stdio.h"
#include "../headers/custom_string.h"
#include "../headers/handle_key.h"
#include "../headers/shortcuts.h"
#include "string.h"

// TODO: Make a file type that defines a shortcut with its .dll file
    // read file and evaluate shortcut string to an integer
    // find hashmap library and use to use shortcut integer as key and dll function as value (maybe, need to figure it out)

// TODO: check for mem leaks on windows... yaaaaay

int main(){

    HHOOK keyboard_listener =  SetWindowsHookExA(WH_KEYBOARD_LL,keyHandler,0,0);
    if (keyboard_listener == NULL)
    {
        printf("ERROR CREATING HOOK");
        printf("Error code: %d",GetLastError());
        getchar();
        return 0;
    }

    MSG message;

    while (GetMessage(&message, NULL, 0, 0) != 0)
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    UnhookWindowsHookEx(keyboard_listener);

    if(pressed_keys.items != NULL){
        free(pressed_keys.items);
    }

    return 0;

}