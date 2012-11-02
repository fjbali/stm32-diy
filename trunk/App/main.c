#include "includes.h"

static OS_STK   TaskStartStk[TASK_START_STK_SIZE];	// 定义起始任务堆栈大小
static OS_STK   Task1Stk[TASK1_STK_SIZE];			// 定义任务堆栈大小

static void TaskStart(void *p_arg);
static void Task1(void *p_arg);


void Delay(vu32 nCount); 
void Delayms (vu32 m);

OS_EVENT *mutex;
OS_EVENT *key_Sem;

u8 m; 
int main(void)
{
	INT8U err = 1;

    OSInit();	 //初始化 uC/OS-II 
	mutex=OSMutexCreate(3,&err);	// 建立互斥信号量
	key_Sem = OSSemCreate(0);  	    // 建立信号量  起始值为0 
    OSTaskCreate(TaskStart,(void*)0,&TaskStartStk[TASK_START_STK_SIZE-1],1); // 创建起始任务，赋予最高优先级1 
    OSStart();					   //开始多任务
	D1_H;D2_H;D3_H;D4_H;D5_H;D6_H;D7_H;D1_H;D8_H;D9_H;D10_H;D11_H;D12_H;D13_H;D14_H;D15_H;D16_H;D18_H;
}

/*
********************************************************************************
**起始任务，优先级1
********************************************************************************
*/
static void TaskStart(void *p_arg)
{
    (void)p_arg;
    BSP_Init();
   
#if (OS_TASK_STAT_EN > 0)
     OSStatInit();
#endif
    OSTaskCreate(Task1,(void*)0,&Task1Stk[TASK1_STK_SIZE-1],2);  // 在起始任务中创建Task1，优先级2 
	 
    
	D1_H;D2_H;D3_H;D4_H;D5_H;D6_H;D7_H;D1_H;D8_H;D9_H;D10_H;D11_H;D12_H;D13_H;D14_H;D15_H;D16_H;D18_H;
    while(1)
    {
	   OSTimeDly(10);
       OSTaskSuspend(OS_PRIO_SELF);	  // 挂起自身
    }    
}
/*
********************************************************************************
**任务1，优先级2
********************************************************************************
*/
#define LCD_GPIO	GPIOA
#define LCD_EN	GPIO_Pin_0
#define LCD_RW	GPIO_Pin_1
#define LCD_RS	GPIO_Pin_2
#define LCD_D7	GPIO_Pin_7
#define LCD_D6	GPIO_Pin_6
#define LCD_D5	GPIO_Pin_5
#define LCD_D4	GPIO_Pin_4
#define LCD_BLK	GPIO_Pin_3

#define EN_CLR \
	GPIO_WriteBit(LCD_GPIO, LCD_EN, Bit_RESET)
#define EN_SET \
	GPIO_WriteBit(LCD_GPIO, LCD_EN, Bit_SET)

#define RW_CLR \
	GPIO_WriteBit(LCD_GPIO, LCD_RW, Bit_RESET)
#define RW_SET \
	GPIO_WriteBit(LCD_GPIO, LCD_RW, Bit_SET)

#define RS_CLR \
	GPIO_WriteBit(LCD_GPIO, LCD_RS, Bit_RESET)
#define RS_SET \
	GPIO_WriteBit(LCD_GPIO, LCD_RS, Bit_SET)

#define BLK_ON \
	GPIO_WriteBit(LCD_GPIO, LCD_BLK, Bit_SET)

#define BLK_OFF \
	GPIO_WriteBit(LCD_GPIO, LCD_BLK, Bit_RESET)	

int LCD_Check_Busy(void)
{
	unsigned char dat = 0;

	GPIO_WriteBit(LCD_GPIO, LCD_D7, Bit_SET);

	RS_CLR;
	RW_SET;
	EN_SET;
	
	dat = GPIO_ReadInputDataBit(LCD_GPIO, LCD_D7);
	
	return dat;	 	
}
void LCD_Write_Byte(unsigned command, unsigned data);
void LCD_Clear(void);

void LCD_Init(void)
{
	EN_CLR;
	RW_CLR;
	RS_CLR;
	
	GPIO_WriteBit(LCD_GPIO, LCD_BLK, Bit_SET);
		
	GPIO_WriteBit(LCD_GPIO, LCD_D4, Bit_RESET);	
	GPIO_WriteBit(LCD_GPIO, LCD_D5, Bit_RESET);	
	GPIO_WriteBit(LCD_GPIO, LCD_D6, Bit_RESET);	
	GPIO_WriteBit(LCD_GPIO, LCD_D7, Bit_RESET);

	LCD_Write_Byte(1, 0x33);	
	LCD_Write_Byte(1, 0x32);
	LCD_Write_Byte(1, 0x28);
	LCD_Write_Byte(1, 0x0c);
	LCD_Write_Byte(1, 0x01);
	LCD_Write_Byte(1, 0x06);
	LCD_Clear();
} 

void LCD_Write_HalfByte(unsigned char data)
{
	RW_CLR;
	EN_SET;
	GPIO_WriteBit(LCD_GPIO, LCD_D4, (data & (1 << 4)) ? Bit_SET : Bit_RESET);
	GPIO_WriteBit(LCD_GPIO, LCD_D5, (data & (1 << 5)) ? Bit_SET : Bit_RESET);
	GPIO_WriteBit(LCD_GPIO, LCD_D6, (data & (1 << 6)) ? Bit_SET : Bit_RESET);
	GPIO_WriteBit(LCD_GPIO, LCD_D7, (data & (1 << 7)) ? Bit_SET : Bit_RESET);
	EN_CLR;
}

void LCD_Write_Byte(unsigned command, unsigned data)
{
	while(LCD_Check_Busy());
	if(command)
		RS_CLR;
	else
		RS_SET;
		
	LCD_Write_HalfByte(data);

	LCD_Write_HalfByte(data << 4);
}

void LCD_Clear(void)
{
	LCD_Write_Byte(1, 0x01);
}

void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
{     
	if (y == 0) 
	{     
		LCD_Write_Byte(1, 0x80 + x);     //表示第一行
	}
	else 
	{      
		LCD_Write_Byte(1, 0xC0 + x);      //表示第二行
	}        
	while (*s) 
	{     
		LCD_Write_Byte(0, *s);     
		s++;     
	}
}

void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data) 
{     
	if (y == 0) 
	{     
		LCD_Write_Byte(1, 0x80 + x);     
	}    
	else 
	{     
		LCD_Write_Byte(1, 0xC0 + x);     
	}        
	LCD_Write_Byte(0, Data);  
}

void LCD_Test(void)
{
	LCD_Init();
	LCD_Clear();
	while(1)
	{
		LCD_Write_Char(7, 0, 'o');
		LCD_Write_Char(8, 0, 'k');
		LCD_Write_String(1, 1, "www.doflye.net");

		while(1)
		{
			BLK_ON;
			OSTimeDly(50);
			BLK_OFF;
			OSTimeDly(50);
		}
	}
}

static void Task1(void *p_arg)
{     
   while(1)
   {	
		LCD_Test(); 
 	}
}

