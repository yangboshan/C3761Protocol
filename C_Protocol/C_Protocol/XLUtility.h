//
//  XLUtility.h
//  C_Protocol
//
//  Created by JY on 14-1-14.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#ifndef C_Protocol_XLUtility_h
#define C_Protocol_XLUtility_h
#include "XLDataType.h"

XL_UINT16 parsedadt(XL_UINT16 group,XL_UINT16 number,XL_UINT8 ispn);

XL_UINT64 bcdtouint(Byte* value,XL_UINT8 byteslen,XL_UINT8 digitlen);

XL_SINT64 bcdtosint(Byte* value,XL_UINT8 byteslen,XL_UINT8 digitlen);

Byte bcdToTime(Byte* value);

Byte* decimaltobcd_s(XL_FP64 dec,XL_UINT8 byteslen,XL_UINT8 digitlen);

XL_SINT16 a22intwithparam(Byte* value);

XL_CHAR a2powvaluewithparam(Byte* value);

#endif
