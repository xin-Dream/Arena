#!/usr/bin/python
# -*- coding: utf-8 -*-
#     main program
#     主要工作内容：
#         检测二维码
#         检测赛道中点
#
import cv2
import apriltag as apriltag  # 树莓派下安装该包的名字 不是pupil_apriltags 应该是apriltag
import math
import imutils
import numpy as np

from MicroSerial import MicroSerial


def get_max_y(centers):  # 将中心坐标的y坐标取出，然后取出最大的y坐标
    y_list = []
    for i in range(len(centers)):
        y_list.append(centers[i][1])
    print(max(y_list))
    return max(y_list)


def get_push_center(centers, maxy):  # 给出离自己最近的二维码的中心位置
    for i in range(len(centers)):
        if centers[i][1] == maxy:
            push_center = [centers[i][0], centers[i][1]]
            return push_center, i  # 返回中心和中心值的列表索引
        else:
            pass


def count_Perimeter(points):
    '''
    计算周长
    :param points: 列表类型 传入含有矩形四个点位置的列表
    :return: 输入矩形的周长
    '''
    l1 = math.sqrt((points[0][0] - points[1][0]) ** 2 + (points[0][1] - points[1][1]) ** 2)  # 左上右上
    l2 = math.sqrt((points[0][0] - points[3][0]) ** 2 + (points[0][1] - points[3][1]) ** 2)  # 左上左下
    l3 = math.sqrt((points[2][0] - points[3][0]) ** 2 + (points[2][1] - points[3][1]) ** 2)  # 右下 左下
    l4 = math.sqrt((points[2][0] - points[1][0]) ** 2 + (points[2][1] - points[1][1]) ** 2)  # 右下右上
    return int(l1 + l2 + l3 + l4)


def get_corners_potions(corners, center):  # 将检测到的一个二维码的坐标转换为整形列表
    temp_list = [[] for _ in range(5)]
    for i in range(4):
        temp_list[i] = list(corners[i].astype(int))
        # print(temp_list[i])
    temp_list[4] = (list(center.astype(int)))
    # print('测试点temp_list',temp_list)
    return temp_list


def get_tags_information(tags):
    '''
    :param tags: tags列表
    :return:centers_1 检测到所有ID为1的中心
            centers_0 检测到所有ID为0的中心
    '''
    # 初始化存储列表
    zeroID_infromation = []  # 初始存储0列表
    onesID_information = []  # 存储格式为 [[左上，右上，右下，左下，中心坐标],...]
    centers_0 = []  # 初始化存储中点的坐标列表
    centers_1 = []
    print('函数调用')
    for tag in tags:
        if tag.tag_id == 0:
            centers_0.append(list(tag.center.astype(int)))
            zeroID = []
            # 备注：[x,y] ->[宽度，高度]->[列数,行数]
            # 与opencv坐标的表示相反
            zeroID = (get_corners_potions(tag.corners, tag.center))  # [[左上], [右上], [右下], [左下], [cx, cy]]
            zeroID_infromation.append(zeroID)  # zeroID_information的长度为存储的二维码ID为0的张数，进入下一层为该张二维码的各参数

        if tag.tag_id == 1:
            centers_1.append(list(tag.center.astype(int)))
            onesID = []
            onesID = (get_corners_potions(tag.corners, tag.center))
            onesID_information.append(onesID)
    print('共检测到炸弹二维码{0}张'.format(len(zeroID_infromation)))
    print('共检测到能量块二维码{0}张'.format(len(onesID_information)))
    zero_primeterList = []  # 初始化存储两类周长的列表
    ones_primeterList = []
    for i in range(len(zeroID_infromation)):  # 得到检测到的ID 为0 的二维码的数量
        zero_primeterList.append(count_Perimeter(zeroID_infromation[i]))
    for i in range(len(onesID_information)):
        ones_primeterList.append(count_Perimeter(onesID_information[i]))
    print('能量块二维码中心列表: ', centers_1)
    print('炸弹二维码中心列表: ', centers_0)
    return onesID_information, zeroID_infromation, centers_1, centers_0


