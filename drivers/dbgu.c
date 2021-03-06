#include "stm32f4xx.h"
#include "dbgu.h"


void debug_init_default(void)
{
	// Enable peripheral clocks
	//
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	// Initialize Serial Port
	//
	GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
		.GPIO_Pin   = GPIO_Pin_9,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode  = GPIO_Mode_AF,
		.GPIO_OType = GPIO_OType_PP
	});
	
	GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
		.GPIO_Pin = GPIO_Pin_10,
		.GPIO_Mode = GPIO_Mode_AF,
		.GPIO_PuPd = GPIO_PuPd_UP
	});
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	USART_OverSampling8Cmd(USART1,DISABLE);
	
	USART_Init(USART1, &(USART_InitTypeDef) {
		.USART_BaudRate = 115200,
		.USART_WordLength = USART_WordLength_8b,
		.USART_StopBits = USART_StopBits_1,
		.USART_Parity = USART_Parity_No ,
		.USART_HardwareFlowControl = USART_HardwareFlowControl_None,
		.USART_Mode = USART_Mode_Rx | USART_Mode_Tx
	});
	
	
	USART_Cmd(USART1, ENABLE);
}

int debug_test(void)
{
	return ( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET ) ? 0 : 1;
}


//send chr via UART (platform dependent)
void debug_chr(char chr)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) { ; }
	USART_SendData(USART1, (uint16_t)chr);
}

int putChar(int ch)
{
	debug_chr(ch);
	return ch;
}



//returns ascii value of last char received
//returns 0 if no char was received since last debug_inkey call
//(platform dependent)
char debug_inkey(void)
{
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
		return(0);
	else
		return (unsigned char)USART_ReceiveData(USART1);
}

//halts program/task execution until a char is received
//(platform dependent)
char debug_waitkey(void)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) { ; }
	return (unsigned char)USART_ReceiveData(USART1);
}

