//
//  XL3761PackFrame.c
//  C_Protocol
//
//  组帧接口
//
//  Created by JY on 14-1-14.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "XL3761PackFrame.h"

//起始位
#define START 0x68

//结束
#define END 0x16

//协议类型
#define PROTOCOL 0x02

//ZERO
#define ZERO 0x00

//控制域
#define CF 0x4b

//SEQ
#define SEQ 0x61

Byte* frame;
XL_UINT8 length = 0;
XL_UINT8 offset_ = 0;

//设置用户数据区DADT
void setuserdata(PACKITEM* userdata,XL_UINT8 count);

//设置校验和
void setchecksum(Byte* userdata);

//设置数据单元标识
void setdadt(XL_UINT16 pn,XL_UINT16 fn);

void setdata(XL_UINT16 num,XL_UINT8 ispn);

//十进制转BCD
void decimaltobcd(XL_FP64 dec,XL_UINT8 byteslen,XL_UINT8 digitlen);


/*－－－－－－－－－－－－－－－－－
 组帧接口不带数据单元
 －－－－－－－－－－－－－－－－－*/
Byte* PackFrameWithDadt(Byte afn,XL_UINT8 pn,XL_UINT8 fn,XL_UINT16* outlen){
    
    PACKITEM dataitem;
    dataitem.fn = fn;dataitem.pn = pn;dataitem.datalen = 0;
    dataitem.shouldUseByte = 0;
    return PackFrame(afn, &dataitem, 1, outlen);
}


/*－－－－－－－－－－－－－－－－－
 二类数据日冻结类数据时标
 －－－－－－－－－－－－－－－－－*/
Byte* PackFrameWithTdd(Byte afn,XL_UINT8 pn,XL_UINT8 fn,XL_UINT8 year,XL_UINT8 month,XL_UINT8 day,XL_UINT16* outlen){
    PACKITEM dataitem;
    dataitem.fn = fn;dataitem.pn = pn;
    dataitem.data[0] = day;dataitem.data[1] = month;dataitem.data[2] = year;dataitem.datalen = 3;
    dataitem.shouldUseByte = 0;
    return PackFrame(afn, &dataitem, 1, outlen);
}


/*－－－－－－－－－－－－－－－－－
 二类数据月冻结类数据时标
 －－－－－－－－－－－－－－－－－*/
Byte* PackFrameWithTdm(Byte afn,XL_UINT8 pn,XL_UINT8 fn,XL_UINT8 year,XL_UINT8 month,XL_UINT16* outlen){
    PACKITEM dataitem;
    dataitem.fn = fn;dataitem.pn = pn;
    dataitem.data[0] = month;dataitem.data[1] = year;dataitem.datalen = 2;
    dataitem.shouldUseByte = 0;
    return PackFrame(afn, &dataitem, 1, outlen);
}


/*－－－－－－－－－－－－－－－－－
 曲线类数据时标
 －－－－－－－－－－－－－－－－－*/
Byte* PackFrameWithTdc(Byte afn,XL_UINT8 pn,XL_UINT8 fn,XL_UINT8 year,XL_UINT8 month,XL_UINT8 day,XL_UINT8 hour,XL_UINT8 mimute,XL_UINT8 density,XL_UINT8 points,XL_UINT16* outlen){
    PACKITEM dataitem;
    dataitem.fn = fn;dataitem.pn = pn;
    dataitem.data[0] = mimute;dataitem.data[1] = hour;dataitem.data[2] = day;dataitem.data[3] = month;
    dataitem.data[4] = year;dataitem.data[5] = density;dataitem.data[6] = points;dataitem.datalen = 7;
    dataitem.shouldUseByte = 0;
    return PackFrame(afn, &dataitem, 1, outlen);
}



/*－－－－－－－－－－－－－－－－－
 三类数据事件
 －－－－－－－－－－－－－－－－－*/
Byte* PackFrameForEvent(Byte afn,XL_UINT8 pn,XL_UINT8 fn,XL_UINT8 p1,XL_UINT8 p2,XL_UINT16* outlen){
    PACKITEM dataitem;
    dataitem.fn = fn;dataitem.pn = pn;
    dataitem.data[0] = p1;dataitem.data[1] = p2;dataitem.datalen = 2;
    dataitem.shouldUseByte = 1;
    return PackFrame(afn, &dataitem, 1, outlen);
}

/*－－－－－－－－－－－－－－－－－
 组合组帧接口
 －－－－－－－－－－－－－－－－－*/
