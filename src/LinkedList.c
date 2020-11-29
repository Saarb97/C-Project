/*
 * LinkedList.c
 *
 *  Created on: Nov 28, 2020
 *      Author: ise
 */
#include "LinkedList.h"

struct Node_s{
	Element data;
	struct Node_s *next;
	struct Node_s *prev;
};

struct LinkedList_s {
	struct Node_s *head;
	struct Node_s *tail;
	AppedFunction appendFunction;
	DeleteFunction deleteFunction;
	DisplayFunction displayFunction;
	GetDataFunction getDataFunction;
	SearchFunction searchFunction;
};


LinkedList createLinkedList (AppedFunction appendKey, DeleteFunction deleteKey, DisplayFunction displayKey, GetDataFunction getDataKey,
																															SearchFunction searchKey)
{
	LinkedList linkedlist = (LinkedList) malloc (sizeof(LinkedList));
	if (linkedlist == NULL)
		return NULL;

	linkedlist->head = NULL;
	linkedlist->tail = NULL;
	linkedlist->appendFunction = appendKey;
	linkedlist->deleteFunction = deleteKey;
	linkedlist->displayFunction = displayKey;
	linkedlist->getDataFunction = getDataKey;
	linkedlist->searchFunction = searchKey;

	return linkedlist;
}
status destoryList(LinkedList inputList) {

	//TODO
	free(inputList);
	return success;
}
status appendNode(LinkedList inputList, Element key) {
	Node node = (Node) malloc (sizeof(Node));
	if(node == NULL)
		return failure;
	node->data = key;
	if(inputList->head == NULL) {
		inputList->head = node;
		inputList->tail = node;
	}
	else {
		inputList->tail->next = node;
		inputList->tail = node;
	}
	return success;
}
status deleteNode(LinkedList inputList, Element key) {
	Node current = inputList->head;
	if(current == NULL)
		return failure;
	if(current->data == key) {
		inputList->head = NULL;
		inputList->tail = NULL;
		free(current);
		return success;
	}
	current = current->next;
	while (current != NULL) {
		if(current->data == key && current != inputList->tail) { //somewhere in the middle of the list
			current->next->prev = current->prev;
			free(current);
			return success;
		}
		else if (current->data == key && current == inputList->tail) { //the tail of the list
			inputList->tail = current->prev;
			free(current);
			return success;
		}
		else
			current = current->next;
	}
	return failure;
}
status displayList(LinkedList inputList) {
	Node current = inputList->head;
	if(current == NULL)
		return failure;
	while (current != NULL) {
		inputList->displayFunction(current->data);
		current = current->next;
	}
	return success;
}
Element getDataByIndex(LinkedList inputList, int index) {
	int counter = 0;
	Node current = inputList->head;
	if(current == NULL)
		return NULL;
	while (current != NULL) {
		if (counter == index)
			return current->data;
		counter++;
		current = current->next;
	}
	return NULL;
}
int getLengthList(LinkedList inputList) {
	int counter = 0;
	Node current = inputList->head;
	while (current != NULL) {
		counter++;
		current = current->next;
	}
	return counter;
}
Element searchByKeyInList(LinkedList inputList, Element key) {
	Node current = inputList->head;
	while (current != NULL) {
		if (inputList->searchFunction(current->data,key) == success)
			return current;
	}
	return NULL;
}
