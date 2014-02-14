//
//  XL3761AFNE.c
//  C_Protocol
//
//  三类数据 事件
//
//  Created by JY on 14-1-14.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "XL3761AFNC.h"
#include "XLDataId.h"
#include "XLCommon.h"
#include "XLUtility.h"


void AFNE_RecursiveParse();

void AFNE_F1();
void AFNE_F2();

void parseEvents();


//***************************************************
//数据初始化和版本变更记录
void geterc1();

//参数变更记录
void geterc3();

//电压回路异常
void geterc10(); //ADD

//相序异常
void geterc11();

//终端停上电事件
void geterc14();

//谐波越限告警
void geterc15();

//电压电流不平衡度越限记录
void geterc17();

//电压越限记录
void geterc24();

//电流越限记录
void geterc25();

//视在功率越限记录
void geterc26();

//终端与主站通信流量统计
void geterc32();

//用户登录事件记录
void geterc45(); //ADD

//过载事件记录
void geterc46(); //ADD

//***************************************************


//参数丢失记录
//**终端不支持
void geterc2();

//状态量变位记录
//**终端不支持
void geterc4();

//遥控跳闸记录
//**终端不支持
void geterc5();

//电能表参数变更
//**终端不支持
void geterc8();

//电能表时间超差
//**终端不支持
void geterc12();

//电表故障信息
//**终端不支持
void geterc13();

//直流模拟量越限记录
//**终端不支持
void geterc16();

//终端故障记录
//**终端不支持
void geterc21();

//电能表示度下降记录
//**终端不支持
void geterc27();

//电能量超差记录
//**终端不支持
void geterc28();

//电能表飞走记录
//**终端不支持
void geterc29();

//电能表停走记录
//**终端不支持
void geterc30();

//终端485抄表失败事件记录
//**终端不支持
void geterc31();



XL_CHAR * gettimestr(XL_UINT8 len);
XL_CHAR * getasciistr(XL_UINT8 len);

void initUserDataForAfne(XL_SINT16 *output,void *frame,XL_UINT16* outlen,Byte** outbuf){
    
    printf("解析文件AFNE\n");
    
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
    
    AFNE_RecursiveParse();
    *outlen = outoffset;
    
    free(userdata);
    free(_frame);
    
    //用完之后,将outoffset置位初值0
	outoffset = 0;
    offset = 0;
}

void AFNE_RecursiveParse(){
    
    XL_UINT16 fn = parsedadt((XL_UINT16)userdata[offset + 3],
                                    (XL_UINT16)userdata[offset + 2],0);
    
    
    memcpy(buff + outoffset, userdata + offset, 1); offset+=2;outoffset++;
    memcpy(buff + outoffset, &fn, 1); offset+=2;outoffset++;
    
    switch (fn) {
        case 1:
            AFNE_F1();
            break;
        case 2:
            AFNE_F2();
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
        AFNE_RecursiveParse();
    }
}


/*－－－－－－－－－－－－－－/
 请求重要事件
 
/－－－－－－－－－－－－－－*/
void AFNE_F1(){
    parseEvents();
}


/*－－－－－－－－－－－－－－/
 请求一般事件
 
 /－－－－－－－－－－－－－－*/
void AFNE_F2(){
    parseEvents();
}

void parseEvents(){
    
//    for(int i =0;i<30;i++){
//        printf("%2d\n",userdata[i]);
//    }
    
    //表名
    buff[outoffset] = eventlist; outoffset++;
    
    //跳过两字节长度
    outoffset+=2;
    
    XL_UINT16 begin;
    XL_UINT16 end;
    
    begin = outoffset;
 
    //重要事件计数器
//    XL_UINT8 ec1 = buff[offset];offset++;
    
    //一般事件计数器
//    XL_UINT8 ec2 = buff[offset];offset++;
    
    offset+=2;
    
    //事件记录起始指针
    XL_UINT8 pm = userdata[offset];offset++;
    
    //事件记录结束指针
    XL_UINT8 pn = userdata[offset];offset++;
    
    /*事件条数*/
    XL_UINT8 count = (pn > pm) ? (pn - pm) : (256 + pn - pm) ;
    
    while (count>0) {
        XL_UINT8 ecode = userdata[offset];offset++;
        
        switch (ecode) {
            case 1:
                geterc1();
                break;
//            case 2:
//                geterc2();
//                break;
            case 3:
                geterc3();
                break;
//            case 4:
//                geterc4();
//                break;
//            case 5:
//                geterc5();
//                break;
//            case 8:
//                geterc8();
//                break;
            case 10:
                geterc10();
                break;
            case 11:
                geterc11();
                break;
//            case 12:
//                geterc12();
//                break;
//            case 13:
//                geterc13();
//                break;
            case 14:
                geterc14();
                break;
            case 15:
                geterc15();
                break;
//            case 16:
//                geterc16();
//                break;
            case 17:
                geterc17();
                break;
//            case 21:
//                geterc21();
//                break;
            case 24:
                geterc24();
                break;
            case 25:
                geterc25();
                break;
            case 26:
                geterc26();
                break;
//            case 27:
//                geterc27();
//                break;
//            case 28:
//                geterc28();
//                break;
//            case 29:
//                geterc29();
//                break;
//            case 30:
//                geterc30();
//                break;
//            case 31:
//                geterc31();
//                break;
            case 32:
                geterc32();
                break;
            case 45:
                geterc45();
                break;
            case 46:
                geterc46();
                break;
            default:
                *_output = XL_ERROR;
                return;
                break;
        }
        count--;
    }
    
    end = outoffset;
    
    XL_UINT16 len = end -begin;
    memcpy(buff + begin -2, &len, 2);
}


/*－－－－－－－－－－－－－－/
 时间字符串
 
 /－－－－－－－－－－－－－－*/
XL_CHAR * gettimestr(XL_UINT8 len){
    
//    XL_UINT8 hlen = strlen("年");
    XL_CHAR time[2*len];
    XL_CHAR *timec = malloc(2*len);
    memset(timec, 0, 2*len);
    XL_UINT8 vtime;

    for(XL_UINT8 i =len;i>0;i--){
        
        for(int k =0;k<2*len;k++){time[k] = '\0';}
        
        vtime = (userdata[offset + i-1]>>4 & 0x0f) * 10 + (userdata [offset + i-1]&0x0f);
        sprintf(time,"%02d",vtime);
 
        switch (i) {
            case 5:
                strcat(time, "-");
                break;
            case 4:
                strcat(time, "-");
                break;
            case 3:
                strcat(time, " ");
                break;
            case 2:
                strcat(time, ":");
                break;
            case 1:
                strcat(time, " ");
                break;
        }
        strcat(timec, time);
    }
 
//    timec[len*(hlen+1)+1] = '\0';
//    printf("%d",(int)strlen(timec));
    return timec;
}


