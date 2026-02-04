#include "stdio.h"
#include "../headers/memory.h"
#include "../headers/key.h" // this includes windows.h so no need to do it again here

HHOOK keyboard_listener;

LRESULT CALLBACK keyHandler(int nCode, WPARAM wParam, LPARAM lParam);

keyPresses pressed_keys = {0};


unsigned int readBits(DWORD data,int beginning, int end){

    unsigned int mask = 0;
    for (int i = beginning; i <= end; i++) {
        mask = mask | (1 << i);
    }

    unsigned int extracted_bits = (data & mask) >> 4;

    return extracted_bits;
}

void printKeys(){
    for(int i = 0; i < pressed_keys.count; ++i){
        printf("CHAR %c\n",pressed_keys.items[i]);
    }
}

void addKeyToArray(keyPress key){
    printf("%c was lowered\n",key.keyCode);

    da_append(pressed_keys,key);
}

void removeKeyFromArray(DWORD keyCode){
    // Remove key from array
    for (int i = 0; i < pressed_keys.count; i++){
        if(pressed_keys.items[i].keyCode == keyCode){
            printf("%c was lifted\n",pressed_keys.items[i].keyCode);
        }
    }
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

            addKeyToArray(key);
            printf("Added %c\n",key.keyCode);            
            break;
        }
        case WM_KEYUP:
        {   
            

            break;
           
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


// TODO: if a key is pressed down, it goes to the pressed_keys array
//      if the key goes up, the key is removed from the array
//      on a key add event, check if the current combination fits into a user defined shortcut

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
