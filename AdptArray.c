#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//here we init PAdptArray (pointer to AdptArray_)
PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete, PRINT_FUNC print){
	PAdptArray pAdptArray = (PAdptArray)calloc(1, sizeof(AdptArray_));
	pAdptArray->copy_func = copy;
	pAdptArray->del_func = delete;
	pAdptArray->print_func = print;
	pAdptArray->len = -1;
	pAdptArray->arr=NULL;

	return pAdptArray;
}

void DeleteAdptArray(PAdptArray ptr){
	int size = GetAdptArraySize(ptr); 
	
	for (int i =0; i<size; i++){
		if(!ptr->arr[i]){ //check if the current is null avoid access null and make seg-fault
			continue;
		}
		ptr->del_func(ptr->arr[i]); 
	}
	free(ptr->arr);
	free(ptr);
}

Result SetAdptArrayAt(PAdptArray pAdptArray, int idx, PElement pElement){
	int size = pAdptArray->len;
	if(!pElement){
		return FAIL;
	} //cant set to null
	PElement copy_pElement = pAdptArray->copy_func(pElement); //return the copy of the element
	
	if(idx>=0){ //positive index
		if(size==-1){//wasn't init yet
			pAdptArray->arr = (PElement*)calloc(idx+1, sizeof(pElement));
			if(!pAdptArray->arr){
				return FAIL;
			}
			
			pAdptArray->arr[idx] = copy_pElement;
			pAdptArray->len = idx+1;
			return SUCCESS;
			
		}
		
		if(idx<size){ //index in bound
			pAdptArray->arr[idx] = copy_pElement;
			return SUCCESS;
		}
		
		else{ //index out of bound range but addaptive
			//pAdptArray->arr = (PElement*)realloc(pAdptArray->arr, (idx+1)*sizeof(pElement));
			PElement* temp = (PElement*)calloc(idx+1, sizeof(pElement));
			memcpy(temp, pAdptArray->arr, size*sizeof(pElement));
			free(pAdptArray->arr);
			pAdptArray->arr=temp;
			
			if(!pAdptArray->arr){
				return FAIL;
			}
			pAdptArray->arr[idx] = copy_pElement;
			pAdptArray->len = idx+1;
			return SUCCESS;
		}
	
	}
	
	if(idx<0){ //negative index
		if(size==-1){//wasn't init yet
			return FAIL;
		}
		
		idx+=size; //to specified the correct index
		
		if(idx>=0 && idx<size){ //the index is good
			pAdptArray->arr[idx] = copy_pElement;
			return SUCCESS;
		}
	
	
		else if(idx>=size){ //index is out of bound range
			return FAIL;
		}
	}
	
	return FAIL;
}

PElement GetAdptArrayAt(PAdptArray pAdptArray, int idx){
	int size = pAdptArray->len;
	PElement copy_pElement;
	
	if(idx>=0){ //positive index
		if(size==-1 || idx>=size){//wasn't init yet
			return NULL;	
		}
	
		if(idx<size){ //index in bound
			if(!pAdptArray->arr[idx]){
				return NULL;
			}
			copy_pElement = pAdptArray->copy_func(pAdptArray->arr[idx]);
			
			return copy_pElement;
		}
	}
	
	if(idx<0){ //negative index
		if(size==-1){//wasn't init yet
			return NULL;
		}
		
		idx+=size; //to specified the correct index
		
		if(idx>=0 && idx<size){ //the index is good
			if(!pAdptArray->arr[idx]){
				return NULL;
			}
			copy_pElement = pAdptArray->copy_func(pAdptArray->arr[idx]);
			
			return copy_pElement;
		}
	
	
		else if(idx>=size){ //index is out of bound range
			return NULL;
		}
	}
	return FAIL;
}

int GetAdptArraySize(PAdptArray pAdptArray){
    	return pAdptArray->len;
}

void PrintDB(PAdptArray pAdptArray){
	int size = GetAdptArraySize(pAdptArray);
	if (size==-1){ //wasnt init yet
		return;
	}

	int i = 0;
	while(i < size){
		if(!pAdptArray->arr[i]){
			i++;
			continue;
		} //check if the current is null: continue, else: print it
		
		pAdptArray->print_func(pAdptArray->arr[i]);
		i++;
	}
        
}
