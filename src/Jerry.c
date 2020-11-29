/*
 * jerry->c
 *
 *  Created on: Nov 17, 2020
 *      Author: harel
 */

#include "Jerry.h"


//===========================ORIGIN====================================================

origin* originCreate(planet *planet , char *dimension){
	origin *originP = (origin *) malloc(sizeof(origin));
	if (originP == NULL)
		exit(1);
	originP->dimension = (char *) malloc(sizeof (dimension));
	if (dimension == NULL)
		exit(1);
	strcpy(originP->dimension,dimension);
	originP->planet = planet;
	return originP;
}
status destroyOrigin(origin *origin){
	free(origin->dimension);
	free(origin);
	return success;
}


//============================PhysicalCharacteristic===================================================

pChar charsCreate(char *name,float value){
	pChar pCharP;
	//pCharP.name = (char *) malloc(sizeof (name));
	strcpy(pCharP.name,name);
	pCharP.value = value;
	return pCharP;


}

//===========================PLANET====================================================


planet* planetCreate(char *name , float x,float y , float z){
	planet *planetP = (planet *) malloc( sizeof(planet) );
	if (planetP == NULL)
		exit(1);
	planetP->name= (char *)malloc(sizeof(name));
	if (planetP->name == NULL)
		exit(1);
	strcpy(planetP->name,name);
	planetP->location[0] = x;
	planetP->location[1] = y;
	planetP->location[2] = z;
	return planetP;
}

status printPlanet(planet *planetP){
	printf("Planet : %s (%.2f,%.2f,%.2f) \n",planetP->name,planetP->location[0],planetP->location[1],planetP->location[2]);
	return success;
}

status destroyPlanet(planet *planetP){

		free(planetP->name);
		free(planetP);
		return success;
}


//===========================JERRY====================================================
jerry *jerryCreate(char *ID , int happiness , planet *planet,origin *origin){
	jerry *jerryP = (jerry *) malloc(sizeof( jerry ));
	if (jerryP == NULL)
		exit(1);
	jerryP->ID = (char *) malloc(sizeof(ID));
	if (jerryP->ID == NULL)
		exit(1);
	strcpy(jerryP->ID,ID);
	jerryP->happiness = happiness;
	jerryP->planetP = planet;
	jerryP->numOfChars = 0;
	jerryP->pChars = NULL;
	jerryP->originP = origin;

	return jerryP;
}

bool isCharExist(jerry *jerryArg,char *charName){
	int i;
	jerry *jerry = jerryArg;
	char *name = charName;
	if (jerry->pChars != NULL){
		for (i=0;i<jerry->numOfChars;i++){
			if ( strcmp( name,jerry->pChars[i].name ) ==0){
				return true;
			}
		}

	}

		return false;
}

status addChar(jerry *jerryArg,pChar Char){
	jerry *jerry = jerryArg;

	//int i;
	pChar *tmpP = NULL;
	tmpP = realloc(jerry->pChars,sizeof(pChar)*(jerry->numOfChars+1));
	if (tmpP == NULL)
		exit(1);
	jerry->pChars = tmpP;
	jerry->pChars[jerry->numOfChars] = Char;
	jerry->numOfChars++;
	return success;

}

status delChar (jerry *jerryArg, char *nameOfChar){
	jerry *jerry = jerryArg;
	char *name = nameOfChar;
	int i,j,k=0;
	pChar *tmpP = NULL;
	status isDeleted = failure;

	if (jerry->pChars == NULL){
		return false;
	}
	//locating pChar and deleting te pChar name
	for (i=0;i<jerry->numOfChars;i++){
		if ( strcmp(jerry->pChars[i].name, name) ==0){
			isDeleted = success;
			//free(jerry->pChars[i].name);
			if (jerry->numOfChars==1){
				jerry->numOfChars--;
				free(jerry->pChars);//freeing original pointer
				jerry->pChars = NULL;
				break;
			}
			tmpP = (pChar *) malloc((jerry->numOfChars-1) * sizeof(pChar));//allocating designated memory for names pointer array
			if (tmpP == NULL){
				exit(1);
			}
			//copy all existing names to temp array of pointers
			for (j=0;j<jerry->numOfChars;j++){
				//this condition prevents from the name that we want to delete to get in the temp array
				if (j==i){

					continue;
				}
				tmpP[k] = charsCreate(jerry->pChars[j].name,jerry->pChars[j].value);
				//strcpy(tmpP[k].name,jerry->pChars[j].name);
		        //free(jerry->pChars[j].name);
				k++;
			}




			jerry->numOfChars--;
			free(jerry->pChars);//freeing original pointer
			jerry->pChars = tmpP;
			break;
		}

	}
	return isDeleted;
}

status printJerry(jerry *jerryArg){
	jerry *jerry=jerryArg;
	int i;

	printf("Jerry , ID - %s : \n",jerry->ID);
	printf("Happiness level : %d \n",jerry->happiness);
	printf("Origin : %s \n",jerry->originP->dimension);
	printPlanet(jerry->planetP);
	if (jerry->numOfChars != 0){
		printf("Jerry's physical Characteristics available : \n");
		printf("\t");
		for (i=0; i<jerry->numOfChars;i++){
			printf("%s : %.2f ",jerry->pChars[i].name,jerry->pChars[i].value);
			if (i != jerry->numOfChars-1){
				printf(", ");
			}
		}
		printf("\n");

	}

	return success;
	}
status destroyJerry(jerry *jerry){
	int i;
	int tmpNumOfChars = jerry->numOfChars;

	free(jerry->ID);
	if (jerry->numOfChars != 0){
		for (i=0 ; i<tmpNumOfChars;i++){
			delChar(jerry,jerry->pChars[0].name);

		}
	}

	free(jerry->pChars);
	destroyOrigin(jerry->originP);
	free(jerry);
	return success;
};














