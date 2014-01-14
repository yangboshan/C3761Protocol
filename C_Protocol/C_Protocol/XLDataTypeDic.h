//
//  XLDictionaryDataType.h
//  C_Protocol
//
//  Created by JY on 14-1-8.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#ifndef C_Protocol_XLDataTypeDic_h
#define C_Protocol_XLDataTypeDic_h
#include "XLDataType.h"

//类型列表
enum typelist {
    A1 = 0,
    A2,
    A3,
    A4,
    A5,
    A6,
    A7,
    A8,
    A9,
    A10,
    A11,
    A12,
    A13,
    A14,
    A15,
    A16,
    A17,
    A18,
    A19,
    A20,
    A21,
    A22,
    A23,
    A24,
    A25,
    A26,
    A27,
    A28,
    BIN1,
    BIN2,
    BIN3,
    BIN4,
}DATATYPE;

//终端日统计数据
const int terminal_day_sta[] =
{
    A20,
    BIN2,
    BIN2
};

//终端日统计数据
const int terminal_month_sta[] =
{
    A21,
    BIN2,
    BIN2
};


#endif


