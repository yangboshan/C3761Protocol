//
//  XL3761AFNA.c
//  C_Protocol
//
//  Created by admin on 14-1-22.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "XL3761AFNC.h"
#include "XLDataId.h"
#include "XLCommon.h"
#include "XLUtility.h"


void AFNA_RecursiveParse(); //函数声明
//参数查询功能项

void AFNA_F1();//终端上行通信口通信参数设置
void AFNA_F3();//主站IP地址和端口
void AFNA_F7();//终端IP地址和端口
void AFNA_F9();//终端事件记录配置设置
void AFNA_F10(); //终端电能表/交流采样装置配置参数-jp柜
void AFNA_F12();//终端状态量输入参数
void AFNA_F14();//终端总加组配置参数
void AFNA_F15();//有功总电能量差动越限事件参数设置
void AFNA_F16();//虚拟专网用户名、密码

//测量点参数
void AFNA_F25();//测量点基本参数
void AFNA_F26();//测量点限值参数
void AFNA_F27();//测量点铜损、铁损参数
void AFNA_F28();//测量点功率因数分段限值
void AFNA_F36();//终端上行通信流量门限设置

void AFNA_F45();//功控轮次设定
void AFNA_F60();//谐波限值
void AFNA_F61();//直流模拟量接入参数


////JP柜参数
//void AFNA_F73();//电容器参数
//void AFNA_F74();//电容器投切运行参数
//void AFNA_F75();//电容器保护参数
//void AFNA_F76();//电容器投切控制方式


void AFNA_F81();//直流模拟量变比
void AFNA_F82();//直流模拟量限值
void AFNA_F83();//直流模拟量冻结参数
void AFNA_F90();//设置无线通信参数


void AFNA_F91();//终端地理位置信息

//增补
void AFNA_F169();//变压器基本参数设置
void AFNA_F170();//wifi通信设置
void AFNA_F172();//用户管理


void initUserDataForAfna(XL_SINT16 *output,void *frame,XL_UINT16* outlen,Byte** outbuf){
    
    
    offset=0;
    outoffset = 0;
    
    _output = output;
    _outlen = outlen;
    _outbuf = outbuf;
    
    _frame = (FRAME*)frame;
    
    userdata = _frame->frameData;
    
    buff = malloc(_frame->userlen*16 + 50);
    memset(buff,0,_frame->userlen*16 + 50);
    *_outbuf = buff;
    
    AFNA_RecursiveParse();
    *outlen = outoffset;
    
    free(userdata);
    free(_frame);
    //用完之后,将outoffset置位初值0
	outoffset = 0;
    offset = 0;
}

void AFNA_RecursiveParse()
{
    
    XL_UINT16 fn = parsedadt((XL_UINT16)userdata[offset + 3],
                             (XL_UINT16)userdata[offset + 2],0);
    
    //拷贝
    memcpy(buff + outoffset, userdata + offset, 1); offset+=2;outoffset++;
    
    memcpy(buff + outoffset, &fn, 1);                offset+=2;outoffset++;
    printf("fn=%d\n",fn);
    
    switch (fn) {
        case 1:
            AFNA_F1();//终端上行通信口通信参数设置
            break;
        case 3:
            AFNA_F3();//主站IP地址和端口
            break;
        case 7:
            AFNA_F7();//终端IP地址和端口   ERR暂不支持
            break;
            
        case 9:
            AFNA_F9();//终端事件记录配置设置
            break;
        case 10:
            AFNA_F10();//终端电能表/交流采样装置配置参数-jp柜
            break;
        case 12:
            AFNA_F12();//终端状态量输入参数
            break;
        case 14:
            AFNA_F14();//终端总加组配置参数
            break;
        case 15:
            AFNA_F15();//有功总电能量差动越限事件参数设置
            break;
        case 16:
            AFNA_F16();//虚拟专网用户名、密码  ERR
            break;
        case 25:
            AFNA_F25();//测量点基本参数
            break;
        case 26:
            AFNA_F26();//测量点限值参数
            break;
        case 27:
            AFNA_F27();//测量点铜损、铁损参数
            break;
        case 28:
            AFNA_F28();//测量点功率因数分段限值
            break;
        case 36:
            AFNA_F36();//终端上行通信流量门限设置
            break;
        case 45:
            AFNA_F45();//功控轮次设定
            break;
        case 60:
            AFNA_F60();//谐波限值
            break;
        case 61:
            AFNA_F61();//直流模拟量接入参数
            break;
//        case 73:
//            AFNA_F73();//电容器参数
//            break;
//        case 74:
//            AFNA_F74();//电容器投切运行参数
//            break;
//        case 75:
//            AFNA_F75();//电容器保护参数
//            break;
//        case 76:
//            AFNA_F76();//电容器投切控制方式
//            break;
        case 81:
            AFNA_F81();//直流模拟量变比
            break;
        case 82:
            AFNA_F82();//直流模拟量限值
            break;
        case 83:
            AFNA_F83();//直流模拟量冻结参数
            break;
        case 90:
            AFNA_F90();//设置无线通信参数
            break;
            
        case 169:
            AFNA_F169();
            break;
            
        case 170:
            AFNA_F170();
            break;
        case 172:
            AFNA_F172();
            break;
            
        default:
            break;
    }
    
    XL_UINT16 auxlen = 0;
    if (_frame->aux.hasEC) {
        auxlen += 2;
    }
    if (_frame->aux.hasTP) {
        auxlen += 6;
    }
    
    if (_frame->userlen - 8 > offset + auxlen) {
        AFNA_RecursiveParse();
    }
}


