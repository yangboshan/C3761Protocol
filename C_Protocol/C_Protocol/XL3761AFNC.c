//
//  XL3761AFNC.c
//  C_Protocol
//
//  Created by JY on 14-1-15.
//  Copyright (c) 2014骞?XLDZ. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "XL3761AFNC.h"
#include "XLDataId.h"
#include "XLCommon.h"
#include "XLUtility.h"


void AFNC_RecursiveParse();

void AFNC_F3();
void AFNC_F7();
void AFNC_F9();
void AFNC_F10();
void AFNC_F33();
void AFNC_F34();
void AFNC_F35();
void AFNC_F36();
void AFNC_F57();
void AFNC_F58();
void AFNC_F73();

void AFNC_F29();
void AFNC_F49();
void AFNC_F25();

void initUserDataForAfnc(XL_UINT16 *type,void *frame,XL_UINT16* outlen,Byte** outbuf){
    
    
    offset=0;
    outoffset = 0;
    
    _type = type;
    _outlen = outlen;
    _outbuf = outbuf;
    
    _frame = (FRAME*)frame;
    
    userdata = _frame->frameData;
    
    buff = malloc(_frame->userlen*3 + 50);
    memset(buff,0,_frame->userlen*3 + 50);
    *_outbuf = buff;

    AFNC_RecursiveParse();
    *outlen = outoffset;
    
    free(userdata);
    free(_frame);
    //用完之后,将outoffset置位初值0
	outoffset = 0;
    offset = 0;
}

void AFNC_RecursiveParse(){
    
    XL_UINT16 fn = parsedadt((XL_UINT16)userdata[offset + 3],
                                    (XL_UINT16)userdata[offset + 2],0);
    
    //拷贝
    memcpy(buff + outoffset, userdata + offset, 1); offset+=2;outoffset++;
    
    memcpy(buff + outoffset, &fn, 1);                offset+=2;outoffset++;
    printf("fn=%d\n",fn);

    switch (fn) {
        case 49:
            AFNC_F49();
            break;
        case 25:
            AFNC_F25();
            break;
        case 3:
            AFNC_F3();
            break;
        case 7:
            AFNC_F7();
            break;
        case 9:
            AFNC_F9();
            break;
        case 10:
            AFNC_F10();
            break;
        case 29:
            AFNC_F29();
            break;
        case 33:
            printf("into AFNC_F33\n");
            AFNC_F33();
            break;
        case 34:
            AFNC_F34();
            break;
        case 35:
            AFNC_F35();
            break;
        case 36:
            AFNC_F36();
            break;
        case 57:
            AFNC_F57();
            break;
        case 58:
            AFNC_F58();
            break;
        case 73:
            AFNC_F73();
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
        AFNC_RecursiveParse();
}
}
/*终端参数状态*/
void AFNC_F3()
{
    buff[outoffset] = terminal_rt_basic_sta; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;
    
    XL_UINT16 identifier;
    identifier = rtParameterStatus;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    int i = 0;
    printf("解析1类数据,F3:");
    for(i=0;i<31;i++)
    {
        buff[outoffset] = *(Byte*)(userdata +offset);
        printf("buff[%d]=%02x,",i,buff[outoffset]);
        outoffset += 1;
        offset += 1;
    }
    printf("\n");
    
    end = outoffset;
    
    XL_UINT16 len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}

/*终端事件计数器当前值*/
void AFNC_F7()
{
    buff[outoffset] = terminal_rt_basic_sta; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;

    printf("解析1类数据,F7:");
    
    XL_UINT16 identifier;
    //重要事件计数器EC1
    identifier = rtImptEventCount;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    buff[outoffset] = *(Byte*)(userdata +offset);
    printf("重要事件计数器的值:%02x\n",buff[outoffset]);
    
    offset++;
    outoffset++;
    //一般事件计数器EC2
    identifier = rtCommonEventCount;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    buff[outoffset] = *(Byte*)(userdata +offset);
    printf("一般事件计数器的值:%02x\n",buff[outoffset]);
    offset++;
    outoffset++;

    end = outoffset;
    
    XL_UINT16 len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}
