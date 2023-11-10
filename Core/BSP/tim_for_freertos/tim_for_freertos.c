#include "tim_for_freertos.h"
// #include "tim.h"

volatile unsigned long FreeRTOSRunTimeTicks = 0;

void BSP_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim == &htim3)
    {
        FreeRTOSRunTimeTicks++;
    }
}

void configureTimerForRunTimeStats(void) {
    FreeRTOSRunTimeTicks = 0;
}
unsigned long getRunTimeCounterValue(void) {
    return FreeRTOSRunTimeTicks;
}