/*
 * ADC.c
 *
 *  Created on: Mar 16, 2021
 *      Author: ivan dario
 */

#include "ADC.h"
#include "main.h"
//#include "stm32l476xx.h"
//#include "stm32l4xx_hal.h"

 void init_ADC(void)
 {
	 // in this section introduce the code
	 // Define  PIN PB13 PB14 PB15:
	 GPIOB->MODER &= 0xABFFFFFFF ;

	 // Enable SPI2
	 RCC->APB1ENR1 |=  (1 << 14);
     //Set pin very high speed configuration
	 GPIOB->OSPEEDR |= 0xFC00000000;

	 //Choose AF5 for SPI alternate function register
	 GPIOB->AFR[1] |= (0x5 << 20); //for pin 13, 20 is LSB, 0x5 is the alternate value
	 GPIOB->AFR[1] |= (0x5 << 24); //for pin 14, 24 is LSB, 0x5 is the alternate value
	 GPIOB->AFR[1] |= (0x5 << 28); //for pin 15, 24 is LSB, 0x5 is the alternate value

	 //Define SPI2 clock
	 SPI2->CR1 |= (1<<5);

	 //Define operate mode:
	 //define mode SPI in 0
	 //(clock polarity)
	 SPI2->CR1 |= (0<<1); // CPOL 0 Polarity
	 SPI2->CR1 |= (0<<0); // CPHA 0 Phase

	 //set data size to 16 bits
	 SPI2->CR2 |= (0xF << 8);

	 //set master mode
	 SPI2->CR1 |= (1 << 2);

	 //software slave management
	 SPI2->CR1 |= (1<<9);
	 SPI2->CR1 |= (1<<8);

	 //Enable SPI2
	 SPI2->CR1 |= (1<<6);

	 //wait while initialize
	 HAL_Delay (100);

 }
 uint16_t ReadTemp(void)
 {

int16_t ReadT;
HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
// Send data
*(uint16_t*)&SPI2->DR = 0x0A0A;
//while until transmit is empty
while(!(SPI2->SR & (1 << 1)));
//wait busy
while(!(SPI2->SR & (1 << 7))); // 7 is the register

ReadT = *(uint16_t*)SPI2->DR;
HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin, GPIO_PIN_SET);

return ReadT;
 }
