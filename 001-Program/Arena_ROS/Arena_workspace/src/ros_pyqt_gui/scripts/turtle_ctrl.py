#!/usr/bin/python
# coding: utf-8
import rospy
from PyQt5.QtWidgets import *
import sys

from window import MyMainWindow

if __name__ == '__main__':
    rospy.init_node("arena_ctrl_node")

    # QT UI
    app = QApplication(sys.argv)

    window = MyMainWindow()
    window.show()

    sys.exit(app.exec_())
