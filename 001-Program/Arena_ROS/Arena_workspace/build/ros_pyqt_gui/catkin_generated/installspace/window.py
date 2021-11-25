#!/usr/bin/python
# coding: utf-8
import os

import rospy
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import sys

from firstMainWin import *

from geometry_msgs.msg import Twist


class MyMainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MyMainWindow, self).__init__(parent)
        self.setupUi(self)

        self.setWindowTitle("Arena_Control")
        self.resize(1000, 700)

        topic_name = "/cmd_vel"
        self.publisher = rospy.Publisher(topic_name, Twist, queue_size=100)

        self.send_btn.clicked.connect(lambda: self.click_send())

        self.serial_button.clicked.connect(lambda: self.serial_click())

        self.Linear_Slider.valueChanged.connect(lambda : self.SliderPub())
        self.Angula_Slider.valueChanged.connect(lambda : self.SliderPub())

    def click_send(self):
        linear = self.Linear.text()
        angular = self.Angula.text()
        # linear = self.Linear_Slider.value()
        # angular = self.Angula_Slider.value()

        twist = Twist()
        twist.linear.x = float(linear)
        twist.angular.z = float(angular)
        self.publisher.publish(twist)

    def SliderPub(self):
        linear = self.Linear_Slider.value()
        angular = self.Angula_Slider.value()

        twist = Twist()
        twist.linear.x = float(linear)
        twist.angular.z = float(angular)
        self.publisher.publish(twist)

    def serial_click(self):
        os.system(
            "gnome-terminal -x --roslaunch ros_stm32_bridge ros_talk_stm32.launch"
        )
