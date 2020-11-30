/*
 * KeyValuePair.c
 *
 *  Created on: Nov 28, 2020
 *      Author: ise
 */
#include "KeyValuePair.h"

struct KeyValuePair_s{
	Element key;
	Element value;
	PrintFunction printvalue;
	PrintFunction printKey;
};

KeyValuePairPointer createKeyValuePair(Element key,Element value,PrintFunction printvalue,PrintFunction printkey ){
	KeyValuePairPointer KVP = NULL;
	if (value == NULL || printvalue == NULL || printkey == NULL ){
		return NULL;
	}
	KVP->printvalue = printvalue;
	KVP->printKey =printkey;
	KVP->value = value;
	KVP->key = key;
	return KVP;
}

status destroyKeyValuePair(KeyValuePairPointer KVP){
	free(KVP->value);
	free(KVP);
	if(KVP->value == NULL && KVP == NULL){
		return success;
	}
	return failure;
}
status displayValue(KeyValuePairPointer KVP){
	if (KVP == NULL){
		return failure;
	}
	KVP->printvalue(KVP->value);
	return success;
}
status displayKey(KeyValuePairPointer KVP){
	if (KVP == NULL){
		return failure;
	}
	KVP->printvalue(KVP->key);
	return success;
}
Element getValue(KeyValuePairPointer KVP){
	return KVP->value;
}
Element getKey(KeyValuePairPointer KVP){
	return KVP->key;
}
bool isEqualKey(KeyValuePairPointer KVP,Element key){//NOT SURE ABOUT KEY TYPE
	if (KVP->key == key){
		return true;
	}
	return false;
}