/*－－－－－－－－－－－－－－/
 ASCII转字符串
 
 /－－－－－－－－－－－－－－*/
XL_CHAR * getasciistr(XL_UINT8 len){

    XL_CHAR *asciistr = malloc(len+1);
    memset(asciistr, 0, len);
    
    for(XL_UINT8 i = 0;i<len;i++){
        asciistr[i] =userdata[offset+i];
    }
    asciistr[len] = '\0';
    return asciistr;
}


/*－－－－－－－－－－－－－－/
 数据初始化和版本变更记录
 
 /－－－－－－－－－－－－－－*/
void geterc1(){

    //2字节标识
    XL_UINT8 flag = 0;
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;

    offset++;
    
    //初始化/版本变更时间
    XL_CHAR* time = gettimestr(5);offset+=5;

    //事件标志
    if ((*(Byte*)(userdata + offset) & 0x01 )) {
        flag = 1;
        
    } else if ((*(Byte*)(userdata + offset)>>1 & 0x01 )){
        flag = 0;
    }
    offset++;

    //变更前软件版本号
    XL_CHAR* pversion = getasciistr(4); offset+=4;
    
    //变更后软件版本号
    XL_CHAR* nversion = getasciistr(4); offset+=4;
    
    XL_CHAR *result = (XL_CHAR *) malloc(500);
    memset(result, 0, strlen(result));
    
    if (flag) {
        strcat(result, "终端进行参数及数据区初始化 ");
    }else{
        strcat(result, "终端版本变更,变更前软件版本号:");
        
//        printf("长度%d",(int)strlen(pversion));
        strcat(result, pversion);
        strcat(result, " 变更后软件版本号:");
//        printf("长度%d",(int)strlen(pversion));
        strcat(result, nversion);
    }
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    printf("\n%s\n",result);
    
    XL_UINT16 eventlen = strlen(result);
    
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16)); outoffset+=2;
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    free(result);
    free(time);
    free(pversion);
    free(nversion);
}


/*－－－－－－－－－－－－－－/
 参数变更记录
 
 /－－－－－－－－－－－－－－*/
void geterc3(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;

    int len = userdata[offset];offset++;
    int _len = 0;
    
    //参数更新时间
    XL_CHAR* time = gettimestr(5);offset+=5;_len+=5;
    
    //启动站地址
    XL_UINT8 address = userdata[offset];offset++;_len+=1;
    XL_CHAR address_[sizeof(XL_CHAR)];
    sprintf(address_,"%d", address);
    
    XL_CHAR *result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, "终端参数变更,");
    
//    printf("\n%s\n",result);
    
    strcat(result, "启动站地址:");
    
    printf("\n%s\n",result);
    strcat(result, address_);
    
//    printf("\n%s\n",result);
    
    XL_UINT32 dataid;
    char dataid_[50];
    
    while (len>_len) {
        strcat(result, " 变更参数数据单元标示:");
//        printf("\n%s\n",result);
        
        //变更参数数据单元标识
        dataid = *(XL_UINT32*)(userdata+offset);offset+=4 ;_len+=4;
        sprintf(dataid_, "%d",dataid);
//        printf("\n%s\n",dataid_);
        
        strcat(result, dataid_);
        
//        printf("\n%s\n",result);
        
        _len+=4;
    };
    
    strcat(result, " 参数更新时间:");
    strcat(result, time);
    
//    printf("\n%s\n",result);
    
    XL_UINT16 eventlen = strlen(result);
    
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16)); outoffset+=2;
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    
    
    free(result);
    free(time);
}


/*－－－－－－－－－－－－－－/
 电压回路异常
 
 /－－－－－－－－－－－－－－*/
void geterc10(){
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    //事件长度
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata + offset)&0x0fff;
    XL_CHAR mpoint_[50];sprintf(mpoint_, "%d",mpoint);
    
    //起止标志
    XL_CHAR *flag = (*(XL_UINT16*)(userdata + offset)>>15)&0x0001 ? "电压回路异常发生,": "电压回路异常恢复,";
    offset+=2;
    
    XL_CHAR *result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, flag);
    strcat(result, " 测量点号:");
    strcat(result, mpoint_);
    
    //异常标志
    Byte status = *(Byte*)(userdata+offset);offset++;
    
    //A相发生越限
    if (status&0x01) {
        strcat(result, " A相电压回路异常 ");
    }
    
    //B相发生越限
    if ((status>>1)&0x01) {
        strcat(result, " B相电压回路异常 ");
    }
    
    //C相发生越限
    if ((status>>2)&0x01) {
        strcat(result, " C相电压回路异常 ");
    }
    
    XL_UINT8 type = status>>6 & 0x03;
    
    //越限类型:越上上限
    if (type == 1) {
        strcat(result, "异常类型:断相");
    }
    
    //越限类型:越下下限
    if (type == 2) {
        strcat(result, "异常类型:失压");
    }

    //发生时Ua/Uab
    XL_FP32 uauab = bcdtouint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    //发生时Ub
    XL_FP32 ub =    bcdtouint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    //发生时Uc/Ucb
    XL_FP32 ucucb = bcdtouint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    //发生时Ia
    XL_FP32 ia =    bcdtosint(userdata + offset, 3, 3)/1000.0;offset+=3;
    
    //发生时Ib
    XL_FP32 ib =    bcdtosint(userdata + offset, 3, 3)/1000.0;offset+=3;
    
    //发生时Ic
    XL_FP32 ic =    bcdtosint(userdata + offset, 3, 3)/1000.0;offset+=3;
    
    XL_CHAR uauab_[50]; sprintf(uauab_,"%.1f",uauab);
    XL_CHAR    ub_[50]; sprintf(ub_,"%.1f",ub);
    XL_CHAR ucucb_[50]; sprintf(ucucb_,"%.1f",ucucb);
    XL_CHAR    ia_[50]; sprintf(ia_,"%.3f",ia);
    XL_CHAR    ib_[50]; sprintf(ib_,"%.3f",ib);
    XL_CHAR    ic_[50]; sprintf(ic_,"%.3f",ic);
    
    strcat(result, " 发生时Ua/Uab:");strcat(result,uauab_);
    strcat(result, " 发生时Ub:");    strcat(result,ub_);
    strcat(result, " 发生时Uc/Ucb:");strcat(result,ucucb_);
    
    strcat(result, " 发生时Ia:");strcat(result,ia_);
    strcat(result, " 发生时Ib:");strcat(result,ib_);
    strcat(result, " 发生时Ic:");strcat(result,ic_);
    
    XL_FP64 power = bcdtouint(userdata + offset, 5, 4)/10000.0;offset+=5;
    XL_CHAR power_[50];sprintf(power_, "%.4f",power);
    strcat(result, " 发生时电能表正向有功总电能示值:");
    strcat(result, power_);
    
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    printf("\n%s\n",result);
    
    XL_UINT16 eventlen = strlen(result);
    
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16)); outoffset+=2;
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    
    free(result);
    free(time);
}

