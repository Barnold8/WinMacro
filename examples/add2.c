// Compile me in gcc with "gcc -shared -o <MODULE_PATH>.dll <SOURCE_PATH>add2.c" 

#include <stdio.h>

int add2(int num){
   return num + 2;
}

__declspec( dllexport ) int _dll_main (){
   
   int n = 2;
   
   return add2(n);

   // if failure return none 0 exit code
}

