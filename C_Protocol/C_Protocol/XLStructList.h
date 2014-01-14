//
//  XLStructList.h
//  C_Protocol
//
//  Created by JY on 14-1-13.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#ifndef C_Protocol_XLStructList_h
#define C_Protocol_XLStructList_h



#endif

#include "XLDataType.h"


#pragma pack(1)

typedef struct{
    XL_UINT16 _size;
    void* _struct;
}CMSTRUCT;



typedef struct{
    XL_UINT8 day;
    XL_UINT8 month;
    XL_UINT8 year;
    
}DAYMONTHYEAR;


typedef struct
{
    DAYMONTHYEAR date;
    XL_UINT16 time;
    XL_UINT16 times;
    
}AFNDF49;


