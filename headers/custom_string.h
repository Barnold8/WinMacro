#ifndef CUSTOM_STRING_H
#define CUSTOM_SRING_H

#include <string.h>

#include <stdio.h>

typedef struct{
    
    char* items;
    size_t count;
    size_t capacity;
    
}StringBuilder;

typedef struct{
    
    StringBuilder* items;
    size_t count;
    size_t capacity;
    
}StringArray;



StringBuilder new_string(char* stack_string){

    size_t i = 0;

    StringBuilder new_string = {0};
    while(stack_string[i] != '\0'){
        da_append(new_string,stack_string[i]);
        i++;
    }
    return new_string;
}

void generate_string(StringBuilder* heap_string,char* stack_string){
    // Assumes heap_string is empty. It will append to whatever is already there
    size_t i = 0;
    while(stack_string[i] != '\0'){
        da_append((*heap_string),stack_string[i]);
        i++;
    }

}

void generate_string_verbose(StringBuilder* heap_string,char* stack_string){
    // Wrapper function for generate_string but only accepts empty strings

    if(heap_string->count > 0){
        return;
    }
    generate_string(heap_string,stack_string);

}


StringArray split_string(StringBuilder * string,char delim){
    
    StringArray splitString = {0};
    char* tempString = strtok(string->items, " ");

    while(tempString != NULL){
        da_append(
            splitString,new_string(tempString)
        );
        tempString = strtok(NULL, " ");
    }
    return splitString;
}

StringArray split_string_and_free(StringBuilder * string,char delim){
    // Wrapper function for split_string but also frees the input string to split
    StringArray splitString = split_string(string,delim);

    if(string->items != NULL){
        free(string->items);
    }

    return splitString;
}



#endif