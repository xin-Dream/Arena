//
// Created by dream on 2021/8/20.
//

#include <robot.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt8.h>




void oled_set(const std_msgs::UInt8 &msg);

ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

ros::Subscriber<std_msgs::UInt8> oled_sub("oled_show", &oled_set);

char hello[] = "Hello GUIXIN ROS stm32!";

void setup(void) {
    nh.initNode();
    nh.advertise(chatter);

    nh.subscribe(oled_sub);
}

void loop(void) {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

    str_msg.data = hello;
    chatter.publish(&str_msg);
    nh.spinOnce();

    HAL_Delay(100);
}

void oled_set(const std_msgs::UInt8 &msg){
    uint32_t a=msg.data;
    OLED_ShowNum(32,10,a,5,12);
}

