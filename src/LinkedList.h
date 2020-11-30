#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Defs.h"

typedef struct Node_s *Node;
typedef struct LinkedList_s *LinkedList;


LinkedList createLinkedList (PrintFunction PrintFunction,EqualFunction EqualFunction,FreeFunction FreeData ,CopyFunction CopyData );

status destroyList(LinkedList inputList);
status appendNode(LinkedList inputList, Element key);
status deleteNode(LinkedList inputList, Element key);
status displayList(LinkedList inputList);
Element getDataByIndex(LinkedList inputList, int index);
int getLengthList(LinkedList inputList);
Element searchByKeyInList(LinkedList inputList, Element key);





#endif /* LINKEDLIST_H_ */
