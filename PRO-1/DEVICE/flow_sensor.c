#include "flow_sensor.h"
#include <string.h>

#define SensorChannel0_IRQHandler EXTI9_5_IRQHandler
#define SensorChannel1_IRQHandler EXTI15_10_IRQHandler

SensorDevCtx_t sensor_dev_ctx[MAX_SENOR_NR];

SensorDevCtx_t * Get_SensorDevCtx(void)
{
	return sensor_dev_ctx;
}

void Calculate_target(int n, float x)
{
	sensor_dev_ctx[n].target = (x * sensor_dev_ctx[n].pulsePerML * 10 + 5)/10;
}

void Enable_Sensor(int n)
{
	sensor_dev_ctx[n].status = SENSOR_ON;
	sensor_dev_ctx[n].counter = 0;
}

void Disable_Sensor(int n)
{
	sensor_dev_ctx[n].status = SENSOR_OFF;
	sensor_dev_ctx[n].counter = 0;
}

uint8_t Get_Sensor_Status(int n)
{
	return sensor_dev_ctx[n].status;
}

static void Set_Sensor_Status(int n, int s)
{
	sensor_dev_ctx[n].status = s;
}

uint32_t Get_Sensor_Counter(int n)
{
	return sensor_dev_ctx[n].counter;
}

void SensorChannel1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line12) != RESET)
  {
		//Sample collection for sensor channel 3
    if (IS_SENSOR_STATUS_ON(sensor_dev_ctx[3].status))
		{			
		  sensor_dev_ctx[3].counter++;
			if (sensor_dev_ctx[3].counter >= sensor_dev_ctx[3].target)
			{
				Set_Sensor_Status(3, SENSOR_COLLECT_DONE);
			}
		}
		else
		{
			Set_Sensor_Status(3, SENSOR_LEAKAGE);
		}
    EXTI_ClearITPendingBit(EXTI_Line12);
  }
	else if(EXTI_GetITStatus(EXTI_Line13) != RESET)
  {
		//Sample collection for sensor channel 4 
		if (IS_SENSOR_STATUS_ON(sensor_dev_ctx[4].status))
		{			
		  sensor_dev_ctx[4].counter++;
			if (sensor_dev_ctx[4].counter >= sensor_dev_ctx[4].target)
			{
				Set_Sensor_Status(4, SENSOR_COLLECT_DONE);
			}
		}
		else
		{
			Set_Sensor_Status(4, SENSOR_LEAKAGE);
		}
    EXTI_ClearITPendingBit(EXTI_Line13);
  }
  else if(EXTI_GetITStatus(EXTI_Line14) != RESET)
  {
		//Sample collection for sensor channel 5 
		if (IS_SENSOR_STATUS_ON(sensor_dev_ctx[5].status))
		{			
		  sensor_dev_ctx[5].counter++;
			if (sensor_dev_ctx[5].counter >= sensor_dev_ctx[5].target)
			{
				Set_Sensor_Status(5, SENSOR_COLLECT_DONE);
			}
		}
		else
		{
			Set_Sensor_Status(5, SENSOR_LEAKAGE);
		}
    EXTI_ClearITPendingBit(EXTI_Line14);
  }	
}

void SensorChannel0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line5) != RESET)
  {
		//Sample collection for sensor channel 0
    if (IS_SENSOR_STATUS_ON(sensor_dev_ctx[0].status))
		{			
		  sensor_dev_ctx[0].counter++;
			if (sensor_dev_ctx[0].counter >= sensor_dev_ctx[0].target)
			{
				Set_Sensor_Status(0, SENSOR_COLLECT_DONE);
			}
		}
		else
		{
			Set_Sensor_Status(0, SENSOR_LEAKAGE);
		}
    EXTI_ClearITPendingBit(EXTI_Line5);
  }
	else if(EXTI_GetITStatus(EXTI_Line6) != RESET)
  {
		//Sample collection for sensor channel 1
    if (IS_SENSOR_STATUS_ON(sensor_dev_ctx[1].status))
		{			
		  sensor_dev_ctx[1].counter++;
			if (sensor_dev_ctx[1].counter >= sensor_dev_ctx[1].target)
			{
				Set_Sensor_Status(1, SENSOR_COLLECT_DONE);
			}
		}
		else
		{
			Set_Sensor_Status(1, SENSOR_LEAKAGE);
		}
    EXTI_ClearITPendingBit(EXTI_Line6);
  }
  else if(EXTI_GetITStatus(EXTI_Line7) != RESET)
  {
		//Sample collection for sensor channel 2 
		if (IS_SENSOR_STATUS_ON(sensor_dev_ctx[2].status))
		{			
		  sensor_dev_ctx[2].counter++;
			if (sensor_dev_ctx[2].counter >= sensor_dev_ctx[2].target)
			{
				Set_Sensor_Status(2, SENSOR_COLLECT_DONE);
			}
		}
		else
		{
			Set_Sensor_Status(2, SENSOR_LEAKAGE);
		}
    EXTI_ClearITPendingBit(EXTI_Line7);
  }	
}

static void GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 |
	                              GPIO_Pin_7 | GPIO_Pin_12 |
	                              GPIO_Pin_13 | GPIO_Pin_14;
  	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

static void EXTI_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	
	NVIC_Configuration();

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
  EXTI_InitStructure.EXTI_Line = EXTI_Line5 | EXTI_Line6 | EXTI_Line7 |
	                               EXTI_Line12 | EXTI_Line13 | EXTI_Line14;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

void Flow_Sensor_Init(void)
{
	GPIO_Config();
	EXTI_Config();
	memset((void *)&sensor_dev_ctx, 0, sizeof(SensorDevCtx_t));
}
