//
//  XLUtility.c
//  C_Protocol
//
//  Created by JY on 14-1-14.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#include <stdio.h>
#include "XLUtility.h"
#include <math.h>

//解析DADT
XL_UINT16 parseFnwithGroup(XL_UINT16 group,XL_UINT16 number){
    
    XL_UINT16 tNumber = 0;
    
    for (int i = 7; i >= 0;i--)
    {
        Byte mask;
        
        if (i>=4) {
            mask = ((Byte)pow(2, i-4))<<4 & 0xf0;
            
        } else {
            mask = (Byte)pow(2, i) & 0x0f;
        }
        
        if((number & mask) >> i)
        {
            tNumber = group * 8 + 1 + i;
        }
    }
    return tNumber;
}