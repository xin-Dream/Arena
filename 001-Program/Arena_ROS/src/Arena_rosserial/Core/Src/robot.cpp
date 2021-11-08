//
// Created by dream on 2021/8/20.
//

#include <robot.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt8.h>

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
char hear[] = "I heard!";

ros::NodeHandle nh;

void oled_set(const std_msgs::UInt8 &msg);

ros::Subscriber<std_msgs::UInt8> oled_sub("oled_show", &oled_set);

void setup(void) {
    nh.initNode();
    nh.advertise(chatter);

    nh.subscribe(oled_sub);

}

void loop(void) {

    str_msg.data=hear;
    chatter.publish(&str_msg);

    nh.spinOnce();

    HAL_Delay(100);
}

int a = 0;

void oled_set(const std_msgs::UInt8 &msg) {
    uint8_t number = msg.data;
    a++;

    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

    OLED_ShowNum(20, 12, a, 6, 12);
    OLED_Refresh_Gram();
}

