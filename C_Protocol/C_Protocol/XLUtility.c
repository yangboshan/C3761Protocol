//
//  XLUtility.c
//  C_Protocol
//
//  Created by JY on 14-1-14.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "XLUtility.h"
#include <math.h>


/*－－－－－－－－－－－－－－/
 解析DADT
 
 /－－－－－－－－－－－－－－*/
XL_UINT16 parsedadt(XL_UINT16 group,XL_UINT16 number,XL_UINT8 ispn){
    
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
            if (ispn) {
                tNumber = (group - 1) * 8 + 1 + i;
            } else {
                tNumber = group * 8 + 1 + i;
            }
        }
    }
    return tNumber;
}

/*－－－－－－－－－－－－－－/
 BCD转Double
 
 value buff
 byteslen 字节长度
 digitlen 小数位数
 /－－－－－－－－－－－－－－*/
XL_UINT64 bcdtouint(Byte* value,XL_UINT8 byteslen,XL_UINT8 digitlen)
{
    //num 转换的字节数
    XL_UINT64 result = 0;
    XL_UINT64 temp = 0;
    
    XL_UINT8 i =0;
    
    //判断是否是非法报文
    for(i = 0;i<byteslen; i++)
    {
        if(*(value + i) != 0xFF)//判断是否全部是FF
        {
            break;
        }
    }
    if(i == byteslen)
    {
        return ERRORDATA;
    }
    for(i = 0;i<byteslen; i++)
    {
        if(*(value + i) != 0xEE)//判断是否全部是EE
        {
            break;
        }
    }
    if(i == byteslen)
    {
        return ERRORDATA;
    }
    
    for(i =0;i<byteslen;i++)
    {
        temp   = (*(value + i)>>4 & 0x0f)*10 + (*(value + i) & 0x0f);
        result += temp * pow(10,2*i);
    }
//    result = result/pow(10,digitlen);
    return  result;
}

/*－－－－－－－－－－－－－－/
 BCD转有符号Double
 
 value buff
 byteslen 字节长度
 digitlen 小数位数
 /－－－－－－－－－－－－－－*/
XL_SINT64 bcdtosint(Byte* value,XL_UINT8 byteslen,XL_UINT8 digitlen){
    
    XL_UINT64 result =0;
    XL_UINT64 temp = 0;
    XL_UINT8 sign = 0;
    
    XL_UINT8 i =0;
    
    //判断是否是非法报文
    for(i = 0;i<byteslen; i++)
    {
        if(*(value + i) != 0xFF)//判断是否全部是FF
        {
            break;
        }
    }
    if(i == byteslen)
    {
        return ERRORDATA;
    }
    for(i = 0;i<byteslen; i++)
    {
        if(*(value + i) != 0xEE)//判断是否全部是EE
        {
            break;
        }
    }
    if(i == byteslen)
    {
        return ERRORDATA;
    }
    
    for(i =0;i<byteslen;i++)
    {
        if (i == byteslen -1) {
            sign = *(value + i)>>7 & 0x01;
            temp =(*(value + i)>>4 & 0x07)*10 +
                  (*(value + i) & 0x0f);
        } else {
            temp =(*(value + i)>>4 & 0x0f)*10 +
                  (*(value + i) & 0x0f);
        }
        result += temp * pow(10,2*i);
    }
//    result = result/pow(10,digitlen);
    
    if (sign) { return -result;}
    
    return  result;
}

/*－－－－－－－－－－－－－－/
 BCD转时间
 
 value buff
 /－－－－－－－－－－－－－－*/
Byte bcdToTime(Byte* value)
{
    Byte result =0;
    if((*value == 0xee) |(*value==0xff))
    {
        return 0xff;
    }
    
    result   = (Byte)(*(value)>>4 & 0x0f)*10 + (*(value) & 0x0f);
    return result;
}


/*－－－－－－－－－－－－－－－－－
 十进制转BCD
 －－－－－－－－－－－－－－－－－*/
Byte* decimaltobcd_s(XL_FP64 dec,XL_UINT8 byteslen,XL_UINT8 digitlen){
    
    
    XL_SINT64 decimal = dec * pow(10, digitlen + 1) / 10;
    XL_SINT64 temp;
    
    int flag =-1;
    
    flag = (dec<0)?1:0;
    
    if (dec<0) {
        decimal = -decimal;
    }
    
    Byte* value =malloc(byteslen);
    
    for(XL_UINT8 i = 0; i < byteslen; i++)
    {
        temp = decimal%100;
        value[i]=((temp/10)<<4) + ((temp%10) & 0x0F);
        decimal /= 100;
    }
    
    if(flag)
    {
        value[byteslen-1]=( value[byteslen-1]|0x80);
    }
    return value;
}


//获取a.2格式数据
XL_SINT16 a22intwithparam(Byte* value)
{
    XL_SINT16 result = ((*(Byte*)(value+1))&0x0F)*100;
    result += ((*(Byte*)(value)>>4)&0x0F)*10;
    result += ((*(Byte*)(value))&0x0F);
    if(((*(Byte*)(value+1))&0x10) > 0)
    {
        result = 0 - result;
    }
    return result;
}
//获取a.2格式幂数
XL_CHAR a2powvaluewithparam(Byte* value)
{
    switch(((*value)>>5)&0x07)
    {
        case 0:
            return 4;
        case 1:
            return 3;
        case 2:
            return 2;
        case 3:
            return 1;
        case 4:
            return 0;
        case 5:
            return -1;
        case 6:
            return -2;
        case 7:
            return -3;
        default:
            return 0;
    }
}


