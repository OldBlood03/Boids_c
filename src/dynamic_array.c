#include"raylib.h"
#include<stdlib.h>


typedef struct DArray {
    size_t size; 
    size_t members; 
    Vector2 *arr;
}DArray;

void push (DArray *arr, Vector2 value){
    if (++arr -> members > arr -> size){ 
        arr -> size *= 2; arr -> size += 1;
        arr -> arr = realloc(arr -> arr, arr -> size);
    }
    arr -> arr[(arr -> members)-1] = value;
}
