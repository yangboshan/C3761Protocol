//
//  XL3761UnPack.h
//  chand
//
//  Created by JY on 14-1-6.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//


#ifndef C_Protocol_XL3761UnPack_h
#define C_Protocol_XL3761UnPack_h
#include "XLDataType.h"


XL_SINT32 UnPackFrame(XL_UINT16 *type, XL_UINT16 inlen,Byte *inbuf,XL_UINT16* outlen,Byte** outbuf,int* multiFrameFlag);

#endif