/*－－－－－－－－－－－－－－/
 相序异常
 
 /－－－－－－－－－－－－－－*/
void geterc11(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    //事件长度
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata + offset)&0x0fff;
    XL_CHAR mpoint_[50];sprintf(mpoint_, "%d",mpoint);
    
    //起止标志
    XL_CHAR *flag = (*(XL_UINT16*)(userdata + offset)>>15)&0x0001 ? "相序异常发生,": "相序异常恢复,";
    offset+=2;
    
    XL_CHAR *result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, flag);
    strcat(result, " 测量点号:");
    strcat(result, mpoint_);
    
    //发生时∠Ua/Uab
    XL_FP32 uauab = bcdtosint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    //发生时∠Ub
    XL_FP32 ub =    bcdtosint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    //发生时∠Uc/Ucb
    XL_FP32 ucucb = bcdtosint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    //发生时∠Ia
    XL_FP32 ia =    bcdtosint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    //发生时∠Ib
    XL_FP32 ib =    bcdtosint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    //发生时∠Ic
    XL_FP32 ic =    bcdtosint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    XL_CHAR uauab_[50]; sprintf(uauab_,"%.1f",uauab);
    XL_CHAR    ub_[50]; sprintf(ub_,"%.1f",ub);
    XL_CHAR ucucb_[50]; sprintf(ucucb_,"%.1f",ucucb);
    XL_CHAR    ia_[50]; sprintf(ia_,"%.1f",ia);
    XL_CHAR    ib_[50]; sprintf(ib_,"%.1f",ib);
    XL_CHAR    ic_[50]; sprintf(ic_,"%.1f",ic);
    
    strcat(result, " 发生时∠Ua/Uab:");strcat(result,uauab_);
    strcat(result, " 发生时∠Ub:");    strcat(result,ub_);
    strcat(result, " 发生时∠Uc/Ucb:");strcat(result,ucucb_);
    
    strcat(result, " 发生时∠Ia:");strcat(result,ia_);
    strcat(result, " 发生时∠Ib:");strcat(result,ib_);
    strcat(result, " 发生时∠Ic:");strcat(result,ic_);
    
    XL_FP64 power = bcdtouint(userdata + offset, 5, 4)/10000.0;offset+=5;
    XL_CHAR power_[50];sprintf(power_, "%.4f",power);
    strcat(result, " 发生时电能表正向有功总电能示值:");
    strcat(result, power_);
    
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    printf("\n%s\n",result);
    
    XL_UINT16 eventlen = strlen(result);
    
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16)); outoffset+=2;
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    
    free(result);
    free(time);
}


/*－－－－－－－－－－－－－－/
 终端停上电事件
 
 /－－－－－－－－－－－－－－*/
void geterc14(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    //事件长度
    offset++;
    
    //停电发生时间
    XL_CHAR* time1 = gettimestr(5);offset+=5;
    
    //上电时间
    XL_CHAR* time2 = gettimestr(5);offset+=5;
    
    XL_CHAR *result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, "终端停上电事件 ");
    strcat(result, " 停电发生时间:");
    strcat(result, time1);
    strcat(result, " 上电时间:");
    strcat(result, time2);
    
    printf("\n%s\n",result);
    
    XL_UINT16 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
    
    free(result);
    free(time1);
    free(time2);
}

/*－－－－－－－－－－－－－－/
 谐波越限告警
 
 /－－－－－－－－－－－－－－*/
void geterc15(){
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata+offset)&0x0fff;
    XL_CHAR mpoint_[50];sprintf(mpoint_, "%d",mpoint);
    
    //起止标志
    XL_CHAR* seflag = (*(XL_UINT16*)(userdata+offset)>>15&0x0001)?"谐波越限告警发生":"谐波越限告警恢复";
    offset+=2;
    
    //异常标志
    Byte status = *(Byte*)(userdata+offset);offset++;
    
    XL_CHAR* result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, seflag);
    strcat(result, " 测量点号:");
    strcat(result, mpoint_);
    
    if (status>>7&0x01) {
        strcat(result, " 类型:谐波电压越限 ");
    }else{
        strcat(result, " 类型:谐波电流越限 ");
    }
    
    strcat(result, " 越限次数:");
    XL_CHAR num[50];
    for(int i = 0;i<3;i++){
        Byte status = *(Byte*)(userdata+offset + i);
        for(int j = 0;j<8;j++){
            if (status>>j&0x01) {
                sprintf(num,"%d",i*8+j+1);
                strcat(result, num);
                strcat(result, " ");
            }
        }
    }
    offset+=3;
    
    for(int i = 0;i<19;i++){
        if (i==0) {
            strcat(result, " 越限时总畸变:");
        }else{
            strcat(result, " 越限时该相");
            sprintf(num,"%d",i+1);
            strcat(result, num);
            strcat(result, "次:");
        }
        
        if (status>>7&0x01){
            XL_FP64 value = bcdtosint(userdata + offset, 2, 1)/10.0;
            XL_CHAR value_[50];sprintf(value_, "%.1f",value);
            strcat(result, value_);
        }else{
            XL_FP64 value = bcdtosint(userdata + offset, 2, 2)/100.0;
            XL_CHAR value_[50];sprintf(value_, "%.2f",value);
            strcat(result, value_);
        }
        offset+=2;
    }
    
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    printf("\n%s\n",result);
    
    XL_UINT16 eventlen = strlen(result);
    
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16)); outoffset+=2;
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    
    free(result);
    free(time);
}


/*－－－－－－－－－－－－－－/
 电压电流不平衡度越限记录
 
 /－－－－－－－－－－－－－－*/
