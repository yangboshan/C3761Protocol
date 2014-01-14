//
//  XLCommon.h
//  C_Protocol
//
//  Created by JY on 14-1-14.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#ifndef C_Protocol_XLCommon_h
#define C_Protocol_XLCommon_h

#include "XLDataType.h"
#include "XLFrame.h"


Byte *userdata;
FRAME *_frame;
XL_UINT16 offset=0;
XL_UINT16 outoffset = 0;

Byte* buff;
XL_UINT16* _type;
XL_UINT16* _outlen;
Byte** _outbuf;



#endif