/*终端状态量及变位标志*/
void AFNC_F9()
{
    buff[outoffset] = terminal_rt_basic_sta; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;
 
    printf("解析1类数据,F9:");   
    XL_UINT16 identifier;   

    //状态量的状态
    identifier = rtStateVarValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;        
    buff[outoffset] = *(Byte*)(userdata +offset);
    printf("状态量的状态:%02x\n",buff[outoffset]);
    outoffset += 1;
    offset += 1;
    //状态量的变位标志
    identifier = rtStateVarChangeFlag;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;        
    buff[outoffset] = *(Byte*)(userdata +offset);
    printf("状态量的变位标志:%02x\n",buff[outoffset]);
    outoffset += 1;
    offset += 1;
    
    end = outoffset;
    
    XL_UINT16 len = end -begin;
    memcpy(buff + begin -2, &len, 2);
 
}

/*终端与主站当日、月通信流量*/
void AFNC_F10()
{
    buff[outoffset] = terminal_rt_basic_sta; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;
 
    printf("解析1类数据,F10:");    
    XL_UINT16 identifier;

    identifier = rtDayCommunicateFlows;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //终端与主站当日通信流量
    *(XL_UINT32*)(buff+outoffset)=*(XL_UINT32*)(userdata+offset);
    printf("日通信流量,%u\n",*(XL_UINT32*)(buff+outoffset));
    offset +=4;
    outoffset += sizeof(XL_UINT32);

    identifier = rtMonCommunicateFlows;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //终端与主站当月通信流量
    *(XL_UINT32*)(buff+outoffset)=*(XL_UINT32*)(userdata+offset);
    printf("月通信流量,%u\n",*(XL_UINT32*)(buff+outoffset));
    offset +=4;
    outoffset += sizeof(XL_UINT32);
 
    end = outoffset;    
    XL_UINT16 len = end -begin;
    memcpy(buff + begin -2, &len, 2);   
}


/*当前三相及总有/无功功率、功率因数，三相电压、电流、零序电流、视在功率*/
void AFNC_F25()
{
    buff[outoffset] = mtr_rt_basic_sta; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;
    //终端抄表时间,5字节,暂时不用,直接跳过
    offset += 5;
    XL_UINT16 identifier;
    identifier = rtTotalActivePower;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //float 总有功功率
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 3, 4);
    offset +=3;
    outoffset += sizeof(XL_SINT64);

    identifier = rtAActivePower;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //float A相有功功率
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 3, 4);
    offset +=3;

    outoffset +=sizeof(XL_SINT64);

    identifier = rtBActivePower;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //float B相有功功率
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 3, 4);
    offset +=3;
    outoffset +=sizeof(XL_SINT64);

    identifier = rtCActivePower;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    //float C相有功功率
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 3, 4);
    offset +=3;
    outoffset +=sizeof(XL_SINT64);   

    identifier = rtTotalReactivePower;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //float 总无功功率
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 3, 4);
    offset +=3;
    outoffset +=sizeof(XL_SINT64); 

    identifier = rtAReactivePower;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //float A相无功功率
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 3, 4);
    offset +=3;

    outoffset +=sizeof(XL_SINT64);

    identifier = rtBReactivePower;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //float B相无功功率
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 3, 4);
    offset +=3;
    outoffset +=sizeof(XL_SINT64);

    identifier = rtCReactivePower;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    //float C相无功功率
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 3, 4);
    offset +=3;
    outoffset +=sizeof(XL_SINT64);
    
    identifier = rtTotalPowerFactor;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    //float 总功率因数
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 2, 1);
    offset +=2;
    outoffset +=sizeof(XL_SINT64);

    identifier = rtAPowerFactor;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    //float A相功率因数
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 2, 1);
    offset +=2;
    outoffset +=sizeof(XL_SINT64);

    identifier = rtBPowerFactor;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    //float B相功率因数
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 2, 1);
    offset +=2;
    outoffset +=sizeof(XL_SINT64);

    identifier = rtCPowerFactor;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    //float C相功率因数
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 2, 1);
    offset +=2;
    outoffset +=sizeof(XL_SINT64);

    //A相电压
    identifier = rtAVolt;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 2, 1);
    offset +=2;
    outoffset +=sizeof(XL_UINT64);

    //B相电压
    identifier = rtBVolt;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 2, 1);
    offset +=2;
    outoffset +=sizeof(XL_UINT64);

    //C相电压
    identifier = rtCVolt;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 2, 1);
    offset +=2;
    outoffset +=sizeof(XL_UINT64);

    //A相电流
    identifier = rtACurrent;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset,3,3);
    offset +=3;
    outoffset +=sizeof(XL_SINT64);

    //B相电流
    identifier = rtBCurrent;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset,3,3);
    offset +=3;
    outoffset +=sizeof(XL_SINT64);

    //C相电流
    identifier = rtCCurrent;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset,3,3);
    offset +=3;
    outoffset +=sizeof(XL_SINT64);

    //零序电流
    identifier = rtZeroSequenceCurrent;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset,3,3);
    offset +=3;
    outoffset +=sizeof(XL_SINT64);

    identifier = rtTotalApparentPower;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //float 总视在功率
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 3, 4);
    offset +=3;
    outoffset += sizeof(XL_SINT64);

    identifier = rtAApparentPower;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //float A相视在功率
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 3, 4);
    offset +=3;

    outoffset +=sizeof(XL_SINT64);

    identifier = rtBApparentPower;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //float B相视在功率
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 3, 4);
    offset +=3;
    outoffset +=sizeof(XL_SINT64);

    identifier = rtCApparentPower;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2; 
    //float C相视在功率
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 3, 4);
    offset +=3;
    outoffset +=sizeof(XL_SINT64);

    end = outoffset;    
    XL_UINT16 len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}

