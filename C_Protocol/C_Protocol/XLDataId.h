//
//  XLDictionaryDataId.h
//  C_Protocol
//
//  Created by JY on 14-1-8.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#ifndef C_Protocol_XLDataId_h
#define C_Protocol_XLDataId_h


#endif

//类型枚举
enum frame_type{
    
    //终端日统计数据
    terminal_day_sta = 0,
    
    //终端月统计数据
    terminal_month_sta
    
}FRAMETYPE;



//终端日统计数据
enum terminal_day_sta {
    //数据时标
    hdDataTime = 0,
    
    //终端日供电时间
    hdPowerOnAccTm,
    
    //终端日复位次数
    hdResetAccCnt,
    
    //终端与主站日通信流量
    hdCommFlow
}TERMINAL_DAY_STA;

//终端月统计数据
enum terminal_month_sta {
    //数据时标
    hmDataTime = 0,
    
    //终端月供电时间
    hmPowerOnAccTm,
    
    //终端月复位次数
    hmResetAccCnt,
    
    //终端与主站月通信流量
    hmCommFlow
}TERMINAL_MONTH_STA;


