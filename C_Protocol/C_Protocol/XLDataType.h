
//  XLDataType.h
//  C_Protocol
//
//  Created by JY on 14-1-6.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#ifndef C_Protocol_XLDataType_h
#define C_Protocol_XLDataType_h

typedef char                    XL_CHAR;
typedef unsigned char 			Byte;		/*无符号单字节*/
typedef unsigned char 			XL_UINT8;		/*无符号单字节*/
typedef signed   char 			XL_SINT8;		/*有符号单字节*/
typedef unsigned short int 		XL_UINT16;		/*无符号双字节*/
typedef signed	 short int		XL_SINT16;		/*有符号双字节*/
typedef unsigned       int		XL_UINT32;		/*无符号四字节*/
typedef signed         int		XL_SINT32;		/*有符号四字节*/
typedef unsigned long  long 	XL_UINT64;		/*无符号八字节*/
typedef signed   long  long		XL_SINT64;		/*有符号八字节*/
typedef unsigned long 			XL_OFFSET;		/*偏移量*/
typedef unsigned long			XL_ADDRESS;		/*地址*/
typedef float          			XL_FP32;		/*四字节浮点数*/
typedef double         			XL_FP64;		/*八字节浮点数*/
typedef unsigned int		    XL_MTRNUM;		/*测量点号数据类型*/
typedef unsigned int            XL_FIELDINDEX;  /*数据字典号类型*/

typedef unsigned short int      XL_UINT16_2;//2字节 无符号 两位小数×100格式
typedef signed short int        XL_SINT16_2;//2字节 有符号 两位小数×100格式

typedef unsigned short int      XL_UINT16_3;//2字节 无符号 三位小数×1000格式
typedef signed short int        XL_SINT16_3;//2字节 有符号 三位小数×1000格式

typedef unsigned int            XL_UINT32_2;//4字节 无符号 两位小数×100格式
typedef signed int              XL_SINT32_2;//4字节 有符号 两位小数×100格式

typedef unsigned int            XL_UINT32_4;//4字节 无符号 四位小数×10000格式
typedef signed int              XL_SINT32_4;//4字节 有符号 四位小数×10000格式

typedef unsigned long  long     XL_UINT64_4;//8字节 无符号 四位小数×10000格式
typedef signed long  long       XL_SINT64_4;//8字节 有符号 四位小数×10000格式


#define AFN00 0x00
#define AFN04 0x04
#define AFN0A 0x0a
#define AFN0C 0x0c
#define AFN0D 0x0d
#define AFN0E 0x0e


#define NONECHAR		0xff				/*字节型无效数据类型*/
#define APP_NONECHAR	0xee				/*字节型无效数据类型*/

#define NONEWORD		0xffff		        /*双字节型无效数据类型*/
#define APP_NONEWORD	0xeeee				/*双字节型无效数据类型*/

#define SRCLL            0xffffffffffLL
#define NONELLWORD 	     0xffffffffffffffffLL		/*八字节型无效数据类型*/
#define NONELWORD		 0xffffffffL			    /*四字节型无效数据类型*/
#define APP_NONELLWORD	 0xeeeeeeeeeeeeeeeeLL	    /*八字节型无效数据类型*/
#define APP_NONELWORD    0xeeeeeeeeL                /*四字节型无效数据类型*/
#define DEFAULT_EN_PARA	 99999990000LL
#define DEFAULT_EN_PARA1 999999999999LL


#define XL_INLINE inline
#define XL_TRUE 1
#define XL_FALSE 0
#define XL_NULL 0

#define XL_ERROR -1
#define XL_NORMAL 1
#define XL_CONFIRM 1
#define XL_DENY 2
#define ERRORDATA 0xFFFFFFFFFFFFFFFF
#define XL_CV96 60


#pragma pack(1)
typedef struct{
    
    XL_UINT16 pn;
    XL_UINT16 fn;
    XL_UINT8  data[50];
    XL_UINT8  datalen;
    XL_UINT8  digitlen;
    XL_UINT8  shouldUseByte;
}PACKITEM;

typedef struct{
    
    //十进制数值
    XL_FP64 value1;
    
    XL_UINT8 value1blen;
    
    XL_UINT8 value1dlen;
    
    //字节
    XL_UINT8  value2[64];
    
    //字节长度
    XL_UINT8  value2blen;
    
    //是否使用数值OR字节 flag
    XL_UINT8  shouldUseValue2;
    
    //是否使用BCD
    XL_UINT8  shouldUseBcd;
    
}PACKITEM_P;



#endif

