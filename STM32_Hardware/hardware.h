#include "config.h"
#include "stm32f10x.h"

//********************************************************************************
#ifndef	_HARDWARE_H_
#define	_HARDWARE_H_

#define IMU_STOP() EXTI->IMR &= ~(EXTI_Line5)
#define IMU_START() EXTI->IMR |= EXTI_Line5

#define TIMER_FOR_BUTTON_ENABLE TIM_Cmd(TIM4,ENABLE)
#define TIMER_FOR_BUTTON_DISABLE TIM_Cmd(TIM4,DISABLE)

#define LED_ON GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET)
#define LED_OFF GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET)

void Hardware_Init(void);
    void EXTI_Stop(void);
void EXTI_Restore(void);

void USART1_IRQHandler(void);
#endif	//_HARDWARE_H_

