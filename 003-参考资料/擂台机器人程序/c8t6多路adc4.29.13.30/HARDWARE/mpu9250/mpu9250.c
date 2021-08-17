#include "mpu9250.h"

short int mpu_origin[9];
u8 biaoji=0;
void mpu9250_iic_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//先使能外设IO PORTB时钟 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;	 // 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIO 
  GPIO_SetBits(GPIOB,GPIO_Pin_14|GPIO_Pin_15);						 //PB12,PB11 输出高	
	
}
void I2C_delay(void)
{
		
   u8 i=30; //这里可以优化速度	，经测试最低到5还能写入
   while(i) 
   { 
     i--; 
   }  
}

void delay5ms(void)
{
		
   int i=5000;  
   while(i) 
   { 
     i--; 
   }  
}
/*******************************************************************************
* Function Name  : I2C_Start
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather	 Start
****************************************************************************** */
u8 I2C_Start(void)
{
	SDA_H;
	SCL_H;
	I2C_delay();
	if(!SDA_read)return FALSE;	//SDA线为低电平则总线忙,退出
	SDA_L;
	I2C_delay();
	if(SDA_read) return FALSE;	//SDA线为高电平则总线出错,退出
	SDA_L;
	I2C_delay();
	return TRUE;
}
/*******************************************************************************
* Function Name  : I2C_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_Stop(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
} 
/*******************************************************************************
* Function Name  : I2C_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_Ack(void)
{	
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}   
/*******************************************************************************
* Function Name  : I2C_NoAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
} 
/*******************************************************************************
* Function Name  : I2C_WaitAck
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather	 Reserive Slave Acknowledge Single
****************************************************************************** */
u8 I2C_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	SCL_L;
	I2C_delay();
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
      SCL_L;
	  I2C_delay();
      return FALSE;
	}
	SCL_L;
	I2C_delay();
	return TRUE;
}
/*******************************************************************************
* Function Name  : I2C_SendByte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_SendByte(u8 SendByte) //数据从高位到低位//
{
    u8 i=8;
    while(i--)
    {
        SCL_L;
        I2C_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        I2C_delay();
		SCL_H;
        I2C_delay();
    }
    SCL_L;
}  
/*******************************************************************************
* Function Name  : I2C_RadeByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
unsigned char I2C_RadeByte(void)  //数据从高位到低位//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      I2C_delay();
	  SCL_H;
      I2C_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
				biaoji=1;
      }
    }
    SCL_L;
    return ReceiveByte;
} 
//ZRX          
//单字节写入*******************************************

u8 Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	if(!I2C_Start())return FALSE;
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck()){I2C_Stop(); return FALSE;}
    I2C_SendByte(REG_Address );   //设置低起始地址      
    I2C_WaitAck();	
    I2C_SendByte(REG_data);
    I2C_WaitAck();   
    I2C_Stop(); 
    delay5ms();
    return TRUE;
}

//单字节读取*****************************************
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   unsigned char REG_data;     	
		if(!I2C_Start())return FALSE;
    I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck()){I2C_Stop();/*test=1; */return FALSE;}
    I2C_SendByte((u8) REG_Address);   //设置低起始地址      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();

		REG_data= I2C_RadeByte();
    I2C_NoAck();
    I2C_Stop();
    //return TRUE;
		return REG_data;
}

void MPU_Init(void)
{
	mpu9250_iic_init();
	Single_Write(GYRO_ADDRESS,PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_Write(GYRO_ADDRESS,SMPLRT_DIV, 0x07);
	Single_Write(GYRO_ADDRESS,CONFIG, 0x06);
	Single_Write(GYRO_ADDRESS,GYRO_CONFIG, 0x18);
	Single_Write(GYRO_ADDRESS,ACCEL_CONFIG, 0x01);
}


//******读取MPU9250数据****************************************
void READ_MPU9250_origin(void)
{
	mpu_origin[0]=(Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_H)<<8|Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_L));
	mpu_origin[1]=(Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_H)<<8|Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_L));
	mpu_origin[2]=(Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_H)<<8|Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_L));
	mpu_origin[3]=(Single_Read(GYRO_ADDRESS,GYRO_XOUT_H)<<8|Single_Read(GYRO_ADDRESS,GYRO_XOUT_L))-26; 
	mpu_origin[4]=(Single_Read(GYRO_ADDRESS,GYRO_YOUT_H)<<8|Single_Read(GYRO_ADDRESS,GYRO_YOUT_L))+29;
	mpu_origin[5]=(Single_Read(GYRO_ADDRESS,GYRO_ZOUT_H)<<8|Single_Read(GYRO_ADDRESS,GYRO_ZOUT_L))-2 ;
	mpu_origin[6]=(Single_Read(MAG_ADDRESS,MAG_XOUT_H)<<8|Single_Read (MAG_ADDRESS,MAG_XOUT_L));
	mpu_origin[7]=(Single_Read(MAG_ADDRESS,MAG_YOUT_H)<<8|Single_Read(MAG_ADDRESS,MAG_YOUT_L));
	mpu_origin[8]=(Single_Read(MAG_ADDRESS,MAG_ZOUT_H)<<8|Single_Read(MAG_ADDRESS,MAG_ZOUT_L));
}

