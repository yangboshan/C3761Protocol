//
//  XL3761PackFrame.h
//  C_Protocol
//
//  组帧接口
//
//  Created by JY on 14-1-14.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#ifndef C_Protocol_XL3761PackFrame_h
#define C_Protocol_XL3761PackFrame_h

#include "XLDataType.h"

//组合DADT组帧接口
Byte* PackFrame(Byte afn,PACKITEM array[],XL_UINT8 itemcount,XL_UINT16* outlen);

//组帧接口不带数据单元
Byte* PackFrameWithDadt(Byte afn,XL_UINT8 pn,XL_UINT8 fn,XL_UINT16* outlen);

//二类数据日冻结类数据时标
Byte* PackFrameWithTdd(Byte afn,XL_UINT8 pn,XL_UINT8 fn,XL_UINT8 year,XL_UINT8 month,XL_UINT8 day,XL_UINT16* outlen);

//二类数据月冻结类数据时标
Byte* PackFrameWithTdm(Byte afn,XL_UINT8 pn,XL_UINT8 fn,XL_UINT8 year,XL_UINT8 month,XL_UINT16* outlen);

//曲线类数据时标
Byte* PackFrameWithTdc(Byte afn,XL_UINT8 pn,XL_UINT8 fn,XL_UINT8 year,XL_UINT8 month,XL_UINT8 day,XL_UINT8 hour,XL_UINT8 mimute,XL_UINT8 density,XL_UINT8 points,XL_UINT16* outlen);

//三类数据事件
Byte* PackFrameForEvent(Byte afn,XL_UINT8 pn,XL_UINT8 fn,XL_UINT8 p1,XL_UINT8 p2,XL_UINT16* outlen);

#endif
