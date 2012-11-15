#include "24C64.h"
#include "includes.h"

#define WriteDeviceAddress 	0xa0 //����������IIC�����еĵ�ַ
#define ReadDviceAddress 	0xa1

#define AT24C64_GPIO	GPIOB
#define AT24C64_SDA		GPIO_Pin_7
#define AT24C64_SCL		GPIO_Pin_6	

//��ʱ����
void DelayMs(unsigned int number)
{
	OSTimeDlyHMSM(0, 0, 0, number);
}

//��ʼ����
void I2C_Start()
{
//	SDA=1;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SDA, Bit_SET);
//	DelayMs(2);
//	SCL=1;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SCL, Bit_SET);
//	DelayMs(2);
//	SDA=0;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SDA, Bit_RESET);
//	DelayMs(2);
//	SCL=0;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SCL, Bit_RESET);
//	DelayMs(2);
}

//��������
void I2C_Stop()
{
//	SCL=0;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SCL, Bit_RESET);
//	DelayMs(2);
//	SDA=0;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SDA, Bit_RESET);
//	DelayMs(2);
//	SCL=1;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SCL, Bit_SET);
//	DelayMs(2);
//	SDA=1;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SDA, Bit_SET);
//	DelayMs(2);
}
//��ACK0
void I2C_NoAck()
{
//	SDA=1;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SDA, Bit_SET);
//	DelayMs(2);
//	SCL=1;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SCL, Bit_SET);
//	DelayMs(2);
//	SCL=0;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SCL, Bit_RESET);
//	DelayMs(2);
}
//����ACK
int I2C_TestAck()
{
	int ErrorBit;
//	SDA=1;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SDA, Bit_SET);
//	DelayMs(2);
//	SCL=1;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SCL, Bit_SET);
//	DelayMs(2);
//	ErrorBit=SDA;
	ErrorBit = GPIO_ReadInputDataBit(AT24C64_GPIO, AT24C64_SDA);
//	DelayMs(2);
//	SCL=0;
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SCL, Bit_RESET);
//	DelayMs(2);
	return(ErrorBit);
}
//д��8��bit��24c02
void I2C_Write8Bit(unsigned char input)
{
	unsigned char temp;

	for(temp=8;temp!=0;temp--)
	{
//		SDA=(bit)(input&0x80);
		GPIO_WriteBit(AT24C64_GPIO, AT24C64_SDA, (input & 0x80) ? Bit_SET : Bit_RESET);
//		DelayMs(2);
//		SCL=1;
		GPIO_WriteBit(AT24C64_GPIO, AT24C64_SCL, Bit_SET);
//		DelayMs(2);
//		SCL=0;
		GPIO_WriteBit(AT24C64_GPIO, AT24C64_SCL, Bit_RESET);
//		DelayMs(2);
		input=input<<1;
	}
}
//д��һ���ֽڵ�24c02��
void AT24C64_Write(unsigned char ch,unsigned short address)
{
	I2C_Start();
	I2C_Write8Bit(WriteDeviceAddress);
	I2C_TestAck();
	I2C_Write8Bit((address >> 8) & 0xff);
	I2C_TestAck();
	I2C_Write8Bit((address) & 0xff);
	I2C_TestAck();
	I2C_Write8Bit(ch);
	I2C_TestAck();
	I2C_Stop();
	DelayMs(10);
}
//��24c02�ж���8��bit
unsigned char I2C_Read8Bit()
{
	unsigned char temp,rbyte=0;

	for(temp=8;temp!=0;temp--)
	{
//		SCL=1;
		GPIO_WriteBit(AT24C64_GPIO, AT24C64_SCL, Bit_SET);
		DelayMs(1);
		rbyte=rbyte<<1;
//		rbyte=rbyte|((unsigned char)(SDA));
		rbyte = rbyte | GPIO_ReadInputDataBit(AT24C64_GPIO, AT24C64_SDA);
		DelayMs(1);
//		SCL=0;
		GPIO_WriteBit(AT24C64_GPIO, AT24C64_SCL, Bit_RESET);
		DelayMs(1);
	}
	return(rbyte);
}
//��24c02�ж���1���ֽ�
unsigned char AT24C64_Read(unsigned short address)
{
	unsigned char ch = 0;

	I2C_Start();
	I2C_Write8Bit(WriteDeviceAddress);
	I2C_TestAck();
	I2C_Write8Bit((address >> 8) & 0xff);
	I2C_TestAck();
	I2C_Write8Bit((address) & 0xff);
	I2C_TestAck();
	I2C_Start();
	I2C_Write8Bit(ReadDviceAddress);
	I2C_TestAck();
	ch=I2C_Read8Bit();
	I2C_NoAck();
	I2C_Stop();
	return(ch);
}

void AT24C64_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = AT24C64_SDA | AT24C64_SCL;
   	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   // ����������50MHz
	GPIO_Init(AT24C64_GPIO, &GPIO_InitStructure);			       // ѡ��B�˿�
		
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SDA, Bit_SET);
	GPIO_WriteBit(AT24C64_GPIO, AT24C64_SDA, Bit_SET);	
}

#if 0
//��������д��һ���ֽڵ�24c02����������֤
void main(void) // ������
{
uchar c1;
uchar address = 0x01;
for ( address = 0x01;address<0xff;address++)
{
Write24c64(0x00,address);// ��0x88д�뵽24c02�ĵ�2����ַ�ռ�
c1=Read24c64(address);
}
P20=0;
while(1); //�������
}
#endif

