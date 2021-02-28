#ifndef __FLOW_SENSOR_H
#define	__FLOW_SENSOR_H

#include "stm32f10x.h"

#define MAX_SENOR_NR 6
#define SENSOR_OFF 0
#define SENSOR_ON (1)
#define SENSOR_COLLECT_DONE (2)
//Abnormal status
#define SENSOR_LEAKAGE (20)

#define IS_SENSOR_STATUS_ON(STATUS) (STATUS == SENSOR_ON)
#define IS_SENSOR_STATUS_OFF(STATUS) (STATUS == SENSOR_OFF)
#define IS_SENSOR_STATUS_COLLECT_DONE(STATUS) (STATUS == SENSOR_COLLECT_DONE)

typedef struct
{
	uint8_t status;
	uint32_t counter;
	uint32_t target;
	float pulsePerML;
}SensorDevCtx_t;

//typedef enum
//{
//	SENSOR_OFF = 0,
//	SENSOR_ON = 1,
//	SENSOR_COLLECT_DONE = 
//}Sensor_StatusEnum;

//extern SensorDevCtx_t sensor_dev_ctx[MAX_SENOR_NR];

void Flow_Sensor_Init(void);
SensorDevCtx_t * Get_SensorDevCtx(void);
void Enable_Sensor(int n);
void Disable_Sensor(int n);
uint8_t Get_Sensor_Status(int n);
uint32_t Get_Sensor_Counter(int n);

#endif /* __FLOW_SENSOR_H */
