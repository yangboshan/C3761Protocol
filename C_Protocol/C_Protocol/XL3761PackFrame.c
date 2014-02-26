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
#include "XLUtility.h"


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
#define CF1 0x4a

//SEQ
#define SEQ 0x61

Byte* frame;
XL_UINT8 length = 0;
XL_UINT8 offset_ = 0;
static XL_UINT8 seqfield = 0;

//设置用户数据区DADT
void setuserdata(PACKITEM* userdata,XL_UINT8 count);


void setuserdatafor4(PACKITEM_P* userdata,XL_UINT8 count);

//设置校验和
void setchecksum(Byte* userdata);

//设置数据单元标识
void setdadt(XL_UINT16 pn,XL_UINT16 fn);

void setdata(XL_UINT16 num,XL_UINT8 ispn);

Byte getseq();

//十进制转BCD
void decimaltobcd(XL_FP64 dec,XL_UINT8 byteslen,XL_UINT8 digitlen);

//PACKITEM_P BuildPackItem(XL_FP64 value1,XL_UINT8 value1blen,XL_UINT8 value1dlen,XL_UINT8  value2[64],XL_UINT8  value2blen,XL_UINT8  shouldUseValue2,XL_UINT8  shouldUseBcd);

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


//Byte* PackFrameForAfn04F25(XL_UINT16 m1,XL_UINT16 m2,double v,double c,double l,Byte type){
//    return 0;
//}


//build packitem instance
PACKITEM_P BuildPackItem(XL_FP64 value1,XL_UINT8 value1blen,XL_UINT8 value1dlen,XL_UINT8  value2[64],XL_UINT8  value2blen,XL_UINT8  shouldUseValue2,XL_UINT8  shouldUseBcd){
    
    PACKITEM_P packItem;
    packItem.value1 = value1;
    packItem.value1blen = value1blen;
    packItem.value1dlen = value1dlen;
    
    if (value2blen>0) {
        for(int i = 0;i<value2blen;i++){
            packItem.value2[i] = value2[i];
        }
    }

    packItem.value2blen = value2blen;
    packItem.shouldUseValue2 = shouldUseValue2;
    packItem.shouldUseBcd = shouldUseBcd;
    
    return packItem;
}

//生成对时
Byte* PackFrameForClock(Byte afn,XL_UINT8 pn,XL_UINT8 fn,XL_UINT8 year,XL_UINT8 month,XL_UINT8 day,XL_UINT8 week,XL_UINT8 hour,XL_UINT8 mimute,XL_UINT8 second,XL_UINT16* outlen){
    
    // 星期四    1       2
    //1  0  0   1  | 0 0 2 0 -->星期四 12月
    XL_UINT8 weekmonth = ((week<<5 & 0xe0)|(month/10 <<4 & 0x10))|(month%10&0x0f);
    XL_UINT8  value[1];value[0] = weekmonth;
    
    PACKITEM_P array[6] = {
        BuildPackItem(second,    1, 0, 0, 0, 0, 1),
        BuildPackItem(mimute,    1, 0, 0, 0, 0, 1),
        BuildPackItem(hour,      1, 0, 0, 0, 0, 1),
        BuildPackItem(day,       1, 0, 0, 0, 0, 1),
        BuildPackItem(weekmonth, 0, 0, value, 1, 1, 0),
        BuildPackItem(year,      1, 0, 0, 0, 0, 1),
    };
    
    return PackFrameForAfn04(afn, pn, fn, array, 6, outlen);
}

//参数设置组帧接口
Byte* PackFrameForAfn04(Byte afn,XL_UINT8 pn,XL_UINT8 fn,PACKITEM_P array[],XL_UINT8 itemcount,XL_UINT16* outlen){
    
    XL_UINT8 userdatalen = 0;
    offset_ = 0;
    
    for(XL_UINT8 i = 0;i<itemcount;i++){
        
        PACKITEM_P item = array[i];
        
        //数据单元长度
        if (!item.shouldUseValue2) {
            userdatalen += item.value1blen;
        }else {
            userdatalen += item.value2blen;
        }
    }
    
    //数据单元标识
    userdatalen += 4;
    
    //C(1) Addr(5) AFN(1) SEQ(1) DADT
    userdatalen += 8;
    
    //密码域
    userdatalen += 16;
    
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
    frame[offset_++] = CF1;
    
    //地址域
    frame[offset_++]  = 0x00;frame[offset_++]  = 0x25;
    frame[offset_++]  = 0x01;frame[offset_++]  = 0x00;
    frame[offset_++]  = 0x04;
    
    //设置AFN
    frame[offset_++] = afn;
    
    //设置SEQ
    frame[offset_++] = getseq();
    
    setdadt(pn, fn);
    
    //设置用户数据
    setuserdatafor4(array,itemcount);
    
    for(int i = 0;i<16;i++){
        frame[offset_++] = 0x00;
    }
    
    //设置校验和
    setchecksum((frame + 6));
    
    //    for(int i = 0;i<length;i++){
    //        printf("%2x ",frame[i]);
    //    }
    
    return frame;
}

/*－－－－－－－－－－－－－－－－－
 设置参数用户数据区
 －－－－－－－－－－－－－－－－－*/
void setuserdatafor4(PACKITEM_P* userdata,XL_UINT8 count){

    for(XL_UINT8 i = 0;i < count;i++ ){
        PACKITEM_P item;
        item = userdata[i];
        
        //使用value2
        if (item.shouldUseValue2) {
            
            for(XL_UINT8 m = 0;m<item.value2blen;m++){
                
                frame[offset_++] = (Byte)item.value2[m];
            }
            
        }else{
            //使用Bcd
            if (item.shouldUseBcd) {
                Byte* tmp = decimaltobcd_s(item.value1,
                                           item.value1blen,
                                           item.value1dlen);
                
                for(XL_UINT8 k = 0;k < item.value1blen;k++){
                    
                    frame[offset_++] = tmp[k];
                }
                
                free(tmp);
            
            //BIN BS..
            } else {
                
                if (item.value1blen == 1) {
                    *(frame + offset_) = (XL_UINT8)item.value1;offset_++;
                    
                } else if (item.value1blen == 2){
                    *(XL_UINT16*)(frame + offset_) = (XL_UINT16)item.value1;offset_+=2;
                    
                } else if (item.value1blen == 4){
                    *(XL_UINT64*)(frame + offset_) = (XL_UINT64)item.value1;offset_+=4;
                    
                } else if(item.value1blen == 6){
                    *(XL_UINT64*)(frame + offset_) = (XL_UINT64)item.value1;
                    offset_ += 6;
                    
                }
            }
        }
    }
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
    frame[offset_++] = getseq();
    
    //设置用户数据
    setuserdata(array,itemcount);
    
    //设置校验和
    setchecksum((frame + 6));
    
//    for(int i = 0;i<length;i++){
//        printf("%2x ",frame[i]);
//    }
  
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
    
    //设置PN
    if (ispn) {
        
        //终端P0
        if (num == 0) {
            frame[offset_++] = 0x00;
            frame[offset_++] = 0x00;
            return;
        //测量点
        } else {
             group = (num - 1) / 8 + 1;
        }
    //设置FN
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

Byte getseq(){
    
    seqfield++;
    
    return 0x60|(seqfield & 0x0f);
}
