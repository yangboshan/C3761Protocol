//
//  XL3761AFND.c
//  chand
//
//  Created by JY on 14-1-6.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "XL3761AFND.h"
#include "XLDataId.h"
#include "XLCommon.h"
#include "XLUtility.h"


void RecursiveParse();

void F49();
void F51();

void initUserDataForAfnd(XL_UINT16 *type,void *frame,XL_UINT16* outlen,Byte** outbuf){
    
    printf("解析文件AFND\n");
    
    offset=0;
    outoffset = 0;
    
    _type = type;
    _outlen = outlen;
    _outbuf = outbuf;
    
    _frame = (FRAME*)frame;
    
    userdata = _frame->frameData;
    
    buff = malloc(_frame->userlen*3 + 50);
    memset(buff,0,_frame->userlen*3 + 50);
    *_outbuf = buff;

    RecursiveParse();
    *outlen = outoffset;
    
    free(userdata);
    free(_frame);
}

void RecursiveParse(){
    
    XL_UINT16 fn = parseFnwithGroup((XL_UINT16)userdata[offset + 3],
                                    (XL_UINT16)userdata[offset + 2]);
    
    //拷贝
    memcpy(buff + outoffset, userdata + offset, 1); offset+=2;outoffset++;
    
    memcpy(buff + outoffset, &fn, 1);                offset+=2;outoffset++;

    switch (fn) {
        case 49:
            F49();
            break;
            
        case 51:
            F51();
            break;
            
        default:
            break;
    }
    
    XL_UINT16 auxlen = 0;
    if (_frame->aux.hasEC) {
        auxlen += 2;
    }
    if (_frame->aux.hasTP) {
        auxlen += 6;
    }
    
    if (_frame->userlen - 8 > offset + auxlen) {
        RecursiveParse();
    }
}

//日冻结终端月供电时间
//日复位累计次数
void F49(){
    printf("执行F49\n");
    
    //两个字节长度
    buff[outoffset] = terminal_day_sta; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;
    
//    buff[outoffset] = terminal_day_sta; outoffset++;
    
    XL_UINT16 identifier;
    identifier = hdDataTime;

    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;

    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;

//    buff[outoffset] = terminal_day_sta; outoffset++;
    identifier = hdPowerOnAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    memcpy(buff + outoffset, (XL_UINT16*)(userdata + offset), 2);offset += 2;outoffset+=2;
    
    
//    buff[outoffset] = terminal_day_sta; outoffset++;
    identifier = hdResetAccCnt;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    memcpy(buff + outoffset, (XL_UINT16*)(userdata + offset), 2);offset += 2;outoffset+=2;

    end = outoffset;
    
    XL_UINT16 len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
}
 
//月冻结终端月供电时间
//月复位累计次数
void F51(){
    printf("执行F51\n");
}


