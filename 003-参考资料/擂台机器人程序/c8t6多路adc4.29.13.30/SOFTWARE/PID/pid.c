#include "pid.h"
#include "math.h"

#define cha_max 300
#define cha_min -300


float PID_p_1 = 5, PID_i_1=0.000 ,PID_d_1=0 ;
float PID_error_1,PID_last_error_1;
float PID_x_1,PID_y_1,PID_z_1;
float pid_calculate_1(float a,float b)
{
	float out;
	PID_error_1 = b-a;
	PID_x_1=PID_error_1;
	PID_y_1=PID_y_1+PID_x_1;
	PID_z_1=PID_error_1-PID_last_error_1;
  PID_last_error_1=PID_error_1;
	out=PID_p_1*PID_x_1+PID_i_1*PID_y_1+PID_d_1*PID_z_1;
	return out;
}

float PID_p_2 = 5,PID_i_2=0.00 ,PID_d_2=0 ;
float PID_error_2,PID_last_error_2;
float PID_x_2,PID_y_2,PID_z_2;
float pid_calculate_2(float a,float b)
{
	float out;
	PID_error_2=b-a;
	PID_x_2=PID_error_2;
	PID_y_2=PID_y_2+PID_x_2;
	PID_z_2=PID_error_2-PID_last_error_2;
  PID_last_error_2=PID_error_2;
	out=PID_p_2*PID_x_2+PID_i_2*PID_y_2+PID_d_2*PID_z_2;
	return out;
}

float major_power=500,power_L=700,power_R=700,power_1=500,power_2=500,power_3=500,power_4=500;
float pwmcha_L,pwmcha_R;
void moto_calculate(void)
{
	pwmcha_L=1*pid_calculate_1(angle[0],0);
	pwmcha_R=1*pid_calculate_2(angle[1],0);
	
	if(pwmcha_L>cha_max)
		pwmcha_L=cha_max;
	if(pwmcha_L<cha_min)
		pwmcha_L=cha_min;
	if(pwmcha_R>cha_max)
		pwmcha_R=cha_max;
	if(pwmcha_R<cha_min)
		pwmcha_R=cha_min;
				
	
	power_1=power_L+pwmcha_L;
	power_3=power_L-pwmcha_L;
	power_2=power_R+pwmcha_R;
	power_4=power_R-pwmcha_R;

	TIM_SetCompare1(TIM2,power_1);
	TIM_SetCompare2(TIM2,power_2);
	TIM_SetCompare3(TIM2,power_3);
	TIM_SetCompare4(TIM2,power_4);

}
