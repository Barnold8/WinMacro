#include "stdio.h"
#include "../headers/memory.h"
#include "../headers/key.h" // this includes windows.h so no need to do it again here

HHOOK keyboard_listener;

LRESULT CALLBACK keyHandler(int nCode, WPARAM wParam, LPARAM lParam);

keyPresses pressed_keys = {0};


void printKeys(){
    for(int i = 0; i < pressed_keys.count; ++i){
        printf("CHAR %c\n",pressed_keys.items[i]);
    }

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

    return 0;
}

void handleKeyPress(WPARAM wParam, LPARAM lParam){

    struct tagKBDLLHOOKSTRUCT* test = (struct tagKBDLLHOOKSTRUCT *)lParam;

    switch(wParam){
        case WM_KEYDOWN:
        {

            keyPress key = {
                    test->vkCode,
                    test->time,
            };
            if(test->vkCode == 32){
                printKeys();
            }else{
                
                da_append(pressed_keys,key);

                printf("COUNT %d\n",pressed_keys.count);
                printf("Keydown-Key     : [CHAR: %c] [DWORD: %lu]\n",test->vkCode,test->vkCode);
                printf("Keydown-ScanCode: [CHAR: %c] [DWORD: %lu]\n",test->scanCode,test->scanCode);
                printf("Time? %lu\n",test->time);
            }

  
        }
    }

}

LRESULT CALLBACK keyHandler(int nCode, WPARAM wParam, LPARAM lParam)
{
  
  // Checks whether params contain action about keystroke
  if (nCode == HC_ACTION)
  {
    //lparam holds the info but i cant fucking use it normally cos windows code is fucking dogshit
    //  LPARAM is a long_ptr which is one of those stupid fucking windows type defs that just make code harder to write
    handleKeyPress(wParam,lParam);
  }
  

  return CallNextHookEx(keyboard_listener, nCode,
                        wParam, lParam);
}
