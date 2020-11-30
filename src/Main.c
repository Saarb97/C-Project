/*
 ============================================================================
 Name        : JerryBoree.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Defs.h"
#include "Jerry.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "MultiValueHashTable.h"

/* FUNCTIONS TO USE ON CURRENT HOMEWORK  */

status PrintJerry(Element elem) {
	if (elem == NULL)
		return failure;
	return printJerry((jerry *)elem);
}
bool JerryEqual(Element elemjerry, Element elem) {
	/*if(jerryArg == NULL || elem == NULL )
		return false;
	if (elem == jerryArg->originP ||elem == jerryArg->planetP ||elem == jerryArg->happiness || isCharExist(jerryArg,elem)|| strcmp(elem,jerryArg->ID) == 0 )
		return true;*/

	return true;

}

status FreeJerry(Element elem) {
	if (elem == NULL)
		return failure;
	return(destroyJerry((jerry *)elem));

}
Element CopyJerry(Element elemjerry) {
	if(elemjerry == NULL)
		return NULL;
	jerry *jerryCopy = (jerry *) malloc(sizeof( jerry ));
	jerryCopy = (jerry *)elemjerry;
	if (jerryCopy != NULL)
		return jerryCopy;
	return NULL;

}




status PrintAllJerries(int numOfJerrys, jerry **jerrys) {
		for (int i = 0; i < numOfJerrys; i++) {
			printJerry(jerrys[i]);

		}
		return success;
	}
	status PrintAllPlanets(int numOfPlanets, planet **planets) {
		for (int i = 0; i < numOfPlanets; i++) {
			printPlanet(planets[i]);

		}
		return success;
	}


	status printJerryByPlanet(char *planetName,int numOfJerrys,jerry **jerrys){
		int i;
		int found = 0;
		for(i=0;i<numOfJerrys;i++){
			if (strcmp(jerrys[i]->planetP->name,planetName)==0){
				printJerry(jerrys[i]);
				found =1;
			}
		}

		if (found != 1){
			printf("RICK I NEVER HEARD ABOUT %s ! \n",planetName);
			return failure;
		}
		return success;
	}

	status printJerrybyPchar(jerry **jerrys,char *answer,int numOfJerrys){
		int i,j=0;
		int found = 0;
		for(i=0;i<numOfJerrys;i++){
			for(j=0;j<jerrys[i]->numOfChars;j++){
				if (strcmp(jerrys[i]->pChars[j].name,answer)==0){
						printJerry(jerrys[i]);
						found =1;
				}

			}
		}

		if (found != 1){
			printf("OH NO! I DON'T KNOW ANY JERRY'S %s ! \n",answer);
			return failure;
		}
		return success;
	}
	jerry *searchJerry(int numOfJerries, jerry **jerrys, char *id) {
		int i;
		for (i = 0; i < numOfJerries; i++) {
			if (strcmp(id,jerrys[i]->ID) == 0) {
				return jerrys[i];
			}
		}
		return NULL;
	}


int main(int argc,char *argv[]) {
	int i,j;
	int numOfPlanets = atoi(argv[1]);
	int numOfJerrys = atoi(argv[2]);
	char *tmpPlanetName;
	char *tmpID=NULL,*tmpDimantionName, *tmpHappiness;
	char *tmpX,*tmpY,*tmpZ;
	planet *tmpPlanet=NULL;
	origin *tmpOrigin=NULL;
	//pChar tmpPchar;
	char *tmpPcharName=NULL;
	float tmpPcharValue;
	const char commaArr[2] = ",";
	char *token;
	int tmpHappinessInt;
	char *tmpPcharValueString;
	char *endfilecheck;



	//creating planets jerrys array
	planet **planets =(planet **) malloc(sizeof(planet) * numOfPlanets );
	if (planets == NULL)
		exit(1);
	jerry **jerrys =(jerry **) malloc(sizeof(jerry) * numOfJerrys );
	if (jerrys == NULL)
		exit(1);

	FILE *file;
	file = fopen(argv[3],"r");
	char inputRow[400];
	fgets(inputRow,400,file);//"planets"

	for (i=0 ; i<numOfPlanets;i++){//for each planet
		fgets(inputRow,400,file);
		token = strtok(inputRow,commaArr);
		tmpPlanetName = token;
		token = strtok(NULL,commaArr);
		tmpX = token;
		token = strtok(NULL,commaArr);
		tmpY = token;
		token = strtok(NULL,commaArr);
		tmpZ = token;
		float x = atof(tmpX);
		float y = atof(tmpY);
		float z = atof(tmpZ);

		planets[i] = planetCreate(tmpPlanetName,x,y,z);
	}
	fgets(inputRow,400,file);//"Jerries"
	fgets(inputRow,400,file); // First Jerry
	for (j=0 ; j<numOfJerrys;j++){//for each Jerry
			token = strtok(inputRow,commaArr);
			tmpID= token;
			token = strtok(NULL,commaArr);
			tmpDimantionName = token;
			token = strtok(NULL,commaArr);
			tmpPlanetName = token;
			token = strtok(NULL,commaArr);
			tmpHappiness = token;
			tmpHappinessInt = atoi(tmpHappiness);
			//searching for planet and assigning him for tmpPlanet:
			for (i=0;i<numOfPlanets;i++){
				if (strcmp(planets[i]->name,tmpPlanetName) == 0){
					tmpPlanet= planets[i];
					break;
				}
			}
			tmpOrigin=originCreate(tmpPlanet,tmpDimantionName);

			jerrys[j] = jerryCreate(tmpID , tmpHappinessInt , tmpPlanet,tmpOrigin);
			//assigning pChars
			fgets(inputRow,400,file);//first pChar or next jerry if there is no pChar
			while ('\t'==(char)inputRow[0]){
				tmpPcharName = strtok(inputRow,"\t:\n");
				tmpPcharValueString = strtok(NULL,"\t:\n");
				tmpPcharValue = atof(tmpPcharValueString);
				addChar(jerrys[j],charsCreate(tmpPcharName,tmpPcharValue));
				endfilecheck = fgets(inputRow,400,file);
				if (endfilecheck == NULL)
					break;
			}



	}
	fclose(file);

	/*************************LINKEDLIST TESTING TIME*******************************************/
	LinkedList lst = createLinkedList(PrintJerry,JerryEqual,FreeJerry,CopyJerry);
	Element elem2 = ((Element)jerrys[0]); // doesn't work for
	appendNode(lst,elem2);
	printf("number of nodes, should be 1: %d\n",getLengthList(lst));
	deleteNode(lst,elem2);
	printf("number of nodes, should be 0: %d\n",getLengthList(lst));
	appendNode(lst,elem2);
	elem2 = ((Element)jerrys[1]);
	appendNode(lst,elem2);
	printf("number of nodes, should be 2: %d\n",getLengthList(lst));
	printf("using displayList below:\n");
	displayList(lst);
	printf("using getDataByIndex to print second jerry(1q456):\n");
	getDataByIndex(lst,1);
	/*elem2 = ((Element)jerrys[1]->ID);
	printf("Performing search by ID of the second Jerry (1q456):\n");
	*/
	printf("Destroying all jerries and planets\n");
	for (i=0;i<numOfJerrys;i++){
		destroyJerry(jerrys[i]);
	}
	free(jerrys);


	for (i=0;i<numOfPlanets;i++){
		destroyPlanet(planets[i]);
	}
	free(planets);
	printf("Destroying list\n");
	destroyList(lst);
	printf("List Destroyed, all memory should be clean.\n");





}
