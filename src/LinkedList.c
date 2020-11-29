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
	PrintFunction PrintFunction;
	EqualFunction EqualFunction;
};


LinkedList createLinkedList (PrintFunction PrintFunction,EqualFunction EqualFunction)
{
	LinkedList linkedlist = (LinkedList) malloc (sizeof(LinkedList));
	if (linkedlist == NULL) //in case memory allocation didnt work
		return NULL;

	linkedlist->head = NULL;
	linkedlist->tail = NULL;
	linkedlist->PrintFunction = PrintFunction;
	linkedlist->EqualFunction = EqualFunction;

	return linkedlist;
}
status destoryList(LinkedList inputList) {

	Node current = inputList->head;
	while (current != NULL) {
		if (deleteNode(inputList,current) == failure) //using deletenode function on the head of the list to minimize duplicated code
			return failure; //in case there was an issue with deleting the node and the process failed
		current = inputList->head; //for the next iteration pointing to the new head
	}

	free(inputList);
	return success;
}
status appendNode(LinkedList inputList, Element key) {
	Node node = (Node) malloc (sizeof(Node));
	if(node == NULL)
		return failure; //in case memory allocation didnt work
	node->data = key;
	if(inputList->head == NULL) { // if list the empty, new node is head and tail
		inputList->head = node;
		inputList->tail = node;
	}
	else { //node not empty, adjusting just the tail of the list
		inputList->tail->next = node;
		inputList->tail = node;
	}
	return success;
}
status deleteNode(LinkedList inputList, Element key) {
	Node current = inputList->head;
	if(current == NULL)
		return failure;
	if(current->data == key) { //checking if desired node is the head of the list
		inputList->head = NULL;
		if(inputList->tail == current) //if current is head and tail, it is the only node in the list
			inputList->tail = NULL;
		else { // if current node is not tail, its just the head and there is at least one other node
			inputList->head = current->next; // changing head node to the next node
			inputList->head->prev = NULL; //putting NULL into prev value for the new head
		}
		free(current);
		return success;
	}
	current = current->next;
	while (current != NULL) {
		if(current->data == key && current != inputList->tail) { //node is somewhere in the middle of the list (not first not last)
			current->next->prev = current->prev; //adjusting prev value for the next node
			current->prev->next = current->next; //adjusting next value for the previous node
			free(current);
			return success;
		}
		else if (current->data == key && current == inputList->tail) { //node is the tail of the list
			inputList->tail = current->prev; //changing tail node to previous node
			current->prev->next = NULL; //putting NULL into next value for the new tail
			free(current);
			return success;
		}
		else
			current = current->next;
	}
	return failure; //in case of desired element not found in any node in the list
}
status displayList(LinkedList inputList) {
	Node current = inputList->head;
	if(current == NULL)
		return failure;
	while (current != NULL) {
		inputList->PrintFunction(current->data);
		current = current->next;
	}
	return success;
}
Element getDataByIndex(LinkedList inputList, int index) {
	int counter = 1;
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
		if (inputList->EqualFunction(current->data,key) == true)
			return current;
		current = current->next;
	}
	return NULL;
}