void AFNA_F9()//终端事件记录配置设置
{
    printf("执行F9\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_terminal; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    //    Byte temp_value =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    begin = outoffset;
    
    //数据标志  2个字节
    identifier = pmEventEffecFlag;//事件记录有效标志位
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    XL_CHAR *result = malloc(150);
    memset(result, 0, strlen(result));
    XL_SINT8 i = 0;
    XL_SINT8 j = 0;
    XL_UINT64 temp = 0;
    XL_CHAR chTemp[20];
    for(i=0;i<8;i++)
    {
        temp = *(XL_UINT8*)(userdata + offset + i);
        for(j=0;j<8;j++)
        {
            if((temp & (0x01 << j))>0)
            {
                sprintf(chTemp,"%d",(i*8)+j+1);
                strcat(chTemp,",");
                strcat(result,chTemp);
            }
        }
        
    }
    printf("%s\n",result);
    XL_UINT16 stringlen = strlen(result);
    memcpy(buff + outoffset, &stringlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=stringlen;
    offset += 8;
    free(result);
    
    //数据标志  2个字节
    identifier = pmEventImptFlag;//事件重要性等级标志位
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    result = malloc(150);
    memset(result, 0, strlen(result));
    for(i=0;i<8;i++)
    {
        temp = *(XL_UINT8*)(userdata + offset+ i);
        for(j=0;j<8;j++)
        {
            if((temp & (0x01 << j))>0)
            {
                sprintf(chTemp,"%d",(i*8)+j+1);
                strcat(chTemp,",");
                strcat(result,chTemp);
            }
        }
        
    }
    
    printf("%s",result);
    stringlen = strlen(result);
    memcpy(buff + outoffset, &stringlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=stringlen;
    offset += 8;
    free(result);
    
    end = outoffset;
    len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}

void AFNA_F12()//终端状态量输入参数
{
    printf("执行F12\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_terminal; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    //    Byte temp_value =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    XL_SINT8 i = 0;
    
    begin = outoffset;
    
    XL_CHAR *result = malloc(50);
    
    memset(result, 0, strlen(result));
    //数据标志  2个字节
    identifier = pmStateVariableInter;//状态量接入标志位（对应1～8路状态量）
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    Byte temp = *(Byte*)(userdata+offset);
    XL_CHAR chTemp[4];
    for(i=0;i<8;i++)
    {
        if(( temp & ( 0x01 << i ) ) > 0)
        {
            sprintf(chTemp,"%d",i+1);
            strcat(chTemp,",");
            strcat(result,chTemp);
        }
    }
    printf("%s",result);
    XL_UINT16 stringlen = strlen(result);
    memcpy(buff + outoffset, &stringlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=stringlen;
    free(result);
    
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmStateVariableAttr;//状态量属性标志位（对应1～8路状态量）
    
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    result = malloc(50);
    
    memset(result, 0, strlen(result));
    for(i=0;i<8;i++)
    {
        if(( temp & ( 0x01 << i ) ) > 0)
        {
            sprintf(chTemp,"%d",i+1);
            strcat(chTemp,",");
            strcat(result,chTemp);
        }
    }
    stringlen = strlen(result);
    memcpy(buff + outoffset, &stringlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=stringlen;
    free(result);
    
    offset+=1;
    
    end = outoffset;
    len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}

void AFNA_F36()//终端上行通信流量门限设置
{
    printf("执行F36\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_terminal; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    //    Byte temp_value =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    
    //数据标志  2个字节
    identifier = pmCommFlowLmt;//月通信流量门限
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    *(XL_UINT32*)(buff+outoffset)=*(XL_UINT32*)(userdata+offset);
    outoffset+=sizeof(XL_UINT32);
    printf("%d",*(XL_UINT32*)(userdata+offset));
    offset+=4;
    
    end = outoffset;
    len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}

void AFNA_F60()//谐波限值
{
    printf("执行F60\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_terminal; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    int i=0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    
    //数据标志  2个字节
    for(i=0;i<21;i++)
    {
        identifier = pmVoltHarmoRateHiLmtZ+i;//总畸变电压含有率上限+i
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset,2,1);
    
        outoffset+=sizeof(XL_SINT64);
        offset+=2;
    }
    
    for(i=0;i<19;i++)
    {
        identifier = pmCurHarmoEffecHiLmtZ+i;//总畸变电流有效值上限+i
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset,2,2);
  
        outoffset+=sizeof(XL_SINT64);
        offset+=2;
    }
    end = outoffset;
    len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}

void AFNA_F61()//直流模拟量接入参数
{
    printf("执行F61\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_terminal; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    //    Byte temp_value =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    XL_CHAR *result = malloc(50);//存放解析结果字符串
    XL_SINT8 i=0;
    
    memset(result, 0, strlen(result));
    
    begin = outoffset;
    
    //数据标志  2个字节
    identifier = pmDCAnalogInter;//直流模拟量接入参数
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    Byte temp = *(Byte*)(userdata+offset);
    XL_CHAR chTemp[4];
    for(i=0;i<8;i++)
    {
        if(( temp & ( 0x01 << i ) ) > 0)
        {
            sprintf(chTemp,"%d",i+1);
            strcat(chTemp,",");
            strcat(result,chTemp);
        }
    }
    printf("%s",result);
    XL_UINT16 stringlen = strlen(result);
    memcpy(buff + outoffset, &stringlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=stringlen;
    free(result);
    offset+=1;
    
    end = outoffset;
    len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}

void AFNA_F91()//终端地理位置信息
{
    printf("执行F91\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_terminal; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    //    Byte temp_value =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    
    //数据标志  2个字节
    identifier = pmLongitude;//经度,秒
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 2, 2);

    outoffset+=sizeof(XL_UINT64);
    offset+=2;
    //经度,分
    *(Byte*)(buff+outoffset)=bcdToTime(userdata+offset);
    printf("%d\n",bcdToTime(userdata+offset));
    outoffset+=sizeof(Byte);
    offset+=1;
    //经度,度
    *(Byte*)(userdata+offset+1) &= 0x8F;
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 2, 0);

    outoffset+=sizeof(XL_SINT64);
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmLatitude;//纬度,秒
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 2, 2);

    outoffset+=sizeof(XL_UINT64);
    offset+=2;
    //经度,分
    *(Byte*)(buff+outoffset)=bcdToTime(userdata+offset);
    printf("%d分\n",bcdToTime(userdata+offset));
    outoffset+=sizeof(Byte);
    offset+=1;
    //经度,度
    *(Byte*)(userdata+offset+1) &= 0x8F;
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 2, 0);

    outoffset+=sizeof(XL_SINT64);
    offset+=2;
    
    end = outoffset;
    len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}



//终端上行通信口通信参数设置
void AFNA_F1()
{
    
    //上行通讯参数设置
    
    printf("执行F1\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_comm; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    
    //    int  i =0;
    XL_UINT16 temp  =0;
    //    Byte temp_value =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    //数据标志  2个字节
    identifier = pmRtsDelayTm;//终端数传机延时时间RTS
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    buff[outoffset]=*(Byte*)(userdata+offset);
    outoffset++;offset++;
    
    //数据标志  2个字节
    identifier = pmSendDelayTm;//终端作为启动站允许发送传输延时时间
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    buff[outoffset]=*(Byte*)(userdata+offset);
    outoffset++;offset++;
    
    //数据标志  2个字节
    identifier = pmRecvDelayTm;//终端等待从动站响应的超时时间
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  超时时间
    temp=(*(XL_UINT16*)(userdata+offset)&0x0fff);
    memcpy(buff + outoffset, &temp, 2);outoffset+=2;
    //重发次数
    identifier = pmRecvRetryTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp=((*(XL_UINT16*)(userdata+offset)>>12)&0x03);
    memcpy(buff + outoffset, &temp, 2);outoffset+=2;
    
    offset+=2;
    
    
    
    
    //数据标志  2个字节
    identifier = pmNeedConfirm1;//1类数据自动上报
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容
    buff[outoffset]=(*(Byte*)(userdata+offset)&0x01);
    outoffset++;
    
    //数据标志  2个字节
    identifier = pmNeedConfirm2;//2类数据自动上报
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    buff[outoffset]=(*(Byte*)(userdata+offset)&0x02);
    outoffset++;
    
    //数据标志  2个字节
    identifier = pmNeedConfirm3;//3类数据自动上报
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    buff[outoffset]=(*(Byte*)(userdata+offset)&0x04);
    outoffset++;offset++;
    
    
    //数据标志  2个字节
    identifier = pmHeartPeriod;//心跳周期
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    buff[outoffset]=(*(Byte*)(userdata+offset));
    outoffset++;offset++;
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
}
//主站IP地址和端口
void AFNA_F3()
{
    printf("执行F3\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_comm; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    
    //    int  i =0;
    //    XL_UINT16 temp  =0;
    //    Byte temp_value =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    
    //数据标志  2个字节
    identifier = pmMasterPrimeIP;//主站主用IP
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //
    memcpy(buff + outoffset, userdata+offset, 1);
    outoffset+=1;
    offset+=1;
    identifier = pmMasterPrimeIP;//主站主用IP
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //
    memcpy(buff + outoffset, userdata+offset, 1);
    outoffset+=1;
    offset+=1;
    identifier = pmMasterPrimeIP;//主站主用IP
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //
    memcpy(buff + outoffset, userdata+offset, 1);
    outoffset+=1;
    offset+=1;
    identifier = pmMasterPrimeIP;//主站主用IP
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //
    memcpy(buff + outoffset, userdata+offset, 1);
    outoffset+=1;
    offset+=1;
    
    
    
    
    
    
    
    
    //数据标志  2个字节
    identifier = pmMasterPrimePort;//主站主用端口
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //主站端口  2个字节
    memcpy(buff + outoffset, userdata+offset, 2);
    outoffset+=2;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmMasterStandbyIP;//主站备用IP
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //主站备用ip
    memcpy(buff + outoffset, userdata+offset, 1);
    outoffset+=1;
    offset+=1;
    
    identifier = pmMasterStandbyIP;//主站备用IP
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //主站备用ip
    memcpy(buff + outoffset, userdata+offset, 1);
    outoffset+=1;
    offset+=1;
    
    identifier = pmMasterStandbyIP;//主站备用IP
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //主站备用ip
    memcpy(buff + outoffset, userdata+offset, 1);
    outoffset+=1;
    offset+=1;
    
    identifier = pmMasterStandbyIP;//主站备用IP
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //主站备用ip
    memcpy(buff + outoffset, userdata+offset, 1);
    outoffset+=1;
    offset+=1;

    
    //数据标志  2个字节
    identifier = pmMasterStandbyPort;//主站备用端口
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //主站端口  2个字节
    memcpy(buff + outoffset, userdata+offset, 2);
    outoffset+=2;
    offset+=2;
    
    
    //主站APN
    identifier = pmMasterAPN;//主站APN
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //主站端口  2个字节
    memcpy(buff + outoffset, userdata+offset, 16);
    outoffset+=16;
    offset+=16;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);

    
}
//终端IP地址和端口
void AFNA_F7()
{
    printf("执行F7\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_comm; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    
    //    int  i =0;
    XL_UINT16 temp  =0;
    //    Byte temp_value =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    
    //数据标志  2个字节
    identifier = pmIP;//终端IP标志
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);//终端ip地址
    outoffset+=1;
    offset+=1;
    //数据标志  2个字节
    identifier = pmIP;//终端IP标志
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);//终端ip地址
    outoffset+=1;
    offset+=1;
    //数据标志  2个字节
    identifier = pmIP;//终端IP标志
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);//终端ip地址
    outoffset+=1;
    offset+=1;
    //数据标志  2个字节
    identifier = pmIP;//终端IP标志
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);//终端ip地址
    outoffset+=1;
    offset+=1;
    
    
    //数据标志  2个字节
    identifier = pmSubnetMask;//子网掩码
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);//子网掩码
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmSubnetMask;//子网掩码
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);//子网掩码
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmSubnetMask;//子网掩码
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);//子网掩码
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmSubnetMask;//子网掩码
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);//子网掩码
    outoffset+=1;
    offset+=1;
    
    
    //数据标志  2个字节
    identifier = pmGateWay;//网关
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);//网关
    outoffset+=1;
    offset+=1;
    
    identifier = pmGateWay;//网关
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);//网关
    outoffset+=1;
    offset+=1;
    
    identifier = pmGateWay;//网关
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);//网关
    outoffset+=1;
    offset+=1;
    
    identifier = pmGateWay;//网关
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);//网关
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmProxyType;//代理类型
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    memcpy(buff + outoffset, userdata+offset, 1);//代理类型
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmProxyAddr;//代理服务器地址
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);
    outoffset+=1;
    offset+=1;
    
    identifier = pmProxyAddr;//代理服务器地址
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);
    outoffset+=1;
    offset+=1;
    
    identifier = pmProxyAddr;//代理服务器地址
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);
    outoffset+=1;
    offset+=1;
    
    identifier = pmProxyAddr;//代理服务器地址
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  4个字节
    memcpy(buff + outoffset, userdata+offset, 1);
    outoffset+=1;
    offset+=1;
    
    
    
    //数据标志  2个字节
    identifier = pmProxyPort;//代理服务器端口
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    memcpy(buff + outoffset, userdata+offset, 2);//代理类型端口
    outoffset+=2;
    offset+=2;
    
    
    //数据标志  2个字节
    identifier = pmProxyConnType;//代理服务器连接方式
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    memcpy(buff + outoffset, userdata+offset, 1);//代理服务器连接方式
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmProxyUserNameLen;//用户名长度m
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    temp =*(Byte*)(userdata+offset);
    memcpy(buff + outoffset, userdata+offset, 1);//
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmProxyUserName;//用户名
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据长度 可变长
    memcpy(buff + outoffset, &temp, 1);outoffset+=1;
    
    
    //数据内容  m个字节
    memcpy(buff + outoffset, userdata+offset,temp);//
    outoffset+=temp;
    offset+=temp;
    
    //数据标志  2个字节
    identifier = pmProxyPassWordLen;//密码长度
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp =*(Byte*)(userdata+offset);
    //数据内容  m个字节
    memcpy(buff + outoffset, userdata+offset,1);//
    outoffset+=1;
    offset+=1;
    
    
    //数据标志  2个字节
    identifier = pmProxyPassWord;//密码
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //密码长度
    memcpy(buff + outoffset, &temp, 1);outoffset+=1;
    
    
    //数据内容  m个字节
    memcpy(buff + outoffset, userdata+offset,temp);//
    outoffset+=temp;
    offset+=temp;
    
    //数据标志  2个字节
    identifier = pmListenPort;//终端侦听端口
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  m个字节
    memcpy(buff + outoffset, userdata+offset,2);//
    outoffset+=2;
    offset+=2;
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);}


