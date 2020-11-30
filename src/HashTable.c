/*
 * HashTable.c
 *
 *  Created on: Nov 28, 2020
 *      Author: ise
 */

#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"

struct hashTable_s{
	CopyFunction copyKey;
	FreeFunction freeKey;
	PrintFunction printKey;
	CopyFunction copyValue;
	FreeFunction freeValue;
	PrintFunction printValue;
	EqualFunction equalKey;
	TransformIntoNumberFunction transformIntoNumber;
	int hashSize;
	LinkedList *table;
};

hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
							CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
							EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
	hashTable htb = NULL;
	if (copyKey== NULL || freeKey== NULL ||printKey== NULL ||copyValue== NULL ||freeValue== NULL ||printValue== NULL ||
			equalKey== NULL ||transformIntoNumber== NULL){
		return NULL;
	}
	htb->copyKey =copyKey;
	htb->copyValue = copyValue;
	htb->equalKey = equalKey;
	htb->freeKey = freeKey;
	htb->freeValue = freeValue;
	htb->printKey = printKey;
	htb->printValue = printValue;
	htb->transformIntoNumber = transformIntoNumber;
	htb->hashSize = hashNumber;
	htb->table = (LinkedList *) calloc(hashNumber,sizeof(LinkedList));//LinkedList is a pointer to Linked List
	if (htb->table == NULL){
			return NULL;
		}

	return htb;
}


status destroyHashTable(hashTable htb){
	if(htb == NULL){
		return failure;
	}
	int i;
	for (i=0 ; i< htb->hashSize;i++){
		destroyList(htb->table[i]);
	}
	free(htb->table);//************free*************
	return success;


}
status addToHashTable(hashTable htb, Element key,Element value){
	if (htb == NULL || key == NULL || value == NULL){
		return failure;
	}
	int intKey = htb->transformIntoNumber(key);
	KeyValuePairPointer KVP = createKeyValuePair(htb->copyKey(key),htb->copyValue(value),htb->printValue,htb->printKey );
	int place = intKey % htb->hashSize;
	if (htb->table[place] == 0){
		htb->table[place] = createLinkedList (htb->printValue,htb->equalKey,htb->freeValue,htb->copyValue);
	}

	appendNode(htb->table[place], KVP);
	return success;
}


Element lookupInHashTable(hashTable htb, Element key){
	if (htb == NULL || key == NULL){
		return NULL;
	}
	int intKey = htb->transformIntoNumber(key);
	int place = intKey % htb->hashSize;
	return searchByKeyInList(htb->table[place],key);

}


status removeFromHashTable(hashTable htb, Element key){
	if (htb == NULL || key == NULL){
		return failure;
	}
	int intKey = htb->transformIntoNumber(key);
	int place = intKey % htb->hashSize;
	if (searchByKeyInList(htb->table[place],key) == NULL){
		return failure;
	}
	deleteNode(htb->table[place],key);
	return success;

}
status displayHashElements(hashTable htb){
	if (htb == NULL){
		return failure;
	}
	int i;
	for (i=0 ; i<htb->hashSize ; i++){
		displayList(htb->table[i]);
	}
	return success;

}