/*当前铜损、铁损有功总电能示值*/
void AFNC_F29()
{
    
}

/*当前正向有/无功（组合无功1）电能示值、一/四象限无功电能示值（总、费率1～M，1≤M≤12）*/
void AFNC_F33()
{
    buff[outoffset] = rt_power_value_sta; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;
    //终端抄表时间,5字节,暂时不用,直接跳过
    offset += 5;
    //费率数,bin格式,1字节
    offset += 1;
    XL_UINT16 identifier;
    identifier = rtPosAEValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前正向有功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,5,4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=5;

    outoffset +=sizeof(XL_UINT64);

    
    identifier = rtRate1PosAEValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率1正向有功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,5,4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=5;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtRate2PosAEValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率2正向有功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,5,4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=5;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtRate3PosAEValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率3正向有功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,5,4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=5;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtRate4PosAEValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率4正向有功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,5,4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=5;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtPosREValueG;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前正向无功（组合无功1）总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    
    identifier = rtRate1PosREValueG;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率1正向无功（组合无功1）总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtRate2PosREValueG;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率2正向无功（组合无功1）总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtRate3PosREValueG;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率3正向无功（组合无功1）总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtRate4PosREValueG;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率4正向无功（组合无功1）总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtFirstQuarREValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前一象限无功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    
    identifier = rtFirstQuarRate1REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前一象限费率1无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtFirstQuarRate2REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前一象限费率2无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtFirstQuarRate3REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前一象限费率3无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtFirstQuarRate4REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前一象限费率4无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64); 
  
    identifier = rtForthQuarREValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前四象限无功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtForthQuarRate1REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前四象限费率1无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtForthQuarRate2REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前四象限费率2无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);
    
    
    identifier = rtForthQuarRate3REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前四象限费率3无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtForthQuarRate4REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前四象限费率4无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    end = outoffset;    
    XL_UINT16 len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}