Byte* PackFrame(Byte afn,PACKITEM array[],XL_UINT8 itemcount,XL_UINT16* outlen){
    
    XL_UINT8 userdatalen = 0;
    offset_ = 0;
    
    for(XL_UINT8 i = 0;i<itemcount;i++){
        
        PACKITEM item = array[i];
        
        //数据单元长度
        userdatalen += item.datalen;
        
        //数据单元标识
        userdatalen += 4;
    }
    
    //C(1) Addr(5) AFN(1) SEQ(1) DADT
    userdatalen += 8;
    
    //帧总长度 1 2 2 1 C(1) Addr(5)
    //    AFN(1) SEQ(1) DADT CS(1) 1
    length = userdatalen + 8;
    *outlen = length;
    
    frame = malloc(length);
    memset(frame, 0, length);

    frame[offset_++] = START;
    *(frame + 5) = START;
    *(frame + length -1) = END;
    
    XL_UINT16 lengthl = userdatalen<<2|PROTOCOL;
    
    //长度L1
    frame[offset_++] = (Byte)(lengthl & 0x00ff);
    frame[offset_++] = (Byte)((lengthl & 0xff00)>>8);
    
    //长度L2
    frame[offset_++] = *(frame+1);
    frame[offset_++] = *(frame+2);
    
    offset_++;
    
    //控制域
    frame[offset_++] = CF;
    
    //地址域
    frame[offset_++]  = 0x00;frame[offset_++]  = 0x25;
    frame[offset_++]  = 0x01;frame[offset_++]  = 0x00;
    frame[offset_++]  = 0x04;
    
    //设置AFN
    frame[offset_++] = afn;
    
    //设置SEQ
    frame[offset_++] = SEQ;
    
    //设置用户数据
    setuserdata(array,itemcount);
    
    //设置校验和
    setchecksum((frame + 6));
    
    for(int i = 0;i<length;i++){
        printf("%2x ",frame[i]);
    }
  
    return frame;
}

/*－－－－－－－－－－－－－－－－－
 设置用户数据区
 －－－－－－－－－－－－－－－－－*/
void setuserdata(PACKITEM* userdata,XL_UINT8 count){
    
    for(XL_UINT8 i = 0;i < count;i++ ){
        PACKITEM item;
        item = userdata[i];
        setdadt(item.pn, item.fn);
        
        //数据单元长度不为0
        if (item.datalen) {
            
            //***************参数设置部分待完善***************//
            if (item.shouldUseByte) {
                for(XL_UINT8 m = 0;m<item.datalen;m++){
                    frame[offset_++] = (Byte)item.data[m];
                }
            } else {
                for(XL_UINT8 n = 0;n<item.datalen;n++){
                    decimaltobcd(item.data[n],
                                 1,
                                 0);}
            }}
    }
}

/*－－－－－－－－－－－－－－－－－
 十进制转BCD
 －－－－－－－－－－－－－－－－－*/
void decimaltobcd(XL_FP64 dec,XL_UINT8 byteslen,XL_UINT8 digitlen){
    
    XL_UINT32 decimal = dec * pow(10, digitlen);
    XL_UINT32 temp;
    
    for(XL_UINT8 i = 0; i < byteslen; i++)
    {
        temp = decimal%100;
        
        frame[offset_++] = ((temp/10)<<4) + ((temp%10) & 0x0F);
        decimal /= 100;
    }
}

/*－－－－－－－－－－－－－－－－－
 生成校验和
 －－－－－－－－－－－－－－－－－*/
void setchecksum(Byte* userdata){
    
    Byte *pos = userdata;
    Byte total = 0;
    
    for ( int i =0; i < length - 8; ++i)
    {
        total += *pos;
        ++pos;
    }
    
    frame[length-2] = total;
}

/*－－－－－－－－－－－－－－－－－
 设置Pn Fn
 －－－－－－－－－－－－－－－－－*/
void setdadt(XL_UINT16 pn,XL_UINT16 fn){
    
    setdata(pn, 1);
    setdata(fn, 0);
}

/*－－－－－－－－－－－－－－－－－
 8        |0
 1 0 0 0  |0 0 0 0  8-----> 80
 
 7      |0
 0 1 0 0  |0 0 0 0  7-----> 40
 
 6    |0
 0 0 1 0  |0 0 0 0  6-----> 20
 
 5  |0
 0 0 0 1  |0 0 0 0  5-----> 10
 
 生成FN PN
 例如:  F16 ------> 80 01
 －－－－－－－－－－－－－－－－－*/
void setdata(XL_UINT16 num,XL_UINT8 ispn){
   
    XL_UINT16 group;
    
    if (ispn) {
        group = (num - 1) / 8 + 1;
    } else {
        group = (num - 1) / 8;
    }
    
    XL_UINT16 _num = (num - 1) % 8 + 1;
    
    if (_num > 4) {
        frame[offset_++] = ((Byte)pow(2,_num-1-4))<<4 & 0xf0;
    } else {
        frame[offset_++] = (Byte)pow(2, _num-1) & 0x0f;
    }
    
    frame[offset_++] = group;
}
