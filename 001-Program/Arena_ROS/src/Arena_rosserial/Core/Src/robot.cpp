//
// Created by dream on 2021/8/20.
//

#include "robot.h"


void publishData(void) {

    struct TXProtocol *protocol = new TXProtocol;

    uint8_t ProtocolLen = sizeof(TXProtocol);

    protocol->head0 = FLAG_HEAD0;
    protocol->head1 = FLAG_HEAD1;
    protocol->type = TYPE_UPLOAD;
    protocol->len = ProtocolLen;

    protocol->angular = 10;
    protocol->velocity = 20;

    protocol->code = FLAG_TAIL;

}