void geterc17(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata+offset)&0x0fff;
    XL_CHAR mpoint_[50];sprintf(mpoint_, "%d",mpoint);
    
    //起止标志
    XL_CHAR* seflag = (*(XL_UINT16*)(userdata+offset)>>15&0x0001)?"不平衡度越限发生":"不平衡度越限恢复";
    offset+=2;
    
    //异常标志
    Byte status = *(Byte*)(userdata+offset);offset++;
    
    XL_CHAR* result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, seflag);
    strcat(result, " 测量点号:");
    strcat(result, mpoint_);
    
    if (status&0x01) {
        strcat(result, " 类型:电压不平衡度越限 ");
    }
    if ((status>>1)&0x01) {
        strcat(result, " 类型:电流不平衡度越限 ");
    }
    
    //发生时的电压不平衡度(%)
    XL_FP32 unbalancei = bcdtosint(userdata, 2, 1)/10.0;offset+=2;
    
    //发生时的电流不平衡度(%)
    XL_FP32 unbalancev = bcdtosint(userdata, 2, 1)/10.0;offset+=2;
    
    XL_CHAR unbalancei_[50];sprintf(unbalancei_, "%.1f",unbalancei);
    XL_CHAR unbalancev_[50];sprintf(unbalancev_, "%.1f",unbalancev);
    
    //发生时Ua/Uab
    XL_FP32 uauab = bcdtouint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    //发生时Ub
    XL_FP32 ub =    bcdtouint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    //发生时Uc/Ucb
    XL_FP32 ucucb = bcdtouint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    //发生时Ia
    XL_FP32 ia =    bcdtosint(userdata + offset, 3, 3)/1000.0;offset+=3;
    
    //发生时Ib
    XL_FP32 ib =    bcdtosint(userdata + offset, 3, 3)/1000.0;offset+=3;
    
    //发生时Ic
    XL_FP32 ic =    bcdtosint(userdata + offset, 3, 3)/1000.0;offset+=3;
    
    XL_CHAR uauab_[50]; sprintf(uauab_,"%.1f",uauab);
    XL_CHAR    ub_[50]; sprintf(ub_,"%.1f",ub);
    XL_CHAR ucucb_[50]; sprintf(ucucb_,"%.1f",ucucb);
    XL_CHAR    ia_[50]; sprintf(ia_,"%.3f",ia);
    XL_CHAR    ib_[50]; sprintf(ib_,"%.3f",ib);
    XL_CHAR    ic_[50]; sprintf(ic_,"%.3f",ic);
    
    strcat(result, " 发生时的电压不平衡度(%):"); strcat(result, unbalancev_);
    strcat(result, " 发生时的电流不平衡度(%):"); strcat(result, unbalancei_);
    
    strcat(result, " 发生时Ua/Uab:");strcat(result,uauab_);
    strcat(result, " 发生时Ub:");    strcat(result,ub_);
    strcat(result, " 发生时Uc/Ucb:");strcat(result,ucucb_);
    
    strcat(result, " 发生时Ia:");strcat(result,ia_);
    strcat(result, " 发生时Ib:");strcat(result,ib_);
    strcat(result, " 发生时Ic:");strcat(result,ic_);
    
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    printf("\n%s\n",result);
    
    XL_UINT16 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16)); outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result)); outoffset+=eventlen;
    
    free(time);
    free(result);
}

/*－－－－－－－－－－－－－－/
 电压越限记录
 
 /－－－－－－－－－－－－－－*/
void geterc24(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    //事件长度
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata + offset)&0x0fff;
    XL_CHAR mpoint_[50];sprintf(mpoint_, "%d",mpoint);
    
    //起止标志
    XL_CHAR *flag = (*(XL_UINT16*)(userdata + offset)>>15)&0x0001 ? "电压越限发生,": "电压越限恢复,";
    offset+=2;
    
    //越限标志
    Byte status = *(Byte*)(userdata + offset);offset++;
    
    XL_CHAR *result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, flag);
    strcat(result, "测量点号:");
    strcat(result, mpoint_);
    
    //A相发生越限
    if (status&0x01) {
        strcat(result, " A相发生越限 ");
    }
    
    //B相发生越限
    if ((status>>1)&0x01) {
        strcat(result, " B相发生越限 ");
    }
    
    //C相发生越限
    if ((status>>2)&0x01) {
        strcat(result, " C相发生越限 ");
    }
    
    XL_UINT8 type = status>>6 & 0x03;
    
    //越限类型:越上上限
    if (type == 1) {
        strcat(result, "越限类型:越上上限");
    }
    
    //越限类型:越下下限
    if (type == 2) {
        strcat(result, "越限类型:越下下限");
    }
    
    //发生时的Ua/Uab
    XL_FP32 uauab = bcdtouint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    //发生时的Ub
    XL_FP32 ub =    bcdtouint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    //发生时的UcUcb
    XL_FP32 ucucb = bcdtouint(userdata + offset, 2, 1)/10.0;offset+=2;
    
    XL_CHAR uauab_[50];sprintf(uauab_,"%.1f",uauab);
    XL_CHAR    ub_[50];sprintf(ub_,"%.1f",ub);
    XL_CHAR ucucb_[50];sprintf(ucucb_,"%.1f",ucucb);
    
    strcat(result, " 发生时的Ua/Uab:");strcat(result, uauab_);
    strcat(result, " 发生时的Ub:");    strcat(result, ub_);
    strcat(result, " 发生时的UcUcb");  strcat(result, ucucb_);
    
    strcat(result, "发生时间:");
    strcat(result, time);
    
    printf("\n%s\n",result);
    
    XL_UINT16 eventlen = strlen(result);
    
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16));    outoffset+=2;
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    
    free(result);
    free(time);
}


/*－－－－－－－－－－－－－－/
 电流越限记录
 
 /－－－－－－－－－－－－－－*/
