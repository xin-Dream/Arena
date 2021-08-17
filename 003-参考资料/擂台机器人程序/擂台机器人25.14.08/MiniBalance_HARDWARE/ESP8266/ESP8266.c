#include "ESP8266.h"
#include "sys.h"
#include "delay.h"
void Connect(void)
{
	int i=0;
	printf("AT+CWMODE=1\r\n");
	Delay_50ms(20);
//	USART_SendData(USART1,0xaa);
	printf("AT+CIPMODE=1\r\n");
	Delay_50ms(20);
//	USART_SendData(USART1,0xbb);
	printf("AT+CIPSTART=\"TCP\",\"192.168.1.101\",8080\r\n");
	Delay_50ms(40);
//	USART_SendData(USART1,0xcc);
	printf("AT+CIPSEND\r\n");
	Delay_50ms(40);
//	USART_SendData(USART1,0xdd);
	

}

//------------------End of File----------------------------
