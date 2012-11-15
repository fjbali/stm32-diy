#define BSP_GLOBALS
#include "includes.h"

static volatile ErrorStatus HSEStartUpStatus = SUCCESS;
static void SysTick_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void RCC_Configuration(void);
void WWDG_Configuration(void);
void USART1_Configuration(void);
void USART4_Configuration(void);
void TIM1_Configuration(void);

/*
********************************************************************************
** �������� �� BSP_Init(void)
** �������� �� ϵͳ��ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void BSP_Init(void)
{
    RCC_Configuration();
    GPIO_Configuration();
    NVIC_Configuration();
    SysTick_Configuration();
//	USART1_Configuration();
//	USART4_Configuration();
	TIM1_Configuration();
}
/*
********************************************************************************
** �������� �� SysTick_Configuration(void)
** �������� �� ʱ�ӳ�ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
static void SysTick_Configuration(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    u32  cnts;

    RCC_GetClocksFreq(&rcc_clocks);
    
    cnts = (u32)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;

    SysTick_SetReload(cnts);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    SysTick_CounterCmd(SysTick_Counter_Enable);
    SysTick_ITConfig(ENABLE);
}

/*
********************************************************************************
** �������� �� GPIO_Configuration(void)
** �������� �� �˿ڳ�ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | 
							RCC_APB2Periph_GPIOB | 
							RCC_APB2Periph_GPIOC | 
							RCC_APB2Periph_GPIOD | 
							RCC_APB2Periph_GPIOE, ENABLE  );
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);	 //�ͷ�JTAG����Ϊ��ͨIO��
   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 //����ʹ�õ������޸� 

	//����GPIOAΪ�������������LCD1602
	// PA0->E
	// PA1->RW
	// PA2->RS
	// PA4-7 -> DB4-7

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | 
								  GPIO_Pin_1 | 
								  GPIO_Pin_2 | 
								  GPIO_Pin_3 | 
								  GPIO_Pin_4 | 
								  GPIO_Pin_5 | 
								  GPIO_Pin_6 ;
   	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   // ����������50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);			       // ѡ��A�˿�

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
   	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   // ����������50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);			       // ѡ��A�˿�

#if 0
     // 17·ָʾ����ʾ
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 	  
  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // �������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   // ����������50MHz
  	GPIO_Init(GPIOA, &GPIO_InitStructure);			       // ѡ��A�˿�
    
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8| GPIO_Pin_9 ; 	  
  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // �������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   // ����������50MHz
  	GPIO_Init(GPIOC, &GPIO_InitStructure);			       // ѡ��C�˿�
  
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9|  GPIO_Pin_10| GPIO_Pin_11| 
                                  GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15 ;  
  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // �������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   // ����������50MHz
  	GPIO_Init(GPIOD, &GPIO_InitStructure);			       // ѡ��C�˿�
 
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15 ; 
  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // �������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   // ����������50MHz
  	GPIO_Init(GPIOB, &GPIO_InitStructure);			       // ѡ��B�˿�
#endif
}

/*
********************************************************************************
** �������� �� NVIC_Configuration(void)
** �������� �� �жϳ�ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void NVIC_Configuration(void)
{
      NVIC_InitTypeDef NVIC_InitStructure; 

      //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
      //NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick,0,0);
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
      //Step2.�ж�NVIC���ã������жϣ��������ȼ� 
  	  NVIC_InitStructure.NVIC_IRQChannel =  USART3_IRQChannel;    //�����¼� 
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //��ռ���ȼ�0 
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //��Ӧ���ȼ�1 
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж� 
	  NVIC_Init(&NVIC_InitStructure);                             //д������ 
	
	  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQChannel;    //�����¼� 
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //��ռ���ȼ�0 
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //��Ӧ���ȼ�2 
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж� 
	  NVIC_Init(&NVIC_InitStructure);                             //д������ 
	
	  NVIC_InitStructure.NVIC_IRQChannel =  USART2_IRQChannel;    //�����¼� 
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //��ռ���ȼ�0 
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;          //��Ӧ���ȼ�3 
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж� 
	  NVIC_Init(&NVIC_InitStructure);                             //д������
	
	  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;       //�����¼� 
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //��ռ���ȼ�0 
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;          //��Ӧ���ȼ�4 
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж� 
	  NVIC_Init(&NVIC_InitStructure);                             //д������ 
	 
	  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQChannel;		  //�����¼�
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  //��ռ���ȼ�0 
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		  //��Ӧ���ȼ�5
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж�
	  NVIC_Init(&NVIC_InitStructure);							  //д������
												   

}

/*
********************************************************************************
** �������� �� RCC_Configuration(void)
** �������� �� ʱ�ӳ�ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void RCC_Configuration(void)
{   
 	RCC_DeInit();

    RCC_HSEConfig(RCC_HSE_ON);
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if(HSEStartUpStatus == SUCCESS)
    {
      FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
      FLASH_SetLatency(FLASH_Latency_2);
      RCC_HCLKConfig(RCC_SYSCLK_Div1);
      RCC_PCLK2Config(RCC_HCLK_Div1);
      RCC_PCLK1Config(RCC_HCLK_Div2);
      RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);

      RCC_PLLCmd(ENABLE);

      while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)
      {
       }

      RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
      
      while(RCC_GetSYSCLKSource() != 0x08)
      {
       }
      
     }
      
}

   /*
********************************************************************************
** �������� �� WWDG_Configuration(void)
** �������� �� ���Ź���ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void WWDG_Configuration(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
  	
  WWDG_SetPrescaler(WWDG_Prescaler_8);	              //  WWDG clock counter = (PCLK1/4096)/8 = 244 Hz (~4 ms)  
  WWDG_SetWindowValue(0x41);		                 // Set Window value to 0x41
  WWDG_Enable(0x50);		       // Enable WWDG and set counter value to 0x7F, WWDG timeout = ~4 ms * 64 = 262 ms 
  WWDG_ClearFlag();			       // Clear EWI flag
  WWDG_EnableIT();			       // Enable EW interrupt
}

/*
********************************************************************************
** �������� �� TIM1_Configuration(void)
** �������� �� ��ʱ��1��ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void TIM1_Configuration(void)
{
  
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE );
   /* Time Base configuration */
  TIM_DeInit(TIM1);
  TIM_TimeBaseStructure.TIM_Prescaler = 71;                   //����Ԥ��Ƶ����Ƶϵ��71����APB2=72M, TIM1_CLK=72/72=1MHz ��
                                                               //����ȡֵ������0x0000��0xFFFF֮��
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���ģʽ
  //TIM1_TimeBaseStructure.TIM_Period = 1000;	               // 1ms��ʱ�����������ϼ�����1000����������¼�������ֵ����
  TIM_TimeBaseStructure.TIM_Period = 1000*15;	               // 15ms��ʱ	 ����ȡֵ������0x0000��0xFFFF֮��
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;			   //�����˶�ʱ��ʱ�ӷָ
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;		  // ���������ڼ�����ֵ������ȡֵ������0x00��0xFF֮�䡣

  TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);	         // ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
   
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);      //���жϣ�����һ�����жϺ����������ж�   
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //ʹ��TIM1�ж�Դ 
   
  TIM_Cmd(TIM1, ENABLE); 		             //TIM1�ܿ��أ�����
 
}


