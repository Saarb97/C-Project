/*
 * MultiValueHashTable.h
 *
 *  Created on: Nov 28, 2020
 *      Author: ise
 */
#include "Defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef MULTIVALUEHASHTABLE_H_
#define MULTIVALUEHASHTABLE_H_

typedef struct MultiValueHashTable_s *multiValueHashTable;


multiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
		CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
		EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber);

status destroyMultiValueHashTable(multiValueHashTable mv_htb);
status addToMultiValueHashTable(multiValueHashTable mv_htb , Element key , Element Value);
Element lookupInMultiValueHashTable(multiValueHashTable mv_htb,Element key);


#endif /* MULTIVALUEHASHTABLE_H_ */
