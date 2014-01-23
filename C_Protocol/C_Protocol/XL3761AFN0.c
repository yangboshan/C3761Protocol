//
//  XL3761AFN0.c
//  C_Protocol
//
//  Created by JY on 14-1-22.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "XL3761AFN0.h"
#include "XLUtility.h"
#include "XLCommon.h"

void AFN0_RecursiveParse();


void initUserDataForAfn0(XL_SINT16 *output,void *frame,XL_UINT16* outlen,Byte** outbuf){
    
    outoffset = 0;
    offset = 0;
    
    _output = output;

    _frame = (FRAME*)frame;
    
    userdata = _frame->frameData;
    
    AFN0_RecursiveParse();
    
    free(userdata);
    free(_frame);

	outoffset = 0;
    offset = 0;
}

void AFN0_RecursiveParse(){
    
    XL_UINT16 fn = parsedadt((XL_UINT16)userdata[offset + 3],
                             (XL_UINT16)userdata[offset + 2],0);

    switch (fn) {
        case 1:
            *_output = XL_CONFIRM;
            break;
        case 2:
            *_output = XL_DENY;
            break;
        default:
            *_output = XL_ERROR;
            return;
    }
}