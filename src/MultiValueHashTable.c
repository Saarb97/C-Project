/*
 * MultiValueHashTable.c
 *
 *  Created on: Nov 28, 2020
 *      Author: ise
 */
#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "MultiValueHashTable.h"

struct MultiValueHashTable_s{

	PrintFunction printValue;
	EqualFunction equalValue;
	FreeFunction freeValue;
	CopyFunction copyValue;
	PrintFunction printKey;
	CopyFunction copyKey;


	hashTable hashTable;
	int size;
};
/*
 * multiValueHashTable is a hash table that each cell is a pointer to Linked List that
 * in that list each node value is a linked list
*/
multiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
		CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
		EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){

		multiValueHashTable mv_htb = (multiValueHashTable) malloc (sizeof(multiValueHashTable));
		int i;

		if (copyKey== NULL || freeKey== NULL ||printKey== NULL ||copyValue== NULL ||freeValue== NULL ||printValue== NULL ||
				equalKey== NULL ||transformIntoNumber== NULL){
			return NULL;
		}

		mv_htb->hashTable =  createHashTable( copyKey,  freeKey,  printKey,
									 copyValue,  freeValue,  printValue,
									 equalKey,  transformIntoNumber,  hashNumber);//************alloc*************

		mv_htb->size = hashNumber;
		mv_htb->printValue = printValue;
		mv_htb->printKey = printKey;
		mv_htb->equalValue = equalKey;// not sure-weired
		mv_htb->freeValue = freeValue;
		mv_htb->copyValue = copyValue;
		mv_htb->copyKey = copyKey;
		return mv_htb;

}

status destroyMultiValueHashTable(multiValueHashTable mv_htb){
	if(mv_htb ==NULL){
		return failure;
	}
	destroyHashTable(mv_htb->hashTable);
	free(mv_htb);
	return success;
}



status addToMultiValueHashTable(multiValueHashTable mv_htb , Element key , Element value){
	KeyValuePairPointer KVP_sub = createKeyValuePair(mv_htb->copyKey(key),mv_htb->copyValue(value),mv_htb->printValue,mv_htb->printKey);

	if (mv_htb == NULL || key == NULL || value == NULL){
		return failure;
	}

    LinkedList destNodeValue = lookupInHashTable(mv_htb->hashTable, key);
    if (destNodeValue == NULL){//the key is not in the system
    	if( addToHashTable(mv_htb->hashTable,getKey(KVP_sub),createLinkedList (mv_htb->printValue,mv_htb->equalValue,mv_htb->freeValue ,mv_htb->copyValue) )== failure){
    		return failure;
    	}
    }

	return appendNode(lookupInHashTable(mv_htb->hashTable, key), KVP_sub);//failure if node appending did not work


}
LinkedList lookupInMultiValueHashTable(multiValueHashTable mv_htb,Element key){
	if (mv_htb == NULL || key == NULL ){
			return NULL;
	}
	return lookupInHashTable(mv_htb->hashTable, key);


}

status removeFromMultiValueHashTable(multiValueHashTable mv_htb , Element key , Element value){
	if (mv_htb == NULL || key == NULL || value == NULL){
			return failure;
		}
	LinkedList destNodeValue = lookupInHashTable(mv_htb->hashTable, key);
	 if (destNodeValue == NULL){
		 return failure;
	 }
	 return deleteNode(destNodeValue,key);

}

status displayMultiValueHashElementsByKey(multiValueHashTable mv_htb,Element key){
	if (mv_htb == NULL || key == NULL ){
		return failure;
	}
	return displayList(lookupInMultiValueHashTable(mv_htb,key));
}





















