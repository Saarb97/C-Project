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
		//todo:calloc is O(n) and this function should be O(1).find out WTF.
		return mv_htb;

}

status destroyMultiValueHashTable(multiValueHashTable mv_htb){
	int i,j,k;
	KeyValuePairPointer kvp;
	LinkedList LLtail;
	if (mv_htb == NULL){
		return failure;
	}
	/*
	 * for every linked list of hash table cell,got to the tail and delete all nodes in his value.
	 * after that delete the tail himself and do that for every node in the cell linked list
	 * and for every cell
	*/
	for (i=0;i<mv_htb->size;i++){
		for (j=0;j<getLengthList(mv_htb->hashTable->table[i]);j++){
			LLtail = mv_htb->hashTable->table[i]->tail;
			destroyList(LLtail);
		}
		destroyList(mv_htb->hashTable->table[i]);
	}
	free(mv_htb->hashTable);
}
status addToMultiValueHashTable(multiValueHashTable mv_htb , Element key , Element value){
	KeyValuePairPointer KVP_Key;
	if (mv_htb == NULL || key == NULL || value == NULL){
		return failure;
	}
	int intKey = transformIntoNumber(key);
	int place = intKey % mv_htb->size;
	if (mv_htb->hashTable->table[place] == 0){
		//todo : change when linked list is complete;
		mv_htb->hashTable[place] = createLinkedList(mv_htb->hashTable->printKey,mv_htb->hashTable->printValue);
	}

	LinkedList keyNode = searchByKeyInList(mv_htb->hashTable[place],key);//returns the Element,the the Element is another Linked List
	KeyValuePairPointer KVP = createKeyValuePair(key,value,mv_htb->hashTable->printValue,mv_htb->hashTable->printKey );

	if (keyNode == NULL){
		KVP_Key = createKeyValuePair(key,createLinkedList ( displayKey, searchKey),mv_htb->printValue,mv_htb->printKey );
		appendNode(mv_htb->hashTable->table[place],KVP_Key);
		appendNode(KVP_Key->value,KVP);

	}
	else{
		//todo : change when linked list is complete;
		appendNode(keyNode,KVP);
	}

	return success;


}
Element lookupInMultiValueHashTable(multiValueHashTable mv_htb,Element key){
	if (mv_htb == NULL || key == NULL ){
			return failure;
		}
		int intKey = transformIntoNumber(key);
		int place = intKey % mv_htb->hashSize;
		return

}
/*
status removeFromMultiValueHashTable(multiValueHashTable mv_htb , Element key , Element value){


}

*/