/*当前反向有/无功（组合无功2）电能示值、二/三象限无功电能示值（总、费率1～M，1≤M≤12）*/
void AFNC_F34()
{
    buff[outoffset] = rt_power_value_sta; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;
    //终端抄表时间,5字节,暂时不用,直接跳过
    offset += 5;
    //费率数,bin格式,1字节
    offset += 1;

    XL_UINT16 identifier;
    identifier = rtNegAEValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前反向有功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 5, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=5;

    outoffset +=sizeof(XL_UINT64);

    
    identifier = rtRate1NegAEValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率1正向有功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 5, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=5;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtRate2NegAEValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率2反向有功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 5, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=5;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtRate3NegAEValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率3反向有功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 5, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=5;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtRate4NegAEValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率4反向有功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 5, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=5;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtNegREValueG;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前反向无功（组合无功2）总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    
    identifier = rtRate1NegREValueG;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率1反向无功（组合无功2）总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtRate2PosREValueG;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率2反向无功（组合无功2）总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtRate3NegREValueG;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率3反向无功（组合无功2）总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtRate4NegREValueG;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前费率4反向无功（组合无功2）总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtSecQuarREValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前二象限无功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    
    identifier = rtSecQuarRate1REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前二象限费率1无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtSecQuarRate2REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前二象限费率2无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtSecQuarRate3REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前二象限费率3无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtSecQuarRate4REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前二象限费率4无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    offset +=4;

    outoffset +=sizeof(XL_UINT64); 
  
    identifier = rtThirdQuarREValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前三象限无功总电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtThirdQuarRate1REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前三象限费率1无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtThirdQuarRate2REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前三象限费率2无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);
    
    
    identifier = rtThirdQuarRate3REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前三象限费率3无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    identifier = rtThirdQuarRate4REValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当前三象限费率4无功电能示值
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset,4,2);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=4;

    outoffset +=sizeof(XL_UINT64);

    end = outoffset;    
    XL_UINT16 len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}

/*当月正向有/无功最大需量及发生时间（总、费率1～M，1≤M≤12）*/
void AFNC_F35()
{
    buff[outoffset] = rt_power_needs_sta; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;
    //终端抄表时间,5字节,暂时不用,直接跳过
    offset += 5;
    //费率数,bin格式,1字节
    offset += 1;

    XL_UINT16 identifier;
    identifier = rtMonPosAETotalMaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向有功总最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));    
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonPosAERate1MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向有功费率1最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonPosAERate2MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向有功费率2最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);


    identifier = rtMonPosAERate3MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向有功费率3最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonPosAERate4MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向有功费率4最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonPosAETotalMaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向有功总最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonPosAERate1MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向有功费率1最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonPosAERate2MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向有功费率2最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonPosAERate3MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向有功费率3最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonPosAERate4MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向有功费率4最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonPosRETotalMaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向无功总最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonPosRERate1MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向无功费率1最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonPosRERate2MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向无功费率2最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);


    identifier = rtMonPosRERate3MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向无功费率3最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonPosRERate4MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向无功费率4最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonPosRETotalMaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向无功总最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonPosRERate1MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向无功费率1最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonPosRERate2MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向无功费率2最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonPosRERate3MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向无功费率3最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonPosRERate4MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月正向无功费率4最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;   

    end = outoffset;    
    XL_UINT16 len = end -begin;
    memcpy(buff + begin -2, &len, 2);    
}

/*当月反向有/无功最大需量及发生时间（总、费率1～M，1≤M≤12）*/
void AFNC_F36()
{
    buff[outoffset] = rt_power_needs_sta; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;
    //终端抄表时间,5字节,暂时不用,直接跳过
    offset += 5;
    //费率数,bin格式,1字节
    offset += 1;

    XL_UINT16 identifier;
    identifier = rtMonNegAETotalMaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向有功总最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonNegAERate1MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向有功费率1最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonNegAERate2MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向有功费率2最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonNegAERate3MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向有功费率3最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonNegAERate4MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向有功费率4最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonNegAETotalMaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向有功总最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonNegAERate1MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向有功费率1最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonNegAERate2MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向有功费率2最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonNegAERate3MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向有功费率3最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonNegAERate4MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向有功费率4最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonNegRETotalMaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向无功总最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonNegRERate1MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向无功费率1最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonNegRERate2MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向无功费率2最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonNegRERate3MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向无功费率3最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonNegRERate4MaxNeed;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向无功费率4最大需量
    *(XL_UINT64*)(buff+outoffset)=bcdtouint(userdata+offset, 3, 4);
    printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
    offset +=3;
    outoffset +=sizeof(XL_UINT64);

    identifier = rtMonNegRETotalMaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向无功总最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonNegRERate1MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向无功费率1最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonNegRERate2MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向无功费率2最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonNegRERate3MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向无功费率3最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    identifier = rtMonNegRERate4MaxNeedTm;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //当月反向无功费率4最大需量发生时间
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;
    *(Byte*)(buff+outoffset)=(bcdToTime(userdata+offset));
    offset ++;
    outoffset ++;

    end = outoffset;    
    XL_UINT16 len = end -begin;
    memcpy(buff + begin -2, &len, 2);   
}

