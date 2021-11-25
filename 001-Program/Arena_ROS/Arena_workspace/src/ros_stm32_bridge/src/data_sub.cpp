//
// Created by dream on 2021/9/4.
//

#include "ros/ros.h"
#include "std_msgs/String.h"

void doMsg(const std_msgs::String::ConstPtr& msg_p){
    ROS_INFO("stm32发送的数据为:%s",msg_p->data.c_str());
}

int main(int argc ,char *argv[]){
    setlocale(LC_ALL,"");

    ros::init(argc,argv,"listener");
    ros::NodeHandle nh;

    ros::Subscriber sub=nh.subscribe<std_msgs::String>("chatter",10,doMsg);

    ros::spin();
    return 0;
}