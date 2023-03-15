

#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>

PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df, PRINT_FUNC pf){
    PAdptArray pAdptArray = (PAdptArray)malloc(sizeof(AdptArray_));
    pAdptArray->copy_func = cf;
    pAdptArray->del_func = df;
    pAdptArray->print_func = pf;
    return pAdptArray;
}

void DeleteAdptArray(PAdptArray ptr){
    free(ptr->arr);
    free(ptr);
}

Result SetAdptArrayAt(PAdptArray pAdptArray, int idx, PElement pElement){
    PElement new_pElement = pAdptArray->copy_func(pElement);
    pAdptArray->del_func(pElement);

    if (idx >= 0 && idx < GetAdptArraySize(pAdptArray)) {
        if ((pAdptArray->arr)[idx] == NULL){

        }
        (pAdptArray->arr)[idx] = new_pElement;
    }
    else if (idx < 0 && abs(idx) <= GetAdptArraySize(pAdptArray)) {
        (pAdptArray->arr)[GetAdptArraySize(pAdptArray) + idx] = new_pElement;
    }
    else {
        printf("Index out of range\n");
        Result r = 0;
        return r;
    }
}

PElement GetAdptArrayAt(PAdptArray pAdptArray, int idx){
    if (idx >= 0 && idx < GetAdptArraySize(pAdptArray)) {
        return pAdptArray->copy_func((pAdptArray->arr)[idx]);
    }
    else if (idx < 0 && abs(idx) <= GetAdptArraySize(pAdptArray)) {
        return pAdptArray->copy_func((pAdptArray->arr)[GetAdptArraySize(pAdptArray) + idx]);
    }
    else {
        printf("Index out of range\n");
        return (PElement)NULL;
    }
}

int GetAdptArraySize(PAdptArray pAdptArray){
    int i = 0;
    while((pAdptArray->arr)[i] != NULL){
        i++;
    }
    if(i==0){
        return -1;
    }
    return i;
}

void PrintDB(PAdptArray pAdptArray){
    int i = 0;
    printf("[");
    while(i != GetAdptArraySize(pAdptArray)){
        if (i == GetAdptArraySize(pAdptArray) - 1){
            printf("%d", i);
        }
        else{
            printf("%d, ", i);
        }
        i++;
    }
    printf("]");
}