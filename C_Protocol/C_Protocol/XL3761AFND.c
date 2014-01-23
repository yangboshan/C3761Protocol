//
//  XL3761AFND.c
//  chand
//
//  Created by JY on 14-1-6.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "XL3761AFND.h"
#include "XLDataId.h"
#include "XLCommon.h"
#include "XLUtility.h"


void RecursiveParse();

void AFND_F1();
void AFND_F2();
void AFND_F3();


void AFND_F17();
void AFND_F18();
void AFND_F26();
void AFND_F27();
void AFND_F28();
void AFND_F29();
void AFND_F30();
void AFND_F33();
void AFND_F34();
void AFND_F35();
void AFND_F36();
void AFND_F37();
void AFND_F38();

void AFND_F43();
void AFND_F44();
void AFND_F49();


void AFND_F50();
void AFND_F51();
void AFND_F52();
void AFND_F53();
void AFND_F54();


void AFND_F81();
void AFND_F82();
void AFND_F83();
void AFND_F84();
void AFND_F85();
void AFND_F86();
void AFND_F87();
void AFND_F88();
void AFND_F89();
void AFND_F90();

void AFND_F91();
void AFND_F92();
void AFND_F93();
void AFND_F94();
void AFND_F95();


void AFND_F105();
void AFND_F106();
void AFND_F107();
void AFND_F108();

void AFND_F113();
void AFND_F114();
void AFND_F115();
void AFND_F116();
void AFND_F117();
void AFND_F118();

void AFND_F129();
void AFND_F130();
void AFND_F138();
void AFND_F161();
void AFND_F162();
void AFND_F163();
void AFND_F164();

void AFND_F177();
void AFND_F178();
void AFND_F179();
void AFND_F180();


void AFND_F193();
void AFND_F194();
void AFND_F195();
void AFND_F196();



void initUserDataForAfnd(XL_SINT16 *output,void *frame,XL_UINT16* outlen,Byte** outbuf){
    
    printf("解析文件AFND\n");
    
    //偏移初始化
    offset=0;
    outoffset = 0;
    
    _output = output;
    _outlen = outlen;
    _outbuf = outbuf;
    
    _frame = (FRAME*)frame;
    
    userdata = _frame->frameData;
    
    buff = malloc(_frame->userlen*3 + 50);
    memset(buff,0,_frame->userlen*3 + 50);
    *_outbuf = buff;
    
    RecursiveParse();
    *outlen = outoffset;
    
    free(userdata);
    free(_frame);
    
    //用完之后,将outoffset置位初值0
	outoffset = 0;
    offset = 0;
}

void RecursiveParse(){
    
    XL_UINT16 fn = parsedadt((XL_UINT16)userdata[offset + 3],
                                    (XL_UINT16)userdata[offset + 2],0);
    
    //拷贝
    memcpy(buff + outoffset, userdata + offset, 1); offset+=2;outoffset++;
    
    memcpy(buff + outoffset, &fn, 1);                offset+=2;outoffset++;
    
    switch (fn) {
        case 1:
            AFND_F1();//日冻结正向有/无功电能示值、一/四象限无功电能示值（总、费率1～M，1≤M≤12
            break;
        case 2:
            AFND_F2();//日冻结反向有／无功电能示值，二／三象限无功电能示值
            break;
        case 3:
            AFND_F3();//日冻结正向有／无功最大需量及发生时间（总、费率1～m）
            break;
        case 17:
            AFND_F17();//月冻结正向有／无功电能示值、一／四象限无功电能示值（总、费率1～m）
            break;
        case 18:
            AFND_F18();//月冻结反向有／无功电能示值、二／三象限无功电能示值（总、费率1～m）
            break;
        case 26:
            AFND_F26();//日冻结日总及分相最大需量及发生时间
            break;
        case 27:
            AFND_F27();//日冻结日电压统计数据
            break;
        case 28:
            AFND_F28();//日冻结日不平衡度越限累计时间
            break;
        case 29:
            AFND_F29();//日冻结日电流越限数据
            break;
        case 30:
            AFND_F30();//日冻结日视在功率越限累计时间
            break;
        case 33:
            AFND_F33();//月冻结月总及分相最大有功功率及发生时间、有功功率为零时间
            break;
            
        case 34:
            AFND_F34();//月冻结月总及分相有功最大需量及发生时间
            break;
        case 35:
            AFND_F35();//月冻结月电压统计数据
            break;
        case 36:
            AFND_F36();//月冻结月不平衡度越限累计时间
            break;
        case 37:
            AFND_F37();//月冻结月电流越限数据
            break;
            
        case 38:
            AFND_F38();//月冻结月视在功率越限累计时间
            break;
            
        case 43:
            AFND_F43();//日冻结日功率因素区段累计时间
            break;
        case 44:
            AFND_F44();//月冻结月功率因素区段累计时间
            break;
        case 49:
            AFND_F49();//日冻结终端月供电时间+日复位累计次数
            break;
            
        case 50:
            AFND_F50();//日冻结终端日控制统计数据
            break;
        case 51:
            AFND_F51();//月冻结终端月供电时间+月复位累计次数
            
            break;
            
        case 52:
            AFND_F52();//月冻结终端月控制统计数据
            break;
            
        case 53:
            AFND_F53();//终端与主站日通信流量
            break;
        case 54:
            AFND_F54();//终端与主站月通信流量
            break;
            
        case 81:
            AFND_F81();//测量点有功功率曲线
            break;
        case 82:
            AFND_F82();//测量点A相有功功率曲线
            break;
            
        case 83:
            AFND_F83();//测量点B相有功功率曲线
            break;
            
        case 84:
            AFND_F84();//测量点C相有功功率曲线
            break;
            
        case 85:
            AFND_F85();//测量点无功功率曲线
            break;
            
        case 86:
            AFND_F86();//测量点A相无功功率曲线
            break;
            
        case 87:
            AFND_F87();//测量点B相无功功率曲线
            break;
            
        case 88:
            AFND_F88();//测量点C相无功功率曲线
            break;
            
        case 89:
            AFND_F89();//测量点A相电压曲线
            break;
            
        case 90:
            AFND_F90();//测量点B相电压曲线
            break;
            
        case 91:
            AFND_F91();//测量点C相电压曲线
            break;
        case 92:
            AFND_F92();//测量点A相电流曲线
            break;
        case 93:
            AFND_F93();//测量点B相电流曲线
            break;
        case 94:
            AFND_F94();//测量点C相电流曲线
            break;
        case 95:
            AFND_F95();//测量点零序电流曲线
            break;
        case 105:
            AFND_F105();//测量点功率因素曲线
            break;
        case 106:
            AFND_F106();//测量点A相功率因素曲线
            break;
        case 107:
            AFND_F107();//测量点B相功率因素曲线
            break;
        case 108:
            AFND_F108();//测量点C相功率因素曲线
            break;
            
        case 113:
            AFND_F113();//日冻结测量点A相2—19次谐波电流日最大值及发生时间
            break;
        case 114:
            AFND_F114();//日冻结测量点B相2—19次谐波电流日最大值及发生时间
            break;
        case 115:
            AFND_F115();//日冻结测量点C相2—19次谐波电流日最大值及发生时间
            break;
        case 116:
            AFND_F116();//日冻结测量点A相2—19次谐波电压含有率及总畸变率日最大值及发生时间
            break;
        case 117:
            AFND_F117();//日冻结测量点B相2—19次谐波电压含有率及总畸变率日最大值及发生时间
            break;
        case 118:
            AFND_F118();//日冻结测量点C相2—19次谐波电压含有率及总畸变率日最大值及发生时间
            break;
        case 129:
            AFND_F129();//日冻结直流模拟量日越限日累计时间、最大／最小值及发生时间
            break;
        case 130:
            AFND_F130();//月冻结直流模拟量越限月累计时间、最大／最小值及发生时间
            break;
        case 138:
            AFND_F138();//直流模拟量数据曲线
            break;
        case 161:
            AFND_F161();//日冻结正向有功电能示值（总、费率1~m）
            break;
        case 162:
            AFND_F162();//日冻结正向无功（组合无功1）电能示值（总、费率1~m
            break;
        case 163:
            AFND_F163();//日冻结反向有功电能示值（总、费率1~m）
            break;
        case 164:
            AFND_F164();//日冻结反向无功（组合无功1）电能示值（总、费率1~m）
            break;
        case 177:
            AFND_F177();//月冻结正向有功电能示值（总、费率1～m）
            break;
        case 178:
            AFND_F178();//月冻结正向无功（组合无功1）电能示值（总、费率1～m）
            break;
        case 179:
            AFND_F179();//月冻结反向有功电能示值（总、费率1～m）
            break;
        case 180:
            AFND_F180();//月冻结反向无功（组合无功1）电能示值（总、费率1～m）
            break;
        case 193:
            AFND_F193();//月冻结正向有功最大需量及发生时间（总、费率1～m）
            break;
        case 194:
            AFND_F194();//月冻结正向无功最大需量及发生时间（总、费率1～m）
            break;
        case 195:
            AFND_F195();//月冻结反向有功最大需量及发生时间（总、费率1～m）
            break;
        case 196:
            AFND_F196();//月冻结反向无功最大需量及发生时间（总、费率1～m）
            break;
        default:
            *_output = XL_ERROR;
            return;
    }
    
    XL_UINT16 auxlen = 0;
    if (_frame->aux.hasEC) {
        auxlen += 2;
    }
    if (_frame->aux.hasTP) {
        auxlen += 6;
    }
    
    if (_frame->userlen - 8 > offset + auxlen) {
        RecursiveParse();
    }
}