void geterc25(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    //事件长度
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata + offset)&0x0fff;
    XL_CHAR mpoint_[50];sprintf(mpoint_, "%d",mpoint);
    
    //起止标志
    XL_CHAR *flag = (*(XL_UINT16*)(userdata + offset)>>15)&0x0001 ? "电流越限发生,": "电流越限恢复,";
    offset+=2;
    
    //越限标志
    Byte status = *(Byte*)(userdata + offset);offset++;
    
    XL_CHAR *result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, flag);
    strcat(result, "测量点号:");
    strcat(result, mpoint_);
    
    //A相发生越限
    if (status&0x01) {
        strcat(result, " A相发生越限 ");
    }
    
    //B相发生越限
    if ((status>>1)&0x01) {
        strcat(result, " B相发生越限 ");
    }
    
    //C相发生越限
    if ((status>>2)&0x01) {
        strcat(result, " C相发生越限 ");
    }
    
    XL_UINT8 type = status>>6 & 0x03;
    
    //越限类型:越上上限
    if (type == 1) {
        strcat(result, "越限类型:越上上限");
    }
    
    //越限类型:越下下限
    if (type == 2) {
        strcat(result, "越限类型:越下下限");
    }
    
    //发生时的Ia
    XL_FP32 ia = bcdtosint(userdata + offset, 3, 3)/1000.0;offset+=3;
    
    //发生时的Ib
    XL_FP32 ib = bcdtosint(userdata + offset, 3, 3)/1000.0;offset+=3;
    
    //发生时的Ic
    XL_FP32 ic = bcdtosint(userdata + offset, 3, 3)/1000.0;offset+=3;
    
    XL_CHAR ia_[50];sprintf(ia_,"%.3f",ia);
    XL_CHAR ib_[50];sprintf(ib_,"%.3f",ib);
    XL_CHAR ic_[50];sprintf(ic_,"%.3f",ic);
    
    strcat(result, " 发生时的Ia:");
    strcat(result, ia_);
    strcat(result, " 发生时的Ib:");
    strcat(result, ib_);
    strcat(result, " 发生时的Ic:");
    strcat(result, ic_);
    
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    printf("\n%s\n",result);
    
    XL_UINT16 eventlen = strlen(result);
    
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16)); outoffset+=2;
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    
    free(result);
    free(time);
}


/*－－－－－－－－－－－－－－/
 视在功率越限
 
 /－－－－－－－－－－－－－－*/
void geterc26(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata+offset)&0x0fff;
    XL_CHAR mpoint_[50];sprintf(mpoint_,"%d",mpoint);
    
    //起止标志
    XL_CHAR* seflag = (*(XL_UINT16*)(userdata+offset)>>15 & 0x0001)?"视在功率越限发生":"视在功率越限恢复";
    offset+=2;
    
    //越限标志
    Byte status = *(Byte*)(userdata+offset);offset++;
    
    XL_CHAR* result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, seflag);
    strcat(result, " 测量点号:");
    strcat(result, mpoint_);
    
    //越视在功率上上限
    if ((status>>6 & 0x02) == 1) {
        strcat(result, " 类型:越上上限 ");
    }
    //越视在功率上限
    if ((status>>6 & 0x02) == 2) {
        strcat(result, " 类型:越上限 ");
    }
    
    //发生时的视在功率
    XL_FP32 apower =   bcdtouint(userdata, 3, 4)/10000.0; offset+=3;
    
    //发生时的视在功率限值
    XL_FP32 apowerlm = bcdtouint(userdata, 3, 4)/10000.0; offset+=3;
    
    
    XL_CHAR apower_[50];  sprintf(apower_, "%.4f",apower);
    
    XL_CHAR apowerlm_[50];sprintf(apowerlm_, "%.4f",apowerlm);
    
    strcat(result, " 发生时的视在功率:"); strcat(result, apower_);
    strcat(result, " 发生时的视在功率限值"); strcat(result, apowerlm_);
    
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    printf("\n%s\n",result);
    
    XL_UINT16 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
    
    free(result);
    free(time);
}

/*－－－－－－－－－－－－－－/
 终端与主站通信流量超门限事件
 
 /－－－－－－－－－－－－－－*/
void geterc32(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //当月已发生的通信流量
    XL_UINT32   flow = *(XL_UINT32*)(userdata + offset);offset+=4;
    
    //月通信流量门限
    XL_UINT32 flowlm = *(XL_UINT32*)(userdata + offset); offset+=4;
    
    XL_CHAR   flow_[50];sprintf(flow_,   "%d",flow);
    XL_CHAR flowlm_[50];sprintf(flowlm_, "%d",flowlm);
    
    XL_CHAR* result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, " 终端与主站通信流量超门限 ");
    strcat(result, " 当月已发生的通信流量:");strcat(result, flow_);
    strcat(result, " 月通信流量门限:");strcat(result,flowlm_);
    strcat(result, " 发生时间:");strcat(result, time);
    
    printf("\n%s\n",result);
    
    XL_UINT16 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
    
    free(result);
    free(time);
}


/*－－－－－－－－－－－－－－/
 用户登录事件记录
 
 /－－－－－－－－－－－－－－*/
void geterc45(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    XL_CHAR* result = malloc(500);
    memset(result, 0, strlen(result));
    strcat(result, "登录用户名:");
    
    XL_CHAR c_[50];
    
    for(int i = 0;i<16;i++){
        sprintf(c_,"%c",*(Byte*)(userdata + offset + i));
        strcat(result, c_);
    }
    offset+=16;
    
    strcat(result, " 发生时间:");strcat(result, time);
    
    printf("\n%s\n",result);
    
    XL_UINT16 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16));outoffset+=2;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
    
    free(result);
    free(time);
}


/*－－－－－－－－－－－－－－/
 过载事件记录
 
 /－－－－－－－－－－－－－－*/