float MPU9250_DATA_q[4]={1.0f,0.0f,0.0f,0.0f};
float MPU9250_exInt,MPU9250_eyInt,MPU9250_ezInt;
float MPU9250_ki=0.001f;
float MPU9250_kp=1.6f;
float MPU9250_halfT=0.01f;
float MPU9250_ANGLE[3];

void Caculate_MPU9250(void) 
{
		float norm;
		float vx, vy, vz;
		float ex, ey, ez; 
		float ax,ay,az,gx,gy,gz;
		float q0,q1,q2,q3;
		float q0temp,q1temp,q2temp,q3temp;

		ax=(float)mpu_origin[0];
		ay=(float)mpu_origin[1];
		az=(float)mpu_origin[2];

		gx=(float)mpu_origin[3]*2000/32768*3.14/180;
		gy=(float)mpu_origin[4]*2000/32768*3.14/180;
		gz=(float)mpu_origin[5]*2000/32768*3.14/180;

		q0=MPU9250_DATA_q[0];
		q1=MPU9250_DATA_q[1];
		q2=MPU9250_DATA_q[2];
		q3=MPU9250_DATA_q[3];

		// normalise the measurements
		norm = sqrt(ax*ax + ay*ay + az*az); 
		ax = ax / norm;
		ay = ay / norm;
		az = az / norm; 

		// estimated direction of gravity
		vx = 2*(q1*q3 - q0*q2);
		vy = 2*(q0*q1 + q2*q3);
		vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;

		// error is sum of cross product between reference direction of field and direction measured by sensor
		ex = (ay*vz - az*vy);
		ey = (az*vx - ax*vz);
		ez = (ax*vy - ay*vx);

		// integral error scaled integral gain
		MPU9250_exInt = MPU9250_exInt + ex*MPU9250_ki;
		MPU9250_eyInt = MPU9250_eyInt + ey*MPU9250_ki;
		MPU9250_ezInt = MPU9250_ezInt + ez*MPU9250_ki;

		// adjusted gyroscope measurements, PID 
		gx = gx + MPU9250_kp*ex + MPU9250_exInt;
		gy = gy + MPU9250_kp*ey + MPU9250_eyInt;
		gz = gz + MPU9250_kp*ez + MPU9250_ezInt;

		q0temp=q0; 
		q1temp=q1; 
		q2temp=q2;
		q3temp=q3;

		//*Note3
		// integrate quaternion rate and normalise
		q0 = q0temp +(-q1temp *gx - q2temp *gy - q3temp *gz)*MPU9250_halfT;
		q1 = q1temp + (q0temp *gx + q2temp *gz - q3temp *gy)*MPU9250_halfT;
		q2 = q2temp + (q0temp *gy - q1temp *gz + q3temp *gx)*MPU9250_halfT;
		q3 = q3temp + (q0temp *gz + q1temp *gy - q2temp *gx)*MPU9250_halfT; 

		// normalise quaternion
		norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
		q0 = q0 / norm;
		q1 = q1 / norm;
		q2 = q2 / norm;
		q3 = q3 / norm;

		MPU9250_DATA_q[0]=q0;
		MPU9250_DATA_q[1]=q1;
		MPU9250_DATA_q[2]=q2;
		MPU9250_DATA_q[3]=q3;
		
		MPU9250_ANGLE[2]=  atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3; //YAW
		MPU9250_ANGLE[1] = asin(-2 * q1 * q3 + 2 * q0* q2)*57.3; // pitch
		MPU9250_ANGLE[0] = atan2(2 * q2 * q3 + 2 * q0 * q1,-2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
}

void display_mpu9250(void)
{
	u8 display_mpu9250_i;
	for(display_mpu9250_i=0;display_mpu9250_i<3;display_mpu9250_i++)
	{
		if(MPU9250_ANGLE[display_mpu9250_i]<0)
		{
			LCD_ShowxNum(150,10+display_mpu9250_i*20,1,1,12,0);				//显示 数字
			LCD_ShowxNum(100,10+display_mpu9250_i*20,-MPU9250_ANGLE[display_mpu9250_i]*1000,6,12,0);				//显示 数字
		}
		else
		{
			LCD_ShowxNum(150,10+display_mpu9250_i*20,0,1,12,0);				//显示 数字
			LCD_ShowxNum(100,10+display_mpu9250_i*20, MPU9250_ANGLE[display_mpu9250_i]*1000,6,12,0);				//显示 数字
		}
	}
	for(display_mpu9250_i=0;display_mpu9250_i<9;display_mpu9250_i++)
	{
		
		if(mpu_origin[display_mpu9250_i]<0)
		{
			LCD_ShowxNum(50,10+display_mpu9250_i*20,1,1,12,0);				//显示 数字
			LCD_ShowxNum(10,10+display_mpu9250_i*20,-mpu_origin[display_mpu9250_i],5,12,0);				//显示 数字
		}
		else
		{
			LCD_ShowxNum(50,10+display_mpu9250_i*20,0,1,12,0);				//显示 数字
			LCD_ShowxNum(10,10+display_mpu9250_i*20,mpu_origin[display_mpu9250_i],5,12,0);				//显示 数字
		}
	}
}
