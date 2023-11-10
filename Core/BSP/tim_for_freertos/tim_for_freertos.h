#ifndef _TIM_FOR_FREERTOS_H
#define _TIM_FOR_FREERTOS_H
#include "tim.h"
extern volatile unsigned long FreeRTOSRunTimeTicks;
void BSP_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

#endif