void geterc46(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    //事件长度
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata + offset)&0x0fff;
    XL_CHAR mpoint_[50];sprintf(mpoint_, "%d",mpoint);
    
    //起止标志
    XL_CHAR *flag = (*(XL_UINT16*)(userdata + offset)>>15)&0x0001 ? "过载发生,": "过载恢复,";
    offset+=2;
    
    //异常标志
    Byte status = *(Byte*)(userdata + offset);offset++;
    
    XL_CHAR *result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, flag);
    strcat(result, "测量点号:");
    strcat(result, mpoint_);
    
    //A相发生越限
    if (status&0x01) {
        strcat(result, " A相发生过载 ");
    }
    
    //B相发生越限
    if ((status>>1)&0x01) {
        strcat(result, " B相发生过载 ");
    }
    
    //C相发生越限
    if ((status>>2)&0x01) {
        strcat(result, " C相发生过载 ");
    }
    
    XL_UINT8 type = status>>6 & 0x03;
    
    //越限类型:越上上限
    if (type == 1) {
        strcat(result, "变压器类型:油变");
    }
    
    //越限类型:越下下限
    if (type == 2) {
        strcat(result, "变压器类型:干变");
    }
    
    //发生时的Ia
    XL_FP32 ia = bcdtosint(userdata + offset, 3, 3)/1000.0;offset+=3;
    
    //发生时的Ib
    XL_FP32 ib = bcdtosint(userdata + offset, 3, 3)/1000.0;offset+=3;
    
    //发生时的Ic
    XL_FP32 ic = bcdtosint(userdata + offset, 3, 3)/1000.0;offset+=3;
    
    XL_CHAR ia_[50];sprintf(ia_,"%.3f",ia);
    XL_CHAR ib_[50];sprintf(ib_,"%.3f",ib);
    XL_CHAR ic_[50];sprintf(ic_,"%.3f",ic);
    
    strcat(result, " 发生时的Ia:");
    strcat(result, ia_);
    strcat(result, " 发生时的Ib:");
    strcat(result, ib_);
    strcat(result, " 发生时的Ic");
    strcat(result, ic_);
    
    
    if (type == 1) {
        //发生时的Ia
        XL_FP32 tempa = bcdtosint(userdata + offset, 2, 1)/10.0;offset+=2;
        XL_CHAR tempa_[50];sprintf(tempa_,"%.1f",tempa);
        strcat(result, " 发生时油温:");
        strcat(result, tempa_);
    }
    offset+=2;
    
    if (type == 2) {
        XL_FP32 tempaA = bcdtosint(userdata + offset, 2, 1)/10.0;offset+=2;
        XL_CHAR tempaA_[50];sprintf(tempaA_,"%.1f",tempaA);
        strcat(result, " 发生时A相绕组温度:");
        strcat(result, tempaA_);
     
        XL_FP32 tempaB = bcdtosint(userdata + offset, 2, 1)/10.0;offset+=2;
        XL_CHAR tempaB_[50];sprintf(tempaB_,"%.1f",tempaB);
        strcat(result, " 发生时B相绕组温度:");
        strcat(result, tempaB_);
        
        XL_FP32 tempaC = bcdtosint(userdata + offset, 2, 1)/10.0;offset+=2;
        XL_CHAR tempaC_[50];sprintf(tempaC_,"%.1f",tempaC);
        strcat(result, " 发生时C相绕组温度:");
        strcat(result, tempaC_);
    }
    offset+=6;
    
    
    strcat(result, "发生时间:");
    strcat(result, time);
    
    printf("\n%s\n",result);
    
    XL_UINT16 eventlen = strlen(result);
    
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT16)); outoffset+=2;
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    
    free(result);
    free(time);
}


















//**********************************************终端不支持*********************************************************

/*－－－－－－－－－－－－－－/
 参数丢失记录
 
 /－－－－－－－－－－－－－－*/
void geterc2(){
    
    //2字节标识
    XL_UINT8 flag = 0;
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    //事件长度
//    XL_UINT8 len = userdata[offset];offset++;
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //终端参数丢失
    if ((*(Byte*)(userdata + offset) & 0x01 )) {
        flag = 1;
     
    //测量点参数丢失
    } else if ((*(Byte*)(userdata + offset)>>1 & 0x01 )){
        flag = 0;
    }
    offset++;

    XL_CHAR *result = (XL_CHAR *) malloc(500);
    memset(result, 0, strlen(result));
    
    
    if (flag) {
        strcat(result, "终端参数丢失");
    }else{
        strcat(result, "测量点参数丢失");
    }
    
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    printf("%s",result);
    
    XL_UINT8 eventlen = strlen(result);
    
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT8)); outoffset++;
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    free(result);
    free(time);
}

/*－－－－－－－－－－－－－－/
 状态量变位记录
 
 /－－－－－－－－－－－－－－*/
void geterc4(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    //事件长度
    offset++;
    
    //变位时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //状态变位
    Byte status = *(Byte*)(userdata + offset);
    
    XL_CHAR *result = (XL_CHAR *) malloc(500);
    memset(result, 0, strlen(result));
    XL_CHAR statusid[sizeof(XL_CHAR)];

    for(XL_UINT8 i = 0;i<8;i++){
        if((status>>i)&0x01){
            sprintf(statusid, "%d",i);
            strcat(result, "状态量");
            strcat(result, statusid);
            strcat(result, "发生变位 ");
        }
    }
    
    offset++;
    
    //***************完善***************//
    offset++;
    
    strcat(result, "变位时间:");
    strcat(result, time);
    
    XL_UINT8 eventlen = strlen(result);
    
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT8)); outoffset++;
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    
    free(result);
    free(time);
}


/*－－－－－－－－－－－－－－/
 遥控跳闸记录
 
 /－－－－－－－－－－－－－－*/
void geterc5(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    //事件长度
    offset++;
    
    //跳闸时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //跳闸轮次
    Byte status = *(Byte*)(userdata + offset);offset++;
    
    XL_CHAR *result = (XL_CHAR *) malloc(500);
    memset(result, 0, strlen(result));
    XL_CHAR statusid[sizeof(XL_CHAR)];
    
    
    for(XL_UINT8 i = 0;i<8;i++){
        if((status>>i)&0x01){
            sprintf(statusid, "%d",i);
            strcat(result, "控制轮次");
            strcat(result, statusid);
            strcat(result, "发生跳闸 ");
        }
    }
    
    //***************完善***************//
    offset+=4;
    //***************完善***************//
    
    strcat(result, "发生时间:");
    strcat(result, time);
    
    XL_UINT8 eventlen = strlen(result);
    
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT8)); outoffset++;
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    
    free(result);
    free(time);
}

/*－－－－－－－－－－－－－－/
 电能表参数变更
 
 /－－－－－－－－－－－－－－*/
void geterc8(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    //事件长度
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata + offset)&0x0fff;offset+=2;
    XL_CHAR mpoint_[sizeof(XL_UINT16)];sprintf(mpoint_, "%d",mpoint);
    
    //变更标志
    Byte status = *(Byte*)(userdata + offset);offset++;
    
    XL_CHAR *result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, "电能表参数变更 ");
    strcat(result, "测量点号:");strcat(result, mpoint_);
    
    if (status&0x01) {
        strcat(result, " 电能表费率时段变化 ");
    }
    if (status>>1&0x01) {
        strcat(result, " 电能表编程时间更改 ");
    }
    if (status>>2&0x01) {
        strcat(result, " 电能表抄表日更改 ");
    }
    if (status>>3&0x01) {
        strcat(result, " 电能表脉冲常数更改 ");
    }
    if (status>>4&0x01) {
        strcat(result, " 电能表的互感器倍率更改 ");
    }
    if (status>>5&0x01) {
        strcat(result, " 电能表最大需量清零 ");
    }
    strcat(result, "发生时间:");
    strcat(result, time);
    
    XL_UINT8 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT8));outoffset++;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
    
    free(result);
    free(time);
}


/*－－－－－－－－－－－－－－/
 电能表时间超差
 
 /－－－－－－－－－－－－－－*/