//终端参数
//终端电能表/交流采样装置配置参数-jp柜
void AFNA_F10()
{
    printf("执行F10\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_mtr_comm; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;//数据标志
    
    
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    begin = outoffset;
    
    XL_UINT16 mtrCnt = 0;//配置的测量点数
    mtrCnt = *(XL_UINT16*)(userdata + offset);
    offset += 2;
    
    XL_UINT8 i = 0;
    for(i = 0;i < mtrCnt; i++)
    {
        
        identifier = pmMtrDeviceNo;//测量点装置序号
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_UINT16*)(buff+outoffset) = *(XL_UINT16*)(userdata+offset);//两字节bin类型
        offset += 2;
        outoffset += 2;
        
        //数据标志  2个字节
        identifier = pmMtrNo;//测量点号
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_UINT16*)(buff+outoffset) = *(XL_UINT16*)(userdata+offset);//两字节bin类型
        offset += 2;
        outoffset += 2;
        
        XL_UINT8 temp = 0;
        identifier = pmCommSpeed;//通信速率
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        temp = *(Byte*)(userdata + offset);
        switch (temp>>5) {
            case 0:
                //未设置，或使用默认
                *(XL_UINT16*)(buff+outoffset) = 0;
                break;
            case 1:
                *(XL_UINT16*)(buff+outoffset) = 600;
                break;
            case 2:
                *(XL_UINT16*)(buff+outoffset) = 1200;
                break;
            case 3:
                *(XL_UINT16*)(buff+outoffset) = 2400;
                break;
            case 4:
                *(XL_UINT16*)(buff+outoffset) = 4800;
                break;
            case 5:
                *(XL_UINT16*)(buff+outoffset) = 7200;
                break;
            case 6:
                *(XL_UINT16*)(buff+outoffset) = 9600;
                break;
            case 7:
                *(XL_UINT16*)(buff+outoffset) = 19200;
                break;
            default:
                break;
        }
        
        outoffset += sizeof(XL_UINT16);
        
        identifier = pmCommPort;//通信端口号
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(Byte*)(buff+outoffset) = (temp & 0x1F);
        outoffset += sizeof(Byte);
        offset += 1;
        
        identifier = pmCommPrtlType;//通信协议类型
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        XL_CHAR* result = malloc(50);
        memset(result, 0, strlen(result));
        temp = *(XL_UINT8*)(userdata+offset);
        switch (temp) {
            case 0:
                result = "无需抄表";
                break;
            case 1:
                result = "DL/T 645—1997";
                break;
            case 30:
                result = "DL/T 645—2007";
                break;
            case 31:
                result = "串行接口连接窄带低压载波通信模块";
                break;
                
            default:
                break;
        }
        
        //长度
        XL_UINT16 mtrcommlen = strlen(result);
        memcpy(buff + outoffset, &mtrcommlen, sizeof(XL_UINT16)); outoffset+=2;
        //内容
        memcpy(buff + outoffset, result, mtrcommlen);outoffset+= mtrcommlen;
        offset++;
        
        free(result);
        
        identifier = pmCommAddr;//通信地址
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        XL_CHAR chTemp[7];
        for(i = 0; i < 6; i++)
        {
            chTemp[i] = bcdToTime(userdata + offset+i);
        }
        chTemp[6] ='\0';
        
        mtrcommlen = strlen(chTemp);
        memcpy(buff + outoffset, &mtrcommlen, sizeof(XL_UINT16)); outoffset+=2;
        //内容
        memcpy(buff + outoffset, result, mtrcommlen);outoffset+= mtrcommlen;
        offset += 6;
        
        identifier = pmCommPassWord;//通信密码
        memcpy(buff + outoffset, &identifier, 2);outoffset += 2;
        XL_UINT64 pwTemp = 0 ;
        memcpy(&pwTemp, userdata+offset, 6);
        *(XL_UINT64*)(buff + outoffset) = pwTemp;
        offset += 6;
        outoffset += sizeof(XL_UINT64);
        
        identifier = pmFeeNum;//通信费率个数
        memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
        *(XL_UINT8*)(buff+outoffset) = (*(XL_UINT8*)(userdata + offset))&0x3F;
        offset += 1;
        outoffset += 1;
        
        identifier = pmIntegerNum;//整数位个数
        memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
        temp = *(XL_UINT8*)(userdata+offset);
        
        *(XL_UINT8*)(buff+outoffset) = ((temp>>2)&0x03)+4;outoffset++;
        
        identifier = pmDecimalNum;//小数位个数
        memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
        *(XL_UINT8*)(buff + outoffset) = (temp&0x03)+1;
        
        offset++;
        
        offset += 7;//所属采集器通信地址,6字节；用户大类号及用户小类号，1字节，此处不做处理
    }
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);

}

