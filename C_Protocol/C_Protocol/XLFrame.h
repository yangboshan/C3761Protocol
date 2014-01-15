//
//  XLFrame.h
//  C_Protocol
//
//  Created by JY on 14-1-7.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#ifndef C_Protocol_XLFrame_h
#define C_Protocol_XLFrame_h
#include "XLDataType.h"

#pragma pack(1)

typedef struct
{
	Byte pwLen;
	Byte pw[16];
	
	Byte tpLen;
	Byte tp[6];
    
    XL_UINT8 hasEC;
    XL_UINT8 hasPW;
    XL_UINT8 hasTP;
    
}AUX_INFO;

//序号seq
typedef union
{
	struct {
		Byte pseq:4; //帧序号范围为0~15,反馈帧序号从pseq开始
		Byte con:1;  //是否需要确认
		Byte fin:1;  //最后一帧标识
		Byte fir:1;  //第一帧标识
		Byte tpv:1;  //aux中tp 是否有效0:无效 1:有效
	}bit;
	Byte seq;
}FRAME_SEQ;

//控制码
//D7	        D6  	    D5	       D4             D3~D0
//传输方向位DIR	启动标志位PRM	帧计数位FCB 帧计数有效位FCV	  功能码
//                                               ACD
typedef union
{
	struct {
		Byte code:4;    //功能码
		Byte fcv:1;     //计数有效位
		Byte fcbacd:1;  //帧计数位or 要求访问位
		Byte prm:1;     //启动标志位
		Byte dir:1;     //传输方向位
	}bit;
	Byte c;
}FRAME_CONTROL;

typedef struct {
    
    XL_UINT16 framelen;         //帧长
    XL_UINT16 userlen;          //用户数据长度
    
    //地址
	XL_UINT16 districtCode; 	//地市区码A1
	XL_UINT16 terminalAddr; 	//终端地址A2
	Byte  masterAddr;		    //主站地址A3
    
	//广播/组/剔除标识
	Byte broadcastAddrFlag; 	//终端地址广播标识1:广播地址，0:非广播
	Byte taGroupAddrFlag; 		//终端地址组标识:0,单地址；1：组地址
	Byte taOmitFlag;		    //终端状态投入剔除标识, 0 :没有投入，1，投入
    
	//用户数据域信息
	FRAME_CONTROL control;			//控制码C
	Byte afn;  			            //AFN
	FRAME_SEQ seq; 		            //帧序号信息
	AUX_INFO aux; 		            //附加信息,pw ,tp等
    Byte *frameData;                //用户数据
    
}FRAME;
#endif


