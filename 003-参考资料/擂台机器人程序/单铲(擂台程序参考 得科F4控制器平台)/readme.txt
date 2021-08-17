1、网店：marinerobot.taobao.com

2、联系QQ：328615156  联系电话：15867485359  姓周

3、程序架构（用户只要编写function.h和main.c即可）：
   ☆所有的硬件驱动程序都放在HARDWARE、init.c、init.h
   ☆所有业务详细子程序和详细模块程序都放在function.h
   ☆所有跑的模块程序都放在main.c
   ☆串口中断，定时器中断函数都在相应的驱动.c文件内

4、函数汇总
	1、 马达模块
		（1） 启动电机
			函数： void motor(int motorID, int speed);
			说明：启动指定电机
				motorID 为马达号，范围 0,1,2,3
				speed 为马达速度，范围-1000 到 1000
			函数： void allmotor(int speed_0, int speed_1, int speed_2, int speed_3);
			说明：启动所有电机
				Speed_0~speed_3 为马达速度，范围-1000 到 1000
		（2） 停止
			函数： void stop(void);
			说明：停止所有的马达
			函数： void off(int motorID);
			说明：停止指定电机
			
	2、 液晶模块
		（1） 显示
			函数： void LCD_printf(u16 x,u16 y,const char *format, ...);
			说明：在液晶屏上指定显示内容。固定显示内容可以是字符、数字等。
			x为液晶的第几行，y为液晶的第几列。
			
			函数：void ClearScreen(void);
			说明：清屏
			
	3、系统延时
		（1） 毫秒级延时
			函数： void delay_ms(u16 nms);
			说明：延时，单位毫秒
			（2） 秒级延时
			函数： void delay_us(u32 nus);
			说明：延时，单位秒
	
	4、系统计时
		（1） 开始计时
			函数： void start_time(void);
			说明：计时重设为 0
		（2） 获取计时
			函数： u16 mseconds(void);
			说明：返回系统计时，单位毫秒	
		（3）函数： u16 seconds(void);
			说明：返回系统计时，单位秒
		（4）函数： void reset_time(void);
			 说明：计时重设为 0
		（5） 停止计时
			函数： void stop_time(void);
			说明：计时值为最后一次
	
	5、系统输入
		（1） 模拟输入
			函数： u16 analog(u8 port);
			说明：返回指定端口模拟数据，范围 0 到 4095
			port 为端口号，范围为 0～13
		（2） 数字输入
			函数： u8 digital(u8 port);
			说明：返回指定端口数字数据，范围 0 和 1
			port 为端口号，范围为 0～13
	
	6、蜂鸣器和LED
		（1） Beep 音
			函数： void beep(void);
			说明：发出一个 500Hz， 0.3s 的声音
		（2）
			函数： void led_on(void);
			函数： void led_off(void);

	7、伺服电机
		（1） 控制伺服电机
			函数： void init_servos(u8);
			说明：伺服电机开关， 0 为关， 1 为开
		（2） 设定伺服电机
			函数： void servos(u8 ch,int s);
			说明：设的指定伺服电机数值
				ch 为伺服电机号，范围为 0～3（主板）， 4～19（扩展板）
				s 为伺服电机数值，范围为 -90~90
				
	8、串口通信
		（1） 串口初始化
			函数： void uart_init(u8 way, u32 bound);
			说明：初始化串口， way为第几个串口，Baud 为串口波特率
		（2） 串口发送数据
			函数： void USART_SendByte(u8 way, u8 data);
			说明：向串口发送一个字节的数据
		（3） 串口接收数据（串口1）
	        if(USART_RX_STA&0x8000)
			{					   
				len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			}
			数据都在USART_RX_BUF[t]里。
			说明：从串口接收一个字节的数据
			
		（4） 指南针(指定串口I)
			函数： int compass (void);
			说明：读取指南针数据，范围为 0～359
	
	9、现场参数设置
		（1） 参数读取
			函数： int eepread(u32 addr);
			说明：从指定地址读取数据
				addr 为地址，范围为 0～999
				返回值为该地址所存的数据，范围为-32768～32767
		（2） 参数写入
			函数： void eepwrite(u32 addr,int data);
			说明：向指定地址写入数据
				addr 为地址，范围为 0～999
				data 为写入的数据，范围为-32768～32767
	10、指南针(指定串口III复用，SCL为TX3，SDA为RX3)
		（1） 参数读取
			函数： u8 compassRead(void);
			说明：读取指南针数据
				返回值范围为0～359
				
	11、激光测距（指定串口I复用）
		（1） 打开激光测距
			函数：void jiguang_on(void);
			说明：只要读取全部变量jiguang_value即可
		（2） 关闭激光测距
			函数：void jiguang_off(void);
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					