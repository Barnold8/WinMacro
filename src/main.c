#include "stdio.h"
#include "../headers/handle_key.h"
#include "../headers/custom_string.h"

// TODO: Make a file type that defines a shortcut with its .dll file
    // read file and evaluate shortcut string to an integer
        // split string function, String* string_split(string,delim)
    // find hashmap library and use to use shortcut integer as key and dll function as value (maybe, need to figure it out)

// TODO: check for mem leaks on windows... yaaaaay


typedef int (__cdecl *MYPROC)(int); 

void foo(){

    HINSTANCE hinstLib; 
    MYPROC ProcAdd; 
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE; 
 
    // Get a handle to the DLL module.
 
    hinstLib = LoadLibrary(TEXT("..\\modules\\add2.dll")); 
 
    // If the handle is valid, try to get the function address.
 
    if (hinstLib != NULL) 
    { 
        ProcAdd = (MYPROC) GetProcAddress(hinstLib, "add2"); 
 
        // If the function address is valid, call the function.
 
        if (NULL != ProcAdd) 
        {
            fRunTimeLinkSuccess = TRUE;
            printf("12 + 2 %d\n",(ProcAdd (12))); 
        }
        // Free the DLL module.
 
        fFreeResult = FreeLibrary(hinstLib); 
    } 

    // If unable to call the DLL function, use an alternative.
    if (! fRunTimeLinkSuccess) 
        printf("Message printed from executable\n"); 

    return;

}


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

    printf("Press any key to quit...");
    getchar();

    UnhookWindowsHookEx(keyboard_listener);

    if(pressed_keys.items != NULL){
        free(pressed_keys.items);
    }

    StringBuilder testString = new_string("Hello world!\n");
    StringArray strings      = split_string(&testString,' ');

    for(int i = 0; i < strings.count; ++i){
        printf("String in split strings[%d] %s\n",i,strings.items[i].items);
    }

    return 0;

}
