#include "common.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>



void leds_init(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitTypeDef GPIO_InitDef;
	GPIO_InitDef.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitDef.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitDef.GPIO_OType= GPIO_OType_PP;
	GPIO_InitDef.GPIO_PuPd= GPIO_PuPd_NOPULL;
	GPIO_InitDef.GPIO_Speed= GPIO_Speed_50MHz;
	
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	GPIO_DeInit(GPIOG);
	GPIO_Init(GPIOG, &GPIO_InitDef);
  
}

void leds_prog(){

    while (1) {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
            GPIO_SetBits(GPIOG, GPIO_Pin_13 | GPIO_Pin_14);
        } else {
            GPIO_ResetBits(GPIOG, GPIO_Pin_13 | GPIO_Pin_14);
        }
    }
    GPIO_ToggleBits(GPIOG, GPIO_Pin_13 | GPIO_Pin_14);

}