/*当前电压、电流相位角*/
void AFNC_F49()
{
    buff[outoffset] = mtr_rt_basic_sta; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;

    XL_UINT16 identifier;
    identifier = rtAVoltPhaseAngle;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //A相电压相角
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 2, 1);
    printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
    offset +=2;
    outoffset +=sizeof(XL_SINT64);


    identifier = rtBVoltPhaseAngle;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //B相电压相角
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 2, 1);
    printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
    offset +=2;
    outoffset +=sizeof(XL_SINT64);

    identifier = rtCVoltPhaseAngle;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //C相电压相角
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 2, 1);
    printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
    offset +=2;
    outoffset +=sizeof(XL_SINT64);

    identifier = rtACurrentPhaseAngle;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //A相电流相角
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 2, 1);
    printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
    offset +=2;
    outoffset +=sizeof(XL_SINT64);


    identifier = rtBCurrentPhaseAngle;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //B相电流相角
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 2, 1);
    printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
    offset +=2;
    outoffset +=sizeof(XL_SINT64);

    identifier = rtCCurrentPhaseAngle;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //C相电流相角
    *(XL_SINT64*)(buff+outoffset)=bcdtosint(userdata+offset, 2, 1);
    printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
    offset +=2;
    outoffset +=sizeof(XL_SINT64);


    end = outoffset;    
    XL_UINT16 len = end -begin;
    memcpy(buff + begin -2, &len, 2);   
}

