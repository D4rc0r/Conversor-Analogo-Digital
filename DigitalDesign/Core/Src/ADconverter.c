/*
 * ADconverter.c
 *
 *  Created on: 17/03/2021
 *      Author: ivan dario
 */

#include "ADconverter.h"
#include "main.h"

 void ADconverter(void)
 {
	 // in this section introduce the code
	uint16_t Temp;
	float scale, Dgtl;

	Temp = AnalogValue;  // save a random value of 16bit that is gave by function
	scale= (0.049)*Temp + 0.00095 ;
	Dgtl = scale*0.1 ;

	return Dgtl;

 }
 uint16_t AnalogValue(void)
 {
	 uint16_t Anlg1;
	 Anlg1 = srand (getpid()); // save a random value of 10bit that in this case correspond to the temperature

	 return Anlg1;

 }

