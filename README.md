# WinMacro

## Requirements

- [GCC](https://gcc.gnu.org/) - Other compilers may work but your mileage may vary
- [Windows](http://microsoft.com/windows) - [Windows 2000 Professional [desktop apps only] MINIMUM]
- [Some knowledge of C](https://colorcomputerarchive.com/repo/Documents/Books/The%20C%20Programming%20Language%20%28Kernighan%20Ritchie%29.pdf) OR some premade [.dll](https://en.wikipedia.org/wiki/Dynamic-link_library) files that **YOU** trust

## How to use

To use WinMacro you will need something call "modules". These are just simple .dll files that all share a function name and lack of function parameters. The function name being _dll_main. This allows the user to define their own functionality of any scale to be ran at a simple shortcut combination.
The /examples folder contains an example source file that is used to generate the add2.dll file.

The file in question looks like:

```c
#include <stdio.h>

int add2(int num){
   return num + 2;
}

__declspec( dllexport ) int _dll_main (){
   
   int n = 67;

   printf("%d + 2 = %d\n",n,add2(n));
   return 0; // if failure return none 0 exit code
}
```

The place you will place your .c files to generate your modules will be found in /dll_src. When build_dlls.ps1 or build_binary.ps1 is ran, all the .c files in /dll_src will be compiled into the /modules folder with the same name as their source file, just with .dll instead of .c
To actually use these freshly compiled modules, you will need to link them to some keyboard shortcut. The shortcut must conform to the notion of "\<char\>+\<char\>+\<char\>". You can have any amount of chars but they **MUST** be seperated by a plus. And you will need to link them to their respective module

The file holding all your programs shortcuts will be found in "shortcuts.txt"

This is an example of a working shortcuts.txt file

```
"a+b+c" : "modules/add2.dll"
```

# What I want to add

Some compatability with another file type to allow the user to define actions that dont need to be compiled to .dll and can be read at runtime
