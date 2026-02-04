#include "stdio.h"
#include "../headers/memory.h"
#include "../headers/key.h"

HHOOK keyboard_listener;
LRESULT CALLBACK keyHandler(int nCode, WPARAM wParam, LPARAM lParam);
keyPresses pressed_keys = {0};

BOOL DELETING = 0;


void printKeys(){
    for(int i = 0; i < pressed_keys.count; ++i){
        printf("CHAR[%d] %c\n",i,pressed_keys.items[i]);
    }
}

void addKeyToArray(keyPress key){
   
    BOOL hasKey = 0; // Windows slop type which is an int, so it doesnt even save space, its just shit.

    for(int i = 0; i < pressed_keys.count; ++i){
        if(pressed_keys.items[i].keyCode == key.keyCode){
            hasKey = 1;
        }
    }

    if(hasKey == 0){
        da_append(pressed_keys,key);
    }
    
}

void removeKeyFromArray(DWORD keyCode){
    // Remove key from array
    for (int i = 0; i < pressed_keys.count; i++){
        if(pressed_keys.items[i].keyCode == keyCode){
            //SWAP i with last elem
                pressed_keys.items[i] = pressed_keys.items[--pressed_keys.count];
        }
    }

    if(pressed_keys.count == 1){
        pressed_keys.count = 0; // allow whatever is left to be overwritten
    }  
}



void handleKeyPress(WPARAM wParam, LPARAM lParam){

    struct tagKBDLLHOOKSTRUCT* keyInfo = (struct tagKBDLLHOOKSTRUCT *)lParam;

    switch(wParam){
        case WM_KEYDOWN: // Do I do a check in the array if it exists and if not dont add? but thats O(n). Granted on a small data structure
        {
            // DWORD isDown = test->flags & 0x40000000; 
            // for(int i = 0; i < 32; i++){
            //     printf("BIT %d",test->flags >> i);
            // }
            // WORD count = (lParam >> 0) & ((1<<15)-1);
            // WORD isPressed = lParam & (1 << 30);
            // WORD isPressed_i = lParam & (1 << 30);
            // WORD wRepeatCount = (WORD)(lParam & 0x0000FFFF);
            // printf("%d count\n",count);
            // printf("%d isPressed (30)\n",isPressed);
            // printf("%d isPressed (31)\n",isPressed_i);
            // printf("%d flags 30\n",test->flags & (1<<30));
            // printf("%d flags 31\n",test->flags & (1<<31));
            // printf("%d REPEAT COUNT %d\n",wRepeatCount);
            // going to have to check every element to see if vkcode is in it, which is STUPID. but fucking microsoft documentation 
            // is fucking shit and I hate whatever troglodyte fucking wrote it. 
            // WORD keyFlags = HIWORD(lParam); // LOOK <- EVEN THE CODE IN THEIR OFFICIAL DOCS SUCKS COCK
            // BOOL wasKeyDown = (keyFlags & KF_REPEAT) == KF_REPEAT;
            // printf("BOOL %d\n",wasKeyDown);

            keyPress key = {
                    keyInfo->vkCode,
                    keyInfo->time,
            };

            addKeyToArray(key);
            
            
            break;

        }
        case WM_KEYUP:
        {   

            if(pressed_keys.count > 0 && DELETING == 0){
                printf("Keys that were held down:\n");
                printKeys();
            }
            if(pressed_keys.count > 0 && DELETING == 0){ // global variable logic to know WHEN to perform shortcut key lookup

                DELETING = 1;
            }

            else if(pressed_keys.count == 0){ 
                DELETING = 0;
            }

            

            removeKeyFromArray(keyInfo->vkCode);
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
