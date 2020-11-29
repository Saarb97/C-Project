/*
 * KeyValuePair.h
 *
 *  Created on: Nov 28, 2020
 *      Author: ise
 */
#include "Defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_

typedef struct KeyValuePair_s *KeyValuePairPointer ;

KeyValuePairPointer createKeyValuePair(Element key,Element data,PrintFunction printdata,PrintFunction printkey);
status destroyKeyValuePair(KeyValuePairPointer KVP);
status displayValue(KeyValuePairPointer KVP);
status displayKey(KeyValuePairPointer KVP);
Element getValue(KeyValuePairPointer KVP);
bool isEqualKey(KeyValuePairPointer KVP,Element key);


#endif /* KEYVALUEPAIR_H_ */
