#include "init.h"

#define AI 							analog
#define DI							digital
#define ClearScreen 		clear_screen
#define ShowStr 				display_GB2312_string		//�ַ�������
#define ShowAI					display_GB2312_u16 //��λ����
#define ShowDI					display_GB2312_u1		//һλ����
#define ServoSetMode		UP_CDS_SetMode					
#define ServoSetAngle		UP_CDS_SetAngle

void speed_dispaly(void);//�ٶ�����
int abs(int a,int b);
int Touch(void);//����ADת��
void up_stage(void);//���ε�̨
void start_feedback(void);//��������
int analog_scan_close(void);//����¼ ���������
int analog_scan_far(void);//����¼ ��Զ������
void touch_sensor(void);//��������
void test(void);//����ģʽ�ܺ���
int select_high(void);//��̨���
void find_single();
int Find_Taizi();