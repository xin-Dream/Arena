//
// Created by dream on 2021/8/20.
//

#include "robot.h"
#include <ros.h>
#include <std_msgs/String.h>


ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[] = "Hello stm32!";

void setup(void) {
    nh.initNode();
    nh.advertise(chatter);
}

void loop(void) {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

    str_msg.data = hello;
    chatter.publish(&str_msg);
    nh.spinOnce();

    HAL_Delay(100);
}