//日冻结正向有/无功电能示值、一/四象限无功电能示值（总、费率1～M，1≤M≤12）
void AFND_F1()
{
    
    
    printf("执行F1\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_day_powervalue; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    //数据标志  2个字节
    identifier = hdDataTime_mdp;// 数据时标
    
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    
    //终端抄表时间  5个字节  分时日月年 数据标识  不需要解析
    offset+=5;
    
    
    
    //费率数  1个字节
    rateCount=*(userdata+offset);;   //将费率数保存
    offset++;
    
    
    
    
    //正向有功总电能示值  5个字节 BCD码 需要转换 格式1.14
    //置标识
    
    identifier =hdPosAEValueZ; //正向有功总电能示值
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 精确到万分位  A.14-万分位  4个小数点
    temp   =bcdtouint(userdata+offset, 5, 4);
    
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=5;
    
    if(rateCount==0)
    {
        //费率数为0处理
    }
    
    //    for(i=0;i<rateCount;i++)//取四个费率的值
    for(i=0;i<4;i++)
    {
        //费率i正向有功电能示值  5个字节  bcd码需要转换
        
        if(i==0)
        {
            identifier =hdPosAEValue1;
        }
        else
        {
            identifier++;
        }
        //需要置数据标识
        memcpy(buff+outoffset, &identifier, 2);
        outoffset+=2;
        
        
        temp   =bcdtouint(userdata+offset, 5, 4);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=5;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*5;
    }
    
    //正向无功总电能示值  4个字节  bcd码需要转换
    //需要置数据标识
    identifier=hdPosREValueZ;
    memcpy(buff+outoffset, &identifier, 2);
    outoffset+=2;
    //数据内容  精确到百分位 表A.11-2个小数点
    temp   =bcdtouint(userdata+offset, 4, 2);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    
    //费率1～m正向无功电能示值
    //    for(i=0;i<rateCount;i++)  //取四个费率的值
    for(i=0;i<4;i++)
    {
        //费率i正向无功电能示值  4个字节  bcd码需要转换
        //需要置数据标识
        
        if(i==0)
        {
            identifier =hdPosREValue1;
        }
        else
        {
            identifier++;
        }
        //需要置数据标识
        memcpy(buff+outoffset, &identifier, 2);
        outoffset+=2;
        
        
        temp   =bcdtouint(userdata+offset, 4, 2);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=4;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    //一象限无功总电能示值  4个字节 bcd码
    //置标识
    identifier =hdFirstREValueZ;
    memcpy(buff+outoffset, &identifier, 2);
    outoffset+=2;
    
    //数据
    temp   =bcdtouint(userdata+offset, 4, 2);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    //    for(i=0;i<rateCount;i++)  //取四个费率的值
    for(i=0;i<4;i++)
    {
        //置标识
        //费率i一象限无功总电能示值  4个字节
        
        if(i==0)
        {
            identifier =hdFirstREValue1;
        }
        else
        {
            identifier++;
        }
        //需要置数据标识
        memcpy(buff+outoffset, &identifier, 2);
        outoffset+=2;
        
        
        temp   =bcdtouint(userdata+offset, 4, 2);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=4;
        
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    
    
    
    //四象限无功总电能示值  4个字节  bcd码
    //置标识
    identifier =hdFourREValueZ;
    memcpy(buff+outoffset, &identifier, 2);
    outoffset+=2;
    
    //数据
    temp   =bcdtouint(userdata+offset, 4, 2);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    //    for(i=0;i<rateCount;i++)//取四个费率的值
    for(i=0;i<4;i++)
    {
        //费率i四象限无功电能示值  4个字节  bcd吗
        //置标志
        
        if(i==0)
        {
            identifier =hdFourREValue1;
        }
        else
        {
            identifier++;
        }
        //需要置数据标识
        memcpy(buff+outoffset, &identifier, 2);
        outoffset+=2;
        
        
        temp   =bcdtouint(userdata+offset, 4, 2);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=4;
        
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//日冻结反向有／无功电能示值，二／三象限无功电能示值
void AFND_F2()
{
    
    
    printf("执行F2\n");
    
    //1个字节长度  类型
    buff[outoffset] = measure_day_powervalue; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    //标志 2个字节
    identifier = hdDataTime_mdp;// 数据时标
    
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    
    
    
    //终端抄表时间，不保存到输出缓冲区
    offset+=5;
    
    rateCount =*(Byte*)(userdata+offset);  //费率数
    offset++;
    
    
    
    //反响有功总电能示值   5个字节
    //置标志
    identifier=hdNegAEValueZ;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  5个字节
    
    temp  =bcdtouint(userdata+offset, 5, 4);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=5;
    
    //费率i反向有功电能示值  只取4个费率的数据  5个字节
    //    for(i=0;i<rateCount;i++)
    for(i=0;i<4;i++)
    {
        //置标志  2个字节
        if(i==0)
        {
            identifier =hdNegAEValue1; //费率1反向有功电能示值
        }
        else
        {
            identifier++;
        }
        //将标志拷贝到输出缓冲区
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        
        //数据内容  5个字节
        temp   =bcdtouint(userdata+offset, 5, 4);
        memcpy(buff + outoffset, &temp, 8);
        outoffset+=8;
        offset+=5;
        
    }
    
    if(rateCount>4)
    {
        offset+=(rateCount-4)*5;
    }
    
    //反向无功总电能示值 4个字节
    identifier =hdNegREValueZ;
    //将标志拷贝到输出缓冲区
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节  2个小数点
    temp   =bcdtouint(userdata+offset, 4, 2);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    //费率i反向无功电能示值
    //    for(i=0;i<rateCount;i++)
    for(i=0;i<4;i++)
    {
        if(i==0)
        {
            identifier=hdNegREValue1;
        }
        else
        {
            identifier++;
        }
        
        //将标志拷贝到输出缓冲区
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        
        //数据内容  4个字节  2个小数点
        temp=bcdtouint(userdata+offset, 4, 2);
        memcpy(buff + outoffset, &temp, 8);
        outoffset+=8;
        offset+=4;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    //二象限无功总电能示值  4个字节
    //置标志
    identifier=hdSecondREValueZ;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 4个字节 2个小数点
    temp=bcdtouint(userdata+offset, 4, 2);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    
    //费率i二象限无功电能示值    取4个费率的值
    //    for(i=0;i<rateCount;i++)
    for(i=0;i<4;i++)
    {
        
        if(i==0)
        {
            identifier=hdSecondREValue1;
        }
        else
        {
            identifier++;
        }
        //置标志
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        
        //数据内容
        temp=bcdtouint(userdata+offset, 4, 2);
        memcpy(buff + outoffset, &temp, 8);
        outoffset+=8;
        offset+=4;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    
    //三象限无功总电能示值  4个字节
    //置标志
    identifier=hdThirdREValueZ;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 4个字节 2个小数点
    temp=bcdtouint(userdata+offset, 4, 2);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    
    //费率i三象限无功电能示值    取4个费率的值
    //    for(i=0;i<rateCount;i++)
    for(i=0;i<4;i++)
    {
        
        if(i==0)
        {
            identifier=hdThirdREValue1;
        }
        else
        {
            identifier++;
        }
        //置标志
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        
        //数据内容
        temp=bcdtouint(userdata+offset, 4, 2);
        memcpy(buff + outoffset, &temp, 8);
        outoffset+=8;
        offset+=4;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
}

//日冻结正向有／无功最大需量及发生时间（总、费率1～m）
void AFND_F3()
{
    
    printf("执行F3\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = history_day_powerneeds; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    
    //标志 2个字节
    identifier = hdDataTime_hdp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    
    
    
    //终端抄表时间，不保存到输出缓冲区
    offset+=5;
    
    rateCount =*(Byte*)(userdata+offset);  //费率数
    offset++;
    
    
    //正向有功总最大需量 3个值 4个小数点 万分位
    //置标志
    identifier =hdPosADMaxZ;
    memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=3;
    
    
    //费率i正向有功最大需量
    for(i=0;i<4;i++)
    {
        //置标志
        if(i==0)
        {
            identifier=hdPosADMax1;
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
        
        //数据内容
        temp=bcdtouint(userdata+offset, 3, 4);
        memcpy(buff + outoffset, &temp, 8);
        outoffset+=8;
        offset+=3;
    }
    
    if(rateCount>4)
    {
        offset+=(rateCount-4)*3;
    }
    //正向有功总最大需量发生时间  4个字节
    //置标志
    identifier=hdPosADMaxZTm;
    memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
    //数据内容  4个字节  分时日月  bcd格式
    buff[outoffset]=bcdToTime(userdata+offset);  //分
    offset++;  outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //时
    offset++;   outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //日
    offset++;   outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //月
    offset++;   outoffset++;
    
    //费率i正向有功最大需量发生时间 4个字节 取4个费率
    for(i=0;i<4;i++)
    {
        //置标志
        if(i==0)
        {
            identifier=hdPosADMax1Tm;
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
        //数据内容 4个字节
        buff[outoffset]=bcdToTime(userdata+offset);  //分
        offset++;  outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //时
        offset++;   outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //日
        offset++;   outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //月
        offset++;   outoffset++;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    //正向无功总最大需量 3个值 4个小数点 万分位
    //置标志
    identifier =hdPosRDMaxZ;
    memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=3;
    
    
    //费率i正向无功最大需量
    for(i=0;i<4;i++)
    {
        //置标志
        if(i==0)
        {
            identifier=hdPosRDMax1;
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
        
        //数据内容
        temp=bcdtouint(userdata+offset, 3, 4);
        memcpy(buff + outoffset, &temp, 8);
        outoffset+=8;
        offset+=3;
    }
    
    if(rateCount>4)
    {
        offset+=(rateCount-4)*3;
    }
    //正向无功总最大需量发生时间  4个字节
    //置标志
    identifier=hdPosRDMaxZTm;
    memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
    //数据内容  4个字节  分时日月  bcd格式
    buff[outoffset]=bcdToTime(userdata+offset);  //分
    offset++;  outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //时
    offset++;   outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //日
    offset++;   outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //月
    offset++;   outoffset++;
    
    //费率i正向无功最大需量发生时间 4个字节 取4个费率
    for(i=0;i<4;i++)
    {
        //置标志
        if(i==0)
        {
            identifier=hdPosRDMax1Tm;
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
        //数据内容 4个字节
        buff[outoffset]=bcdToTime(userdata+offset);  //分
        offset++;  outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //时
        offset++;   outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //日
        offset++;   outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //月
        offset++;   outoffset++;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
////日冻结反向有／无功最大需量及发生时间（总、费率1～m）
//void AFND_F4()
//{
//
//
//}
////日冻结正向有功电能量（总、费率1～m）
//void AFND_F5()
//{
//
//
//}
////日冻结正向无功电能量（总、费率1～m）
//void AFND_F6()
//{
//
//
//}
////日冻结反向有功电能量（总、费率1～m）
//void AFND_F7()
//{
//
//
//}
////日冻结反向无功电能量（总、费率1～m）
//void AFND_F8()
//{
//
//
//}
////抄表日冻结正向有／无功电能示值、一／四象限无功电能示值（总、费1～m）
//void AFND_F9()
//{
//
//
//}
////抄表日冻结反向有／无功电能示值，二／三象限无功电能示值（总、费率1～m）
//void AFND_F10()
//{
//
//
//}
////抄表日冻结电能表正向有／无功最大需量及发生时间（总、费率1～m）
//void AFND_F11()
//{
//
//
//}
////抄表日冻结电能表反向有／无功最大需量及发生时间（总、费率1～m）
//void AFND_F12()
//{
//
//
//}

//无F13
//void AFND_F13()
//{
//
//
//}

//void AFND_F14()
//{
//
//
//}
//void AFND_F15()
//{
//
//
//}
//void AFND_F16()
//{
//
//
//}
//月冻结正向有／无功电能示值、一／四象限无功电能示值（总、费率1～m）
void AFND_F17()
{
    
    printf("执行F17\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_month_powervalue; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    
    //标志 2个字节
    identifier = hmDataTime_mmp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容 2个字节 月年 bcd码
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //终端抄表时间 不存储
    offset+=5;
    
    
    //费率数
    rateCount=*(Byte*)(userdata+offset);
    offset++;
    
    
    //月正向有功总电能示值
    //置标志
    identifier =hmPosAEValueZ;
    memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
    
    //内容
    temp=bcdtouint(userdata+offset,5,4);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=5;
    
    //费率i月正向有功电能示值
    for(i=0;i<4;i++)
    {
        
        if(i==0)
        {
            identifier=hmPosAEValue1;
        }
        else
        {
            identifier++;
        }
        //置标志
        memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
        //数据内容
        temp=bcdtouint(userdata+offset,5,4);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=5;
        
    }
    
    if(rateCount>4)
    {
        offset+=(rateCount-4)*5;
    }
    
    //月冻结正向无功总电能示值
    //置标志
    identifier =hmPosREValueZ;
    memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
    
    //内容
    temp=bcdtouint(userdata+offset,4,2);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    //费率i月正向无功总电能示值
    for(i=0;i<4;i++)
    {
        
        if(i==0)
        {
            identifier=hmPosREValue1;
        }
        else
        {
            identifier++;
        }
        //置标志
        memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
        //数据内容
        temp=bcdtouint(userdata+offset,4,2);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=4;
        
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    //月冻结一象限无功总电能示值
    identifier =hmFirstREValueZ;
    memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
    
    //内容
    temp=bcdtouint(userdata+offset,4,2);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    //费率i一象限无功电能示值
    for(i=0;i<4;i++)
    {
        
        if(i==0)
        {
            identifier=hmFirstREValue1;
        }
        else
        {
            identifier++;
        }
        //置标志
        memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
        //数据内容
        temp=bcdtouint(userdata+offset,4,2);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=4;
        
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    //月冻结四象限无功总电能示值
    identifier =hmFourREValueZ;
    memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
    
    //内容
    temp=bcdtouint(userdata+offset,4,2);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    //费率i四象限无功电能示值
    for(i=0;i<4;i++)
    {
        
        if(i==0)
        {
            identifier=hmFourREValue1;
        }
        else
        {
            identifier++;
        }
        //置标志
        memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
        //数据内容
        temp=bcdtouint(userdata+offset,4,2);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=4;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//月冻结反向有／无功电能示值、二／三象限无功电能示值（总、费率1～m）
void AFND_F18()
{
    
    printf("执行F18\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_month_powervalue; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    
    //标志 2个字节
    identifier = hmDataTime_mmp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容 2个字节 月年 bcd码
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //终端抄表时间 不存储
    offset+=5;
    
    
    //费率数
    rateCount=*(Byte*)(userdata+offset);
    offset++;
    
    
    //月冻结反向有功总电能示值
    //置标志
    identifier =hmNegAEValueZ;
    memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
    
    //内容
    temp=bcdtouint(userdata+offset,5,4);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=5;
    
    //费率i月反向有功电能示值
    for(i=0;i<4;i++)
    {
        
        if(i==0)
        {
            identifier=hmNegAEValue1;
        }
        else
        {
            identifier++;
        }
        //置标志
        memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
        //数据内容
        temp=bcdtouint(userdata+offset,5,4);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=5;
        
    }
    
    if(rateCount>4)
    {
        offset+=(rateCount-4)*5;
    }
    
    //月冻结反向无功总电能示值
    //置标志
    identifier =hmNegREValueZ;
    memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
    
    //内容
    temp=bcdtouint(userdata+offset,4,2);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    //费率i月反向无功电能示值
    for(i=0;i<4;i++)
    {
        
        if(i==0)
        {
            identifier=hmNegREValue1;
        }
        else
        {
            identifier++;
        }
        //置标志
        memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
        //数据内容
        temp=bcdtouint(userdata+offset,4,2);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=4;
        
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    //月冻结二象限无功总电能示值
    identifier =hmSecondREValueZ;
    memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
    
    //内容
    temp=bcdtouint(userdata+offset,4,2);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    //费率i二象限无功电能示值
    for(i=0;i<4;i++)
    {
        
        if(i==0)
        {
            identifier=hmSecondREValue1;
        }
        else
        {
            identifier++;
        }
        //置标志
        memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
        //数据内容
        temp=bcdtouint(userdata+offset,4,2);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=4;
        
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    //月冻结三象限无功总电能示值
    identifier =hmThirdREValueZ;
    memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
    
    //内容
    temp=bcdtouint(userdata+offset,4,2);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    //费率i三象限无功电能示值
    for(i=0;i<4;i++)
    {
        
        if(i==0)
        {
            identifier=hmThirdREValue1;
        }
        else
        {
            identifier++;
        }
        //置标志
        memcpy(buff+outoffset, &identifier, 2); outoffset+=2;
        //数据内容
        temp=bcdtouint(userdata+offset,4,2);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=4;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
}
//月冻结电能表正向有／无功最大需量及发生时间（总、费率1～m）
//void AFND_F19()
//{
//
//
//}
////月冻结电能表反向有／无功最大需量及发生时间（总、费率1～m）
//void AFND_F20()
//{
//
//
//}
////月冻结正向有功电能量（总、费率1～m）
//void AFND_F21()
//{
//
//
//}
////月冻结正向无功电能量（总、费率1～m）
//void AFND_F22()
//{
//
//
//}
//
////月冻结反向有功电能量（总、费率1～m）
//void AFND_F23()
//{
//
//
//}
////月冻结反向无功电能量（总、费率1～m）
//void AFND_F24()
//{
//
//
//}
//日冻结日总及分享最大有功功率及发生时间、有功功率为零时间
//void AFND_F25()
//{
//
//
//}
//日冻结日总及分相最大需量及发生时间
void AFND_F26()
{
    printf("执行F26\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = history_day_powerneeds; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    //    int  i =0;
    //    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;  //将小数转换城成整数保存
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    //标志 2个字节
    identifier = hdDataTime_hdp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容 3个字节 日月年 bcd码
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //三相有功最大需量  3个字节  4个小数点，精确到万分位
    //置标志
    identifier = hdADMaxZ;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    //三相有功最大需量发生时间  3个字节 分时日
    //置标志
    identifier = hdADMaxZTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //A相有功最大需量  3个字节  4个小数点，精确到万分位
    //置标志
    identifier = hdADMaxA;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    //A相有功最大需量发生时间  3个字节 分时日
    //置标志
    identifier = hdADMaxATm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //B相有功最大需量  3个字节  4个小数点，精确到万分位
    //置标志
    identifier = hdADMaxB;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    //B相有功最大需量发生时间  3个字节 分时日
    //置标志
    identifier = hdADMaxBTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //C相有功最大需量  3个字节  4个小数点，精确到万分位
    //置标志
    identifier = hdADMaxC;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    //C相有功最大需量发生时间  3个字节 分时日
    //置标志
    identifier = hdADMaxCTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//日冻结日电压统计数据
void AFND_F27()
{
    printf("执行F27\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_day_sta; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    XL_UINT16 temp_value=0;//
    //    int  i =0;
    //    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;  //将小数转换城成整数保存
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    //标志 2个字节
    identifier = hdDataTime_mds;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容 3个字节 日月年 bcd码
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    
    //数据内容
    //标志：A相电压越上上限日累计时间  2个字节
    identifier = hdAVoltOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //标志：A相电压越下下限日累计时间  2个字节
    identifier = hdAVoltDownLLAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //A相电压越上限日累计时间
    identifier = hdAVoltOverHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //A相电压越下限日累计时间
    identifier = hdAVoltDownLoAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    
    //A相电压合格日累计时间
    identifier = hdAVoltRegularAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    
    //标志：B相电压越上上限日累计时间  2个字节
    identifier = hdBVoltOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //标志：B相电压越下下限日累计时间  2个字节
    identifier = hdBVoltDownLLAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //B相电压越上限日累计时间
    identifier = hdBVoltOverHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //B相电压越下限日累计时间
    identifier = hdBVoltDownLoAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    
    //B相电压合格日累计时间
    identifier = hdBVoltRegularAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    
    //标志：C相电压越上上限日累计时间  2个字节
    identifier = hdCVoltOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //标志：C相电压越下下限日累计时间  2个字节
    identifier = hdCVoltDownLLAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //C相电压越上限日累计时间
    identifier = hdCVoltOverHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //C相电压越下限日累计时间
    identifier = hdCVoltDownLoAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    //C相电压合格日累计时间
    identifier = hdCVoltRegularAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //A相电压最大值   2个字节 1个小数点，精确到十分位
    //标志
    identifier = hdAVoltMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节，1个小数点
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    
    //A相电压最大值发生时间   3个字节
    identifier = hdAVoltMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  分时日  3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //A相电压最小值  2个字节 1个小数点，精确到十分位
    identifier = hdAVoltMin;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节，1个小数点
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    //A相电压最小值发生时间   3个字节
    identifier = hdAVoltMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  分时日  3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //B相电压最大值   2个字节 1个小数点，精确到十分位
    //标志
    identifier = hdBVoltMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节，1个小数点
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    
    //B相电压最大值发生时间   3个字节
    identifier = hdBVoltMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  分时日  3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //B相电压最小值  2个字节 1个小数点，精确到十分位
    identifier = hdBVoltMin;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节，1个小数点
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    //B相电压最小值发生时间   3个字节
    identifier = hdBVoltMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  分时日  3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    
    
    //C相电压最大值   2个字节 1个小数点，精确到十分位
    //标志
    identifier = hdCVoltMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节，1个小数点
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    
    //C相电压最大值发生时间   3个字节
    identifier = hdCVoltMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  分时日  3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //C相电压最小值  2个字节 1个小数点，精确到十分位
    identifier = hdCVoltMin;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节，1个小数点
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    //C相电压最小值发生时间   3个字节
    identifier = hdCVoltMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  分时日  3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    //A相平均电压 2个字节 1个小数点，精确到十分位
    //置标志
    identifier = hdAVoltAvg;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    
    
    //B相平均电压 2个字节 1个小数点，精确到十分位
    //置标志
    identifier = hdBVoltAvg;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    
    //C相平均电压 2个字节 1个小数点，精确到十分位
    //置标志
    identifier = hdCVoltAvg;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    
    
    
    /**********A25格式  第三个字节为符号位 ***************/
    
    
    //A相电压越上限率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hdAVoltOverHiRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    
    //A相电压越下限率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hdAVoltDownLoRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    //A相电压合格率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hdAVoltRegularRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    
    
    //B相电压越上限率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hdBVoltOverHiRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    
    //B相电压越下限率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hdBVoltDownLoRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    //B相电压合格率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hdBVoltRegularRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    //C相电压越上限率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hdBVoltOverHiRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    
    //C相电压越下限率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hdBVoltDownLoRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    //C相电压合格率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hdBVoltRegularRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//日冻结日不平衡度越限累计时间
void AFND_F28()
{
    printf("执行F28\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_day_sta; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    XL_UINT16 temp_value=0;//
    //    int  i =0;
    //    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;  //将小数转换城成整数保存
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    //标志 2个字节
    identifier = hdDataTime_mds;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    // 数据内容 3个字节 bcd码
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //数据内容
    //电流不平衡度越限日累计时间  两个字节
    //标志 2个字节
    identifier = hdCurUnbalOLmtAccTm;//
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    //电压不平衡度越限日累计时间  两个字节
    //标志 2个字节
    identifier = hdVoltUnbalOLmtAccTm;//
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //电流不平衡度最大值   1个小数点
    //标志 2个字节
    identifier = hdCurUnbalMax;//
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节 1个小数点 十分位
    temp=bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp_value, 8);outoffset+=8;offset+=2;
    
    //电流不平衡最大值发生时间
    identifier = hdCurUnbalMaxTm;//
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 3个字节  分时日
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //电压不平衡度最大值   1个小数点
    //标志 2个字节
    identifier = hdVoltUnbalMax;//
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节 1个小数点 十分位
    temp=bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp_value, 8);outoffset+=8;offset+=2;
    
    //电压不平衡最大值发生时间
    identifier = hdVoltUnbalMaxTm;//
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 3个字节  分时日
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//日冻结日电流越限数据
void AFND_F29()
{
    printf("执行F29\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_day_sta; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    XL_UINT16 temp_value=0;//
    //    int  i =0;
    //    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;  //将小数转换城成整数保存
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    //标志 2个字节
    identifier = hdDataTime_mds;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    // 数据内容 3个字节 bcd码
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //数据内容
    //A相电流越上上限累计时间  2个字节
    //置标志
    identifier = hdACurOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    //A相电流越上限累计时间  2个字节
    //置标志
    identifier = hdACurOverHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    
    //B相电流越上上限累计时间  2个字节
    //置标志
    identifier = hdBCurOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    //B相电流越上限累计时间  2个字节
    //置标志
    identifier = hdBCurOverHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //C相电流越上上限累计时间  2个字节
    //置标志
    identifier = hdCCurOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    //C相电流越上限累计时间  2个字节
    //置标志
    identifier = hdCCurOverHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //零序电流越上限累计时间  2个字节
    //置标志
    identifier = hdZeroCurOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    /********数据格式   A.25 有符号位 **************************/
    //A相电流最大值   3个字节  有符号位 3个小数点
    identifier = hdACurMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 3个字节
    temp =bcdtosint(userdata+offset, 3, 3);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    //A相电流最大值发生时间  3个字节  分时日
    //标志
    identifier = hdACurMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容 分时日 3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //B相电流最大值   3个字节  有符号位 3个小数点
    identifier = hdBCurMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 3个字节
    temp =bcdtosint(userdata+offset, 3, 3);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    //B相电流最大值发生时间  3个字节  分时日
    //标志
    identifier = hdBCurMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容 分时日 3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //C相电流最大值   3个字节  有符号位 3个小数点
    identifier = hdCCurMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 3个字节
    temp =bcdtosint(userdata+offset, 3, 3);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    //C相电流最大值发生时间  3个字节  分时日
    //标志
    identifier = hdCCurMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容 分时日 3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //零序电流最大值   3个字节  有符号位 3个小数点
    identifier = hdZeroCurMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 3个字节
    temp =bcdtosint(userdata+offset, 3, 3);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    //零序电流最大值发生时间  3个字节  分时日
    //标志
    identifier = hdZeroCurMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容 分时日 3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
}
//日冻结日视在功率越限累计时间
void AFND_F30()
{
    
    printf("执行F30\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_day_sta; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    XL_UINT16 temp_value=0;//
    //    int  i =0;
    //    Byte rateCount =0;  //费率数
    // XL_SINT64 temp  =0;  //将小数转换城成整数保存
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    //标志 2个字节
    identifier = hdDataTime_mds;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    // 数据内容 3个字节 bcd码
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //视在功率越上上限累计时间
    //标志 2个字节
    identifier = hdAPOverHHAccTm;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;offset+=2;
    
    //视在功率越上限累计时间
    //标志 2个字节
    identifier = hdAPOverHiAccTm;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;offset+=2;
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//日负载率统计
//void AFND_F31()
//{
//
//
//}
////日冻结电能表断相数据
//void AFND_F32()
//{
//
//
//}
//月冻结月总及分相最大有功功率及发生时间、有功功率为零时间
void AFND_F33()
{
    
    
    printf("执行F33\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_month_sta; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    XL_UINT16 temp_value=0;//
    //    int  i =0;
    //    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;  //将小数转换城成整数保存
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    //标志 2个字节
    identifier = hmDataTime_mms;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    // 数据内容 2个字节 bcd码
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //三相总最大有功功率 3个字节  4个小数位数
    identifier = hmAPMaxZ;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    //三相总最大有功功率发生时间 3个字节，分时日
    identifier = hmAPMaxZTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    //A相总最大有功功率 3个字节  4个小数位数
    identifier = hmAPMaxA;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    //A相总最大有功功率发生时间 3个字节，分时日
    identifier = hmAPMaxATm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //B相总最大有功功率 3个字节  4个小数位数
    identifier = hmAPMaxB;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    //B相总最大有功功率发生时间 3个字节，分时日
    identifier = hmAPMaxBTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //C相总最大有功功率 3个字节  4个小数位数
    identifier = hmAPMaxC;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    //C相总最大有功功率发生时间 3个字节，分时日
    identifier = hmAPMaxCTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //三相总有功功率为零时间  2个字节
    identifier = hmAPZeroAccTmZ;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //A相总有功功率为零时间  2个字节
    identifier = hmAPZeroAccTmA;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    //B相总有功功率为零时间  2个字节
    identifier = hmAPZeroAccTmB;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    //C相总有功功率为零时间  2个字节
    identifier = hmAPZeroAccTmC;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//月冻结月总及分相有功最大需量及发生时间
void AFND_F34()
{
    
    printf("执行F34\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = history_month_powerneeds; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    //XL_UINT16 temp_value=0;//
    //    int  i =0;
    //    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;  //将小数转换城成整数保存
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    //标志 2个字节
    identifier = hmDataTime_hmp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    // 数据内容 2个字节 bcd码
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    //总有功最大需量  3个字节 四个小数位数
    //标志 2个字节
    identifier = hmADMaxZ;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    //时间标志
    identifier = hmADMaxZTm;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //总有功最大需量发生时间  3个字节 分时日
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    //A相有功最大需量  3个字节 四个小数位数
    //标志 2个字节
    identifier = hmADMaxA;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    
    //时间标志
    identifier = hmADMaxATm;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //A相有功最大需量发生时间  3个字节 分时日
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //B相有功最大需量  3个字节 四个小数位数
    //标志 2个字节
    identifier = hmADMaxB;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    //时间标志
    identifier = hmADMaxBTm;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //B相有功最大需量发生时间  3个字节 分时日
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    //C相有功最大需量  3个字节 四个小数位数
    //标志 2个字节
    identifier = hmADMaxC;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    
    //时间标志
    identifier = hmADMaxCTm;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //C相有功最大需量发生时间  3个字节 分时日
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//月冻结月电压统计数据
void AFND_F35()
{
    
    
    printf("执行F35\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_month_sta; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    XL_UINT16 temp_value=0;//
    //    int  i =0;
    //    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;  //将小数转换城成整数保存
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    //标志 2个字节
    identifier = hmDataTime_hmp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    // 数据内容 2个字节 bcd码
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //数据内容
    //标志：A相电压越上上限月累计时间  2个字节
    identifier = hmAVoltOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //标志：A相电压越下下限月累计时间  2个字节
    identifier = hmAVoltDownLLAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //A相电压越上限月累计时间
    identifier = hmAVoltOverHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //A相电压越下限月累计时间
    identifier = hmAVoltDownLoAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    
    //A相电压合格月累计时间
    identifier = hmAVoltRegularAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    
    //标志：B相电压越上上限月累计时间  2个字节
    identifier = hmBVoltOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //标志：B相电压越下下限月累计时间  2个字节
    identifier = hmBVoltDownLLAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //B相电压越上限月累计时间
    identifier = hmBVoltOverHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //B相电压越下限月累计时间
    identifier = hmBVoltDownLoAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    
    //B相电压合格月累计时间
    identifier = hmBVoltRegularAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    
    //标志：C相电压越上上限月累计时间  2个字节
    identifier = hmCVoltOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //标志：C相电压越下下限月累计时间  2个字节
    identifier = hmCVoltDownLLAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //C相电压越上限月累计时间
    identifier = hmCVoltOverHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //C相电压越下限月累计时间
    identifier = hmCVoltDownLoAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    //C相电压合格月累计时间
    identifier = hmCVoltRegularAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp_value =*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //A相电压最大值   2个字节 1个小数点，精确到十分位
    //标志
    identifier = hmAVoltMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节，1个小数点
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    
    //A相电压最大值发生时间   3个字节
    identifier = hmAVoltMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  分时日  3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //A相电压最小值  2个字节 1个小数点，精确到十分位
    identifier = hmAVoltMin;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节，1个小数点
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    //A相电压最小值发生时间   3个字节
    identifier = hmAVoltMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  分时日  3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //B相电压最大值   2个字节 1个小数点，精确到十分位
    //标志
    identifier = hmBVoltMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节，1个小数点
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    
    //B相电压最大值发生时间   3个字节
    identifier = hmBVoltMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  分时日  3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //B相电压最小值  2个字节 1个小数点，精确到十分位
    identifier = hmBVoltMin;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节，1个小数点
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    //B相电压最小值发生时间   3个字节
    identifier = hmBVoltMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  分时日  3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    
    
    //C相电压最大值   2个字节 1个小数点，精确到十分位
    //标志
    identifier = hmCVoltMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节，1个小数点
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    
    //C相电压最大值发生时间   3个字节
    identifier = hmCVoltMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  分时日  3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //C相电压最小值  2个字节 1个小数点，精确到十分位
    identifier = hmCVoltMin;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节，1个小数点
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    //C相电压最小值发生时间   3个字节
    identifier = hmCVoltMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  分时日  3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    //A相平均电压 2个字节 1个小数点，精确到十分位
    //置标志
    identifier = hmAVoltAvg;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    
    
    //B相平均电压 2个字节 1个小数点，精确到十分位
    //置标志
    identifier = hmBVoltAvg;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    
    //C相平均电压 2个字节 1个小数点，精确到十分位
    //置标志
    identifier = hmCVoltAvg;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    
    
    
    /**********A25格式  第三个字节为符号位 ***************/
    
    
    //A相电压越上限率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hmAVoltOverHiRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    
    //A相电压越下限率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hmAVoltDownLoRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    //A相电压合格率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hmAVoltRegularRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    
    
    //B相电压越上限率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hmBVoltOverHiRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    
    //B相电压越下限率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hmBVoltDownLoRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    //B相电压合格率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hmBVoltRegularRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    //C相电压越上限率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hmBVoltOverHiRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    
    //C相电压越下限率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hmBVoltDownLoRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    
    //C相电压合格率  3个字节  3个小数点，精确到千分位
    //置标志
    identifier = hmBVoltRegularRate;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    temp =bcdtosint(userdata+offset, 3, 1);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
}
//月冻结月不平衡度越限累计时间
void AFND_F36()
{
    //与f28类似
    printf("执行F36\n");
    
    //1个字节长度  数据类型measure_day_sta
    buff[outoffset] = measure_month_sta; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    XL_UINT16 temp_value=0;//
    //    int  i =0;
    //    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;  //将小数转换城成整数保存
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    //标志 2个字节
    identifier = hmDataTime_mms;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    // 数据内容 2个字节 bcd码
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    //数据内容
    //电流不平衡度越限月累计时间  两个字节
    //标志 2个字节
    identifier = hmCurUnbalOLmtAccTm;//
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    //电压不平衡度越限月累计时间  两个字节
    //标志 2个字节
    identifier = hmVoltUnbalOLmtAccTm;//
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //电流不平衡度最大值   1个小数点
    //标志 2个字节
    identifier = hmCurUnbalMax;//
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节 1个小数点 十分位
    temp=bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp_value, 8);outoffset+=8;offset+=2;
    
    //电流不平衡最大值发生时间
    identifier = hmCurUnbalMaxTm;//
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 3个字节  分时日
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //电压不平衡度最大值   1个小数点
    //标志 2个字节
    identifier = hmVoltUnbalMax;//
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节 1个小数点 十分位
    temp=bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp_value, 8);outoffset+=8;offset+=2;
    
    //电压不平衡最大值发生时间
    identifier = hmVoltUnbalMaxTm;//
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 3个字节  分时日
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//月冻结月电流越限数据
void AFND_F37()
{
    //与f29相似   测量点月冻结统计数据
    
    printf("执行F37\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_month_sta; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    XL_UINT16 temp_value=0;//
    //    int  i =0;
    //    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;  //将小数转换城成整数保存
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    //标志 2个字节
    identifier = hmDataTime_mms;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    // 数据内容 2个字节 bcd码
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //数据内容
    //A相电流越上上限累计时间  2个字节
    //置标志
    identifier = hmACurOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    //A相电流越上限累计时间  2个字节
    //置标志
    identifier = hmACurOverHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    
    //B相电流越上上限累计时间  2个字节
    //置标志
    identifier = hmBCurOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    //B相电流越上限累计时间  2个字节
    //置标志
    identifier = hmBCurOverHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //C相电流越上上限累计时间  2个字节
    //置标志
    identifier = hmCCurOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    //C相电流越上限累计时间  2个字节
    //置标志
    identifier = hmCCurOverHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //零序电流越上限累计时间  2个字节
    //置标志
    identifier = hmZeroCurOverHHAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 2个字节
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    /********数据格式   A.25 有符号位 **************************/
    //A相电流最大值   3个字节  有符号位 3个小数点
    identifier = hmACurMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 3个字节
    temp =bcdtosint(userdata+offset, 3, 3);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    //A相电流最大值发生时间  3个字节  分时日
    //标志
    identifier = hmACurMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容 分时日 3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //B相电流最大值   3个字节  有符号位 3个小数点
    identifier = hmBCurMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 3个字节
    temp =bcdtosint(userdata+offset, 3, 3);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    //B相电流最大值发生时间  3个字节  分时日
    //标志
    identifier = hmBCurMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容 分时日 3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //C相电流最大值   3个字节  有符号位 3个小数点
    identifier = hmCCurMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 3个字节
    temp =bcdtosint(userdata+offset, 3, 3);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    //C相电流最大值发生时间  3个字节  分时日
    //标志
    identifier = hmCCurMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容 分时日 3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //零序电流最大值   3个字节  有符号位 3个小数点
    identifier = hmZeroCurMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 3个字节
    temp =bcdtosint(userdata+offset, 3, 3);
    memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    //零序电流最大值发生时间  3个字节  分时日
    //标志
    identifier = hmZeroCurMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容 分时日 3个字节
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
    
}
//月冻结月视在功率越限累计时间
void AFND_F38()
{
    //与f30类似
    printf("执行F38\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_month_sta; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    XL_UINT16 temp_value=0;//
    //    int  i =0;
    //    Byte rateCount =0;  //费率数
    // XL_SINT64 temp  =0;  //将小数转换城成整数保存
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    //标志 2个字节
    identifier = hmDataTime_mms;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    // 数据内容 2个字节 bcd码
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //视在功率越上上限累计时间
    //标志 2个字节
    identifier = hmAPOverHHAccTm;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;offset+=2;
    
    //视在功率越上限累计时间
    //标志 2个字节
    identifier = hmAPOverHiAccTm;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;offset+=2;
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//月负载率统计
//void AFND_F39()
//{
//
//
//}
////void AFND_F40()
////{
////
////    //无F40
////}
////日冻结电容器累计投入时间和次数
//void AFND_F41()
//{
//
//
//}
////日冻结日、月电容器累计补偿的无功电能量
//void AFND_F42()
//{
//
//
//}
//日冻结日功率因素区段累计时间
void AFND_F43()
{
    
    printf("执行F43\n");
    
    //1个字节长度  数据类型  测量点统计数据
    buff[outoffset] = measure_day_sta; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    XL_UINT16 temp_value=0;//
    //    int  i =0;
    //    Byte rateCount =0;  //费率数
    // XL_SINT64 temp  =0;  //将小数转换城成整数保存
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    //标志 2个字节
    identifier = hdDataTime_mds;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容  3个字节 日月年
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //区段1累计时间  2个字节
    //标志
    identifier = hdPfSector1AccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //区段2累计时间  2个字节
    //标志
    identifier = hdPfSector2AccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //区段3累计时间  2个字节
    //标志
    identifier = hdPfSector3AccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//月冻结月功率因素区段累计时间
void AFND_F44()
{
    
    //与f43类似
    printf("执行F44\n");
    
    //1个字节长度  数据类型  测量点统计数据
    buff[outoffset] = measure_month_sta; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    XL_UINT16 temp_value=0;//
    //    int  i =0;
    //    Byte rateCount =0;  //费率数
    // XL_SINT64 temp  =0;  //将小数转换城成整数保存
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    //标志 2个字节
    identifier = hmDataTime_mms;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容  3个字节 日月年
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //区段1累计时间  2个字节
    //标志
    identifier = hmPfSector1AccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //区段2累计时间  2个字节
    //标志
    identifier = hmPfSector2AccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //区段3累计时间  2个字节
    //标志
    identifier = hmPfSector3AccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //内容
    temp_value=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
}
//日冻结铜损、铁损有功电能示值
//void AFND_F45()
//{
//
//
//}
////月冻结铜损、铁损有功电能示值
//void AFND_F46()
//{
//
//
//}
//
//void AFND_F47()
//{
//
//
//}
//void AFND_F48()
//{
//
//
//}

//日冻结终端月供电时间
//日复位累计次数
void AFND_F49(){
    printf("执行F49\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = terminal_day_sta; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;
    
    //    buff[outoffset] = terminal_day_sta; outoffset++;
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = hdDataTime_tds;
    
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    
    //    buff[outoffset] = terminal_day_sta; outoffset++;
    
    XL_UINT16 tempvalue = 0;
    
    identifier = hdPowerOnAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    tempvalue = *(XL_UINT16*)(userdata + offset);offset += 2;
    
    memcpy(buff + outoffset, &tempvalue, 2);outoffset+=2;
    
    
    //    buff[outoffset] = terminal_day_sta; outoffset++;
    identifier = hdResetAccCnt;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    tempvalue = *(XL_UINT16*)(userdata + offset);offset += 2;
    memcpy(buff + outoffset, (XL_UINT16*)(userdata + offset), 2);outoffset+=2;
    
    end = outoffset;
    
    XL_UINT16 len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
}
//日冻结终端日控制统计数据
void AFND_F50()
{
    //先不做
    //需量类数据
    printf("执行F50\n");
    
    //    //1个字节长度  数据类型  测量点统计数据
    //    buff[outoffset] = measure_month_sta; outoffset++;
    //
    //    outoffset+=2;
    //
    //    XL_UINT16 begin=0;
    //    XL_UINT16 end=0;
    //    XL_UINT16 identifier=0;
    //    XL_UINT16 temp_value=0;//
    //    //    int  i =0;
    //    //    Byte rateCount =0;  //费率数
    //    // XL_SINT64 temp  =0;  //将小数转换城成整数保存
    //    XL_UINT16 len=0;  //输出缓冲区数据长度
    //
    //
    //    begin = outoffset;//数据长度起始位置
    //    //标志 2个字节
    //    identifier = hmDataTime_mms;// 数据时标
    //    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
}
//月冻结终端月供电时间
//月复位累计次数
void AFND_F51(){
    
    //与f49一样
    
    printf("执行F51\n");
    //1个字节长度  数据类型
    buff[outoffset] = terminal_month_sta; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;
    
    //    buff[outoffset] = terminal_day_sta; outoffset++;
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = hmDataTime_tms;
    
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    
    XL_UINT16 tempvalue = 0;
    //    buff[outoffset] = terminal_day_sta; outoffset++;
    identifier = hmPowerOnAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    tempvalue = *(XL_UINT16*)(userdata + offset);offset += 2;
    memcpy(buff + outoffset, &tempvalue, 2);outoffset+=2;
    
    
    //    buff[outoffset] = terminal_day_sta; outoffset++;
    identifier = hmResetAccCnt;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    tempvalue = *(XL_UINT16*)(userdata + offset);offset += 2;
    memcpy(buff + outoffset, &tempvalue, 2);outoffset+=2;
    
    end = outoffset;
    XL_UINT16 len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//月冻结终端月控制统计数据
void AFND_F52()
{
    //与f50类似  先不做
    printf("执行F52\n");
    //    //1个字节长度  数据类型
    //    buff[outoffset] = terminal_month_sta; outoffset++;
    //
    //    outoffset+=2;   //数据长度起始偏移
    //
    //    XL_UINT16 begin;
    //    XL_UINT16 end;
    //
    //    begin = outoffset;
    //
    //    //    buff[outoffset] = terminal_day_sta; outoffset++;
    //
    //    XL_UINT16 identifier;  //标志  2个字节
    //    identifier = hmDataTime_tms;
    //
    //    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    
    
}

//终端与主站日通信流量
void AFND_F53()
{
    printf("执行F53\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = terminal_day_sta; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    begin = outoffset;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = hdDataTime_tds;
    
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //日
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    //月
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    //年
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    
    identifier = hdCommFlow;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //通信流量 4个字节
    memcpy(buff + outoffset, (XL_UINT32*)(userdata + offset), 2);offset += 2;outoffset+=4;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//终端与主站月通信流量
void AFND_F54()
{
    //与f53相同
    printf("执行F54\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = terminal_month_sta; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    begin = outoffset;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = hmDataTime_tms;
    
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    //月
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    //年
    buff[outoffset] = (*(Byte*)(userdata + offset)>>4 &0x0f) * 10 + (*(Byte*)(userdata + offset)&0x0f);offset++;outoffset++;
    
    
    identifier = hmCommFlow;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    memcpy(buff + outoffset, (XL_UINT32*)(userdata + offset), 2);offset += 2;outoffset+=4;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//void AFND_F55()
//{
//
//
//}
//void AFND_F56()
//{
//
//
//}
//日冻结总加组日最大、最小有功功率及其发生时间、有功功率为零时间
//void AFND_F57()
//{
//
//
//}
//日冻结总加组日累计有功电能量（总、费率1～m）
//void AFND_F58()
//{
//
//
//}
//////日冻结总加组日累计无功电能量（总、费率1～m）
//void AFND_F59()
//{
//
//
//}
////月冻结总加组日最大、最小有功功率及其发生时间、有功功率为零时间
//void AFND_F60()
//{
//
//
//}
////月冻结总加组月有功电能量（总、费率1～m）
//void AFND_F61(){
//    printf("执行F51\n");
//}
////月冻结总加组月无功电能量（总、费率1～m）
//void AFND_F62()
//{
//
//
//}
//
////无f63
////void AFND_F63()
////{
////
////
////}
////无f64
////void AFND_F64()
////{
////
////
////}
////月冻结总加组超功率定值的月累计时间及月累计电能量
//void AFND_F65()
//{
//
//
//}
////月冻结总加组超月电能量定值的月累计时间及月累计电能量
//void AFND_F66()
//{
//
//
//}
////无67
////void AFND_F67()
////{
////
////
////}
////void AFND_F68()
////{
////
////
////}void AFND_F69()
////{
////
////
////}
////void AFND_F70()
////{
////
////
////}
////void AFND_F71()
////{
////
////
////}
////void AFND_F72()
////{
////
////
////}
//
////总加组有功功率曲线
//void AFND_F73()
//{
//
//
//}
////总加组无功功率曲线
//void AFND_F74()
//{
//
//
//}
////总加组有功电能量曲线
//void AFND_F75()
//{
//
//
//}
////总加组无功电能量曲线
//void AFND_F76()
//{
//
//
//}
//void AFND_F77()
//{
//
//
//}
//void AFND_F78()
//{
//
//
//}
//void AFND_F79()
//{
//
//
//}
//void AFND_F80()
//{
//
//
//}

//测量点有功功率曲线
void AFND_F81()
{
    
    printf("执行F81\n");
    //1个字节长度  数据类型
    buff[outoffset] = measure_curve_data; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    XL_SINT64 temp =0;
    Byte curCount=0;
    
    
    begin = outoffset;
    int i =0;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = cvBeginData;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据  7个字节  5个字节时间＋1字节数据冻结密度＋1个字节数据点数
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //数据冻结密度
    identifier = cvCurveDensity;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    buff[outoffset]=*(userdata+offset);outoffset++;offset++;
    
    //数据点数
    identifier = cvCurveCount;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    buff[outoffset]=*(userdata+offset);
    curCount =*(userdata+offset);
    outoffset++;offset++;
    
    
    //具体曲线数据   根据数据点数进行绘制
    for(i=0;i<curCount;i++)
    {
        //数据内容
        //数据格式  A.9   有符号的数据 精确到万分位   4个字节
        //置数据标志 2个字节
        identifier = cvCurvePower;  //功率曲线数据标志
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        //数据内容
        temp= bcdtosint(userdata+offset, 4, 4);
        memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=4;
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//测量点A相有功功率曲线
void AFND_F82()
{
    
    //解析与f81()类似
    
    printf("执行F82\n");
    //解析不区分曲线类型，直接解析保存成曲线数据＋值
    AFND_F81();
    
}
//测量点B相有功功率曲线
void AFND_F83()
{
    printf("执行F83\n");
    //解析不区分曲线类型，直接解析保存成曲线数据＋值
    AFND_F81();
    
}
//测量点C相有功功率曲线
void AFND_F84()
{
    printf("执行F83\n");
    //解析不区分曲线类型，直接解析保存成曲线数据＋值
    AFND_F81();
    
}
//测量点无功功率曲线
void AFND_F85()
{
    printf("执行F83\n");
    //解析不区分曲线类型，直接解析保存成曲线数据＋值
    AFND_F81();
    
}
//测量点A相无功功率曲线
void AFND_F86()
{
    printf("执行F83\n");
    //解析不区分曲线类型，直接解析保存成曲线数据＋值
    AFND_F81();
    
    
}
//测量点B相无功功率曲线
void AFND_F87()
{
    printf("执行F83\n");
    //解析不区分曲线类型，直接解析保存成曲线数据＋值
    AFND_F81();
    
    
}
//测量点C相无功功率曲线
void AFND_F88()
{
    printf("执行F83\n");
    //解析不区分曲线类型，直接解析保存成曲线数据＋值
    AFND_F81();
    
    
}
//测量点A相电压曲线
void AFND_F89()
{
    //数据内容不同  数据位两个字节无符号1位小数
    printf("执行F89\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_curve_data; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    XL_SINT64 temp =0;
    Byte curCount=0;
    begin = outoffset;
    int i =0;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = cvBeginData;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据  7个字节  5个字节时间＋1字节数据冻结密度＋1个字节数据点数
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //数据冻结密度
    identifier = cvCurveDensity;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    buff[outoffset]=*(userdata+offset);outoffset++;offset++;
    
    //数据点数
    identifier = cvCurveCount;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    curCount=*(userdata+offset);
    buff[outoffset]=*(userdata+offset);outoffset++;offset++;
    
    
    //具体曲线数据   根据数据点数进行绘制
    for(i=0;i<curCount;i++)
    {
        //数据内容
        //数据格式  A.7   无符号的数据 精确到十分位   2个字节
        //置数据标志 2个字节
        identifier = cvCurveVolt;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        //数据内容
        temp =bcdtouint(userdata+offset, 2, 1);
        memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
}
//测量点B相电压曲线
void AFND_F90()
{
    //与f89()解析相同
    printf("执行F90\n");
    AFND_F89();
}
//测量点C相电压曲线
void AFND_F91()
{
    //与f89()解析相同
    printf("执行F91\n");
    AFND_F89();
    
}
//测量点A相电流曲线
void AFND_F92()
{
    /**********A25格式  3个字节有符号数据 3位小数点***************/
    printf("执行F92\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_curve_data; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    XL_SINT64 temp =0;
    Byte curCount =0;
    begin = outoffset;
    int i =0;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = cvBeginData;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据  7个字节  5个字节时间＋1字节数据冻结密度＋1个字节数据点数
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //数据冻结密度
    identifier = cvCurveDensity;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    buff[outoffset]=*(userdata+offset);outoffset++;offset++;
    
    //数据点数
    identifier = cvCurveCount;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    curCount=*(userdata+offset);
    buff[outoffset]=*(userdata+offset);outoffset++;offset++;
    
    
    //具体曲线数据   根据数据点数进行绘制
    for(i=0;i<curCount;i++)
    {
        //数据内容
        //数据格式  A.25   有符号的数据 精确到千分位   3个字节
        //置数据标志 2个字节
        identifier = cvCurveCur;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        //数据内容
        temp =bcdtosint(userdata+offset, 3, 3);
        memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=3;
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//测量点B相电流曲线
void AFND_F93()
{
    /**********A25格式  3个字节有符号数据 3位小数点***************/
    printf("执行F93\n");
    AFND_F92();
    
}
//测量点C相电流曲线
void AFND_F94()
{
    /**********A25格式  3个字节有符号数据 3位小数点***************/
    printf("执行F94\n");
    AFND_F92();
    
}
//测量点零序电流曲线
void AFND_F95()
{
    /**********A25格式  3个字节有符号数据 3位小数点***************/
    printf("执行F95\n");
    AFND_F92();
    
}
//void AFND_F96()
//{
//
//
//}
//测量点正向有功总电能量曲线
//void AFND_F97()
//{
//
//
//}
////测量点正向无功总电能量曲线
//void AFND_F98()
//{
//
//
//}
////测量点反向有功总电能量曲线
//void AFND_F99()
//{
//
//
//}
////测量点反向无功总电能量曲线
//void AFND_F100()
//{
//
//
//}
////测量点正向有功总电能示值曲线
//void AFND_F101()
//{
//
//
//}
////测量点正向无功总电能示值曲线
//void AFND_F102()
//{
//
//
//}
////测量点反向有功总电能示值曲线
//void AFND_F103()
//{
//
//
//}
////测量点反向无功总电能示值曲线
//void AFND_F104()
//{
//
//
//}
//测量点功率因素曲线
void AFND_F105()
{
    
    /**********数据格式 A5 有符号的精确到十分位的数据  2个字节 1个小数点***************/
    printf("执行F105\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_curve_data; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    XL_SINT64 temp =0;
    Byte curCount =0;
    begin = outoffset;
    int i =0;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = cvBeginData;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据  7个字节  5个字节时间＋1字节数据冻结密度＋1个字节数据点数
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //数据冻结密度
    identifier = cvCurveDensity;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    buff[outoffset]=*(userdata+offset);outoffset++;offset++;
    
    //数据点数
    identifier = cvCurveCount;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    curCount=*(userdata+offset);
    buff[outoffset]=*(userdata+offset);outoffset++;offset++;
    
    
    //具体曲线数据   根据数据点数进行绘制
    for(i=0;i<curCount;i++)
    {
        //数据内容
        //数据格式  A.5   有符号的数据 精确到十分位   2个字节
        //置数据标志 2个字节
        identifier = cvCurvePowerFactor;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        //数据内容
        temp =bcdtosint(userdata+offset, 2, 1);
        memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
    
}
//测量点A相功率因素曲线
void AFND_F106()
{
    /**********数据格式 A5 有符号的精确到十分位的数据  2个字节 1个小数点***************/
    printf("执行F106\n");
    AFND_F105();
    
}
//测量点B相功率因素曲线
void AFND_F107()
{
    /**********数据格式 A5 有符号的精确到十分位的数据  2个字节 1个小数点***************/
    printf("执行F107\n");
    AFND_F105();
    
}
//测量点C相功率因素曲线
void AFND_F108()
{
    /**********数据格式 A5 有符号的精确到十分位的数据  2个字节 1个小数点***************/
    printf("执行F108\n");
    AFND_F105();
    
}
//测量点电压相位角曲线
//void AFND_F109()
//{
//
//
//}
////测量点电流相位角曲线
//void AFND_F110()
//{
//
//
//}

//void AFND_F111()
//{
//
//
//}
//void AFND_F112()
//{
//
//
//}

//日冻结测量点A相2—19次谐波电流日最大值及发生时间
void AFND_F113()
{
    
    
    printf("执行F113\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = daily_data_charmonic; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    XL_SINT64 temp =0;
    begin = outoffset;
    int i =0;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = hdDataTime_ddc;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据  3个字节  日月年
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //A相2－19次谐波电流日最大值及其发生时间以及A相总畸变电流日最大值级发生时间 共19项数据
    for(i=0;i<19;i++)
    {
        //最大值 置标志
        if(i==0)
        {
            identifier = hdHarmoACurMax2;
            
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        //数据内容 2个字节  数据格式A.6 有符号的数据  2个小数点
        //数据－最大值
        temp=bcdtosint(userdata+offset, 2, 2);
        memcpy(buff + outoffset, &identifier, 2);outoffset+=8;offset+=2;
        
        //最大值发生时间  4个字节  分时日月
        //时间置标志
        identifier++;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        
        //分
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //时
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //日
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //月
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//日冻结测量点B相2—19次谐波电流日最大值及发生时间
void AFND_F114()
{
    printf("执行F114\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = daily_data_charmonic; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    XL_SINT64 temp =0;
    begin = outoffset;
    int i =0;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = hdDataTime_ddc;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据  3个字节  日月年
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //A相2－19次谐波电流日最大值及其发生时间以及A相总畸变电流日最大值级发生时间 共19项数据
    for(i=0;i<19;i++)
    {
        //置标志
        if(i==0)
        {
            identifier = hdHarmoBCurMax2;
            
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        //数据内容 2个字节  数据格式A.6 有符号的数据  2个小数点
        temp=bcdtosint(userdata+offset, 2, 2);
        memcpy(buff + outoffset, &identifier, 2);outoffset+=8;offset+=2;
        
        
        //最大值发生时间  4个字节  分时日月
        //时间置标志
        identifier++;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        
        //分
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //时
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //日
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //月
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        
        
        
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//日冻结测量点C相2—19次谐波电流日最大值及发生时间
void AFND_F115()
{
    printf("执行F115\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = daily_data_charmonic; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    XL_SINT64 temp =0;
    begin = outoffset;
    int i =0;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = hdDataTime_ddc;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据  3个字节  日月年
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //A相2－19次谐波电流日最大值及其发生时间以及A相总畸变电流日最大值级发生时间 共19项数据
    for(i=0;i<19;i++)
    {
        //置标志
        if(i==0)
        {
            identifier = hdHarmoCCurMax2;
            
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        //数据内容 2个字节  数据格式A.6 有符号的数据  2个小数点
        temp=bcdtosint(userdata+offset, 2, 2);
        memcpy(buff + outoffset, &identifier, 2);outoffset+=8;offset+=2;
        
        
        //最大值发生时间  4个字节  分时日月
        //时间置标志
        identifier++;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        
        //分
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //时
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //日
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //月
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//日冻结测量点A相2—19次谐波电压含有率及总畸变率日最大值及发生时间
void AFND_F116()
{
    
    printf("执行F116\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = daily_data_vharmonic; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    XL_SINT64 temp =0;
    begin = outoffset;
    int i =0;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = hdDataTime_ddv;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据  3个字节  日月年
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //A相2次谐波电压含有率日最大值及最大值发生时间 19个数据项
    //数据格式 A.5 2个字节 有符号数据  精确到十分位
    for(i=0;i<19;i++)
    {
        //置标志
        if(i==0)
        {
            identifier=hdHarmoAVoltMax2;
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        //数据
        temp=bcdtosint(userdata+offset, 2, 1);
        memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
        //发生时间 4个字节  分时日月
        //置时间标志
        identifier++;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        //时间
        //分
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //时
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //日
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //月
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//日冻结测量点B相2—19次谐波电压含有率及总畸变率日最大值及发生时间
void AFND_F117()
{
    
    printf("执行F117\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = daily_data_vharmonic; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    XL_SINT64 temp =0;
    begin = outoffset;
    int i =0;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = hdDataTime_ddv;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据  3个字节  日月年
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //A相2次谐波电压含有率日最大值及最大值发生时间 19个数据项
    //数据格式 A.5 2个字节 有符号数据  精确到十分位
    for(i=0;i<19;i++)
    {
        //置标志
        if(i==0)
        {
            identifier=hdHarmoBVoltMax2;
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        //数据
        temp=bcdtosint(userdata+offset, 2, 1);
        memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
        //发生时间 4个字节  分时日月
        //置时间标志
        identifier++;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        //时间
        //分
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //时
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //日
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //月
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//日冻结测量点C相2—19次谐波电压含有率及总畸变率日最大值及发生时间
void AFND_F118()
{
    
    printf("执行F118\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = daily_data_vharmonic; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    XL_SINT64 temp =0;
    begin = outoffset;
    int i =0;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = hdDataTime_ddv;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据  3个字节  日月年
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //A相2次谐波电压含有率日最大值及最大值发生时间 19个数据项
    //数据格式 A.5 2个字节 有符号数据  精确到十分位
    for(i=0;i<19;i++)
    {
        //置标志
        if(i==0)
        {
            identifier=hdHarmoCVoltMax2;
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        //数据
        temp=bcdtosint(userdata+offset, 2, 1);
        memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=2;
        //发生时间 4个字节  分时日月
        //置时间标志
        identifier++;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        //时间
        //分
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //时
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //日
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
        //月
        buff[outoffset]=bcdToTime(userdata+offset);
        outoffset++;offset++;
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//void AFND_F119()
//{
//
//
//}
//void AFND_F120()
//{
//
//
//}

//日冻结测量点A相谐波越限日统计数据
//void AFND_F121()
//{
//
//
//}
////日冻结测量点B相谐波越限日统计数据
//void AFND_F122()
//{
//
//
//}
////日冻结测量点C相谐波越限日统计数据
//void AFND_F123()
//{
//
//
//}
////日冻结A相电压谐波电压含油率、谐波电流95%概率值
//void AFND_F124()
//{
//
//
//}
////日冻结B相电压谐波电压含油率、谐波电流95%概率值
//void AFND_F125()
//{
//
//
//}
////日冻结C相电压谐波电压含油率、谐波电流95%概率值
//void AFND_F126()
//{
//
//
//}
//void AFND_F127()
//{
//
//
//}
//void AFND_F128()
//{
//
//
//}
//日冻结直流模拟量日越限日累计时间、最大／最小值及发生时间
void AFND_F129()
{
    
    
    printf("执行F129\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = dcanalog_day_data; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    //    XL_SINT64 temp =0;
    //    double  temp =0.0;
    XL_SINT16 temp_value =0;
    XL_UINT16 temp =0;
    
    XL_CHAR powrer =0;
    
    begin = outoffset;
    //    int i =0;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = hdDataTime_ddd;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据  3个字节  日月年
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //直流模拟量越上限日累计时间
    //置标志
    identifier = hdDCAnalogDHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp, 2);outoffset+=2;
    outoffset+=2;offset+=2;
    
    //直流模拟量越下限日累计时间
    //置标志
    identifier = hdDCAnalogDLoAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp, 2);outoffset+=2;offset+=2;
    
    
    //直流模拟量日最大值 格式A.2  2个字节  需要转换完善
    identifier = hdDCAnalogMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    //    temp_value=*(XL_UINT16*)(userdata+offset);
    //获取幂数
    powrer =a2powvaluewithparam(userdata+offset);
    memcpy(buff + outoffset, &powrer, 1);
    outoffset+=1;
    //获取数据
    temp_value=a22intwithparam(userdata+offset);
    memcpy(buff + outoffset, &temp_value,2);
    outoffset+=2; offset+=2;
    
    
    //最大值发生时间  3个字节  分时日
    identifier = hdDCAnalogMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //直流模拟量日最小值 格式A.2  2个字节  需要转换完善
    identifier = hdDCAnalogMin;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //获取幂数
    powrer =a2powvaluewithparam(userdata+offset);
    memcpy(buff + outoffset, &powrer, 1);
    outoffset+=1;
    //获取数据
    temp_value=a22intwithparam(userdata+offset);
    memcpy(buff + outoffset, &temp_value,2);
    outoffset+=2; offset+=2;
    
    ////    temp_value=*(XL_UINT16*)(userdata+offset);
    //    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //最小值发生时间  3个字节  分时日
    identifier = hdDCAnalogMinTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
    
}
//月冻结直流模拟量越限月累计时间、最大／最小值及发生时间
void AFND_F130()
{
    
    printf("执行F130\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = dcanalog_month_data; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    //    XL_SINT64 temp =0;
    XL_SINT16 temp_value =0;
    XL_CHAR powrer =0;
    XL_UINT16 temp =0;
    
    begin = outoffset;
    //    int i =0;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = hmDataTime_dmd;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据  2个字节  月年
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //直流模拟量越上限月累计时间
    //置标志
    identifier = hmDCAnalogDHiAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp, 2);outoffset+=2;
    outoffset+=2;offset+=2;
    
    //直流模拟量越下限月累计时间
    //置标志
    identifier = hmDCAnalogDLoAccTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp=*(XL_UINT16*)(userdata+offset);
    memcpy(buff + outoffset, &temp, 2);outoffset+=2;offset+=2;
    
    
    //直流模拟量月最大值 格式A.2  2个字节  需要转换完善
    identifier = hmDCAnalogMax;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //获取幂数
    powrer =a2powvaluewithparam(userdata+offset);
    memcpy(buff + outoffset, &powrer, 1);
    outoffset+=1;
    //获取数据
    temp_value=a22intwithparam(userdata+offset);
    memcpy(buff + outoffset, &temp_value,2);
    outoffset+=2; offset+=2;
    
    //    temp_value=*(XL_UINT16*)(userdata+offset);
    //    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //最大值发生时间  3个字节  分时日
    identifier = hmDCAnalogMaxTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //直流模拟量月最小值 格式A.2  2个字节  需要转换完善
    identifier = hmDCAnalogMin;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //获取幂数
    powrer =a2powvaluewithparam(userdata+offset);
    memcpy(buff + outoffset, &powrer, 1);
    outoffset+=1;
    //获取数据
    temp_value=a22intwithparam(userdata+offset);
    memcpy(buff + outoffset, &temp_value,2);
    outoffset+=2; offset+=2;
    
    //    temp_value=*(XL_UINT16*)(userdata+offset);
    //    memcpy(buff + outoffset, &temp_value, 2);outoffset+=2;offset+=2;
    
    
    //最小值发生时间  3个字节  分时日
    identifier = hmDCAnalogMinTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}

//
//void AFND_F131()
//{
//
//
//}
//void AFND_F132()
//{
//
//
//}
//
//
//void AFND_F133()
//{
//
//
//}
//void AFND_F134()
//{
//
//
//}
//void AFND_F135()
//{
//
//
//}
//void AFND_F136()
//{
//
//
//}
//void AFND_F137()
//{
//
//
//}
//直流模拟量数据曲线
void AFND_F138()
{
    
    printf("执行F138\n");
    
    //解析不区分曲线类型，直接解析保存成曲线数据＋值
    
    //A.2 数据格式需要转换   需要完善
    //    AFND_F81();
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_curve_data; outoffset++;
    
    outoffset+=2;   //数据长度起始偏移
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 len=0;
    //    XL_SINT64 temp =0;
    
    XL_SINT16 temp_value =0;
    XL_CHAR powrer =0;
    
    
    begin = outoffset;
    int i =0;
    
    
    XL_UINT16 identifier;  //标志  2个字节
    identifier = cvBeginData;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据  7个字节  5个字节时间＋1字节数据冻结密度＋1个字节数据点数
    //分
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //时
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    //数据冻结密度
    identifier = cvCurveDensity;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    buff[outoffset]=*(userdata+offset);outoffset++;offset++;
    
    //数据点数
    identifier = cvCurveCount;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    buff[outoffset]=*(userdata+offset);outoffset++;offset++;
    
    
    //具体曲线数据   根据数据点数进行绘制
    for(i=0;i<cvCurveCount;i++)
    {
        //数据内容
        //数据格式  A.2   有符号的数据
        //置数据标志 2个字节
        identifier = cvCurveDireCurAnalog;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        
        //数据内容  A.2格式
        //获取幂数
        powrer =a2powvaluewithparam(userdata+offset);
        memcpy(buff + outoffset, &powrer, 1);
        outoffset+=1;
        //获取数据
        temp_value=a22intwithparam(userdata+offset);
        memcpy(buff + outoffset, &temp_value,2);
        outoffset+=2; offset+=2;
        
        //        temp= bcdToSignDouble(userdata+offset, 4, 4)*10000;
        //        memcpy(buff + outoffset, &temp, 8);outoffset+=8;offset+=4;
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//void AFND_F139()
//{
//
//
//}
//void AFND_F140()
//{
//
//
//}
//void AFND_F141()
//{
//
//
//}
//void AFND_F142()
//{
//
//
//}
//
//
//void AFND_F143()
//{
//
//
//}
//void AFND_F144()
//{
//
//
//}
//测量点一象限无功总电能示值曲线
//void AFND_F145()
//{
//
//
//}
////测量点四象限无功总电能示值曲线
//void AFND_F146()
//{
//
//
//}
////测量点二象限无功总电能示值曲线
//void AFND_F147()
//{
//
//
//}
////测量点三象限无功总电能示值曲线
//void AFND_F148()
//{
//
//
//}
////void AFND_F149()
////{
////
////
////}
////void AFND_F150()
////{
////
////
////}
////
////void AFND_F151()
////{
////
////
////}
////void AFND_F152()
////{
////
////
////}
//
////日冻结测量点分相正向有功电能示值
//void AFND_F153()
//{
//
//
//}
////日冻结测量点分相正向无功电能示值
//void AFND_F154()
//{
//
//
//}
////日冻结测量点分相反向有功电能示值
//void AFND_F155()
//{
//
//
//}
////日冻结测量点分相反向无功电能示值
//void AFND_F156()
//{
//
//
//}
////月冻结测量点分相正向有功电能示值
//void AFND_F157()
//{
//
//
//}
////月冻结测量点分相正向无功电能示值
//void AFND_F158()
//{
//
//
//}
////月冻结测量点分相反向有功电能示值
//void AFND_F159()
//{
//
//
//}
////月冻结测量点分相反向无功电能示值
//void AFND_F160()
//{
//
//
//}
//日冻结正向有功电能示值（总、费率1~m）
void AFND_F161()
{
    
    
    //解析与f1 类似
    printf("执行F161\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_day_powervalue; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    //数据标志  2个字节
    identifier = hdDataTime_mdp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  3个字节
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //终端抄表时间 5个字节 不保存
    offset+=5;
    
    
    //费率数  1个字节
    rateCount=*(userdata+offset);;   //将费率数保存
    offset++;
    
    
    //正向有功总电能示值  5个字节 BCD码 需要转换 格式1.14
    //置标识
    
    identifier =hdPosAEValueZ; //正向有功总电能示值
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 精确到万分位  A.14-万分位  4个小数点
    temp   =bcdtouint(userdata+offset, 5, 4);
    
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=5;
    
    
    
    for(i=0;i<rateCount;i++)
    {
        
        //费率i正向有功电能示值  5个字节  bcd码需要转换
        
        if(i==0)
        {
            identifier =hdPosAEValue1;
        }
        else
        {
            identifier++;
        }
        //需要置数据标识
        memcpy(buff+outoffset, &identifier, 2);
        outoffset+=2;
        
        
        temp   =bcdtouint(userdata+offset, 5, 4);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=5;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*5;
    }
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
    
}
//日冻结正向无功（组合无功1）电能示值（总、费率1~m）
void AFND_F162()
{
    
    //解析与f1 类似
    printf("执行F162\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_day_powervalue; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    //数据标志  2个字节
    identifier = hdDataTime_mdp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  3个字节
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //终端抄表时间 5个字节 不保存
    offset+=5;
    
    
    //费率数  1个字节
    rateCount=*(userdata+offset);;   //将费率数保存
    offset++;
    
    
    //正向无功总电能示值  4个字节 BCD码 需要转换 格式A1.11
    //置标识
    
    identifier =hdPosREValueZ; //正向有功总电能示值
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 精确到百分位    2个小数点
    temp   =bcdtouint(userdata+offset, 4, 2);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    
    
    for(i=0;i<rateCount;i++)
    {
        
        //费率i正向无功电能示值  4个字节  bcd码需要转换
        
        if(i==0)
        {
            identifier =hdPosREValue1;
        }
        else
        {
            identifier++;
        }
        //需要置数据标识
        memcpy(buff+outoffset, &identifier, 2);
        outoffset+=2;
        
        temp   =bcdtouint(userdata+offset, 4, 2);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=4;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//日冻结反向有功电能示值（总、费率1~m）
void AFND_F163()
{
    
    //与f161解析类似
    //只是标志不同
    printf("执行F163\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_day_powervalue; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    //数据标志  2个字节
    identifier = hdDataTime_mdp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  3个字节
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //终端抄表时间 5个字节 不保存
    offset+=5;
    
    
    //费率数  1个字节
    rateCount=*(userdata+offset);;   //将费率数保存
    offset++;
    
    
    //反向有功总电能示值  5个字节 BCD码 需要转换 格式1.14
    //置标识
    
    identifier =hdNegAEValueZ; //反向有功总电能示值
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 精确到万分位  A.14-万分位  4个小数点
    temp   =bcdtouint(userdata+offset, 5, 4);
    
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=5;
    
    
    
    for(i=0;i<rateCount;i++)
    {
        
        //费率i反向有功电能示值  5个字节  bcd码需要转换
        
        if(i==0)
        {
            identifier =hdNegAEValue1;
        }
        else
        {
            identifier++;
        }
        //需要置数据标识
        memcpy(buff+outoffset, &identifier, 2);
        outoffset+=2;
        
        
        temp   =bcdtouint(userdata+offset, 5, 4);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=5;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*5;
    }
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//日冻结反向无功（组合无功1）电能示值（总、费率1~m）
void AFND_F164()
{
    //与f162解析类似
    //只是标志不同
    printf("执行F162\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_day_powervalue; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    //数据标志  2个字节
    identifier = hdDataTime_mdp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  3个字节
    //日
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //终端抄表时间 5个字节 不保存
    offset+=5;
    
    
    //费率数  1个字节
    rateCount=*(userdata+offset);;   //将费率数保存
    offset++;
    
    
    //反向无功总电能示值  4个字节 BCD码 需要转换 格式A1.11
    //置标识
    
    identifier =hdNegREValueZG; //反向有功总电能示值
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 精确到百分位   2个小数点
    temp   =bcdtouint(userdata+offset, 4, 2);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    
    
    for(i=0;i<rateCount;i++)
    {
        
        //费率i反向无功电能示值  4个字节  bcd码需要转换
        
        if(i==0)
        {
            identifier =hdNegREValueG1;
        }
        else
        {
            identifier++;
        }
        //需要置数据标识
        memcpy(buff+outoffset, &identifier, 2);
        outoffset+=2;
        
        temp   =bcdtouint(userdata+offset, 4, 2);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=4;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//日冻结一象限无功电能示值（总、费率1～m）
//void AFND_F165()
//{
//
//
//}
////日冻结二象限无功电能示值（总、费率1～m）
//void AFND_F166()
//{
//
//
//}
////日冻结三象限无功电能示值（总、费率1～m）
//void AFND_F167()
//{
//
//
//}
//日冻结四象限无功电能示值（总、费率1～m）
//void AFND_F168()
//{
//
//
//}
////抄表日冻结正向有功电能示值（总、费率1～m）
//void AFND_F169()
//{
//
//
//}
////抄表日冻结正向无功（组合无功1）电能示值（总、费率1～m）
//void AFND_F170()
//{
//
//
//}
////抄表日冻结反向有功电能示值（总、费率1～m）
//void AFND_F171()
//{
//
//
//}
////抄表日冻结反向无功（组合无功1）电能示值（总、费率1～m）
//void AFND_F172()
//{
//
//
//}
////抄表日冻结一象限无功电能示值（总、费率1～m）
//void AFND_F173()
//{
//
//
//}
////抄表日冻结二象限无功电能示值（总、费率1～m）
//void AFND_F174()
//{
//
//
//}
////抄表日冻结三象限无功电能示值（总、费率1～m）
//void AFND_F175()
//{
//
//
//}
////抄表日冻结四象限无功电能示值（总、费率1～m）
//void AFND_F176()
//{
//
//
//}
//月冻结正向有功电能示值（总、费率1～m）
void AFND_F177()
{
    //与f161解析类似
    //标志置不同
    printf("执行F177\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_month_powervalue; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    //数据标志  2个字节
    identifier = hmDataTime_mmp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //终端抄表时间 5个字节 不保存
    offset+=5;
    
    
    //费率数  1个字节
    rateCount=*(userdata+offset);;   //将费率数保存
    offset++;
    
    
    //正向有功总电能示值  5个字节 BCD码 需要转换 格式1.14
    //置标识
    
    identifier =hmPosAEValueZ; //正向有功总电能示值
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 精确到万分位  A.14-万分位  4个小数点
    temp   =bcdtouint(userdata+offset, 5, 4);
    
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=5;
    
    for(i=0;i<rateCount;i++)
    {
        
        //费率i正向有功电能示值  5个字节  bcd码需要转换
        
        if(i==0)
        {
            identifier =hmPosAEValue1;
        }
        else
        {
            identifier++;
        }
        //需要置数据标识
        memcpy(buff+outoffset, &identifier, 2);
        outoffset+=2;
        
        
        temp   =bcdtouint(userdata+offset, 5, 4);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=5;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*5;
    }
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
}
//月冻结正向无功（组合无功1）电能示值（总、费率1～m）
void AFND_F178()
{
    //解析与f1 类似
    printf("执行F178\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_month_powervalue; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    //数据标志  2个字节
    identifier = hmDataTime_mmp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  3个字节
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //终端抄表时间 5个字节 不保存
    offset+=5;
    
    
    //费率数  1个字节
    rateCount=*(userdata+offset);;   //将费率数保存
    offset++;
    
    
    //正向无功总电能示值  4个字节 BCD码 需要转换 格式A1.11
    //置标识
    
    identifier =hmPosREValueZ; //正向有功总电能示值
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 精确到百分位    2个小数点
    temp   =bcdtouint(userdata+offset, 4, 2);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    
    
    for(i=0;i<rateCount;i++)
    {
        
        //费率i正向无功电能示值  4个字节  bcd码需要转换
        
        if(i==0)
        {
            identifier =hmPosREValue1;
        }
        else
        {
            identifier++;
        }
        //需要置数据标识
        memcpy(buff+outoffset, &identifier, 2);
        outoffset+=2;
        
        temp   =bcdtouint(userdata+offset, 4, 2);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=4;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
}
//月冻结反向有功电能示值（总、费率1～m）
void AFND_F179()
{
    
    //与f163解析类似
    //只是标志不同
    printf("执行F179\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_month_powervalue; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    //数据标志  2个字节
    identifier = hmDataTime_mmp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //终端抄表时间 5个字节 不保存
    offset+=5;
    
    
    //费率数  1个字节
    rateCount=*(userdata+offset);;   //将费率数保存
    offset++;
    
    
    //反向有功总电能示值  5个字节 BCD码 需要转换 格式1.14
    //置标识
    
    identifier =hmNegAEValueZ; //反向有功总电能示值
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 精确到万分位  A.14-万分位  4个小数点
    temp   =bcdtouint(userdata+offset, 5, 4);
    
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=5;
    
    
    
    for(i=0;i<rateCount;i++)
    {
        
        //费率i反向有功电能示值  5个字节  bcd码需要转换
        
        if(i==0)
        {
            identifier =hmNegAEValue1;
        }
        else
        {
            identifier++;
        }
        //需要置数据标识
        memcpy(buff+outoffset, &identifier, 2);
        outoffset+=2;
        
        
        temp   =bcdtouint(userdata+offset, 5, 4);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=5;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*5;
    }
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
    
}
//月冻结反向无功（组合无功1）电能示值（总、费率1～m）
void AFND_F180()
{
    
    //与f164解析类似
    //只是标志不同
    printf("执行F180\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = measure_month_powervalue; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    //数据标志  2个字节
    identifier = hmDataTime_mmp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    //终端抄表时间 5个字节 不保存
    offset+=5;
    
    
    //费率数  1个字节
    rateCount=*(userdata+offset);;   //将费率数保存
    offset++;
    
    
    //反向无功总电能示值  4个字节 BCD码 需要转换 格式A1.11
    //置标识
    
    identifier =hmNegREValueZG; //反向有功总电能示值
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 精确到百分位   2个小数点
    temp   =bcdtouint(userdata+offset, 4, 2);
    memcpy(buff+outoffset, &temp, 8);
    outoffset+=8;offset+=4;
    
    
    
    for(i=0;i<rateCount;i++)
    {
        
        //费率i反向无功电能示值  4个字节  bcd码需要转换
        
        if(i==0)
        {
            identifier =hmNegREValueG1;
        }
        else
        {
            identifier++;
        }
        //需要置数据标识
        memcpy(buff+outoffset, &identifier, 2);
        outoffset+=2;
        
        temp   =bcdtouint(userdata+offset, 4, 2);
        memcpy(buff+outoffset, &temp, 8);
        outoffset+=8;offset+=4;
    }
    if(rateCount>4)
    {
        offset+=(rateCount-4)*4;
    }
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
}
//月冻结一象限无功电能示值（总、费率1～m）
//void AFND_F181()
//{
//
//
//}
////月冻结二象限无功电能示值（总、费率1～m）
//void AFND_F182()
//{
//
//
//}
////月冻结三象限无功电能示值（总、费率1～m）
//void AFND_F183()
//{
//
//
//}
////月冻结四象限无功电能示值（总、费率1～m）
//void AFND_F184()
//{
//
//
//}
////日冻结正向有功最大需量及发生时间（总、费率1～m）
//void AFND_F185()
//{
//
//
//}
////日冻结正向无功最大需量及发生时间（总、费率1～m）
//void AFND_F186()
//{
//
//
//}
////日冻结反向有功最大需量及发生时间（总、费率1～m）
//void AFND_F187()
//{
//
//
//}
////日冻结反向无功最大需量及发生时间（总、费率1～m）
//void AFND_F188()
//{
//
//
//}
////抄表日冻结正向有功最大需量及发生时间（总、费率1～m）
//void AFND_F189()
//{
//
//
//}
////抄表日冻结正向无功最大需量及发生时间（总、费率1～m）
//void AFND_F190()
//{
//
//
//}
//////抄表日冻结反向有功最大需量及发生时间（总、费率1～m）
//void AFND_F191()
//{
//
//
//}
////抄表日冻结反向无功最大需量及发生时间（总、费率1～m）
//void AFND_F192()
//{
//
//
//}
//月冻结正向有功最大需量及发生时间（总、费率1～m）
void AFND_F193()
{
    //解析与f3类似
    printf("执行F193\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = history_month_powerneeds; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0.0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    
    //标志 2个字节
    identifier = hmDataTime_hmp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    //终端抄表时间，不保存到输出缓冲区
    offset+=5;
    
    rateCount =*(Byte*)(userdata+offset);  //费率数
    offset++;
    
    
    
    //正向有功总最大需量 3个字节 4个小数点 万分位
    //置标志
    identifier =hmPosADMaxZ;
    memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=3;
    //正向有功总最大需量发生时间  4个字节
    identifier =hmPosADMaxZTm;
    memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
    buff[outoffset]=bcdToTime(userdata+offset);  //分
    offset++;  outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //时
    offset++;   outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //日
    offset++;   outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //月
    offset++;   outoffset++;
    
    
    //费率i正向有功最大需量
    for(i=0;i<4;i++)
    {
        //置标志
        if(i==0)
        {
            identifier=hmPosADMax1;
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
        
        //数据内容
        temp=bcdtouint(userdata+offset, 3, 4);
        memcpy(buff + outoffset, &temp, 8);
        outoffset+=8;
        offset+=3;
        //费率i正向有功最大需量发生时间
        identifier++; //发生时间标志
        
        memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
        buff[outoffset]=bcdToTime(userdata+offset);  //分
        offset++;  outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //时
        offset++;   outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //日
        offset++;   outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //月
        offset++;   outoffset++;
    }
    
    if(rateCount>4)
    {
        offset+=(rateCount-4)*7;
    }
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//月冻结正向无功最大需量及发生时间（总、费率1～m）
void AFND_F194()
{
    
    //解析与f193类似
    printf("执行F194\n");
    //1个字节长度  数据类型
    buff[outoffset] = history_month_powerneeds; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0.0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    
    //标志 2个字节
    identifier = hmDataTime_hmp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    //终端抄表时间，不保存到输出缓冲区
    offset+=5;
    
    rateCount =*(Byte*)(userdata+offset);  //费率数
    offset++;
    
    
    
    //正向无功总最大需量 3个字节 4个小数点 万分位
    //置标志
    identifier =hmPosRDMaxZ;
    memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=3;
    //正向无功总最大需量发生时间  4个字节
    identifier =hmPosRDMaxZTm;
    memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
    buff[outoffset]=bcdToTime(userdata+offset);  //分
    offset++;  outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //时
    offset++;   outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //日
    offset++;   outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //月
    offset++;   outoffset++;
    
    
    //费率i正向无功最大需量
    for(i=0;i<4;i++)
    {
        //置标志
        if(i==0)
        {
            identifier=hmPosRDMax1;
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
        
        //数据内容
        temp=bcdtouint(userdata+offset, 3, 4);
        memcpy(buff + outoffset, &temp, 8);
        outoffset+=8;
        offset+=3;
        //费率i正向无功最大需量发生时间
        identifier++; //发生时间标志
        
        memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
        buff[outoffset]=bcdToTime(userdata+offset);  //分
        offset++;  outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //时
        offset++;   outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //日
        offset++;   outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //月
        offset++;   outoffset++;
    }
    
    if(rateCount>4)
    {
        offset+=(rateCount-4)*7;
    }
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
}
//月冻结反向有功最大需量及发生时间（总、费率1～m）
void AFND_F195()
{
    //与f193类似
    printf("执行F195\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = history_month_powerneeds; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0.0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    
    //标志 2个字节
    identifier = hmDataTime_hmp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    //终端抄表时间，不保存到输出缓冲区
    offset+=5;
    
    rateCount =*(Byte*)(userdata+offset);  //费率数
    offset++;
    
    
    
    //反向有功总最大需量 3个字节 4个小数点 万分位
    //置标志
    identifier =hmNegADMaxZ;
    memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=3;
    //反向有功总最大需量发生时间  4个字节
    identifier =hmNegADMaxZTm;
    memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
    buff[outoffset]=bcdToTime(userdata+offset);  //分
    offset++;  outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //时
    offset++;   outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //日
    offset++;   outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //月
    offset++;   outoffset++;
    
    
    //费率i反向有功最大需量
    for(i=0;i<4;i++)
    {
        //置标志
        if(i==0)
        {
            identifier=hmNegADMax1;
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
        
        //数据内容
        temp=bcdtouint(userdata+offset, 3, 4);
        memcpy(buff + outoffset, &temp, 8);
        outoffset+=8;
        offset+=3;
        //费率i反向有功最大需量发生时间
        identifier++; //发生时间标志
        
        memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
        buff[outoffset]=bcdToTime(userdata+offset);  //分
        offset++;  outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //时
        offset++;   outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //日
        offset++;   outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //月
        offset++;   outoffset++;
    }
    
    if(rateCount>4)
    {
        offset+=(rateCount-4)*7;
    }
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
}
//月冻结反向无功最大需量及发生时间（总、费率1～m）
void AFND_F196()
{
    
    //与f193类似
    printf("执行F196\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = history_month_powerneeds; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin=0;
    XL_UINT16 end=0;
    XL_UINT16 identifier=0;
    int  i =0;
    Byte rateCount =0;  //费率数
    XL_SINT64 temp  =0.0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;//数据长度起始位置
    
    //标志 2个字节
    identifier = hmDataTime_hmp;// 数据时标
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    //月
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    //年
    buff[outoffset]=bcdToTime(userdata+offset);
    outoffset++;offset++;
    
    
    
    //终端抄表时间，不保存到输出缓冲区
    offset+=5;
    
    rateCount =*(Byte*)(userdata+offset);  //费率数
    offset++;
    
    
    
    //反向无功总最大需量 3个字节 4个小数点 万分位
    //置标志
    identifier =hmNegRDMaxZ;
    memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=3;
    //反向有功总最大需量发生时间  4个字节
    identifier =hmNegRDMaxZTm;
    memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
    buff[outoffset]=bcdToTime(userdata+offset);  //分
    offset++;  outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //时
    offset++;   outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //日
    offset++;   outoffset++;
    buff[outoffset]=bcdToTime(userdata+offset); //月
    offset++;   outoffset++;
    
    
    //费率i反向无功最大需量
    for(i=0;i<4;i++)
    {
        //置标志
        if(i==0)
        {
            identifier=hmNegRDMax1;
        }
        else
        {
            identifier++;
        }
        memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
        
        //数据内容
        temp=bcdtouint(userdata+offset, 3, 4);
        memcpy(buff + outoffset, &temp, 8);
        outoffset+=8;
        offset+=3;
        //费率i反向无功最大需量发生时间
        identifier++; //发生时间标志
        
        memcpy(buff + outoffset, &identifier, 2);  outoffset+=2;
        buff[outoffset]=bcdToTime(userdata+offset);  //分
        offset++;  outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //时
        offset++;   outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //日
        offset++;   outoffset++;
        buff[outoffset]=bcdToTime(userdata+offset); //月
        offset++;   outoffset++;
    }
    
    if(rateCount>4)
    {
        offset+=(rateCount-4)*7;
    }
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
    
}
//void AFND_F197()
//{
//
//
//}
//void AFND_F198()
//{
//
//
//}
//void AFND_F199()
//{
//
//
//}
//void AFND_F200()
//{
//
//
//}
//月冻结第一时区冻结正向有功电能示值（总、费率1～m）
//void AFND_F201()
//{
//
//
//}
////月冻结第二时区冻结正向有功电能示值（总、费率1～m）
//void AFND_F202()
//{
//
//
//}
////月冻结第三时区冻结正向有功电能示值（总、费率1～m）
//void AFND_F203()
//{
//
//
//}
////月冻结第四时区冻结正向有功电能示值（总、费率1～m）
//void AFND_F204()
//{
//
//
//}
////月冻结第五时区冻结正向有功电能示值（总、费率1～m）
//void AFND_F205()
//{
//
//
//}
////月冻结第六时区冻结正向有功电能示值（总、费率1～m）
//void AFND_F206()
//{
//
//
//}
////月冻结第七时区冻结正向有功电能示值（总、费率1～m）
//void AFND_F207()
//{
//
//
//}
////月冻结第八时区冻结正向有功电能示值（总、费率1～m）
//void AFND_F208()
//{
//
//
//}
//日冻结电能表远程控制状态及信息
//void AFND_F209()
//{
//
//
//}
////日冻结电能表购、用电信息
//void AFND_F210()
//{
//
//
//}
////日冻结三相电压、电流不平衡度95%概率值
//void AFND_F211()
//{
//
//
//}
////月冻结三相电压、电流不平衡度95%概率值
//void AFND_F212()
//{
//
//
//}
////月冻结电能表开关操作次数及时间
//void AFND_F213()
//{
//
//
//}
////月冻结电能表参数修改次数及时间
//void AFND_F214()
//{
//
//
//}
////月冻结电能表购、用电信息
//void AFND_F215()
//{
//
//
//}
////月冻结电能表结算信息
//void AFND_F216()
//{
//
//
//}
////台区集中抄表载波主节点白噪声曲线
//void AFND_F217()
//{
//
//
//}
////台区集中抄表载波主节点色噪声曲线
//void AFND_F218()
//{
//
//
//}
////测量点组合数据曲线
//void AFND_F219()
//{
//    /**********A25格式  第三个字节为符号位 ***************/
//
//}