/*当前A、B、C三相电压、电流2～N次谐波有效值*/
void AFNC_F57()
{
    buff[outoffset] = mtr_rt_harmonic; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;

    XL_UINT16 identifier;
    XL_CHAR harmoCnt=0;
    harmoCnt = *(Byte*)(userdata+offset);
    offset++;
    int i=0;        
    printf("harmoCnt =%d\n",harmoCnt);

    //A相电压谐波有效值
    for(i=0;i<harmoCnt-1;i++)
    {
        identifier = rtHarmoVoltA2EffecValue+i;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_UINT64*)(buff+outoffset) = bcdtouint(userdata+offset, 2, 1);
        printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
        offset+=2;
        outoffset+= sizeof(XL_UINT64);
    }
    //B相电压谐波有效值
    for(i=0;i<harmoCnt-1;i++)
    {
        identifier = rtHarmoVoltB2EffecValue+i;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_UINT64*)(buff+outoffset) = bcdtouint(userdata+offset, 2, 1);
        printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
        offset+=2;
        outoffset+= sizeof(XL_UINT64);
    }
    //C相电压谐波有效值
    for(i=0;i<harmoCnt-1;i++)
    {
        identifier = rtHarmoVoltC2EffecValue+i;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_UINT64*)(buff+outoffset) = bcdtouint(userdata+offset, 2, 1);
        printf("%llu\n",*(XL_UINT64*)(buff+outoffset));
        offset+=2;
        outoffset+= sizeof(XL_UINT64);
    }

    //A相电流谐波有效值
    for(i=0;i<harmoCnt-1;i++)
    {
        identifier = rtHarmoCurrentA2EffecValue+i;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_SINT64*)(buff+outoffset) = bcdtosint(userdata+offset, 2, 2);
        printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
        offset+=2;
        outoffset+= sizeof(XL_SINT64);
    }
    //B相电流谐波有效值
    for(i=0;i<harmoCnt-1;i++)
    {
        identifier = rtHarmoCurrentB2EffecValue+i;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_SINT64*)(buff+outoffset) = bcdtosint(userdata+offset, 2, 2);
        printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
        offset+=2;
        outoffset+= sizeof(XL_SINT64);
    }
    //C相电流谐波有效值
    for(i=0;i<harmoCnt-1;i++)
    {
        identifier = rtHarmoCurrentC2EffecValue+i;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_SINT64*)(buff+outoffset) = bcdtosint(userdata+offset, 2, 2);
        printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
        offset+=2;
        outoffset+= sizeof(XL_SINT64);
    }

    end = outoffset;    
    XL_UINT16 len = end -begin;
    printf("len=%d,begin=%d,end=%d\n",len,begin,end);
    memcpy(buff + begin -2, &len, 2);
}
/*当前A、B、C三相电压、电流2～N次谐波含有率*/
void AFNC_F58()
{
    buff[outoffset] = mtr_rt_harmonic; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;

    XL_UINT16 identifier;
    XL_CHAR harmoCnt=0;
    harmoCnt = *(Byte*)(userdata+offset);
    offset++;

    int i=0;
    //A相电压谐波含有率
    for(i=0;i<harmoCnt-1;i++)
    {
        identifier = rtVoltA2HarmoRate+i;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_SINT64*)(buff+outoffset) = bcdtosint(userdata+offset, 2, 1);
        printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
        offset+=2;
        outoffset+= sizeof(XL_SINT64);
    }
    //B相电压谐波含有率
    for(i=0;i<harmoCnt-1;i++)
    {
        identifier = rtVoltB2HarmoRate+i;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_SINT64*)(buff+outoffset) = bcdtosint(userdata+offset, 2, 1);
        printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
        offset+=2;
        outoffset+= sizeof(XL_SINT64);
    }
    //C相电压谐波含有率
    for(i=0;i<harmoCnt-1;i++)
    {
        identifier = rtVoltC2HarmoRate+i;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_SINT64*)(buff+outoffset) = bcdtosint(userdata+offset, 2, 1);
        printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
        offset+=2;
        outoffset+= sizeof(XL_SINT64);
    }

    //A相电流谐波含有率
    for(i=0;i<harmoCnt-1;i++)
    {
        identifier = rtCurrentA2HarmoRate+i;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_SINT64*)(buff+outoffset) = bcdtosint(userdata+offset, 2, 1);
        printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
        offset+=2;
        outoffset+= sizeof(XL_SINT64);
    }
    //B相电流谐波含有率
    for(i=0;i<harmoCnt-1;i++)
    {
        identifier = rtCurrentB2HarmoRate+i;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_SINT64*)(buff+outoffset) = bcdtosint(userdata+offset, 2, 1);
        printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
        offset+=2;
        outoffset+= sizeof(XL_SINT64);
    }
    //C相电流谐波含有率
    for(i=0;i<harmoCnt-1;i++)
    {
        identifier = rtCurrentC2HarmoRate+i;
        memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
        *(XL_SINT64*)(buff+outoffset) = bcdtosint(userdata+offset, 2, 1);
        printf("%lld\n",*(XL_SINT64*)(buff+outoffset));
        offset+=2;
        outoffset+= sizeof(XL_SINT64);
    }
    end = outoffset;    
    XL_UINT16 len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}

/*直流模拟量实时数据*/
void AFNC_F73()
{
    buff[outoffset] = mtr_rt_basic_sta; outoffset++;
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;

    XL_UINT16 identifier;

    identifier = rtDcAnalogValue;
    memcpy(buff + outoffset, &identifier, 2);outoffset+=2;
    //直流模拟量实时数据
    *(XL_CHAR*)(buff+outoffset) = a2powvaluewithparam(userdata+offset);
    printf("%d\n",*(XL_CHAR*)(buff+outoffset));
    outoffset += sizeof(XL_CHAR);
    *(XL_SINT16*)(buff+outoffset)=a22intwithparam(userdata+offset);
    printf("%d\n",*(XL_SINT16*)(buff+outoffset));
    offset +=2;
    outoffset +=sizeof(XL_SINT16);

    end = outoffset;    
    XL_UINT16 len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}
