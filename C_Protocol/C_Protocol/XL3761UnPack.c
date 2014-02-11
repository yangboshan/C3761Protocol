//
//  XL3761UnPack.c
//  chand
//
//  Created by JY on 14-1-6.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "XLFrame.h"
#include "XL3761UnPack.h"

#include "XL3761AFN0.h"
#include "XL3761AFNA.h"
#include "XL3761AFNC.h"
#include "XL3761AFND.h"
#include "XL3761AFNE.h"



Byte* framedata;

FRAME *frame;

//帧检查
XL_SINT32 FrameCheck();

XL_SINT32 ParseUserDataLength();

//校验和
Byte CheckSum(Byte *data,XL_UINT16 len);

//解析基本结构
void ParseStructure();

//分发报文到具体处理区
XL_SINT32 HandOutFrame(XL_SINT16 *output,XL_UINT16* outlen,Byte** outbuf);


//－－－－－－－－－－－－－－－－－
//
//解帧入口
//
//－－－－－－－－－－－－－－－－－
XL_SINT32 UnPackFrame(XL_SINT16 *output, XL_UINT16 inlen,Byte *inbuf,XL_UINT16* outlen,Byte** outbuf,int* multiFrameFlag){
    
    //初始化Frame结构
    frame = malloc(sizeof(FRAME));
    memset(frame, 0, sizeof(FRAME));
    
    //拷贝报文到FrameData
    framedata = (XL_UINT8*)malloc(inlen);
    memcpy(framedata,inbuf,inlen);
    
    //报文长度
    frame->framelen = inlen;

    //帧检查
    if (FrameCheck() == XL_ERROR) {
        return XL_ERROR;
    }
    
    //解析基本结构
    ParseStructure(multiFrameFlag);
    
    //分发解析
    if(HandOutFrame(output,outlen,outbuf) == XL_ERROR){
        return XL_ERROR;
    }
    
    return XL_NORMAL;
}


//帧检查
XL_SINT32 FrameCheck(){
    
    //检查帧头帧尾
    if (framedata[0]!=0x68
     || framedata[5]!=0x68
     || framedata[frame->framelen-1]!=0x16) {
        
        return XL_ERROR;
    }
    
    //解析用户数据长度
    frame->userlen = ParseUserDataLength();
    
    //检查校验和
    if (framedata[frame->framelen -2]!=
        CheckSum(&framedata[6], frame->userlen)) {
        return XL_ERROR;
    }
    return XL_NORMAL;
}


//检测协议类型 解析用户数据长度
XL_SINT32 ParseUserDataLength(){
    XL_UINT16 length = *(XL_UINT16*)(framedata + 1);
    if ((length & 0x0003) != 0x2) {
        return XL_ERROR;
    }
    
    return length>>2;
}

//计算校验和
Byte CheckSum(Byte *data,XL_UINT16 len){
    
    Byte value = 0;
    
    for(XL_UINT16 i = 0;i<len;i++){
        
        value += data[i];
    }
    return value;
}

//解析基本结构
void ParseStructure(int* multiFrameFlag){
    
    XL_UINT16 _offset = 6;
    
    //解析控制域
    frame->control.c = framedata[_offset++];

    //解析地址
    frame->districtCode = (XL_UINT16)(framedata + _offset);
    _offset+=2;
    
    frame->terminalAddr = (XL_UINT16)(framedata + _offset);
    _offset+=2;
    
    frame->masterAddr =  (Byte)(framedata + _offset++);
    
    //解析功能码
    frame->afn = framedata[_offset++];
    
    //解析SEQ
    frame->seq.seq =     framedata[_offset++];
    
    //判断是否多帧以及后续有无后续帧
    if(!frame->seq.bit.fir&&!frame->seq.bit.fin)
    {
        //多帧，有后续帧
        *multiFrameFlag=1;
    }
    if(!frame->seq.bit.fir&&frame->seq.bit.fin)
    {
        //多帧，结束帧
        *multiFrameFlag=0;
    }
    if(frame->seq.bit.fir&&!frame->seq.bit.fin)
    {
        //多帧，第一帧 有后续帧
        *multiFrameFlag=1;
    }
    
    if(frame->seq.bit.fir&&frame->seq.bit.fin)
    {
        //单帧
        *multiFrameFlag=0;
    }
    
    if (frame->seq.bit.tpv) {
        frame->aux.hasTP = 1;
    }
    
    if (frame->control.bit.dir && frame->control.bit.fcbacd) {
        frame->aux.hasEC = 1;
    }

    //SEQ后用户数据区
    Byte* userdata = malloc(frame->userlen - 3);
    memcpy(userdata, framedata+_offset,frame->userlen - 3);
    frame->frameData = userdata;
    
    free(framedata);
}

//分发处理报文
XL_SINT32 HandOutFrame(XL_SINT16 *output,XL_UINT16* outlen,Byte** outbuf){
    
    switch (frame->afn) {
            
        //确认否认
        case AFN00:
            initUserDataForAfn0(output,frame,outlen,outbuf);
            break;
        
        case AFN04:
            break;
        
        //查询参数
        case AFN0A:
            initUserDataForAfna(output,frame,outlen,outbuf);
            break;
            
        //一类数据
        case AFN0C:
            initUserDataForAfnc(output,frame,outlen,outbuf);
            break;
         
        //二类数据
        case AFN0D:
            initUserDataForAfnd(output,frame,outlen,outbuf);
            break;
            
        //三类数据
        case AFN0E:
            initUserDataForAfne(output,frame,outlen,outbuf);
            break;
            
        default:{
            return XL_ERROR;
        }
    }
    
    return XL_NORMAL;
}