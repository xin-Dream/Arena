//
// Created by dream on 2021/9/6.
//
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8.h"
#include "sstream"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "talker");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::UInt8>("oled_show", 10);

    //要求以10Hz的频率发布数据
    ros::Rate rate(1);

    std_msgs::UInt8 msg;

    int count = 0;

    while (ros::ok) {
        count++;

        std::stringstream ss;
        ss << count;

        msg.data = ss.get();

        pub.publish(msg);
        ROS_INFO("发布的数据是: %d", msg.data);

        rate.sleep();

        ros::spinOnce();
    }

    return 0;

}
