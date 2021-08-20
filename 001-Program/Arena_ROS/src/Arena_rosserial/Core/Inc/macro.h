//
// Created by dream on 2021/8/20.
//

#ifndef ARENA_ROSSERIAL_MACRO_H
#define ARENA_ROSSERIAL_MACRO_H

#include "main.h"
#include "robot.h"
#include "usbd_cdc_if.h"

/**
 * 数据发送协议
 * 协议内容：协议头--协议类型--长度--内容--协议结尾
 */
#define FLAG_HEAD0  0xce
#define FLAG_HEAD1  0xfa
#define FLAG_TAIL  0xad

#define TYPE_UPLOAD 0x01
#define TYPE_RECEIVE 0x02


struct TXProtocol {

    //uint8_t每个一个字节
    uint8_t head0;
    uint8_t head1;
    uint8_t type;
    uint8_t len;

    //short 每个两个字节
    short velocity;
    short angular;

    short code;
};


#endif //ARENA_ROSSERIAL_MACRO_H