void geterc12(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    //事件长度
    offset++;
    
   //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata + offset)&0x0fff;
    XL_CHAR mpoint_[sizeof(XL_UINT16)];sprintf(mpoint_, "%d",mpoint);
    
    //起止标志
    XL_CHAR *flag = (*(XL_UINT16*)(userdata + offset)>>15)&0x0001 ? "电能表超差发生,": "电能表超差恢复,";
    offset+=2;
    
    XL_CHAR *result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, flag);
    strcat(result, " 测量点号:");
    strcat(result, mpoint_);
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    XL_UINT8 eventlen = strlen(result);
    
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT8)); outoffset++;
    memcpy(buff + outoffset, result, eventlen);outoffset+= eventlen;
    
    free(result);
    free(time);
}

/*－－－－－－－－－－－－－－/
 电表故障信息
 
 /－－－－－－－－－－－－－－*/
void geterc13(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    //事件长度
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata + offset)&0x0fff;
    XL_CHAR mpoint_[sizeof(XL_UINT16)];sprintf(mpoint_, "%d",mpoint);
    
    //起止标志
    XL_CHAR *flag = (*(XL_UINT16*)(userdata + offset)>>15)&0x0001 ? "电能表故障发生,": "电能表故障恢复,";
    offset+=2;
    
    //异常标志
    Byte status = *(Byte*)(userdata + offset);offset++;
    
    XL_CHAR *result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, flag);
    strcat(result, "测量点号:");strcat(result, mpoint_);
    
    if (status&0x01) {
        strcat(result, " 电能表编程次数或最大需量清零次数发生变化 ");
    }
    if (status>>1&0x01) {
        strcat(result, " 电能表断相次数变化 ");
    }
    if (status>>2&0x01) {
        strcat(result, " 电能表失压次数变化 ");
    }
    if (status>>3&0x01) {
        strcat(result, " 电能表停电次数变化 ");
    }
    if (status>>4&0x01) {
        strcat(result, " 电能表电池欠压 ");
    }

    strcat(result, "发生时间:");
    strcat(result, time);
    
    XL_UINT8 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT8));outoffset++;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
    
    free(result);
    free(time);
}

/*－－－－－－－－－－－－－－/
 直流模拟量越限记录
 
 /－－－－－－－－－－－－－－*/
void geterc16(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    offset++;
    
    //事件发生时间
    XL_CHAR *time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT8 mport = *(Byte*)(userdata + offset)&0x3f;
    XL_CHAR mport_[sizeof(XL_UINT16)];sprintf(mport_, "%d",mport);
    
    //起止标志
    XL_CHAR* seflag = (*(Byte*)(userdata + offset)>>7 &0x01)?"直流模拟量越限发生":"直流模拟量越限恢复";
    offset++;
    
    //越限标志
    Byte status = *(Byte*)(userdata + offset);offset++;
    
    XL_CHAR* result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, seflag);
    strcat(result, " 端口号:");
    strcat(result, mport_);
    
    //类型:越上限
    if (status & 0x01) {
        strcat(result, " 类型:越上限");
    }
    
    //类型:越下限
    if ((status>>1) & 0x01) {
        strcat(result, " 类型:越下限");
    }
    
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    XL_UINT8 evetlen = strlen(result);
    memcpy(buff + outoffset, &evetlen, sizeof(XL_UINT8));outoffset++;
    memcpy(buff + outoffset, result, strlen(result));outoffset += evetlen;
    
    free(result);
    free(time);
}



/*－－－－－－－－－－－－－－/
 终端故障记录
 
 /－－－－－－－－－－－－－－*/
void geterc21(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //终端故障编码
    XL_UINT8 status = *(Byte*)(userdata+offset);offset++;
    
    char* type;
    
    switch (status) {
        case 1:
            type = "终端主板内存故障";
            break;
        case 2:
            type = "时钟故障";
            break;
        case 3:
            type = "主板通信故障";
            break;
        case 4:
            type = "485抄表故障";
            break;
        case 5:
            type = "显示板故障";
            break;
        case 6:
            type = "载波通道异常";
            break;
    }
    
    XL_CHAR* result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, "终端故障发生 ");
    strcat(result, "故障类型:");
    strcat(result, type);
    strcat(result, "发生时间:");
    strcat(result, time);
    
    XL_UINT8 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT8));outoffset+=1;
    memcpy(buff + outoffset, result, strlen(result));outoffset += eventlen;
    
    free(time);
    free(result);
}



/*－－－－－－－－－－－－－－/
 电能表示度下降
 
 /－－－－－－－－－－－－－－*/
void geterc27(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata+offset)&0x0fff;
    XL_CHAR mpoint_[sizeof(XL_UINT16)];sprintf(mpoint_,"%d",mpoint);
    
    //起止标志
    XL_CHAR* seflag = (*(XL_UINT16*)(userdata+offset)>>15 & 0x0001)?"电能表示度下降发生":"电能表示度下降恢复";
    offset+=2;
    
    //下降前电能表正向有功总电能示值
    XL_FP64 power1 = bcdtouint(userdata, 5, 4);offset+=5;
    XL_CHAR power1_[sizeof(XL_FP64)];sprintf(power1_, "%.4f",power1);
    
    //下降后电能表正向有功总电能示值
    XL_FP64 power2 = bcdtouint(userdata, 5, 4);offset+=5;
    XL_CHAR power2_[sizeof(XL_FP64)];sprintf(power2_, "%.4f",power2);

    XL_CHAR* result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, seflag);
    strcat(result, " 测量点号:");
    strcat(result, mpoint_);
    strcat(result, " 下降前电能表正向有功总电能示值:");strcat(result,power1_);
    strcat(result, " 下降后电能表正向有功总电能示值:");strcat(result,power2_);
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    XL_UINT8 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT8));outoffset++;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
    
    free(result);
    free(time);
}


/*－－－－－－－－－－－－－－/
 电能表超差记录
 
 /－－－－－－－－－－－－－－*/
