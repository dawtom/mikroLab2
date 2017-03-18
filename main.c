#include "common.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void init(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	
    debug_init_default();
    xprintf("\n*** reset ***\n" ANSI_FG_LTRED "STM32F4-DISCO" ANSI_NORMAL " Empty project\n" );
    printf("This is normal printf test!\r\n");
	
	RCC_ClocksTypeDef RCC_ClocksStatus;
	RCC_GetClocksFreq(&RCC_ClocksStatus);
	xprintf("Clock info: F_APB1 = %d Hz, F_APB2 = %d Hz\n",(int)RCC_ClocksStatus.PCLK1_Frequency,(int)RCC_ClocksStatus.PCLK2_Frequency);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}


int main(void)
{
	//init();
	leds_init();
	
	while(1)
	{
		char key = debug_inkey();
		
		if(key)
		{
			switch(key)
			{
				case 'a':
					xprintf("Wyslano znak \"a\"\n");
					break;
				default:
					xprintf("nie rozpoznane polecenie\n");
					break;
			}
		}
	}
	
    return 0;
}

