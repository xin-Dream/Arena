#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//SSD1306 OLED ����IC��������
//������ʽ:8080����/4�ߴ���
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
u8 OLED_GRAM[128][8];


void OLED_IIC_Start(void)
{

    OLED_SCLK_Set() ;
    OLED_SDIN_Set();
    OLED_SDIN_Clr();
    OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void OLED_IIC_Stop(void)
{
    OLED_SCLK_Set() ;
//	OLED_SCLK_Clr();
    OLED_SDIN_Clr();
    OLED_SDIN_Set();

}

void OLED_IIC_Wait_Ack(void)
{


    OLED_SCLK_Set() ;
    OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
    unsigned char i;
    unsigned char m,da;
    da=IIC_Byte;
    OLED_SCLK_Clr();
    for(i=0; i<8; i++)
    {
        m=da;
        //	OLED_SCLK_Clr();
        m=m&0x80;
        if(m==0x80)
        {
            OLED_SDIN_Set();
        }
        else OLED_SDIN_Clr();
        da=da<<1;
        OLED_SCLK_Set();
        OLED_SCLK_Clr();
    }


}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
    OLED_IIC_Start();
    Write_IIC_Byte(0x78);            //Slave address,SA0=0
    OLED_IIC_Wait_Ack();
    Write_IIC_Byte(0x00);			//write command
    OLED_IIC_Wait_Ack();
    Write_IIC_Byte(IIC_Command);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
    OLED_IIC_Start();
    Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
    OLED_IIC_Wait_Ack();
    Write_IIC_Byte(0x40);			//write data
    OLED_IIC_Wait_Ack();
    Write_IIC_Byte(IIC_Data);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
}
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
    if(cmd)
    {

        Write_IIC_Data(dat);

    }
    else {
        Write_IIC_Command(dat);

    }


}



/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
    unsigned int m;
    for(; Del_50ms>0; Del_50ms--)
        for(m=6245; m>0; m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
    unsigned char j;
    while(Del_1ms--)
    {
        for(j=0; j<123; j++);
    }
}

//��������

void OLED_Set_Pos(unsigned char x, unsigned char y)
{   OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f),OLED_CMD);
}
//����OLED��ʾ
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

void OLED_Refresh_Gram(void)
{
    u8 i,n;
    for(i=0; i<8; i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
        OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
        OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ
        for(n=0; n<128; n++)OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
    }
}

//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!
void OLED_Clear(void)
{
    u8 i,n;
    for(i=0; i<8; i++)for(n=0; n<128; n++)OLED_GRAM[n][i]=0X00;
    OLED_Refresh_Gram();//������ʾ
}
void OLED_On(void)
{
    u8 i,n;
    for(i=0; i<8; i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
        OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
        OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ
        for(n=0; n<128; n++)OLED_WR_Byte(1,OLED_DATA);
    } //������ʾ
}

//����
//x:0~127
//y:0~63
//t:1 ��� 0,���
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
    u8 pos,bx,temp=0;
    if(x>125||y>63)return;//������Χ��.
    pos=y/8;
    bx=7-y%8;
    temp=1<<(7-bx);
    if(t)OLED_GRAM[x+2][pos]|=temp;
    else OLED_GRAM[x+2][pos]&=~temp;
}

//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ
//size:ѡ������ 16/12
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{
    u8 temp,t,t1;
    u8 y0=y;
    chr=chr-' ';//�õ�ƫ�ƺ��ֵ
    for(t=0; t<size; t++)
    {
        if(size==12)temp=oled_asc2_1206[chr][t];  //����1206����
//		else temp=F8X16[chr][t];		 //����1608����
        for(t1=0; t1<8; t1++)
        {
            if(temp&0x80)OLED_DrawPoint(x,y,mode);
            else OLED_DrawPoint(x,y,!mode);
            temp<<=1;
            y++;
            if((y-y0)==size)
            {
                y=y0;
                x++;
                break;
            }
        }
    }
}
//m^n����
u32 oled_pow(u8 m,u8 n)
{
    u32 result=1;
    while(n--)result*=m;
    return result;
}
//��ʾ2������
//x,y :�������
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);
void OLED_ShowNumber(u8 x,u8 y,u32 num,u8 len,u8 size)
{
    u8 t,temp;
    u8 enshow=0;
    for(t=0; t<len; t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_ShowChar(x+(size/2)*t,y,' ',size,1);
                continue;
            } else enshow=1;

        }
        OLED_ShowChar(x+(size/2)*t,y,temp+'0',size,1);
    }
}
//��ʾ�ַ���
//x,y:�������
//*p:�ַ�����ʼ��ַ
//��16����
void OLED_ShowString(u8 x,u8 y,const u8 *p)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58
    while(*p!='\0')
    {
        if(x>MAX_CHAR_POSX) {
            x=0;
            y+=16;
        }
        if(y>MAX_CHAR_POSY) {
            y=x=0;
            OLED_Clear();
        }
        OLED_ShowChar(x,y,*p,12,1);
        x+=8;
        p++;
    }
}
//��ʼ��OLED
//��ʼ��SSD1306
void OLED_Init(void)
{


    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG, ENABLE);	 //ʹ��PC,D,G�˿�ʱ��



    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;	 //PD3,PD6�������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOD3,6


    GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);	//PD3,PD6 �����

    delay_ms_for(200);

    OLED_WR_Byte(0xAE,OLED_CMD);//--display off
    OLED_WR_Byte(0x00,OLED_CMD);//---set low column address0
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address16
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address
    OLED_WR_Byte(0xB0,OLED_CMD);//--set page address176
    OLED_WR_Byte(0x81,OLED_CMD); // contract control
    OLED_WR_Byte(0xFF,OLED_CMD);//--128
    OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap
    OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
    OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
    OLED_WR_Byte(0x00,OLED_CMD);//

    OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
    OLED_WR_Byte(0x80,OLED_CMD);//

    OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
    OLED_WR_Byte(0x05,OLED_CMD);//

    OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
    OLED_WR_Byte(0xF1,OLED_CMD);//

    OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
    OLED_WR_Byte(0x12,OLED_CMD);//

    OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
    OLED_WR_Byte(0x30,OLED_CMD);//

    OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
    OLED_WR_Byte(0x14,OLED_CMD);//

    OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}













