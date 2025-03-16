#include "hardware.h"

#ifdef IMU_IS_MPU6050 
	#include "MPU6050_Reg.h"
	#include "MPU6050.h"
#endif //IMU_IS_MPU6050

void IMU_WriteReg(uint8_t RegAddress, uint8_t Data);

// 硬件初始化函数
void Hardware_Init()
{
    //RCC periphral init****************************************************//   
    // 使能 GPIOB 端口的时钟，以便后续可以对 GPIOB 进行配置和使用
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    // 使能 GPIOA 端口的时钟，以便后续可以对 GPIOA 进行配置和使用
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    // 使能 GPIOC 端口的时钟，以便后续可以对 GPIOC 进行配置和使用
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    // 使能复用功能 I/O 时钟，用于使用一些外设的复用功能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    // 使能 USART1 串口的时钟，以便后续可以对 USART1 进行配置和使用
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    // 使能 TIM4 定时器的时钟，以便后续可以对 TIM4 进行配置和使用
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    
    // 定义 GPIO 初始化结构体变量，用于配置 GPIO 端口的参数
    GPIO_InitTypeDef GPIO_InitStruct;
    // 定义定时器基本初始化结构体变量，用于配置定时器的基本参数
    TIM_TimeBaseInitTypeDef TIM_TimerBaseInitStruct;
    // 定义外部中断初始化结构体变量，用于配置外部中断的参数
    EXTI_InitTypeDef EXTI_InitStruct;
    // 定义嵌套向量中断控制器初始化结构体变量，用于配置中断的优先级等参数
    NVIC_InitTypeDef NVIC_InitStruct;

    //Button Init****************************************************//    
    // 选择要初始化的 GPIO 引脚，这里选择 GPIOA 的引脚 0
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    // 设置 GPIO 模式为上拉输入模式，用于检测按键输入
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    // 设置 GPIO 的输出速度为 50MHz
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    // 使用上述配置初始化 GPIOA 端口
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    // 选择要配置的外部中断线，这里选择外部中断线 0
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;
    // 使能外部中断线 0
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    // 设置外部中断模式为中断模式
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    // 设置外部中断触发方式为上升沿和下降沿触发
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    // 使用上述配置初始化外部中断
    EXTI_Init(&EXTI_InitStruct);
    
    // 选择要配置的中断通道，这里选择外部中断 0 中断通道
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    // 使能外部中断 0 中断通道
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    // 设置外部中断 0 中断通道的抢占优先级为 3
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
    // 设置外部中断 0 中断通道的子优先级为 3
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
    // 使用上述配置初始化嵌套向量中断控制器
    NVIC_Init(&NVIC_InitStruct);

    //TIM4 Init******************************************************//          
    // 设置定时器 4 的预分频器值为 3600 - 1，用于对定时器时钟进行分频
    TIM_TimerBaseInitStruct.TIM_Prescaler = 3600 - 1;
    // 设置定时器 4 的计数模式为向上计数模式
    TIM_TimerBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    // 设置定时器 4 的自动重装载值为 20 - 1，实现每 1ms 产生一次中断
    TIM_TimerBaseInitStruct.TIM_Period = 20 - 1;                   
    // 设置定时器 4 的时钟分频因子为 1
    TIM_TimerBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    // 使用上述配置初始化定时器 4 的基本参数
    TIM_TimeBaseInit(TIM4,&TIM_TimerBaseInitStruct);
    
    // 清除定时器 4 的更新标志位
    TIM_ClearFlag(TIM4,TIM_FLAG_Update);
    // 使能定时器 4 的更新中断
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
    
    // 配置嵌套向量中断控制器的优先级分组为组 2
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    // 选择要配置的中断通道，这里选择定时器 4 中断通道
    NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
    // 使能定时器 4 中断通道
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    // 设置定时器 4 中断通道的抢占优先级为 4
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 4;
    // 设置定时器 4 中断通道的子优先级为 4
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 4;
    // 使用上述配置初始化嵌套向量中断控制器
    NVIC_Init(&NVIC_InitStruct);   

    //USART init*****************************************//
    // 设置 GPIO 模式为复用推挽输出模式，用于 USART1 的发送引脚
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    // 选择要初始化的 GPIO 引脚，这里选择 GPIOA 的引脚 9
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    // 设置 GPIO 的输出速度为 50MHz
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    // 使用上述配置初始化 GPIOA 端口
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    // 设置 GPIO 模式为上拉输入模式，用于 USART1 的接收引脚
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    // 选择要初始化的 GPIO 引脚，这里选择 GPIOA 的引脚 10
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    // 设置 GPIO 的输出速度为 50MHz
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    // 使用上述配置初始化 GPIOA 端口
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    // 定义 USART 初始化结构体变量，用于配置 USART 的参数
    USART_InitTypeDef USART_InitStructure;
    // 设置 USART1 的波特率，BAUD_RATE 应该是一个已定义的常量
    USART_InitStructure.USART_BaudRate = BAUD_RATE;
    // 设置 USART1 的硬件流控制模式为无
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    // 设置 USART1 的工作模式为发送和接收模式
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    // 设置 USART1 的奇偶校验位为无
    USART_InitStructure.USART_Parity = USART_Parity_No;
    // 设置 USART1 的停止位为 1 位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    // 设置 USART1 的数据位长度为 8 位
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    // 使用上述配置初始化 USART1
    USART_Init(USART1,&USART_InitStructure);
    
    // 使能 USART1 的接收缓冲区非空中断
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

    // 配置嵌套向量中断控制器的优先级分组为组 2
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // 选择要配置的中断通道，这里选择 USART1 中断通道
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    // 使能 USART1 中断通道
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    // 设置 USART1 中断通道的抢占优先级为 1
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    // 设置 USART1 中断通道的子优先级为 1
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    // 使用上述配置初始化嵌套向量中断控制器
    NVIC_Init(&NVIC_InitStruct);
    
    // 使能 USART1
    USART_Cmd(USART1,ENABLE);
    // 注释掉的代码，用于打印 "Hello!" 到串口，可能需要重定向 printf 函数
    //printf("Hello!\n");

    //LED init*****************************************//      
    // 设置 GPIO 模式为推挽输出模式，用于控制 LED
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    // 选择要初始化的 GPIO 引脚，这里选择 GPIOC 的引脚 13
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 ;
    // 设置 GPIO 的输出速度为 50MHz
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
    // 使用上述配置初始化 GPIOC 端口
    GPIO_Init(GPIOC,&GPIO_InitStruct);

    //IMU init*****************************************//    
    // 如果定义了 IMU_IS_MPU6050 宏，则进行 MPU6050 传感器的初始化
    #ifdef IMU_IS_MPU6050
        // 设置 GPIO 模式为上拉输入模式，用于 MPU6050 的中断引脚
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
        // 选择要初始化的 GPIO 引脚，这里选择 GPIOB 的引脚 5
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
        // 设置 GPIO 的输出速度为 50MHz
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        // 使用上述配置初始化 GPIOB 端口
        GPIO_Init(GPIOB,&GPIO_InitStruct);
    
        // 配置外部中断线 5 与 GPIOB 的引脚 5 关联
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5); 
    
        // 选择要配置的外部中断线，这里选择外部中断线 5
        EXTI_InitStruct.EXTI_Line = EXTI_Line5 ;
        // 使能外部中断线 5
        EXTI_InitStruct.EXTI_LineCmd = ENABLE;
        // 设置外部中断模式为中断模式
        EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
        // 设置外部中断触发方式为下降沿触发
        EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
        // 使用上述配置初始化外部中断
        EXTI_Init(&EXTI_InitStruct);
    
        // 选择要配置的中断通道，这里选择外部中断 9_5 中断通道
        NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
        // 使能外部中断 9_5 中断通道
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        // 设置外部中断 9_5 中断通道的抢占优先级为 6
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;
        // 设置外部中断 9_5 中断通道的子优先级为 6
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = 6;
        // 使用上述配置初始化嵌套向量中断控制器
        NVIC_Init(&NVIC_InitStruct);
    
        // 停止 IMU 传感器
        IMU_STOP();
        // 初始化 MPU6050 传感器
        MPU6050_Init();
		LED_OFF;
    #endif //IMU_IS_MPU6050	
}

int fputc( int ch, FILE *f )
{
        while((USART1->SR & (1 << 7) ) == 0);
        USART1->DR = ch;
	return ch;
}

void EXTI_Stop(void)
{
	EXTI->IMR &= ~(EXTI_Line0);
	EXTI->IMR &= ~(EXTI_Line4);
	EXTI->IMR &= ~(EXTI_Line8);
}

void EXTI_Restore(void)
{
	EXTI->IMR |= EXTI_Line0;
	EXTI->IMR |= EXTI_Line4;
	EXTI->IMR |= EXTI_Line8;
}

