#ifndef _INCLUDES_H
#define _INCLUDES_H
#include "stm32f10x_lib.h"
#include "ucos_ii.h"
#include "bsp.h"
#endif

#define   BAUDRATE1  115200		// ����1������
#define   BAUDRATE4	 115200	    // ����4������

#define	D1_H	    GPIO_SetBits(GPIOA, GPIO_Pin_8)		 // D1ָʾ�� Ϩ��
#define	D1_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_8)	 // D1ָʾ�� ���� 

#define	D2_H	    GPIO_SetBits(GPIOC, GPIO_Pin_9)		 // D2ָʾ�� Ϩ��
#define	D2_L	    GPIO_ResetBits(GPIOC, GPIO_Pin_9)	 // D2ָʾ�� ����  

#define	D3_H	    GPIO_SetBits(GPIOC, GPIO_Pin_8)		 // D3ָʾ�� Ϩ��
#define	D3_L	    GPIO_ResetBits(GPIOC, GPIO_Pin_8)	 // D3ָʾ�� ����  

#define	D4_H	    GPIO_SetBits(GPIOC, GPIO_Pin_7)		 // D4ָʾ�� Ϩ��
#define	D4_L	    GPIO_ResetBits(GPIOC, GPIO_Pin_7)	 // D4ָʾ�� ����  

#define	D5_H	    GPIO_SetBits(GPIOC, GPIO_Pin_6)		 // D5ָʾ�� Ϩ��
#define	D5_L	    GPIO_ResetBits(GPIOC, GPIO_Pin_6)	 // D5ָʾ�� ����  

#define	D6_H	    GPIO_SetBits(GPIOD, GPIO_Pin_15)     // D6ָʾ�� Ϩ��
#define	D6_L	    GPIO_ResetBits(GPIOD, GPIO_Pin_15)	 // D6ָʾ�� ����  

#define	D7_H	    GPIO_SetBits(GPIOD, GPIO_Pin_14)	 // D7ָʾ�� Ϩ��
#define	D7_L	    GPIO_ResetBits(GPIOD, GPIO_Pin_14)	 // D7ָʾ�� ����

#define	D8_H	    GPIO_SetBits(GPIOD, GPIO_Pin_13)     // D8ָʾ�� Ϩ��
#define	D8_L	    GPIO_ResetBits(GPIOD, GPIO_Pin_13)	 // D8ָʾ�� ����  

#define	D9_H	    GPIO_SetBits(GPIOD, GPIO_Pin_12)	 // D9ָʾ�� Ϩ��
#define	D9_L	    GPIO_ResetBits(GPIOD, GPIO_Pin_12)	 // D9ָʾ�� ����

#define	D10_H	    GPIO_SetBits(GPIOD, GPIO_Pin_11)     // D10ָʾ�� Ϩ��
#define	D10_L	    GPIO_ResetBits(GPIOD, GPIO_Pin_11)	 // D10ָʾ�� ����  

#define	D11_H	    GPIO_SetBits(GPIOD, GPIO_Pin_10)	 // D11ָʾ�� Ϩ��
#define	D11_L	    GPIO_ResetBits(GPIOD, GPIO_Pin_10)	 // D11ָʾ�� ����

#define	D12_H	    GPIO_SetBits(GPIOD, GPIO_Pin_9)      // D12ָʾ�� Ϩ��
#define	D12_L	    GPIO_ResetBits(GPIOD, GPIO_Pin_9)	 // D12ָʾ�� ����  

#define	D13_H	    GPIO_SetBits(GPIOD, GPIO_Pin_8)	     // D13ָʾ�� Ϩ��
#define	D13_L	    GPIO_ResetBits(GPIOD, GPIO_Pin_8)	 // D13ָʾ�� ����

#define	D14_H	    GPIO_SetBits(GPIOB, GPIO_Pin_15)     // D14ָʾ�� Ϩ��
#define	D14_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_15)	 // D14ָʾ�� ����  

#define	D15_H	    GPIO_SetBits(GPIOB, GPIO_Pin_14)	 // D15ָʾ�� Ϩ��
#define	D15_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_14)	 // D15ָʾ�� ����

#define	D16_H	    GPIO_SetBits(GPIOB, GPIO_Pin_13)     // D16ָʾ�� Ϩ��
#define	D16_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_13)	 // D16ָʾ�� ����  

#define	D18_H	    GPIO_SetBits(GPIOB, GPIO_Pin_12)	 // D18ָʾ�� Ϩ��  ��������ָʾ��
#define	D18_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_12)	 // D18ָʾ�� ����


