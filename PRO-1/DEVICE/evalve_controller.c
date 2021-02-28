#include "evalve_controller.h"

void Evalve_Controller_Init(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 |
	                              GPIO_Pin_3 | GPIO_Pin_4 |
	                              GPIO_Pin_5 | GPIO_Pin_6;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 |
	                    GPIO_Pin_3 | GPIO_Pin_4 |
	                    GPIO_Pin_5 | GPIO_Pin_6);
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

