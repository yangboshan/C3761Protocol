//
//  XL3761AFNC.c
//  C_Protocol
//
//  Created by JY on 14-1-15.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "XL3761AFNC.h"
#include "XLDataId.h"
#include "XLCommon.h"
#include "XLUtility.h"


void AFNC_RecursiveParse();

void AFNC_F49();


void initUserDataForAfnc(XL_UINT16 *type,void *frame,XL_UINT16* outlen,Byte** outbuf){
    
    printf("解析文件AFNC\n");
    
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
    
    AFNC_RecursiveParse();
    *outlen = outoffset;
    
    free(userdata);
    free(_frame);
}

void AFNC_RecursiveParse(){
    
    XL_UINT16 fn = parseFnwithGroup((XL_UINT16)userdata[offset + 3],
                                    (XL_UINT16)userdata[offset + 2]);
    
    //拷贝
    memcpy(buff + outoffset, userdata + offset, 1); offset+=2;outoffset++;
    
    memcpy(buff + outoffset, &fn, 1);                offset+=2;outoffset++;
    
    switch (fn) {
        case 49:
            AFNC_F49();
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
        AFNC_RecursiveParse();
    }
}

void AFNC_F49(){
    
}
