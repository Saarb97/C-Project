/*
 * Jerry.h
 *
 *  Created on: Nov 17, 2020
 *      Author: harel
 */





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "Defs.h"


//===============Planet===========================


#ifndef PLANET_H_
#define PLANET_H_

typedef struct Planet_s{
	float location[3];
	char *name;

}planet;

planet* planetCreate(char *name , float x,float y , float z);
status printPlanet(planet *planet);
status destroyPlanet(planet *planet);


#endif /* PLANET_H_ */


//===============Origin===========================
#ifndef ORIGIN_H_
#define ORIGIN_H_

typedef struct origin_s{
	planet *planet;
	char *dimension;
}origin;

origin* originCreate(planet *planet , char *dimension);
status destroyOrigin(origin *origin);

#endif /* ORIGIN_H_ */

//===============PHYSICALCHARACTERISTIC_H_===========================
#ifndef PHYSICALCHARACTERISTIC_H_
#define PHYSICALCHARACTERISTIC_H_




typedef struct char_struct{
	char name[400];
	float value;

}pChar;

pChar charsCreate(char *name,float value);


#endif /* PHYSICALCHARACTERISTIC_H_ */


//===============JERRY===========================
#ifndef JERRY_H_
#define JERRY_H_
typedef struct jerry_s{
	char *ID;
	int happiness;
	planet *planetP;
	pChar *pChars;
	int numOfChars;
	origin *originP;


}jerry;

jerry *jerryCreate(char *ID , int happiness , planet *planetP,origin *originP);
bool isCharExist(jerry *jerryArg,char *charName);
status addChar(jerry *jerryArg,pChar Char);
status delChar(jerry *jerryArg, char *nameOfChar);
status destroyJerry(jerry *jerry);
status printJerry(jerry *jerryArg);



#endif /* JERRY_H_ */
