#!/usr/bin/env python
import cv2
import rospy
from cv_bridge import CvBridge,CvBridgeError
from sensor_msgs.msg import Image

class image_converter:
    def __init__(self):
        self.image_pub=rospy.Publisher("cv_bridge_image",Image,queue_size=1)
        self.bridge=CvBridge()
        self.image_sub=rospy.Subscriber("/usb_cam/image_raw",Image,self.callback)

    def callback(self,data):

        try:
            cv_image=self.bridge.imgmsg_to_cv2(data,"bgr8")
        except CvBridgeError as e:
            print (e)

        (rows,cols,channels)=cv_image.shape
        if cols>60 and rows>60:
            cv2.circle(cv_image,(60,60),30,(0,0,255),-1)

        cv2.imshow("Image Window",cv_image)
        cv2.waitKey(3)

        try:
            self.image_pub.publish(self.bridge.cv2_to_imgmsg(cv_image,"bgr8"))
        except CvBridgeError as e:
            print (e)

if __name__ == '__main__':
    try:
        rospy.init_node("cv_bridge_test")
        rospy.loginfo("Starting cv_bridge_test node")

        image_converter()

        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down cv_bridge_test")
        cv2.destroyAllWindows()