//终端总加组配置参数
void AFNA_F14()
{
    
    
}
//有功总电能量差动越限事件参数设置
void AFNA_F15()
{
    
    
}

//虚拟专网用户名、密码
void AFNA_F16()
{
    
    printf("执行F7\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_comm; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    
    //    int  i =0;
    //    XL_UINT16 temp  =0;
    //    Byte temp_value =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    
    XL_CHAR *result = malloc(100);
    memset(result, 0, strlen(result));
    
    //数据标志  2个字节
    identifier = pmVPNUserName;//虚拟专网用户名
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    char v[1];
    for(int i = 0;i<32;i++){
        int tmp = userdata[offset];
        if (tmp) {
            sprintf(v,"%c",tmp);
            strcat(result, v);
        }
        offset++;
    }
    printf("%s",result);
    XL_UINT16 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
    
    free(result);
    
//    //数据内容 32个字节 ascii格式
//    memcpy(buff + outoffset, userdata+offset, 32);
//    outoffset+=32;
//    offset+=32;
    
    
    //数据标志  2个字节
    XL_CHAR *result1 = malloc(100);
    memset(result1, 0, strlen(result1));
    
    identifier = pmVPNPassWord;//虚拟专网密码
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;

    for(int i = 0;i<32;i++){
        XL_UINT8 tmp = userdata[offset];
        if (tmp) {
            sprintf(v,"%c",tmp);
            strcat(result1, v);
        }
        offset++;
    }
    printf("%s",result1);
    eventlen = strlen(result1);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result1));outoffset+=eventlen;
    
    free(result1);

