#ifndef MODULE_H
#define MODULE_H
#include "stdio.h"
#include "windows.h"

typedef int (__cdecl *MYPROC)(); 

void foo(){ // use some of this code to run a _dll_main that the user attaches to shortcut

    HINSTANCE hinstLib; 
    MYPROC ProcAdd; 
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE; 
 
    // Get a handle to the DLL module.
 
    hinstLib = LoadLibrary(TEXT("..\\modules\\add2.dll")); 
 
    // If the handle is valid, try to get the function address.
 
    if (hinstLib != NULL) 
    { 
        ProcAdd = (MYPROC) GetProcAddress(hinstLib, "_dll_main"); 
 
        // If the function address is valid, call the function.
 
        if (NULL != ProcAdd) 
        {
            fRunTimeLinkSuccess = TRUE;
            ProcAdd();
        }
        // Free the DLL module.
 
        fFreeResult = FreeLibrary(hinstLib); 
    } 

    // If unable to call the DLL function, use an alternative.
    if (! fRunTimeLinkSuccess){
        fprintf(stderr, "Could not access code in shared object\n");
    }
         

    return;

}

#endif