void geterc28(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata+offset)&0x0fff;
    XL_CHAR mpoint_[sizeof(XL_UINT16)];sprintf(mpoint_,"%d",mpoint);
    
    //起止标志
    XL_CHAR* seflag = (*(XL_UINT16*)(userdata+offset)>>15 & 0x0001)?"电能表超差记录发生":"电能表超差记录恢复";
    offset+=2;
    
    //电能量超差发生前正向有功总电能示值
    XL_FP64 power1 = bcdtouint(userdata, 5, 4);offset+=5;
    XL_CHAR power1_[sizeof(XL_FP64)];sprintf(power1_, "%.4f",power1);
    
    //电能量超差发生后正向有功总电能示值
    XL_FP64 power2 = bcdtouint(userdata, 5, 4);offset+=5;
    XL_CHAR power2_[sizeof(XL_FP64)];sprintf(power2_, "%.4f",power2);
    
    //电能表超差阈值
    XL_FP32 value = bcdtouint(userdata, 1, 1);offset++;
    XL_CHAR value_[sizeof(XL_FP32)];sprintf(value_,"%.1f",value);
    
    
    XL_CHAR* result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, seflag);
    strcat(result, " 测量点号:");
    strcat(result, mpoint_);
    strcat(result, " 电能量超差发生前正向有功总电能示值:");strcat(result,power1_);
    strcat(result, " 电能量超差发生后正向有功总电能示值:");strcat(result,power2_);
    strcat(result, " 电能表超差阈值:");strcat(result,value_);
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    XL_UINT8 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT8));outoffset++;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
    
    free(result);
    free(time);
}


/*－－－－－－－－－－－－－－/
 电能表飞走记录
 
 /－－－－－－－－－－－－－－*/
void geterc29(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata+offset)&0x0fff;
    XL_CHAR mpoint_[sizeof(XL_UINT16)];sprintf(mpoint_,"%d",mpoint);
    
    //起止标志
    XL_CHAR* seflag = (*(XL_UINT16*)(userdata+offset)>>15 & 0x0001)?"电能表飞走记录发生":"电能表飞走记录恢复";
    offset+=2;
    
    //电能表发生前正向有功总电能示值
    XL_FP64 power1 = bcdtouint(userdata, 5, 4);offset+=5;
    XL_CHAR power1_[sizeof(XL_FP64)];sprintf(power1_, "%.4f",power1);
    
    //电能表发生后正向有功总电能示值
    XL_FP64 power2 = bcdtouint(userdata, 5, 4);offset+=5;
    XL_CHAR power2_[sizeof(XL_FP64)];sprintf(power2_, "%.4f",power2);
    
    //电能表飞走阈值
    XL_FP32 value = bcdtouint(userdata, 1, 1);offset++;
    XL_CHAR value_[sizeof(XL_FP32)];sprintf(value_,"%.1f",value);
    
    
    XL_CHAR* result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, seflag);
    strcat(result, " 测量点号:");
    strcat(result, mpoint_);
    strcat(result, " 电能表发生前正向有功总电能示值:");strcat(result,power1_);
    strcat(result, " 电能表发生后正向有功总电能示值:");strcat(result,power2_);
    strcat(result, " 电能表飞走阈值:");strcat(result,value_);
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    XL_UINT8 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT8));outoffset++;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
    
    free(result);
    free(time);
}


/*－－－－－－－－－－－－－－/
 电能表停走记录
 
 /－－－－－－－－－－－－－－*/
void geterc30(){
    
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata+offset)&0x0fff;
    XL_CHAR mpoint_[sizeof(XL_UINT16)];sprintf(mpoint_,"%d",mpoint);
    
    //起止标志
    XL_CHAR* seflag = (*(XL_UINT16*)(userdata+offset)>>15 & 0x0001)?"电能表停走记录发生":"电能表停走记录恢复";
    offset+=2;
    
    //电能表停走发生时正向有功总电能示值
    XL_FP64 power1 = bcdtouint(userdata, 5, 4);offset+=5;
    XL_CHAR power1_[sizeof(XL_FP64)];sprintf(power1_, "%.4f",power1);
    
    //电能表停走阈值
    XL_UINT8 value = *(XL_UINT8*)(userdata + offset);offset++;
    XL_CHAR value_[sizeof(XL_UINT8)];sprintf(value_,"%d",value);
    
    
    XL_CHAR* result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, seflag);
    strcat(result, " 测量点号:");
    strcat(result, mpoint_);
    strcat(result, " 电能表停走发生时正向有功总电能示值:");strcat(result,power1_);
    strcat(result, " 电能表停走阈值:");strcat(result,value_);
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    XL_UINT8 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT8));outoffset++;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
    
    free(result);
    free(time);
}


/*－－－－－－－－－－－－－－/
 终端485抄表失败事件记录
 
 /－－－－－－－－－－－－－－*/
void geterc31(){
    //2字节标识
    XL_UINT16 identifier = event;
    memcpy(buff + outoffset, &identifier, sizeof(XL_UINT16));outoffset+=2;
    
    offset++;
    
    //事件发生时间
    XL_CHAR* time = gettimestr(5);offset+=5;
    
    //测量点号
    XL_UINT16 mpoint = *(XL_UINT16*)(userdata+offset)&0x0fff;
    XL_CHAR mpoint_[sizeof(XL_UINT16)];sprintf(mpoint_,"%d",mpoint);
    
    //起止标志
    XL_CHAR* seflag = (*(XL_UINT16*)(userdata+offset)>>15 & 0x0001)?"电能表停走记录发生":"电能表停走记录恢复";
    offset+=2;
    
    //最近一次抄表成功时间
    XL_CHAR* time1 = gettimestr(5);offset+=5;
    
    //最近一次抄表成功正向有功总电能示值
    XL_FP64 power1 = bcdtouint(userdata, 5, 4);offset+=5;
    XL_CHAR power1_[sizeof(XL_FP64)];sprintf(power1_, "%.4f",power1);
    
    //最近一次抄表成功正向无功总电能示值
    XL_FP64 power2 = bcdtouint(userdata, 4, 2);offset+=4;
    XL_CHAR power2_[sizeof(XL_FP64)];sprintf(power2_, "%.2f",power2);
 
    XL_CHAR* result = malloc(500);
    memset(result, 0, strlen(result));
    
    strcat(result, seflag);
    strcat(result, " 测量点号:");
    strcat(result, mpoint_);
    strcat(result, " 最近一次抄表成功时间:");strcat(result, time1);
    strcat(result, " 最近一次抄表成功正向有功总电能示值:");strcat(result, power1_);
    strcat(result, " 最近一次抄表成功正向无功总电能示值:");strcat(result, power2_);
    strcat(result, " 发生时间:");
    strcat(result, time);
    
    XL_UINT8 eventlen = strlen(result);
    memcpy(buff + outoffset, &eventlen, sizeof(XL_UINT8));outoffset++;
    memcpy(buff + outoffset, result, strlen(result));outoffset+=eventlen;
    
    free(result);
    free(time);
}


