#include "includes.h"
#include "LCD1602.h"
#include "DS1302.h"
#include "24C64.h"
#include <stdio.h>

static OS_STK   TaskStartStk[TASK_START_STK_SIZE];	// ������ʼ�����ջ��С
static OS_STK   Task1Stk[TASK1_STK_SIZE];			// ���������ջ��С

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

    OSInit();	 //��ʼ�� uC/OS-II 
	mutex=OSMutexCreate(3,&err);	// ���������ź���
	key_Sem = OSSemCreate(0);  	    // �����ź���  ��ʼֵΪ0 
    OSTaskCreate(TaskStart,(void*)0,&TaskStartStk[TASK_START_STK_SIZE-1],1); // ������ʼ���񣬸���������ȼ�1 
    OSStart();					   //��ʼ������
	D1_H;D2_H;D3_H;D4_H;D5_H;D6_H;D7_H;D1_H;D8_H;D9_H;D10_H;D11_H;D12_H;D13_H;D14_H;D15_H;D16_H;D18_H;
}

/*
********************************************************************************
**��ʼ�������ȼ�1
********************************************************************************
*/
static void TaskStart(void *p_arg)
{
    (void)p_arg;
    BSP_Init();
   
#if (OS_TASK_STAT_EN > 0)
     OSStatInit();
#endif
    OSTaskCreate(Task1,(void*)0,&Task1Stk[TASK1_STK_SIZE-1],2);  // ����ʼ�����д���Task1�����ȼ�2 	 
    
	D1_H;D2_H;D3_H;D4_H;D5_H;D6_H;D7_H;D1_H;D8_H;D9_H;D10_H;D11_H;D12_H;D13_H;D14_H;D15_H;D16_H;D18_H;
    while(1)
    {
	   OSTimeDly(10);
       OSTaskSuspend(OS_PRIO_SELF);	  // ��������
    }    
}
/*
********************************************************************************
**����1�����ȼ�2
********************************************************************************
*/


void LCD_Test(void)
{
	LCD_Init();
	LCD_Clear();
	while(1)
	{
		LCD_Write_Char(7, 0, 'o');
		LCD_Write_Char(8, 0, 'k');
		

		while(1)
		{
			LCD_Clear();
			LCD_Write_String(0, 1, "Hello, Hesonghua");
//			LCD_Light(1);
//			OSTimeDlyHMSM(0, 0, 5, 0);
//			LCD_Light(0);
			OSTimeDlyHMSM(0, 0, 1, 0);

			LCD_Clear();
			LCD_Write_String(0, 1, "Hello, Helihua");
//			LCD_Light(1);
//			OSTimeDlyHMSM(0, 0, 5, 0);
//			LCD_Light(0);
			OSTimeDlyHMSM(0, 0, 1, 0);
		}
	}
}

unsigned char timebuf[16] = {0, };
unsigned char databuf[16] = {0, };

void DS1302_Test()
{
	unsigned char timedat[8] = {0, 12, 11, 5, 0, 25, 0};

	LCD_Init();
	LCD_Clear();
//	while(1);
	DS1302_Init();

//	DS1302_WriteTime(timedat);
	while (1)         //��ѭ��
  	{
		memset(timedat, 0, sizeof(timedat));
  		DS1302_ReadTime(timedat);
		sprintf((char*)timebuf, "%02d-%02d %02d:%02d:%02d", timedat[2], timedat[3], timedat[4], timedat[5], timedat[6]);
		LCD_Clear();
//		LCD_Write_String(1, 0, databuf);
		LCD_Write_String(1, 0, timebuf);
		OSTimeDlyHMSM(0, 0, 1, 0);
//		while(1);
	}
}

unsigned char dispbuf[16] = {0, };
void AT24C64_Test(void)
{
	unsigned char data = 0;

	LCD_Init();
	LCD_Clear();
	AT24C64_Init();
	AT24C64_Write(45, 0x8);

	data = AT24C64_Read(0x8);
	sprintf((char*)dispbuf, "I Read:%d", data);
	LCD_Write_String(1, 0, dispbuf);
	while(1)
	{

	}
}

static void Task1(void *p_arg)
{     
   while(1)
   {
//   		AT24C64_Test();	
		DS1302_Test(); 
 	}
}