//    //数据内容 32个字节 ascii格式
//    memcpy(buff + outoffset, userdata+offset, 32);
//    outoffset+=32;
//    offset+=32;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
}

//测量点参数
//测量点基本参数
void AFNA_F25()
{
    printf("执行F25\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_mtr; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    
    //    int  i =0;
    XL_SINT64 temp  =0;
    //    Byte temp_value =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    
    begin = outoffset;
    
    //数据标志  2个字节
    identifier = pmPTRatio;//电压互感器倍率
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    memcpy(buff + outoffset, userdata+offset, 2);//
    outoffset+=2;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmCTRatio;//电流互感器倍率
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    memcpy(buff + outoffset, userdata+offset, 2);//
    outoffset+=2;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmRatedVoltage;//额定电压  A.7格式 2个字节 1个小数点
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节
    temp=bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);//
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmRatedCurrent;//额定电流  A.22格式 1个字节 1个小数点
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    temp=bcdtouint(userdata+offset, 1, 1);
    memcpy(buff + outoffset, &temp, 8);//
    outoffset+=8;
    offset+=1;
    
    
    //数据标志  2个字节
    identifier = pmRatedLoad;//额定负荷  A.23格式3个字节 4个小数点
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);//
    outoffset+=8;
    offset+=3;
    
    
    //数据标志  2个字节
    identifier = pmPowerConnWay;//电源接线方式
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    
    Byte test =0;
    XL_CHAR *result = (XL_CHAR *) malloc(200);
    memset(result, 0, strlen(result));
    test=(*(Byte*)(userdata+offset)&0x03);
    switch (test) {
        case 0:
            strcat(result, "备用");
            break;
        case 1:
            strcat(result, "三相三线");
            break;
        case 2:
            strcat(result, "三相四线");
            break;
        case 3:
            strcat(result, "单相表");
            break;
        default:
            break;
    }
    test=(*(Byte*)(userdata+offset)>>2&0x03);
    switch (test) {
        case 0:
            strcat(result, "接线不确定");
            break;
        case 1:
            strcat(result, "A相接线");
            break;
        case 2:
            strcat(result, "B相接线");
            break;
        case 3:
            strcat(result, "C相接线");
            break;
        default:
            break;
    }
    //长度
    XL_UINT16 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16)); outoffset+=2;
    //内容
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    offset++;
    
    
    
    
    //    //数据内容  1个字节
    //    memcpy(buff + outoffset, userdata+offset, 1);//
    //    outoffset+=1;
    //    offset+=1;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    free(result);
}
//测量点限值参数
void AFNA_F26()
{
    
    printf("执行F26\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_mtr; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    
    //    int  i =0;
    XL_SINT64 temp  =0;
    //    Byte temp_value =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    
    //数据标志  2个字节
    identifier = pmVoltRegularHiLmt;//电压合格上限
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 格式a.7－2个字节   1个小数
    temp=bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    
    //数据标志  2个字节
    identifier = pmVoltRegularLoLmt;//电压合格下限
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 格式a.7－2个字节   1个小数
    temp=bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmSeverVoltLmt;//电压断相门限
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 格式a.7－2个字节   1个小数
    temp=bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmVoltHHLmt;//电压上上限（过压门限）
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 格式a.7－2个字节   1个小数
    temp=bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmVoltHHLmtDuration;//越限持续时间
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    memcpy(buff + outoffset,userdata+offset , 1);
    outoffset+=1;
    offset+=1;
    
    
    //数据标志  2个字节
    identifier = pmVoltOverRecoverFactor;//越限恢复系数
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.5格式 有符号 2个字节  1个小数
    temp=bcdtosint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    
    //数据标志  2个字节
    identifier = pmVoltLLLmt;//电压下下限（欠压门限）
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 格式a.7－2个字节   1个小数
    temp=bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    
    //数据标志  2个字节
    identifier = pmVoltLLLmtDuration;//欠压越限持续时间
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    memcpy(buff + outoffset,userdata+offset , 1);
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmVoltUnderRecoverFactor;//欠压越限恢复系数
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.5格式 有符号 2个字节  1个小数
    temp=bcdtosint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    
    //数据标志  2个字节
    identifier = pmCurHHLmt;//相电流上上限（过流门限）
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.25格式 有符号 3个字节  3个小数
    temp=bcdtosint(userdata+offset, 3, 3);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=3;
    
    //数据标志  2个字节
    identifier = pmCurHHLmtDuration;//上上限越限持续时间
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    memcpy(buff + outoffset,userdata+offset , 1);
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmCurHHRecoverFactor;//上上限越限恢复系数
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.5格式 有符号 2个字节  1个小数
    temp=bcdtosint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    
    
    
    
    
    
    
    //数据标志  2个字节
    identifier = pmCurHiLmt;//相电流上限（额定电流门限）
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.25格式 有符号 3个字节  3个小数
    temp=bcdtosint(userdata+offset, 3, 3);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=3;
    
    //数据标志  2个字节
    identifier = pmCurHiLmtDuration;//上限越限持续时间
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    memcpy(buff + outoffset,userdata+offset , 1);
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmCurHiRecoverFactor;//上限越限恢复系数
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.5格式 有符号 2个字节  1个小数
    temp=bcdtosint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    
    
    
    //数据标志  2个字节
    identifier = pmZeroCurHiLmt;//零序电流上限
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.25格式 有符号 3个字节  3个小数
    temp=bcdtosint(userdata+offset, 3, 3);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=3;
    
    //数据标志  2个字节
    identifier = pmZeroCurHiLmtDuration;//零序电流越限限持续时间
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    memcpy(buff + outoffset,userdata+offset , 1);
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmZeroCurHiRecoverFactor;//零序电流越限越限恢复系数
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.5格式 有符号 2个字节  1个小数
    temp=bcdtosint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    
    //数据标志  2个字节
    identifier = pmAPHHLmt;//视在功率上上限
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.23格式 无符号 3个字节  4个小数
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=3;
    
    //数据标志  2个字节
    identifier = pmAPHHDuration;//视在功率上上限越限限持续时间
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    memcpy(buff + outoffset,userdata+offset , 1);
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmAPHHRecoverFactor;//视在功率上上限越限越限恢复系数
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.5格式 有符号 2个字节  1个小数
    temp=bcdtosint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    
    
    //数据标志  2个字节
    identifier = pmAPHiLmt;//视在功率上限
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.23格式 无符号 3个字节  4个小数
    temp=bcdtouint(userdata+offset, 3, 4);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=3;
    
    //数据标志  2个字节
    identifier = pmAPHiDuration;//视在功率上限越限限持续时间
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    memcpy(buff + outoffset,userdata+offset , 1);
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmAPHiRecoverFactor;//视在功率上限越限越限恢复系数
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.5格式 有符号 2个字节  1个小数
    temp=bcdtosint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    
    
    //数据标志  2个字节
    identifier = pmUnbalVoltLmt;//三相电压不平衡值
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.5格式 有符号 2个字节  1个小数
    temp=bcdtosint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmUnbalVoltDuration;//三相电压不平衡值越限限持续时间
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    memcpy(buff + outoffset,userdata+offset , 1);
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmUnbalVoltRecoverFactor;//三相电压不平衡值越限越限恢复系数
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.5格式 有符号 2个字节  1个小数
    temp=bcdtosint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    
    
    //数据标志  2个字节
    identifier = pmUnbalCurLmt;//三相电流不平衡值
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a5格式 有符号 2个字节  1个小数
    temp=bcdtosint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmUnbalCurDuration;//三相电流不平衡值越限限持续时间
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    memcpy(buff + outoffset,userdata+offset , 1);
    outoffset+=1;
    offset+=1;
    
    //数据标志  2个字节
    identifier = pmUnbalCurRecoverFactor;//三相电流不平衡值越限越限恢复系数
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  2个字节 a.5格式 有符号 2个字节  1个小数
    temp=bcdtosint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    
    //数据标志  2个字节
    identifier = pmLostVoltTmLmt;//三相电流不平衡值越限限持续时间
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容  1个字节
    memcpy(buff + outoffset,userdata+offset , 1);
    outoffset+=1;
    offset+=1;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
}
//测量点铜损、铁损参数
void AFNA_F27()
{
    printf("执行F27\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_mtr; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    
    //    int  i =0;
    XL_SINT64 temp  =0;
    //    Byte temp_value =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    
    //数据标志  2个字节
    identifier = pmRa;//A相电阻RA
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 a.26格式  无符号 2个字节 3位小数
    temp=bcdtouint(userdata+offset, 2, 3);
    memcpy(buff + outoffset,&temp , 8);
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmXa;//A相电抗XA
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 a.26格式  无符号 2个字节 3位小数
    temp=bcdtouint(userdata+offset, 2, 3);
    memcpy(buff + outoffset,&temp , 8);
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmGa;//A相电导GA
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 a.26格式  无符号 2个字节 3位小数
    temp=bcdtouint(userdata+offset, 2, 3);
    memcpy(buff + outoffset,&temp , 8);
    outoffset+=8;
    offset+=2;
    
    
    //数据标志  2个字节
    identifier = pmBa;//A相电纳BA
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 a.26格式  无符号 2个字节 3位小数
    temp=bcdtouint(userdata+offset, 2, 3);
    memcpy(buff + outoffset,&temp , 8);
    outoffset+=8;
    offset+=2;
    
    
    
    
    //数据标志  2个字节
    identifier = pmRb;//b相电阻RA
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 a.26格式  无符号 2个字节 3位小数
    temp=bcdtouint(userdata+offset, 2, 3);
    memcpy(buff + outoffset,&temp , 8);
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmXb;//b相电抗XA
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 a.26格式  无符号 2个字节 3位小数
    temp=bcdtouint(userdata+offset, 2, 3);
    memcpy(buff + outoffset,&temp , 8);
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmGb;//b相电导GA
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 a.26格式  无符号 2个字节 3位小数
    temp=bcdtouint(userdata+offset, 2, 3);
    memcpy(buff + outoffset,&temp , 8);
    outoffset+=8;
    offset+=2;
    
    
    //数据标志  2个字节
    identifier = pmBb;//b相电纳BA
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 a.26格式  无符号 2个字节 3位小数
    temp=bcdtouint(userdata+offset, 2, 3);
    memcpy(buff + outoffset,&temp , 8);
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmRc;//c相电阻RA
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 a.26格式  无符号 2个字节 3位小数
    temp=bcdtouint(userdata+offset, 2, 3);
    memcpy(buff + outoffset,&temp , 8);
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmXc;//c相电抗XA
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 a.26格式  无符号 2个字节 3位小数
    temp=bcdtouint(userdata+offset, 2, 3);
    memcpy(buff + outoffset,&temp , 8);
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmGc;//c相电导GA
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 a.26格式  无符号 2个字节 3位小数
    temp=bcdtouint(userdata+offset, 2, 3);
    memcpy(buff + outoffset,&temp , 8);
    outoffset+=8;
    offset+=2;
    
    
    //数据标志  2个字节
    identifier = pmBc;//c相电纳BA
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //数据内容 a.26格式  无符号 2个字节 3位小数
    temp=bcdtouint(userdata+offset, 2, 3);
    memcpy(buff + outoffset,&temp , 8);
    outoffset+=8;
    offset+=2;
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
    
    
}
//测量点功率因数分段限值
void AFNA_F28()
{
    
    printf("执行F28\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_mtr; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    
    //    int  i =0;
    XL_SINT64 temp  =0;
    //    Byte temp_value =0;
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    
    //数据标志  2个字节
    identifier = pmPfLmt1;//功率因数分段限值1
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp=bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    //数据标志  2个字节
    identifier = pmPfLmt2;//功率因数分段限值2
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    temp=bcdtouint(userdata+offset, 2, 1);
    memcpy(buff + outoffset, &temp, 8);
    outoffset+=8;
    offset+=2;
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
}


void AFNA_F45()//功控轮次设定
{
    
    
}

void AFNA_F81()//直流模拟量变比
{
    
    
    
}
void AFNA_F82()//直流模拟量限值
{
    
    
    
}
void AFNA_F83()//直流模拟量冻结参数
{
    
    
}
void AFNA_F90()//设置无线通信参数
{
    
    
}

void AFNA_F169()//变压器基本参数设置
{
    printf("执行F169\n");
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_terminal; outoffset++;
    
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    XL_UINT16 len=0;  //输出缓冲区数据长度
    
    
    begin = outoffset;
    
    //数据标志  2个字节
    identifier = pmEpId;//设备编号
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    XL_CHAR chTemp[20];
    XL_UINT8 i = 0;
    XL_CHAR* result=malloc(20);
    
    memset(result, 0, strlen(result));
    for(i = 0;i < 16;i++)
    {
        sprintf(chTemp, "%c", *(XL_CHAR*)(userdata + offset+i));
        
        strcat(result, chTemp);
    }
    
    XL_UINT16 stringlen = strlen(result);
    memcpy(buff + outoffset, &stringlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=stringlen;
    offset += 16;
    free(result);
    
    //设备类型，1字节，无具体定义，先跳过
    offset++;
    
    //额定电压
    identifier = pmTerminalRatedVoltage;
    memcpy(buff + outoffset, &identifier, 2);outoffset += 2;
    *(XL_UINT64*)(buff+outoffset) = bcdtouint(userdata+offset, 2, 1);
    offset+=2;
    outoffset+=sizeof(XL_UINT64);
    
    //额定电流
    identifier = pmTerminalRatedCurrent;
    memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
    *(XL_UINT64*)(buff+outoffset) = bcdtouint(userdata + offset, 3, 1);
    offset += 3;
    outoffset += sizeof(XL_UINT64);
    
    //额定容量
    identifier = pmRatedCapital;
    memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
    *(XL_UINT16*)(buff+outoffset) = *(XL_UINT16*)(userdata + offset);
    offset += 2;
    outoffset += sizeof(XL_UINT16);
    
    //满载损耗
    identifier = pmFullLoadLoss;
    memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
    *(XL_UINT16*)(buff+outoffset) = *(XL_UINT16*)(userdata + offset);
    offset += 2;
    outoffset += sizeof(XL_UINT16);
    
    //空载损耗
    identifier = pmNoLoadLoss;
    memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
    *(XL_UINT16*)(buff+outoffset) = *(XL_UINT16*)(userdata + offset);
    offset += 2;
    outoffset += sizeof(XL_UINT16);
    
    //阻抗电压
    identifier = pmImpedanceVoltage;
    memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
    *(XL_UINT64*)(buff+outoffset) = bcdtouint(userdata+offset, 2, 1);
    offset+=2;
    outoffset+=sizeof(XL_UINT64);
    
    //额定频率
    identifier = pmRatedFrequency;
    memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
    *(XL_UINT64*)(buff+outoffset) = bcdtouint(userdata+offset, 2, 1);
    offset+=2;
    outoffset+=sizeof(XL_UINT64);
    
    //制造日期
    identifier = pmManufactureDate;
    memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
    
    *(Byte*)(buff+outoffset) = bcdToTime(userdata +offset);//月
    outoffset++;
    offset++;
    
    *(Byte*)(buff+outoffset) = bcdToTime(userdata +offset);//年
    outoffset++;
    offset++;
    
    *(Byte*)(buff+outoffset) = bcdToTime(userdata +offset);//年
    outoffset++;
    offset++;
    
    //出厂编号,16字节,ASCII码
    identifier = pmManufactureNo;
    memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
    result=malloc(20);
    memset(result, 0, strlen(result));
    for(i = 0;i < 16;i++)
    {
        sprintf(chTemp, "%c", *(XL_CHAR*)(userdata + offset+i));
        
        strcat(result, chTemp);
    }
    
    stringlen = strlen(result);
    memcpy(buff + outoffset, &stringlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=stringlen;
    offset += 16;
    free(result);
    
    //连接组别
    identifier = pmConnGroups;
    memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
    result=malloc(20);
    memset(result, 0, strlen(result));
    for(i = 0;i < 8;i++)
    {
        sprintf(chTemp, "%c", *(XL_CHAR*)(userdata + offset+i));
        
        strcat(result, chTemp);
    }
    
    stringlen = strlen(result);
    memcpy(buff + outoffset, &stringlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=stringlen;
    offset += 16;
    free(result);
    
    //相数
    identifier = pmPhaseNum;
    memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
    *(XL_UINT8*)(buff+outoffset) = *(XL_UINT8*)(userdata + offset);
    offset += 1;
    outoffset += sizeof(XL_UINT8);
    
    //绝缘耐热等级
    identifier = pmInsulationGrade;
    memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
    result=malloc(20);
    
    memset(result, 0, strlen(result));
    sprintf(chTemp, "%c", *(XL_CHAR*)(userdata + offset));
    
    strcat(result, chTemp);
    
    stringlen = strlen(result);
    memcpy(buff + outoffset, &stringlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=stringlen;
    offset += 1;
    free(result);
    
    //温升
    identifier = pmTempratureRise;
    memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
    *(XL_UINT64*)(buff+outoffset) = bcdtouint(userdata+offset, 2, 1);
    offset+=2;
    outoffset+=sizeof(XL_UINT64);
    
    //冷却方式
    identifier = pmCoolingWay;
    memcpy(buff+outoffset, &identifier, 2);outoffset += 2;
    
    result=malloc(50);
    memset(result, 0, strlen(result));
    XL_UINT8 uint8Temp=(*(Byte*)(userdata+offset));
    switch (uint8Temp) {
        case 0:
            break;
        case 1:
            result = "油浸自冷(ONAN)";
            break;
        case 2:
            result = "油浸风冷(ONAF)";
            break;
        case 3:
            result = "强迫油循环风冷(OFAF)";
            break;
        case 4:
            result = "强迫油循环水冷(OFWF)";
            break;
        case 5:
            result = "强迫导向油循环风冷(ODAF)";
            break;
        case 6:
            result = "强迫导向油循环水冷(ODWF)";
            break;
        default:
            break;
    }
    //长度
    XL_UINT16 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16)); outoffset+=2;
    //内容
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    offset++;
    free(result);
    
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
}


//wifi通信设置
void AFNA_F170(){

    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_comm; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    XL_UINT16 len=0;  //输出缓冲区数据长度
    begin = outoffset;
    
    XL_CHAR *result = malloc(100);
    memset(result, 0, strlen(result));
    
    //数据标志  2个字节
    identifier = pmWifiSsid;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    char v[1];
    for(int i = 0;i<16;i++){
        int tmp = userdata[offset];
        if (tmp) {
            sprintf(v,"%c",tmp);
            strcat(result, v);
        }
        offset++;
    }
    printf("%s",result);
    XL_UINT16 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
    
    free(result);
    
    //数据标志  2个字节
    XL_CHAR *result1 = malloc(100);
    memset(result1, 0, strlen(result1));
    
    identifier = pmWifiPsw;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    
    for(int i = 0;i<16;i++){
        XL_UINT8 tmp = userdata[offset];
        if (tmp) {
            sprintf(v,"%c",tmp);
            strcat(result1, v);
        }
        offset++;
    }
    printf("%s",result1);
    eventlen = strlen(result1);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result1));outoffset+=eventlen;
    
    free(result1);
    
    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
}


//用户管理
void AFNA_F172(){
    
    //1个字节长度  数据类型
    buff[outoffset] = parameter_data_comm; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    XL_UINT16 identifier;
    
    XL_UINT16 len=0;  //输出缓冲区数据长度
    begin = outoffset;
    

    
    for(int i = 0;i<4;i++){
        
        XL_CHAR *result = malloc(100);
        memset(result, 0, strlen(result));
        
        //数据标志  2个字节
        identifier = pmUserName;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        
        char v[1];
        for(int i = 0;i<16;i++){
            int tmp = userdata[offset];
            if (tmp) {
                sprintf(v,"%c",tmp);
                strcat(result, v);
            }
            offset++;
        }
        printf("%s",result);
        XL_UINT16 eventlen = strlen(result);
        memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16));outoffset+=2;
        memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
        
        free(result);
        
        //数据标志  2个字节
        XL_CHAR *result1 = malloc(100);
        memset(result1, 0, strlen(result1));
        
        identifier = pmPsw;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        
        for(int i = 0;i<16;i++){
            XL_UINT8 tmp = userdata[offset];
            if (tmp) {
                sprintf(v,"%c",tmp);
                strcat(result1, v);
            }
            offset++;
        }
        printf("%s",result1);
        eventlen = strlen(result1);
        memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16));outoffset+=2;
        memcpy(buff + outoffset, result, strlen(result1));outoffset+=eventlen;
        
        free(result1);
    }

    end = outoffset;
    len = end - begin;
    memcpy(buff + begin - 2,&len, 2);
  
}