/*
********************************************************************************
** �������� �� USART1_Configuration(void)
** �������� �� ����1��ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void USART1_Configuration(void)
{

USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef  USART_ClockInitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE  );

USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;			// ʱ�ӵ͵�ƽ�
USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;				// ʱ�ӵ͵�ƽ
USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;				// ʱ�ӵڶ������ؽ������ݲ���
USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;		// ���һλ���ݵ�ʱ�����岻��SCLK���
/* Configure the USART1 synchronous paramters */
USART_ClockInit(USART1, &USART_ClockInitStructure);					// ʱ�Ӳ�����ʼ������
																	 
USART_InitStructure.USART_BaudRate = BAUDRATE1;						  // ������Ϊ��115200
USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8λ����
USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // ��֡��β����1��ֹͣλ
USART_InitStructure.USART_Parity = USART_Parity_No ;				  // ��żʧ��
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// Ӳ��������ʧ��

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // ����ʹ��+����ʹ��
/* Configure USART1 basic and asynchronous paramters */
USART_Init(USART1, &USART_InitStructure);
    
  /* Enable USART1 */
USART_ClearFlag(USART1, USART_IT_RXNE); 			//���жϣ�����һ�����жϺ����������ж�
USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);		//ʹ��USART1�ж�Դ
USART_Cmd(USART1, ENABLE);							//USART1�ܿ��أ����� 


}

/*
********************************************************************************
** �������� �� USART4_Configuration(void)
** �������� �� ����4��ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/

void USART4_Configuration(void)
{

USART_InitTypeDef USART_InitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE  );
												 
USART_InitStructure.USART_BaudRate = BAUDRATE4;						  // ������Ϊ��57600
USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8λ����
USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // ��֡��β����1��ֹͣλ
USART_InitStructure.USART_Parity = USART_Parity_No ;				  // ��żʧ��
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// Ӳ��������ʧ��

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // ����ʹ��+����ʹ��

USART_Init(UART4, &USART_InitStructure);
    
 
USART_ClearFlag(UART4, USART_IT_RXNE); 			//���жϣ�����һ�����жϺ����������ж�
USART_ITConfig(UART4,USART_IT_RXNE, ENABLE);		//ʹ��USART4�ж�Դ
USART_Cmd(UART4, ENABLE);							//USART4�ܿ��أ����� 
}