def draw_img(tags, img):
    '''
    绘制检测到的二维码点
    :param tags:tags列表
    :param img: 在img图像上绘制
    :return: img绘制后的图像
    '''
    print(len(tags))
    i = 0
    for tag in tags:
        # i=i+1
        # print(i)
        cv2.circle(img, tuple(tag.corners[0].astype(int)), 4, (0, 0, 128), 4)  # left-top
        cv2.circle(img, tuple(tag.corners[1].astype(int)), 4, (255, 0, 255), 2)  # right-top
        cv2.circle(img, tuple(tag.corners[2].astype(int)), 4, (255, 0, 255), 2)  # right-bottom
        cv2.circle(img, tuple(tag.corners[3].astype(int)), 4, (255, 0, 255), 2)  # left-bottom
    return img


def get_center(contour):
    approx = cv2.approxPolyDP(contour, 4, closed=False)
    center = np.int0(sum(approx)[0] / len(approx))
    center = (center[0], center[1])
    return center


if __name__ == '__main__':

    # Arena_Slave = MicroSerial("/dev/ttyS0", 115200, 0.5)
    #
    # Arena_Slave.connect()

    cap = cv2.VideoCapture(0)
    detector = apriltag.Detector()  # 创建检测器

    if cap.isOpened():
        print('摄像头已开启')
        while cap.isOpened():

            # Arena_Slave.recv()

            ret, frame = cap.read()
            frame = imutils.resize(frame, width=500)
            y, x, _ = frame.shape
            img = frame.copy()
            img2 = frame.copy()
            gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            tags = detector.detect(gray)  # 二维码检测实例化
            img_hsv = cv2.cvtColor(img2, cv2.COLOR_BGR2HSV)
            mask1 = cv2.inRange(img_hsv, (0, 50, 20), (5, 255, 255))
            mask2 = cv2.inRange(img_hsv, (175, 50, 20), (180, 255, 255))
            mask = cv2.bitwise_or(mask1, mask2)
            croped = cv2.bitwise_and(img, img, mask=mask)
            # 图像腐蚀 -> 图像膨胀
            # 生成腐蚀核
            erode_kernel = cv2.getStructuringElement(shape=0, ksize=(3, 3))
            # 生成膨胀内核
            dilate_kernel = cv2.getStructuringElement(shape=0, ksize=(9, 9))
            erode_dst = cv2.erode(mask, erode_kernel, iterations=5)  # 腐蚀
            dilate_dst = cv2.dilate(erode_dst, dilate_kernel, iterations=9)  # 膨胀
            # 轮廓检测
            aa, contours, hierarchy = cv2.findContours(dilate_dst, mode=3, method=2)
            Flag = 'center'  # 分阶段执行
            if Flag == 'center':  # 检测地图中心
                Flag = 'apriltag'
                if len(contours) == 0:
                    s_max = 0
                    print('当前画面未检测到中心')

                if len(contours) == 1:
                    # print(contours)
                    s_max = cv2.contourArea(contours[0])
                    centerpoint = get_center(contours[0])
                    cv2.circle(frame, centerpoint, 10, (0, 255, 0), -1)
                    # 检测到中心，面积大小：
                    print('Center detected in current screen', 'square:', s_max)
                    # 中心坐标
                    print('center coordinates:', centerpoint)  # (x,y)
                    # 划分区域2 1 2
                    left_roi = int(x / 5)

                if len(contours) > 1:
                    # 画面检测到多个轮廓
                    print('Image detects multiple Outlines')
                    area_list = []
                    for i in range(len(contours)):
                        s = cv2.contourArea(contours[i])
                        area_list.append(s)
                    # 取出最大面积
                    s_max = max(area_list)
                    max_index = area_list.index(max(area_list))
                    print('max square', s_max)
                    print('max square index', max_index)
                    # print('最大面积位置信息：',contours[max_index])
                    centerpoint = get_center(contours[max_index])
                    cv2.circle(frame, centerpoint, 10, (0, 255, 0), -1)
                    # 中心坐标
                    print('center coordinates:', centerpoint)
                if s_max >= 0.7 * y * x:
                    print('Arrive center', s_max / (y * x))
                    cv2.circle(frame, centerpoint, 20, (255, 0, 0), -1)
                else:
                    print('square per', s_max / (y * x))
            if Flag == 'apriltag':  # 检测二维码
                Flag = 'center'  # push_center (x,y)

                if tags != []:  # 列表内容不为空开始获取检测到的二维码信息
                    # 初始化区域划分
                    roi_width = int(x / 5)  # 划分比例为2 1 2
                    lef_min = 0
                    left_max = roi_width * 2
                    center_min = roi_width * 2
                    center_max = roi_width * 3
                    right_min = roi_width * 3
                    right_max = roi_width * 5
                    onesID_information, zeroID_infromation, centers_1, centers_0 = get_tags_information(tags)
                    print('ok')
                    if onesID_information != []:

                        # 结果为能量块
                        # Arena_Slave.send("1")

                        ones_push_center, ones_center_number = get_push_center(centers_1, get_max_y(centers_1))
                        # print('energy pos',ones_push_center)
                        # print(ones_center_number)
                        # print('okk')

                        print('energy pos', ones_push_center, onesID_information[ones_center_number])
                        ones_push_center = tuple(ones_push_center)
                        cv2.circle(frame, ones_push_center, 4, (0, 0, 255), 4)  # 标记处图像的中心
                        # 进行大致区域划分判断
                        if ones_push_center[0] < left_max and ones_push_center[0] > lef_min:
                            print('energy pos left ')
                            cv2.line(frame, (int(x / 5), 0), (int(x / 5), y), (0, 255, 0), 4)  # 标记处图像的中心
                        elif ones_push_center[0] < right_max and ones_push_center[0] > right_min:
                            print('energy pos right')
                            cv2.line(frame, (int(4 * x / 5), 0), (int(4 * x / 5), y), (0, 255, 0), 4)  # 标记处图像的中心
                        else:
                            print('energy pos center')
                            cv2.line(frame, (int(x / 2), 0), (int(x / 2), y), (0, 255, 0), 4)  # 标记处图像的中心

                    if zeroID_infromation != []:

                        # 结果为炸弹
                        # Arena_Slave.send("2")

                        zero_push_center, zero_center_number = get_push_center(centers_0, get_max_y(centers_0))
                        print(
                            'boom pos', zero_push_center,
                            zeroID_infromation[zero_center_number])  # 输出得到的是 中心点 和检测到中心点二维码列表
                        zero_push_center = tuple(zero_push_center)
                        cv2.circle(frame, zero_push_center, 10, (255, 0, 0), -1)  # 标出图像中的中心点

                        # 进行大致区域划分判断
                        if zero_push_center[0] < left_max and zero_push_center[0] > lef_min:
                            print(' bomb left ')
                            cv2.line(frame, (int(x / 5), 0), (int(x / 5), y), (0, 0, 255), 4)  # 标记处图像的中心
                        elif zero_push_center[0] < right_max and zero_push_center[0] > right_min:
                            print('bomb pos right')
                            cv2.line(frame, (int(4 * x / 5), 0), (int(4 * x / 5), y), (0, 0, 255), 4)  # 标记处图像的中心
                        else:
                            print('bomb pos center')
                            cv2.line(frame, (int(x / 2), 0), (int(x / 2), y), (0, 0, 255), 4)  # 标记处图像的中心
                if tags == []:  # 画面中没有检测到二维码

                    # 未知
                    # Arena_Slave.send("3")

                    print('NO QR')


            # cv2.imshow('img',img)
            # cv2.imshow('mask1', mask1)
            # cv2.imshow('mask2', mask2)
            # cv2.imshow('dilate', dilate_dst)
            # cv2.imshow('erode', erode_dst)
            cv2.imshow('frame', frame)

            if cv2.waitKey(1) == ord('q'):
                break
    else:
        print('摄像头未开启')
    cap.release()
