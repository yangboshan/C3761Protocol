//
//  XLDictionaryDataId.h
//  C_Protocol
//
//  Created by JY on 14-1-8.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#ifndef C_Protocol_XLDataId_h
#define C_Protocol_XLDataId_h

//类型枚举
enum frame_type{
    
    //终端日统计数据 0
    terminal_day_sta = 0,
    
    //终端月统计数据 1
    terminal_month_sta,
    
    
    
    //测量点日电能示值数据 2
    measure_day_powervalue,
    
    //测量点月电能示值数据 3
    measure_month_powervalue,
    
    //历史数据日需量数据 4
    history_day_powerneeds,
    
    //历史数据月需量数据 5
    history_month_powerneeds,
    
    //历史数据测量点日统计数据 6
    measure_day_sta,
    
    //历史数据测量点月统计数据 7
    measure_month_sta,
    
    //测量点曲线数据 8
    measure_curve_data,
    
    //测量点日数据-电流谐波类数据 9
    daily_data_charmonic,
    
    //测量点日数——电压谐波数据 10
    daily_data_vharmonic,
    
    //直流模拟量日数据 11
    dcanalog_day_data,
    
    //直流模拟量月数据 12
    dcanalog_month_data,
    
    
    
    
    //终端基本实时数据 13
    terminal_rt_basic_sta,
    
    //测量点基本实时数据 14
    mtr_rt_basic_sta,
    
    //实时数据电能示值类 15
    rt_power_value_sta,
    
    //实时数据需量类 16
    rt_power_needs_sta,
    
    //实时数据直流模拟量类 17
    rt_dc_analog,
    
    //实时数据谐波类 18
    mtr_rt_harmonic,
    
    //事件 19
    eventlist,
    
    //通讯参数 20
    parameter_data_comm,
    
    //测量点参数 21
    parameter_data_mtr,
    
    //终端参数 22
    parameter_data_terminal,
    
    
    //测量点通信参数
    parameter_data_mtr_comm
    
}FRAMETYPE;


//终端基本实时数据
enum terminal_rt_basic_sta {
    
    //终端抄表时间
    rtTermBasicMeterReadTime,
    
    //终端参数状态
    rtParameterStatus,
    
    //终端与主站当日通信流量
    rtDayCommunicateFlows,
    
    //终端与主站当月通信流量
    rtMonCommunicateFlows,
    
    //状态量的状态
    rtStateVarValue,
    
    //状态量变位标志
    rtStateVarChangeFlag,
    
    //当前重要事件计数器EC1值
    rtImptEventCount,
    
    //当前一般事件计数器EC2值
    rtCommonEventCount,
    
    //当前日历时钟
    rtCalendarClock,
    
    //油温
    rtOilTemperature,
    
    //A相绕组温度
    rtAWindingTemperature,
    
    //B相绕组温度
    rtBWindingTemperature,
    
    //C相绕组温度
    rtCWindingTemperature,
    
    //剩余寿命
    rtRealLifetime,
    
}TERMINAL_RT_BASIC_STA;

//测量点基本实时数据
enum mtr_rt_basic_sta
{
    //终端抄表时间
    rtMtrBasicMeterReadTime,
    
    //当前总有功功率
    rtTotalActivePower,
    
    //当前A相有功功率
    rtAActivePower,
    
    //当前B相有功功率
    rtBActivePower,
    
    //当前C相有功功率
    rtCActivePower,
    
    //当前总无功功率
    rtTotalReactivePower,
    
    //当前A相无功功率
    rtAReactivePower,
    
    //当前B相无功功率
    rtBReactivePower,
    
    //当前C相无功功率
    rtCReactivePower,
    
    //当前总功率因数
    rtTotalPowerFactor,
    
    //当前A相功率因数
    rtAPowerFactor,
    
    //当前B相功率因数
    rtBPowerFactor,
    
    //当前C相功率因数
    rtCPowerFactor,
    
    //当前A相电压
    rtAVolt,
    
    //当前B相电压
    rtBVolt,
    
    //当前C相电压
    rtCVolt,
    
    //当前A相电流
    rtACurrent,
    
    //当前B相电流
    rtBCurrent,
    
    //当前C相电流
    rtCCurrent,
    
    //当前零序电流
    rtZeroSequenceCurrent,
    
    //当前总视在功率
    rtTotalApparentPower,
    
    //当前A相视在功率
    rtAApparentPower,
    
    //当前B相视在功率
    rtBApparentPower,
    
    //当前C相视在功率
    rtCApparentPower,
    
    //A相电压相角
    rtAVoltPhaseAngle,
    
    //B相电压相角
    rtBVoltPhaseAngle,
    
    //C相电压相角
    rtCVoltPhaseAngle,
    
    //A相电流相角
    rtACurrentPhaseAngle,
    
    //B相电流相角
    rtBCurrentPhaseAngle,
    
    //C相电流相角
    rtCCurrentPhaseAngle,
    
    rtCopperLossAEValueZ,//当前铜损有功总电能示值
    
    rtIronLossAEValueZ,//当前铁损有功总电能示值
    
}MTR_RT_BASIC_STA;

enum rt_power_value_sta{
    
    //终端抄表时间
    rtPowerValueMeterReadTime,
    
    //当前正向有功总电能示值
    rtPosAEValue,
    
    //当前费率1正向有功总电能示值
    rtRate1PosAEValue,
    
    //当前费率2正向有功总电能示值
    rtRate2PosAEValue,
    
    //当前费率3正向有功总电能示值
    rtRate3PosAEValue,
    
    //当前费率4正向有功总电能示值
    rtRate4PosAEValue,
    
    //当前正向无功（组合无功1）总电能示值
    rtPosREValueG,
    
    //当前费率1正向无功（组合无功1）总电能示值
    rtRate1PosREValueG,
    
    //当前费率2正向无功（组合无功1）总电能示值
    rtRate2PosREValueG,
    
    //当前费率3正向无功（组合无功1）总电能示值
    rtRate3PosREValueG,
    
    //当前费率4正向无功（组合无功1）总电能示值
    rtRate4PosREValueG,
    
    //当前一象限无功总电能示值
    rtFirstQuarREValue,
    
    //当前一象限费率1无功电能示值
    rtFirstQuarRate1REValue,
    
    //当前一象限费率2无功电能示值
    rtFirstQuarRate2REValue,
    
    //当前一象限费率3无功电能示值
    rtFirstQuarRate3REValue,
    
    //当前一象限费率4无功电能示值
    rtFirstQuarRate4REValue,
    
    //当前四象限无功总电能示值
    rtForthQuarREValue,
    
    //当前四象限费率1无功电能示值
    rtForthQuarRate1REValue,
    
    //当前四象限费率2无功电能示值
    rtForthQuarRate2REValue,
    
    //当前四象限费率3无功电能示值
    rtForthQuarRate3REValue,
    
    //当前四象限费率4无功电能示值
    rtForthQuarRate4REValue,
    
    //当前反向有功总电能示值
    rtNegAEValue,
    
    //当前费率1反向有功总电能示值
    rtRate1NegAEValue,
    
    //当前费率2反向有功总电能示值
    rtRate2NegAEValue,
    
    //当前费率3反向有功总电能示值
    rtRate3NegAEValue,
    
    //当前费率4反向有功总电能示值
    rtRate4NegAEValue,
    
    //当前反向无功（组合无功2）总电能示值
    rtNegREValueG,
    
    //当前费率1反向无功（组合无功2）总电能示值
    rtRate1NegREValueG,
    
    //当前费率2反向无功（组合无功2）总电能示值
    rtRate2NegREValueG,
    
    //当前费率3反向无功（组合无功2）总电能示值
    rtRate3NegREValueG,
    
    //当前费率4反向无功（组合无功2）总电能示值
    rtRate4NegREValueG,
    
    //当前二象限无功总电能示值
    rtSecQuarREValue,
    
    //当前二象限费率1无功电能示值
    rtSecQuarRate1REValue,
    
    //当前二象限费率2无功电能示值
    rtSecQuarRate2REValue,
    
    //当前二象限费率3无功电能示值
    rtSecQuarRate3REValue,
    
    //当前二象限费率4无功电能示值
    rtSecQuarRate4REValue,
    
    //当前三象限无功总电能示值
    rtThirdQuarREValue,
    
    //当前三象限费率1无功电能示值
    rtThirdQuarRate1REValue,
    
    //当前三象限费率2无功电能示值
    rtThirdQuarRate2REValue,
    
    //当前三象限费率3无功电能示值
    rtThirdQuarRate3REValue,
    
    //当前三象限费率4无功电能示值
    rtThirdQuarRate4REValue,
    
}RT_POWER_VALUE_STA;

enum rt_power_needs_sta
{
    
    //终端抄表时间
    rtPowerNeedsMeterReadTime,
    
    //当月正向有功总最大需量
    rtMonPosAETotalMaxNeed,
    
    //当月正向有功费率1最大需量
    rtMonPosAERate1MaxNeed,
    
    //当月正向有功费率2最大需量
    rtMonPosAERate2MaxNeed,
    
    //当月正向有功费率3最大需量
    rtMonPosAERate3MaxNeed,
    
    //当月正向有功费率4最大需量
    rtMonPosAERate4MaxNeed,
    
    //当月正向有功总最大需量发生时间
    rtMonPosAETotalMaxNeedTm,
    
    //当月正向有功费率1最大需量发生时间
    rtMonPosAERate1MaxNeedTm,
    
    //当月正向有功费率2最大需量发生时间
    rtMonPosAERate2MaxNeedTm,
    
    //当月正向有功费率3最大需量发生时间
    rtMonPosAERate3MaxNeedTm,
    
    //当月正向有功费率4最大需量发生时间
    rtMonPosAERate4MaxNeedTm,
    
    //当月正向无功总最大需量
    rtMonPosRETotalMaxNeed,
    
    //当月正向无功费率1最大需量
    rtMonPosRERate1MaxNeed,
    
    //当月正向无功费率2最大需量
    rtMonPosRERate2MaxNeed,
    
    //当月正向无功费率3最大需量
    rtMonPosRERate3MaxNeed,
    
    //当月正向无功费率4最大需量
    rtMonPosRERate4MaxNeed,
    
    //当月正向无功总最大需量发生时间
    rtMonPosRETotalMaxNeedTm,
    
    //当月正向无功费率1最大需量发生时间
    rtMonPosRERate1MaxNeedTm,
    
    //当月正向无功费率2最大需量发生时间
    rtMonPosRERate2MaxNeedTm,
    
    //当月正向无功费率3最大需量发生时间
    rtMonPosRERate3MaxNeedTm,
    
    //当月正向无功费率4最大需量发生时间
    rtMonPosRERate4MaxNeedTm,
    
    //当月反向有功总最大需量
    rtMonNegAETotalMaxNeed,
    
    //当月反向有功费率1最大需量
    rtMonNegAERate1MaxNeed,
    
    //当月反向有功费率2最大需量
    rtMonNegAERate2MaxNeed,
    
    //当月反向有功费率3最大需量
    rtMonNegAERate3MaxNeed,
    
    //当月反向有功费率4最大需量
    rtMonNegAERate4MaxNeed,
    
    //当月反向有功总最大需量发生时间
    rtMonNegAETotalMaxNeedTm,
    
    //当月反向有功费率1最大需量发生时间
    rtMonNegAERate1MaxNeedTm,
    
    //当月反向有功费率2最大需量发生时间
    rtMonNegAERate2MaxNeedTm,
    
    //当月反向有功费率3最大需量发生时间
    rtMonNegAERate3MaxNeedTm,
    
    //当月反向有功费率4最大需量发生时间
    rtMonNegAERate4MaxNeedTm,
    
    //当月反向无功总最大需量
    rtMonNegRETotalMaxNeed,
    
    //当月反向无功费率1最大需量
    rtMonNegRERate1MaxNeed,
    
    //当月反向无功费率2最大需量
    rtMonNegRERate2MaxNeed,
    
    //当月反向无功费率3最大需量
    rtMonNegRERate3MaxNeed,
    
    //当月反向无功费率4最大需量
    rtMonNegRERate4MaxNeed,
    
    //当月反向无功总最大需量发生时间
    rtMonNegRETotalMaxNeedTm,
    
    //当月反向无功费率1最大需量发生时间
    rtMonNegRERate1MaxNeedTm,
    
    //当月反向无功费率2最大需量发生时间
    rtMonNegRERate2MaxNeedTm,
    
    //当月反向无功费率3最大需量发生时间
    rtMonNegRERate3MaxNeedTm,
    
    //当月反向无功费率4最大需量发生时间
    rtMonNegRERate4MaxNeedTm,
    
    
}RT_POWER_NEEDS_STA;

enum rt_dc_analog
{
    //直流模拟量当前数据
    rtDcAnalogValue
}RT_DC_ANALOG;

enum mtr_rt_harmonic
{
    //谐波次数
    rtHarmoTimes,
    //A相电压2次谐波有效值
    rtHarmoVoltA2EffecValue,
    
    //A相电压3次谐波有效值
    rtHarmoVoltA3EffecValue,
    
    //A相电压4次谐波有效值
    rtHarmoVoltA4EffecValue,
    
    //A相电压5次谐波有效值
    rtHarmoVoltA5EffecValue,
    
    //A相电压6次谐波有效值
    rtHarmoVoltA6EffecValue,
    
    //A相电压7次谐波有效值
    rtHarmoVoltA7EffecValue,
    
    //A相电压8次谐波有效值
    rtHarmoVoltA8EffecValue,
    
    //A相电压9次谐波有效值
    rtHarmoVoltA9EffecValue,
    
    //A相电压10次谐波有效值
    rtHarmoVoltA10EffecValue,
    
    //A相电压11次谐波有效值
    rtHarmoVoltA11EffecValue,
    
    //A相电压12次谐波有效值
    rtHarmoVoltA12EffecValue,
    
    //A相电压13次谐波有效值
    rtHarmoVoltA13EffecValue,
    
    //A相电压14次谐波有效值
    rtHarmoVoltA14EffecValue,
    
    //A相电压15次谐波有效值
    rtHarmoVoltA15EffecValue,
    
    //A相电压16次谐波有效值
    rtHarmoVoltA16EffecValue,
    
    //A相电压17次谐波有效值
    rtHarmoVoltA17EffecValue,
    
    //A相电压18次谐波有效值
    rtHarmoVoltA18EffecValue,
    
    //A相电压19次谐波有效值
    rtHarmoVoltA19EffecValue,
    
    //B相电压2次谐波有效值
    rtHarmoVoltB2EffecValue,
    
    //B相电压3次谐波有效值
    rtHarmoVoltB3EffecValue,
    
    //B相电压4次谐波有效值
    rtHarmoVoltB4EffecValue,
    
    //B相电压5次谐波有效值
    rtHarmoVoltB5EffecValue,
    
    //B相电压6次谐波有效值
    rtHarmoVoltB6EffecValue,
    
    //B相电压7次谐波有效值
    rtHarmoVoltB7EffecValue,
    
    //B相电压8次谐波有效值
    rtHarmoVoltB8EffecValue,
    
    //B相电压9次谐波有效值
    rtHarmoVoltB9EffecValue,
    
    //B相电压10次谐波有效值
    rtHarmoVoltB10EffecValue,
    
    //B相电压11次谐波有效值
    rtHarmoVoltB11EffecValue,
    
    //B相电压12次谐波有效值
    rtHarmoVoltB12EffecValue,
    
    //B相电压13次谐波有效值
    rtHarmoVoltB13EffecValue,
    
    //B相电压14次谐波有效值
    rtHarmoVoltB14EffecValue,
    
    //B相电压15次谐波有效值
    rtHarmoVoltB15EffecValue,
    
    //B相电压16次谐波有效值
    rtHarmoVoltB16EffecValue,
    
    //B相电压17次谐波有效值
    rtHarmoVoltB17EffecValue,
    
    //B相电压18次谐波有效值
    rtHarmoVoltB18EffecValue,
    
    //B相电压19次谐波有效值
    rtHarmoVoltB19EffecValue,
    
    //C相电压2次谐波有效值
    rtHarmoVoltC2EffecValue,
    
    //C相电压3次谐波有效值
    rtHarmoVoltC3EffecValue,
    
    //C相电压4次谐波有效值
    rtHarmoVoltC4EffecValue,
    
    //C相电压5次谐波有效值
    rtHarmoVoltC5EffecValue,
    
    //C相电压6次谐波有效值
    rtHarmoVoltC6EffecValue,
    
    //C相电压7次谐波有效值
    rtHarmoVoltC7EffecValue,
    
    //C相电压8次谐波有效值
    rtHarmoVoltC8EffecValue,
    
    //C相电压9次谐波有效值
    rtHarmoVoltC9EffecValue,
    
    //C相电压10次谐波有效值
    rtHarmoVoltC10EffecValue,
    
    //C相电压11次谐波有效值
    rtHarmoVoltC11EffecValue,
    
    //C相电压12次谐波有效值
    rtHarmoVoltC12EffecValue,
    
    //C相电压13次谐波有效值
    rtHarmoVoltC13EffecValue,
    
    //C相电压14次谐波有效值
    rtHarmoVoltC14EffecValue,
    
    //C相电压15次谐波有效值
    rtHarmoVoltC15EffecValue,
    
    //C相电压16次谐波有效值
    rtHarmoVoltC16EffecValue,
    
    //C相电压17次谐波有效值
    rtHarmoVoltC17EffecValue,
    
    //C相电压18次谐波有效值
    rtHarmoVoltC18EffecValue,
    
    //C相电压19次谐波有效值
    rtHarmoVoltC19EffecValue,
    
    //A相电流2次谐波有效值
    rtHarmoCurrentA2EffecValue,
    
    //A相电流3次谐波有效值
    rtHarmoCurrentA3EffecValue,
    
    //A相电流4次谐波有效值
    rtHarmoCurrentA4EffecValue,
    
    //A相电流5次谐波有效值
    rtHarmoCurrentA5EffecValue,
    
    //A相电流6次谐波有效值
    rtHarmoCurrentA6EffecValue,
    
    //A相电流7次谐波有效值
    rtHarmoCurrentA7EffecValue,
    
    //A相电流8次谐波有效值
    rtHarmoCurrentA8EffecValue,
    
    //A相电流9次谐波有效值
    rtHarmoCurrentA9EffecValue,
    
    //A相电流10次谐波有效值
    rtHarmoCurrentA10EffecValue,
    
    //A相电流11次谐波有效值
    rtHarmoCurrentA11EffecValue,
    
    //A相电流12次谐波有效值
    rtHarmoCurrentA12EffecValue,
    
    //A相电流13次谐波有效值
    rtHarmoCurrentA13EffecValue,
    
    //A相电流14次谐波有效值
    rtHarmoCurrentA14EffecValue,
    
    //A相电流15次谐波有效值
    rtHarmoCurrentA15EffecValue,
    
    //A相电流16次谐波有效值
    rtHarmoCurrentA16EffecValue,
    
    //A相电流17次谐波有效值
    rtHarmoCurrentA17EffecValue,
    
    //A相电流18次谐波有效值
    rtHarmoCurrentA18EffecValue,
    
    //A相电流19次谐波有效值
    rtHarmoCurrentA19EffecValue,
    
    //B相电流2次谐波有效值
    rtHarmoCurrentB2EffecValue,
    
    //B相电流3次谐波有效值
    rtHarmoCurrentB3EffecValue,
    
    //B相电流4次谐波有效值
    rtHarmoCurrentB4EffecValue,
    
    //B相电流5次谐波有效值
    rtHarmoCurrentB5EffecValue,
    
    //B相电流6次谐波有效值
    rtHarmoCurrentB6EffecValue,
    
    //B相电流7次谐波有效值
    rtHarmoCurrentB7EffecValue,
    
    //B相电流8次谐波有效值
    rtHarmoCurrentB8EffecValue,
    
    //B相电流9次谐波有效值
    rtHarmoCurrentB9EffecValue,
    
    //B相电流10次谐波有效值
    rtHarmoCurrentB10EffecValue,
    
    //B相电流11次谐波有效值
    rtHarmoCurrentB11EffecValue,
    
    //B相电流12次谐波有效值
    rtHarmoCurrentB12EffecValue,
    
    //B相电流13次谐波有效值
    rtHarmoCurrentB13EffecValue,
    
    //B相电流14次谐波有效值
    rtHarmoCurrentB14EffecValue,
    
    //B相电流15次谐波有效值
    rtHarmoCurrentB15EffecValue,
    
    //B相电流16次谐波有效值
    rtHarmoCurrentB16EffecValue,
    
    //B相电流17次谐波有效值
    rtHarmoCurrentB17EffecValue,
    
    //B相电流18次谐波有效值
    rtHarmoCurrentB18EffecValue,
    
    //B相电流19次谐波有效值
    rtHarmoCurrentB19EffecValue,
    
    //C相电流2次谐波有效值
    rtHarmoCurrentC2EffecValue,
    
    //C相电流3次谐波有效值
    rtHarmoCurrentC3EffecValue,
    
    //C相电流4次谐波有效值
    rtHarmoCurrentC4EffecValue,
    
    //C相电流5次谐波有效值
    rtHarmoCurrentC5EffecValue,
    
    //C相电流6次谐波有效值
    rtHarmoCurrentC6EffecValue,
    
    //C相电流7次谐波有效值
    rtHarmoCurrentC7EffecValue,
    
    //C相电流8次谐波有效值
    rtHarmoCurrentC8EffecValue,
    
    //C相电流9次谐波有效值
    rtHarmoCurrentC9EffecValue,
    
    //C相电流10次谐波有效值
    rtHarmoCurrentC10EffecValue,
    
    //C相电流11次谐波有效值
    rtHarmoCurrentC11EffecValue,
    
    //C相电流12次谐波有效值
    rtHarmoCurrentC12EffecValue,
    
    //C相电流13次谐波有效值
    rtHarmoCurrentC13EffecValue,
    
    //C相电流14次谐波有效值
    rtHarmoCurrentC14EffecValue,
    
    //C相电流15次谐波有效值
    rtHarmoCurrentC15EffecValue,
    
    //C相电流16次谐波有效值
    rtHarmoCurrentC16EffecValue,
    
    //C相电流17次谐波有效值
    rtHarmoCurrentC17EffecValue,
    
    //C相电流18次谐波有效值
    rtHarmoCurrentC18EffecValue,
    
    //C相电流19次谐波有效值
    rtHarmoCurrentC19EffecValue,
    
    //当前A相电压总谐波含有率
    rtVoltAHarmoRateZ,
    
    //当前A相电压2次谐波含有率
    rtVoltA2HarmoRate,
    
    //当前A相电压3次谐波含有率
    rtVoltA3HarmoRate,
    
    //当前A相电压4次谐波含有率
    rtVoltA4HarmoRate,
    
    //当前A相电压5次谐波含有率
    rtVoltA5HarmoRate,
    
    //当前A相电压6次谐波含有率
    rtVoltA6HarmoRate,
    
    //当前A相电压7次谐波含有率
    rtVoltA7HarmoRate,
    
    //当前A相电压8次谐波含有率
    rtVoltA8HarmoRate,
    
    //当前A相电压9次谐波含有率
    rtVoltA9HarmoRate,
    
    //当前A相电压10次谐波含有率
    rtVoltA10HarmoRate,
    
    //当前A相电压11次谐波含有率
    rtVoltA11HarmoRate,
    
    //当前A相电压12次谐波含有率
    rtVoltA12HarmoRate,
    
    //当前A相电压13次谐波含有率
    rtVoltA13HarmoRate,
    
    //当前A相电压14次谐波含有率
    rtVoltA14HarmoRate,
    
    //当前A相电压15次谐波含有率
    rtVoltA15HarmoRate,
    
    //当前A相电压16次谐波含有率
    rtVoltA16HarmoRate,
    
    //当前A相电压17次谐波含有率
    rtVoltA17HarmoRate,
    
    //当前A相电压18次谐波含有率
    rtVoltA18HarmoRate,
    
    //当前A相电压19次谐波含有率
    rtVoltA19HarmoRate,
    
    //当前B相电压总谐波含有率
    rtVoltBHarmoRateZ,
    
    //当前B相电压2次谐波含有率
    rtVoltB2HarmoRate,
    
    //当前B相电压3次谐波含有率
    rtVoltB3HarmoRate,
    
    //当前B相电压4次谐波含有率
    rtVoltB4HarmoRate,
    
    //当前B相电压5次谐波含有率
    rtVoltB5HarmoRate,
    
    //当前B相电压6次谐波含有率
    rtVoltB6HarmoRate,
    
    //当前B相电压7次谐波含有率
    rtVoltB7HarmoRate,
    
    //当前B相电压8次谐波含有率
    rtVoltB8HarmoRate,
    
    //当前B相电压9次谐波含有率
    rtVoltB9HarmoRate,
    
    //当前B相电压10次谐波含有率
    rtVoltB10HarmoRate,
    
    //当前B相电压11次谐波含有率
    rtVoltB11HarmoRate,
    
    //当前B相电压12次谐波含有率
    rtVoltB12HarmoRate,
    
    //当前B相电压13次谐波含有率
    rtVoltB13HarmoRate,
    
    //当前B相电压14次谐波含有率
    rtVoltB14HarmoRate,
    
    //当前B相电压15次谐波含有率
    rtVoltB15HarmoRate,
    
    //当前B相电压16次谐波含有率
    rtVoltB16HarmoRate,
    
    //当前B相电压17次谐波含有率
    rtVoltB17HarmoRate,
    
    //当前B相电压18次谐波含有率
    rtVoltB18HarmoRate,
    
    //当前B相电压19次谐波含有率
    rtVoltB19HarmoRate,
    
    //当前C相电压总谐波含有率
    rtVoltCHarmoRateZ,
    
    //当前C相电压2次谐波含有率
    rtVoltC2HarmoRate,
    
    //当前C相电压3次谐波含有率
    rtVoltC3HarmoRate,
    
    //当前C相电压4次谐波含有率
    rtVoltC4HarmoRate,
    
    //当前C相电压5次谐波含有率
    rtVoltC5HarmoRate,
    
    //当前C相电压6次谐波含有率
    rtVoltC6HarmoRate,
    
    //当前C相电压7次谐波含有率
    rtVoltC7HarmoRate,
    
    //当前C相电压8次谐波含有率
    rtVoltC8HarmoRate,
    
    //当前C相电压9次谐波含有率
    rtVoltC9HarmoRate,
    
    //当前C相电压10次谐波含有率
    rtVoltC10HarmoRate,
    
    //当前C相电压11次谐波含有率
    rtVoltC11HarmoRate,
    
    //当前C相电压12次谐波含有率
    rtVoltC12HarmoRate,
    
    //当前C相电压13次谐波含有率
    rtVoltC13HarmoRate,
    
    //当前C相电压14次谐波含有率
    rtVoltC14HarmoRate,
    
    //当前C相电压15次谐波含有率
    rtVoltC15HarmoRate,
    
    //当前C相电压16次谐波含有率
    rtVoltC16HarmoRate,
    
    //当前C相电压17次谐波含有率
    rtVoltC17HarmoRate,
    
    //当前C相电压18次谐波含有率
    rtVoltC18HarmoRate,
    
    //当前C相电压19次谐波含有率
    rtVoltC19HarmoRate,

    //当前A相电流2次谐波含有率
    rtCurrentA2HarmoRate,
    
    //当前A相电流3次谐波含有率
    rtCurrentA3HarmoRate,
    
    //当前A相电流4次谐波含有率
    rtCurrentA4HarmoRate,
    
    //当前A相电流5次谐波含有率
    rtCurrentA5HarmoRate,
    
    //当前A相电流6次谐波含有率
    rtCurrentA6HarmoRate,
    
    //当前A相电流7次谐波含有率
    rtCurrentA7HarmoRate,
    
    //当前A相电流8次谐波含有率
    rtCurrentA8HarmoRate,
    
    //当前A相电流9次谐波含有率
    rtCurrentA9HarmoRate,
    
    //当前A相电流10次谐波含有率
    rtCurrentA10HarmoRate,
    
    //当前A相电流11次谐波含有率
    rtCurrentA11HarmoRate,
    
    //当前A相电流12次谐波含有率
    rtCurrentA12HarmoRate,
    
    //当前A相电流13次谐波含有率
    rtCurrentA13HarmoRate,
    
    //当前A相电流14次谐波含有率
    rtCurrentA14HarmoRate,
    
    //当前A相电流15次谐波含有率
    rtCurrentA15HarmoRate,
    
    //当前A相电流16次谐波含有率
    rtCurrentA16HarmoRate,
    
    //当前A相电流17次谐波含有率
    rtCurrentA17HarmoRate,
    
    //当前A相电流18次谐波含有率
    rtCurrentA18HarmoRate,
    
    //当前A相电流19次谐波含有率
    rtCurrentA19HarmoRate,
    
    //当前B相电流2次谐波含有率
    rtCurrentB2HarmoRate,
    
    //当前B相电流3次谐波含有率
    rtCurrentB3HarmoRate,
    
    //当前B相电流4次谐波含有率
    rtCurrentB4HarmoRate,
    
    //当前B相电流5次谐波含有率
    rtCurrentB5HarmoRate,
    
    //当前B相电流6次谐波含有率
    rtCurrentB6HarmoRate,
    
    //当前B相电流7次谐波含有率
    rtCurrentB7HarmoRate,
    
    //当前B相电流8次谐波含有率
    rtCurrentB8HarmoRate,
    
    //当前B相电流9次谐波含有率
    rtCurrentB9HarmoRate,
    
    //当前B相电流10次谐波含有率
    rtCurrentB10HarmoRate,
    
    //当前B相电流11次谐波含有率
    rtCurrentB11HarmoRate,
    
    //当前B相电流12次谐波含有率
    rtCurrentB12HarmoRate,
    
    //当前B相电流13次谐波含有率
    rtCurrentB13HarmoRate,
    
    //当前B相电流14次谐波含有率
    rtCurrentB14HarmoRate,
    
    //当前B相电流15次谐波含有率
    rtCurrentB15HarmoRate,
    
    //当前B相电流16次谐波含有率
    rtCurrentB16HarmoRate,
    
    //当前B相电流17次谐波含有率
    rtCurrentB17HarmoRate,
    
    //当前B相电流18次谐波含有率
    rtCurrentB18HarmoRate,
    
    //当前B相电流19次谐波含有率
    rtCurrentB19HarmoRate,
    
    //当前C相电流2次谐波含有率
    rtCurrentC2HarmoRate,
    
    //当前C相电流3次谐波含有率
    rtCurrentC3HarmoRate,
    
    //当前C相电流4次谐波含有率
    rtCurrentC4HarmoRate,
    
    //当前C相电流5次谐波含有率
    rtCurrentC5HarmoRate,
    
    //当前C相电流6次谐波含有率
    rtCurrentC6HarmoRate,
    
    //当前C相电流7次谐波含有率
    rtCurrentC7HarmoRate,
    
    //当前C相电流8次谐波含有率
    rtCurrentC8HarmoRate,
    
    //当前C相电流9次谐波含有率
    rtCurrentC9HarmoRate,
    
    //当前C相电流10次谐波含有率
    rtCurrentC10HarmoRate,
    
    //当前C相电流11次谐波含有率
    rtCurrentC11HarmoRate,
    
    //当前C相电流12次谐波含有率
    rtCurrentC12HarmoRate,
    
    //当前C相电流13次谐波含有率
    rtCurrentC13HarmoRate,
    
    //当前C相电流14次谐波含有率
    rtCurrentC14HarmoRate,
    
    //当前C相电流15次谐波含有率
    rtCurrentC15HarmoRate,
    
    //当前C相电流16次谐波含有率
    rtCurrentC16HarmoRate,
    
    //当前C相电流17次谐波含有率
    rtCurrentC17HarmoRate,
    
    //当前C相电流18次谐波含有率
    rtCurrentC18HarmoRate,
    
    //当前C相电流19次谐波含有率
    rtCurrentC19HarmoRate,
    
}MTR_RT_HARMONIC;


//直流模拟量日数据
typedef enum dcanalog_day_data
{
    
    //数据时标
    hdDataTime_ddd,
    
    //直流模拟量端口号
    hdDCPort,
    
    //直流模拟量越上限日/月累计时间
    hdDCAnalogDHiAccTm,
    
    //直流模拟量越下限日/月累计时间
    hdDCAnalogDLoAccTm,
    
    //直流模拟量日/月最大值
    hdDCAnalogMax,
    
    //直流模拟量日/月最大值发生时间
    hdDCAnalogMaxTm,
    
    //直流模拟量日/月最小值
    hdDCAnalogMin,
    
    //直流模拟量日/月最小值发生时间
    hdDCAnalogMinTm,
    
}DCAMALOG_DAY_DATA;

//直流模拟量月数据
typedef enum dcanalog_month_data
{
    
    //数据时标
    hmDataTime_dmd,
    
    //直流模拟量端口号
    hmDCPort,
    
    //直流模拟量越上限日/月累计时间
    hmDCAnalogDHiAccTm,
    
    //直流模拟量越下限日/月累计时间
    hmDCAnalogDLoAccTm,
    
    //直流模拟量日/月最大值
    hmDCAnalogMax,
    
    //直流模拟量日/月最大值发生时间
    hmDCAnalogMaxTm,
    
    //直流模拟量日/月最小值
    hmDCAnalogMin,
    
    //直流模拟量日/月最小值发生时间
    hmDCAnalogMinTm,
    
}DCAMALOG_MONTH_DATA;





//测量点日数据——电压谐波数据
typedef enum daily_data_vharmonic
{
    //数据时标
    hdDataTime_ddv,
    
    //A相2次谐波电压含有率日最大值
    hdHarmoAVoltMax2,
    
    //A相2次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax2Tm,
    
    //A相3次谐波电压含有率日最大值
    hdHarmoAVoltMax3,
    
    //A相3次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax3Tm,
    
    //A相4次谐波电压含有率日最大值
    hdHarmoAVoltMax4,
    
    //A相4次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax4Tm,
    
    //A相5次谐波电压含有率日最大值
    hdHarmoAVoltMax5,
    
    //A相5次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax5Tm,
    
    //A相6次谐波电压含有率日最大值
    hdHarmoAVoltMax6,
    
    //A相6次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax6Tm,
    
    //A相7次谐波电压含有率日最大值
    hdHarmoAVoltMax7,
    
    //A相7次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax7Tm,
    
    //A相8次谐波电压含有率日最大值
    hdHarmoAVoltMax8,
    
    //A相8次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax8Tm,
    
    //A相9次谐波电压含有率日最大值
    hdHarmoAVoltMax9,
    
    //A相9次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax9Tm,
    
    //A相10次谐波电压含有率日最大值
    hdHarmoAVoltMax10,
    
    //A相10次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax10Tm,
    
    //A相11次谐波电压含有率日最大值
    hdHarmoAVoltMax11,
    
    //A相11次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax11Tm,
    
    //A相12次谐波电压含有率日最大值
    hdHarmoAVoltMax12,
    
    //A相12次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax12Tm,
    
    //A相13次谐波电压含有率日最大值
    hdHarmoAVoltMax13,
    
    //A相13次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax13Tm,
    
    //A相14次谐波电压含有率日最大值
    hdHarmoAVoltMax14,
    
    //A相14次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax14Tm,
    
    //A相15次谐波电压含有率日最大值
    hdHarmoAVoltMax15,
    
    //A相15次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax15Tm,
    
    //A相16次谐波电压含有率日最大值
    hdHarmoAVoltMax16,
    
    //A相16次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax16Tm,
    
    //A相17次谐波电压含有率日最大值
    hdHarmoAVoltMax17,
    
    //A相17次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax17Tm,
    
    //A相18次谐波电压含有率日最大值
    hdHarmoAVoltMax18,
    
    //A相18次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax18Tm,
    
    //A相19次谐波电压含有率日最大值
    hdHarmoAVoltMax19,
    
    //A相19次谐波电压含有率日最大值发生时间
    hdHarmoAVoltMax19Tm,
    
    //A相总谐波电压含有率日最大值
    hdDistortionAVoltMax,
    
    //A相总谐波电压含有率日最大值发生时间
    hdDistortionAVoltMaxTm,
    
    //B相2次谐波电压含有率日最大值
    hdHarmoBVoltMax2,
    
    //B相2次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax2Tm,
    
    //B相3次谐波电压含有率日最大值
    hdHarmoBVoltMax3,
    
    //B相3次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax3Tm,
    
    //B相4次谐波电压含有率日最大值
    hdHarmoBVoltMax4,
    
    //B相4次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax4Tm,
    
    //B相5次谐波电压含有率日最大值
    hdHarmoBVoltMax5,
    
    //B相5次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax5Tm,
    
    //B相6次谐波电压含有率日最大值
    hdHarmoBVoltMax6,
    
    //B相6次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax6Tm,
    
    //B相7次谐波电压含有率日最大值
    hdHarmoBVoltMax7,
    
    //B相7次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax7Tm,
    
    //B相8次谐波电压含有率日最大值
    hdHarmoBVoltMax8,
    
    //B相8次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax8Tm,
    
    //B相9次谐波电压含有率日最大值
    hdHarmoBVoltMax9,
    
    //B相9次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax9Tm,
    
    //B相10次谐波电压含有率日最大值
    hdHarmoBVoltMax10,
    
    //B相10次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax10Tm,
    
    //B相11次谐波电压含有率日最大值
    hdHarmoBVoltMax11,
    
    //B相11次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax11Tm,
    
    //B相12次谐波电压含有率日最大值
    hdHarmoBVoltMax12,
    
    //B相12次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax12Tm,
    
    //B相13次谐波电压含有率日最大值
    hdHarmoBVoltMax13,
    
    //B相13次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax13Tm,
    
    //B相14次谐波电压含有率日最大值
    hdHarmoBVoltMax14,
    
    //B相14次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax14Tm,
    
    //B相15次谐波电压含有率日最大值
    hdHarmoBVoltMax15,
    
    //B相15次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax15Tm,
    
    //B相16次谐波电压含有率日最大值
    hdHarmoBVoltMax16,
    
    //B相16次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax16Tm,
    
    //B相17次谐波电压含有率日最大值
    hdHarmoBVoltMax17,
    
    //B相17次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax17Tm,
    
    //B相18次谐波电压含有率日最大值
    hdHarmoBVoltMax18,
    
    //B相18次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax18Tm,
    
    //B相19次谐波电压含有率日最大值
    hdHarmoBVoltMax19,
    
    //B相19次谐波电压含有率日最大值发生时间
    hdHarmoBVoltMax19Tm,
    
    //B相总谐波电压含有率日最大值
    hdDistortionBVoltMax,
    
    //B相总谐波电压含有率日最大值发生时间
    hdDistortionBVoltMaxTm,
    
    
    hdHarmoCVoltMax2,  //C相2次谐波电压含有率日最大值
    
    hdHarmoCVoltMax2Tm,//C相2次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax3,  //C相3次谐波电压含有率日最大值
    
    hdHarmoCVoltMax3Tm,//C相3次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax4,  //C相4次谐波电压含有率日最大值
    
    hdHarmoCVoltMax4Tm,//C相4次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax5,  //C相5次谐波电压含有率日最大值
    
    hdHarmoCVoltMax5Tm,//C相5次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax6,  //C相6次谐波电压含有率日最大值
    
    hdHarmoCVoltMax6Tm,//C相6次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax7,  //C相7次谐波电压含有率日最大值
    
    hdHarmoCVoltMax7Tm,//C相7次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax8,  //C相8次谐波电压含有率日最大值
    
    hdHarmoCVoltMax8Tm,//C相8次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax9,  //C相9次谐波电压含有率日最大值
    
    hdHarmoCVoltMax9Tm,//C相9次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax10 ,//C相10次谐波电压含有率日最大值
    
    hdHarmoCVoltMax10Tm,//C相10次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax11,  //C相11次谐波电压含有率日最大值
    
    hdHarmoCVoltMax11Tm,//C相11次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax12,  //C相12次谐波电压含有率日最大值
    
    hdHarmoCVoltMax12Tm,//C相12次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax13,  //C相13次谐波电压含有率日最大值
    
    hdHarmoCVoltMax13Tm,//C相13次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax14,  //C相14次谐波电压含有率日最大值
    
    hdHarmoCVoltMax14Tm,//C相14次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax15,  //C相15次谐波电压含有率日最大值
    
    hdHarmoCVoltMax15Tm,//C相15次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax16,  //C相16次谐波电压含有率日最大值
    
    hdHarmoCVoltMax16Tm,//C相16次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax17,  //C相17次谐波电压含有率日最大值
    
    hdHarmoCVoltMax17Tm,//C相17次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax18,  //C相18次谐波电压含有率日最大值
    
    hdHarmoCVoltMax18Tm,//C相18次谐波电压含有率日最大值发生时间
    
    hdHarmoCVoltMax19,  //C相19次谐波电压含有率日最大值
    
    hdHarmoCVoltMax19Tm,//C相19次谐波电压含有率日最大值发生时间
    
    hdDistortionCVoltMax,//C相总谐波电压含有率日最大值
    
    hdDistortionCVoltMaxTm,//C相总谐波电压含有率日最大值发生时间
    
}DAILY_DATA_VHARMONIC;









//测量点日数据－电流谐波类数据
typedef enum daily_data_charmonic
{
    hdDataTime_ddc,//数据时标
    
    hdHarmoACurMax2,  //A相2次谐波电流日最大值
    
    hdHarmoACurMax2Tm,//A相2次谐波电流日最大值发生时间
    
    hdHarmoACurMax3,  //A相3次谐波电流日最大值
    
    hdHarmoACurMax3Tm,//A相3次谐波电流日最大值发生时间
    
    hdHarmoACurMax4,  //A相4次谐波电流日最大值
    
    hdHarmoACurMax4Tm,//A相4次谐波电流日最大值发生时间
    
    hdHarmoACurMax5,  //A相5次谐波电流日最大值
    
    hdHarmoACurMax5Tm,//A相5次谐波电流日最大值发生时间
    
    hdHarmoACurMax6,  //A相6次谐波电流日最大值
    
    hdHarmoACurMax6Tm,//A相6次谐波电流日最大值发生时间
    
    hdHarmoACurMax7,  //A相7次谐波电流日最大值
    
    hdHarmoACurMax7Tm,//A相7次谐波电流日最大值发生时间
    
    hdHarmoACurMax8,  //A相8次谐波电流日最大值
    
    hdHarmoACurMax8Tm,//A相8次谐波电流日最大值发生时间
    
    hdHarmoACurMax9,  //A相9次谐波电流日最大值
    
    hdHarmoACurMax9Tm,//A相9次谐波电流日最大值发生时间
    
    hdHarmoACurMax10, //A相10次谐波电流日最大值
    
    hdHarmoACurMax10Tm,//A相10次谐波电流日最大值发生时间
    
    hdHarmoACurMax11,  //A相11次谐波电流日最大值
    
    hdHarmoACurMax11Tm,//A相11次谐波电流日最大值发生时间
    
    hdHarmoACurMax12,  //A相12次谐波电流日最大值
    
    hdHarmoACurMax12Tm,//A相12次谐波电流日最大值发生时间
    
    hdHarmoACurMax13,  //A相13次谐波电流日最大值
    
    hdHarmoACurMax13Tm,//A相13次谐波电流日最大值发生时间
    
    hdHarmoACurMax14,  //A相14次谐波电流日最大值
    
    hdHarmoACurMax14Tm,//A相14次谐波电流日最大值发生时间
    
    hdHarmoACurMax15,  //A相15次谐波电流日最大值
    
    hdHarmoACurMax15Tm,//A相15次谐波电流日最大值发生时间
    
    hdHarmoACurMax16,  //A相16次谐波电流日最大值
    
    hdHarmoACurMax16Tm,//A相16次谐波电流日最大值发生时间
    
    hdHarmoACurMax17,  //A相17次谐波电流日最大值
    
    hdHarmoACurMax17Tm,//A相17次谐波电流日最大值发生时间
    
    hdHarmoACurMax18,  //A相18次谐波电流日最大值
    
    hdHarmoACurMax18Tm,//A相18次谐波电流日最大值发生时间
    
    hdHarmoACurMax19,  //A相19次谐波电流日最大值
    
    hdHarmoACurMax19Tm,//A相19次谐波电流日最大值发生时间
    
    hdDistortionACurMax,//A相总谐波电流日最大值
    
    hdDistortionACurMaxTm,//A相总畸变电流日最大值发生时间
    
    hdHarmoBCurMax2,  //B相2次谐波电流日最大值
    
    hdHarmoBCurMax2Tm,//B相2次谐波电流日最大值发生时间
    
    hdHarmoBCurMax3,  //B相3次谐波电流日最大值
    
    hdHarmoBCurMax3Tm,//B相3次谐波电流日最大值发生时间
    
    hdHarmoBCurMax4,  //B相4次谐波电流日最大值
    
    hdHarmoBCurMax4Tm,//B相4次谐波电流日最大值发生时间
    
    hdHarmoBCurMax5,  //B相5次谐波电流日最大值
    
    hdHarmoBCurMax5Tm,//B相5次谐波电流日最大值发生时间
    
    hdHarmoBCurMax6,  //B相6次谐波电流日最大值
    
    hdHarmoBCurMax6Tm,//B相6次谐波电流日最大值发生时间
    
    hdHarmoBCurMax7,  //B相7次谐波电流日最大值
    
    hdHarmoBCurMax7Tm,//B相7次谐波电流日最大值发生时间
    
    hdHarmoBCurMax8,  //B相8次谐波电流日最大值
    
    hdHarmoBCurMax8Tm,//B相8次谐波电流日最大值发生时间
    
    hdHarmoBCurMax9,  //B相9次谐波电流日最大值
    
    hdHarmoBCurMax9Tm,//B相9次谐波电流日最大值发生时间
    
    hdHarmoBCurMax10,  //B相10次谐波电流日最大值
    
    hdHarmoBCurMax10Tm,//B相10次谐波电流日最大值发生时间
    
    hdHarmoBCurMax11,  //B相11次谐波电流日最大值
    
    hdHarmoBCurMax11Tm,//B相11次谐波电流日最大值发生时间
    
    hdHarmoBCurMax12,  //B相12次谐波电流日最大值
    
    hdHarmoBCurMax12Tm,//B相12次谐波电流日最大值发生时间
    
    hdHarmoBCurMax13,  //B相13次谐波电流日最大值
    
    hdHarmoBCurMax13Tm,//B相13次谐波电流日最大值发生时间
    
    hdHarmoBCurMax14,  //B相14次谐波电流日最大值
    
    hdHarmoBCurMax14Tm,//B相14次谐波电流日最大值发生时间
    
    hdHarmoBCurMax15,  //B相15次谐波电流日最大值
    
    hdHarmoBCurMax15Tm,//B相15次谐波电流日最大值发生时间
    
    hdHarmoBCurMax16,  //B相16次谐波电流日最大值
    
    hdHarmoBCurMax16Tm,//B相16次谐波电流日最大值发生时间
    
    hdHarmoBCurMax17,  //B相17次谐波电流日最大值
    
    hdHarmoBCurMax17Tm,//B相17次谐波电流日最大值发生时间
    
    hdHarmoBCurMax18,  //B相18次谐波电流日最大值
    
    hdHarmoBCurMax18Tm,//B相18次谐波电流日最大值发生时间
    
    hdHarmoBCurMax19,  //B相19次谐波电流日最大值
    
    hdHarmoBCurMax19Tm,//B相19次谐波电流日最大值发生时间
    
    hdDistortionBCurMax,//B相总畸变电流日最大值
    
    hdDistortionBCurMaxTm,//B相总畸变电流日最大值发生时间
    
    
    hdHarmoCCurMax2,  //C相2次谐波电流日最大值
    
    hdHarmoCCurMax2Tm,//C相2次谐波电流日最大值发生时间
    
    hdHarmoCCurMax3,  //C相3次谐波电流日最大值
    
    hdHarmoCCurMax3Tm,//C相3次谐波电流日最大值发生时间
    
    hdHarmoCCurMax4,  //C相4次谐波电流日最大值
    
    hdHarmoCCurMax4Tm,//C相4次谐波电流日最大值发生时间
    
    hdHarmoCCurMax5,  //C相5次谐波电流日最大值
    
    hdHarmoCCurMax5Tm,//C相5次谐波电流日最大值发生时间
    
    hdHarmoCCurMax6,  //C相6次谐波电流日最大值
    
    hdHarmoCCurMax6Tm,//C相6次谐波电流日最大值发生时间
    
    hdHarmoCCurMax7,  //C相7次谐波电流日最大值
    
    hdHarmoCCurMax7Tm,//C相7次谐波电流日最大值发生时间
    
    hdHarmoCCurMax8,  //C相8次谐波电流日最大值
    
    hdHarmoCCurMax8Tm,//C相8次谐波电流日最大值发生时间
    
    hdHarmoCCurMax9,  //C相9次谐波电流日最大值
    
    hdHarmoCCurMax9Tm,//C相9次谐波电流日最大值发生时间
    
    hdHarmoCCurMax10, //C相10次谐波电流日最大值
    
    hdHarmoCCurMax10Tm,//C相10次谐波电流日最大值发生时间
    
    hdHarmoCCurMax11,  //C相11次谐波电流日最大值
    
    hdHarmoCCurMax11Tm,//C相11次谐波电流日最大值发生时间
    
    hdHarmoCCurMax12,  //C相12次谐波电流日最大值
    
    hdHarmoCCurMax12Tm,//C相12次谐波电流日最大值发生时间
    
    hdHarmoCCurMax13,  //C相13次谐波电流日最大值
    
    hdHarmoCCurMax13Tm,//C相13次谐波电流日最大值发生时间
    
    hdHarmoCCurMax14,  //C相14次谐波电流日最大值
    
    hdHarmoCCurMax14Tm,//C相14次谐波电流日最大值发生时间
    
    hdHarmoCCurMax15,  //C相15次谐波电流日最大值
    
    hdHarmoCCurMax15Tm,//C相15次谐波电流日最大值发生时间
    
    hdHarmoCCurMax16,  //C相16次谐波电流日最大值
    
    hdHarmoCCurMax16Tm,//C相16次谐波电流日最大值发生时间
    
    hdHarmoCCurMax17,  //C相17次谐波电流日最大值
    
    hdHarmoCCurMax17Tm,//C相17次谐波电流日最大值发生时间
    
    hdHarmoCCurMax18,  //C相18次谐波电流日最大值
    
    hdHarmoCCurMax18Tm,//C相18次谐波电流日最大值发生时间
    
    hdHarmoCCurMax19,  //C相19次谐波电流日最大值
    
    hdHarmoCCurMax19Tm,//C相19次谐波电流日最大值发生时间
    
    hdDistortionCCurMax,//C相总畸变电流日最大值
    
    hdDistortionCCurMaxTm,//C相总畸变电流日最大值发生时间
    
}DAILYDATA_CHARMONIC;









typedef enum measure_curve_data
{
    cvBeginData,    //日期
    
    cvCurveDensity, //密度
    
    cvCurveCount,   //点数
    
    //曲线类型
    cvCurvePower, //功率曲线类型
    
    cvCurveVolt,  //电压曲线类型
    
    cvCurveCur,   //电流曲线类型
    
    cvCurvePowerFactor,//功率因素曲线
    
    cvCurveDireCurAnalog,//直流模拟量数据曲线
    
    /*chenbaiqing2014.2.13 增补*/
    cvCurveOilTemp,   //油温曲线
    cvCurveWindingTempA,//A相绕组温度曲线
    cvCurveWindingTempB,//B相绕组温度曲线
    cvCurveWindingTempC,//C相绕组温度曲线
    cvCurveLoadRate,//负载率曲线
    cvCurveVoltUnbRate,//电压不平衡旅曲线
    cvCurveCurUnbRate,//电流不平衡旅曲线
    
}MEASURE_CURVE_DATA;








//历史数据测量点日统计数据
typedef enum measure_day_sta
{
    
    hdDataTime_mds,//数据时标
    
    hdAVoltOverHHAccTm, //A相电压越上上限日/月累计时间
    
    hdAVoltDownLLAccTm, //A相电压越下下限日/月累计时间
    
    hdAVoltOverHiAccTm, //A相电压越上限日/月累计时间
    
    hdAVoltDownLoAccTm, //A相电压越下限日/月累计时间
    
    hdAVoltRegularAccTm,//A相电压合格日/月累计时间
    
    hdBVoltOverHHAccTm, //B相电压越上上限日/月累计时间
    
    hdBVoltDownLLAccTm, //B相电压越下下限日/月累计时间
    
    hdBVoltOverHiAccTm, //B相电压越上限日/月累计时间
    
    hdBVoltDownLoAccTm, //B相电压越下限日/月累计时间
    
    hdBVoltRegularAccTm,//B相电压合格日/月累计时间
    
    hdCVoltOverHHAccTm, //C相电压越上上限日/月累计时间
    
    hdCVoltDownLLAccTm, //C相电压越下下限日/月累计时间
    
    hdCVoltOverHiAccTm, //C相电压越上限日/月累计时间
    
    hdCVoltDownLoAccTm, //C相电压越下限日/月累计时间
    
    hdCVoltRegularAccTm,//C相电压合格日/月累计时间
    
    hdAVoltMax,  //A相电压最大值
    
    hdAVoltMaxTm,//A相电压最大值发生时间
    
    hdAVoltMin,  //A相电压最小值
    
    hdAVoltMinTm,//A相电压最小值发生时间
    
    hdBVoltMax,  //B相电压最大值
    
    hdBVoltMaxTm,//B相电压最大值发生时间
    
    hdBVoltMin,  //B相电压最小值
    
    hdBVoltMinTm,//B相电压最小值发生时间
    
    hdCVoltMax,  //C相电压最大值
    
    hdCVoltMaxTm,//C相电压最大值发生时间
    
    hdCVoltMin,  //C相电压最小值
    
    hdCVoltMinTm,//C相电压最小值发生时间
    
    hdAVoltAvg,  //A相平均电压
    
    hdBVoltAvg,  //B相平均电压
    
    hdCVoltAvg,  //C相平均电压
    
    hdAVoltOverHiRate, //A相电压越上限率
    
    hdAVoltDownLoRate, //A相电压越下限率
    
    hdAVoltRegularRate,//A相电压合格率
    
    hdBVoltOverHiRate, //B相电压越上限率
    
    hdBVoltDownLoRate, //B相电压越下限率
    
    hdBVoltRegularRate,//B相电压合格率
    
    hdCVoltOverHiRate, //C相电压越上限率
    
    hdCVoltDownLoRate, //C相电压越下限率
    
    hdCVoltRegularRate,//C相电压合格率
    
    hdCurUnbalOLmtAccTm, //电流不平衡度越限日/月累计时间
    
    hdVoltUnbalOLmtAccTm,//电压不平衡度越限日/月累计时间
    
    hdCurUnbalMax,       //电流不平衡最大值
    
    hdCurUnbalMaxTm,     //电流不平衡最大值发生时间
    
    hdVoltUnbalMax,  //电压不平衡最大值
    
    hdVoltUnbalMaxTm,//电压不平衡最大值发生时间
    
    hdACurOverHHAccTm,//A相电流越上上限累计时间
    
    hdACurOverHiAccTm,//A相电流越上限累计时间
    
    hdBCurOverHHAccTm,//B相电流越上上限累计时间
    
    hdBCurOverHiAccTm,//B相电流越上限累计时间
    
    hdCCurOverHHAccTm,//C相电流越上上限累计时间
    
    hdCCurOverHiAccTm,//C相电流越上限累计时间
    
    hdZeroCurOverHHAccTm,//零序电流越上限累计时间
    
    hdACurMax,  //A相电流最大值
    
    hdACurMaxTm,//A相电流最大值发生时间
    
    hdBCurMax,  //B相电流最大值
    
    hdBCurMaxTm,//B相电流最大值发生时间
    
    hdCCurMax,  //C相电流最大值
    
    hdCCurMaxTm,//C相电流最大值发生时间
    
    hdZeroCurMax,  //零序电流最大值
    
    hdZeroCurMaxTm,//零序电流最大值发生时间
    
    hdAPOverHHAccTm,//视在功率越上上限累计时间
    
    hdAPOverHiAccTm,//视在功率越上限累计时间
    
    hdPfSector1AccTm,//区段1累计时间（功率因数＜定值1）
    
    hdPfSector2AccTm,//区段2累计时间（定值1≤功率因数＜定值2）
    
    hdPfSector3AccTm,//区段3累计时间（功率因数≥定值2）
    
    hdAPMaxZ,  //三相总最大有功功率
    
    hdAPMaxZTm,//三相总最大有功功率发生时间
    
    hdAPMaxA,  //A相最大有功功率
    
    hdAPMaxATm,//A相最大有功功率发生时间
    
    hdAPMaxB,  //B相最大有功功率
    
    hdAPMaxBTm,//B相最大有功功率发生时间
    
    hdAPMaxC,  //C相最大有功功率
    
    hdAPMaxCTm,//C相最大有功功率发生时间
    
    hdAPZeroAccTmZ,//三相总有功功率为零时间
    
    hdAPZeroAccTmA,//A相有功功率为零时间
    
    hdAPZeroAccTmB,//B相有功功率为零时间
    
    hdAPZeroAccTmC,//C相有功功率为零时间
    
    
    /*chenbaiqing 2014.2.13 增补*/
    hdOverloadTmA,//日冻结A相过载日累计时间
    hdOverloadTmB,//日冻结B相过载日累计时间
    hdOverloadTmC,//日冻结C相过载日累计时间
    
    hdCuAPValueZ,  //日冻结铜损有功总电能示值
	hdFeAPValueZ, //日冻结铁损有功总电能示值
    
}MEASURE_DAY_STA;


//历史数据测量点月统计数据
typedef enum measure_month_sta
{
    
    hmDataTime_mms,    //数据时标
    
    hmAVoltOverHHAccTm,//A相电压越上上限日/月累计时间
    
    hmAVoltDownLLAccTm,//A相电压越下下限日/月累计时间
    
    hmAVoltOverHiAccTm,//A相电压越上限日/月累计时间
    
    hmAVoltDownLoAccTm,//A相电压越下限日/月累计时间
    
    hmAVoltRegularAccTm,//A相电压合格日/月累计时间
    
    hmBVoltOverHHAccTm, //B相电压越上上限日/月累计时间
    
    hmBVoltDownLLAccTm, //B相电压越下下限日/月累计时间
    
    hmBVoltOverHiAccTm, //B相电压越上限日/月累计时间
    
    hmBVoltDownLoAccTm, //B相电压越下限日/月累计时间
    
    hmBVoltRegularAccTm,//B相电压合格日/月累计时间
    
    hmCVoltOverHHAccTm, //C相电压越上上限日/月累计时间
    
    hmCVoltDownLLAccTm, //C相电压越下下限日/月累计时间
    
    hmCVoltOverHiAccTm, //C相电压越上限日/月累计时间
    
    hmCVoltDownLoAccTm, //C相电压越下限日/月累计时间
    
    hmCVoltRegularAccTm,//C相电压合格日/月累计时间
    
    hmAVoltMax,  //A相电压最大值
    
    hmAVoltMaxTm,//A相电压最大值发生时间
    
    hmAVoltMin,  //A相电压最小值
    
    hmAVoltMinTm,//A相电压最小值发生时间
    
    hmBVoltMax,  //B相电压最大值
    
    hmBVoltMaxTm,//B相电压最大值发生时间
    
    hmBVoltMin,  //B相电压最小值
    
    hmBVoltMinTm,//B相电压最小值发生时间
    
    hmCVoltMax,  //C相电压最大值
    
    hmCVoltMaxTm,//C相电压最大值发生时间
    
    hmCVoltMin,  //C相电压最小值
    
    hmCVoltMinTm,//C相电压最小值发生时间
    
    hmAVoltAvg,  //A相平均电压
    
    hmBVoltAvg,  //B相平均电压
    
    hmCVoltAvg,  //C相平均电压
    
    hmAVoltOverHiRate, //A相电压越上限率
    
    hmAVoltDownLoRate, //A相电压越下限率
    
    hmAVoltRegularRate,//A相电压合格率
    
    hmBVoltOverHiRate, //B相电压越上限率
    
    hmBVoltDownLoRate, //B相电压越下限率
    
    hmBVoltRegularRate,//B相电压合格率
    
    hmCVoltOverHiRate, //C相电压越上限率
    
    hmCVoltDownLoRate, //C相电压越下限率
    
    hmCVoltRegularRate,//C相电压合格率
    
    hmCurUnbalOLmtAccTm, //电流不平衡度越限日/月累计时间
    
    hmVoltUnbalOLmtAccTm,//电压不平衡度越限日/月累计时间
    
    hmCurUnbalMax,       //电流不平衡最大值
    
    hmCurUnbalMaxTm,     //电流不平衡最大值发生时间
    
    hmVoltUnbalMax,      //电压不平衡最大值
    
    hmVoltUnbalMaxTm,    //电压不平衡最大值发生时间
    
    hmACurOverHHAccTm,//A相电流越上上限累计时间
    
    hmACurOverHiAccTm,//A相电流越上限累计时间
    
    hmBCurOverHHAccTm,//B相电流越上上限累计时间
    
    hmBCurOverHiAccTm,//B相电流越上限累计时间
    
    hmCCurOverHHAccTm,//C相电流越上上限累计时间
    
    hmCCurOverHiAccTm,//C相电流越上限累计时间
    
    hmZeroCurOverHHAccTm,//零序电流越上限累计时间
    
    hmACurMax,  //A相电流最大值
    
    hmACurMaxTm,//A相电流最大值发生时间
    
    hmBCurMax,  //B相电流最大值
    
    hmBCurMaxTm,//B相电流最大值发生时间
    
    hmCCurMax,  //C相电流最大值
    
    hmCCurMaxTm,//C相电流最大值发生时间
    
    hmZeroCurMax,  //零序电流最大值
    
    hmZeroCurMaxTm,//零序电流最大值发生时间
    
    hmAPOverHHAccTm,//视在功率越上上限累计时间
    
    hmAPOverHiAccTm,//视在功率越上限累计时间
    
    hmPfSector1AccTm,//区段1累计时间（功率因数＜定值1）
    
    hmPfSector2AccTm,//区段2累计时间（定值1≤功率因数＜定值2）
    
    hmPfSector3AccTm,//区段3累计时间（功率因数≥定值2）
    
    hmAPMaxZ,  //三相总最大有功功率
    
    hmAPMaxZTm,//三相总最大有功功率发生时间
    
    hmAPMaxA,  //A相最大有功功率
    
    hmAPMaxATm,//A相最大有功功率发生时间
    
    hmAPMaxB,  //B相最大有功功率
    
    hmAPMaxBTm,//B相最大有功功率发生时间
    
    hmAPMaxC,  //C相最大有功功率
    
    hmAPMaxCTm,//C相最大有功功率发生时间
    
    hmAPZeroAccTmZ,//三相总有功功率为零时间
    
    hmAPZeroAccTmA,//A相有功功率为零时间
    
    hmAPZeroAccTmB,//B相有功功率为零时间
    
    hmAPZeroAccTmC,//C相有功功率为零时间
    
    /*chenbaiqing 2014.2.13 增补*/
    hmOverloadTmA,//月冻结A相过载日累计时间
    hmOverloadTmB,//月冻结B相过载日累计时间
    hmOverloadTmC,//月冻结C相过载日累计时间
    
    /*chenbaiqing2.21 新增*/
	hmCuAPValueZ,  //月冻结铜损有功总电能示值
	hmFeAPValueZ,  //月冻结铁损有功总电能示值
    
    
}MEASURE_MONTH_STA;

//测量点日电能示值数据
typedef enum measure_day_powervalue
{
    
    //数据时标
    hdDataTime_mdp=0,
    
    hdPosAEValueZ, //正向有功总电能示值
    
    hdPosAEValue1, //正向有功费率1电能示值
    
    hdPosAEValue2, //正向有功费率2电能示值
    
    hdPosAEValue3, //正向有功费率3电能示值
    
    hdPosAEValue4, //正向有功费率4电能示值
    
    
    
    hdPosREValueZ,//正向无功总电能示值
    
    hdPosREValue1,//正向无功费率1电能示值
    
    hdPosREValue2,//正向无功费率2电能示值
    
    hdPosREValue3,//正向无功费率3电能示值
    
    hdPosREValue4,//正向无功费率4电能示值
    
    hdFirstREValueZ,//一象限无功总电能示值
    
    hdFirstREValue1,//一象限无功费率1电能示值
    
    hdFirstREValue2,//一象限无功费率2电能示值
    
    hdFirstREValue3,//一象限无功费率3电能示值
    
    hdFirstREValue4,//一象限无功费率4电能示值
    
    
    hdFourREValueZ,//四象限无功总电能示值
    
    hdFourREValue1,//四象限无功费率1电能示值
    
    hdFourREValue2,//四象限无功费率2电能示值
    
    hdFourREValue3,//四象限无功费率3电能示值
    
    hdFourREValue4,//四象限无功费率4电能示值
    
    
    
    
    hdNegAEValueZ,//反向有功总电能示值
    
    hdNegAEValue1,//反向有功费率1电能示值
    
    hdNegAEValue2,//反向有功费率2电能示值
    
    hdNegAEValue3,//反向有功费率3电能示值
    
    hdNegAEValue4,//反向有功费率4电能示值
    
    
    hdNegREValueZ,//反向无功总电能示值
    
    hdNegREValue1,//反向无功费率1电能示值
    
    hdNegREValue2,//反向无功费率2电能示值
    
    hdNegREValue3,//反向无功费率3电能示值
    
    hdNegREValue4,//反向无功费率4电能示值
    
    
    hdSecondREValueZ,//二象限无功总电能示值
    
    hdSecondREValue1,//二象限无功费率1电能示值
    
    hdSecondREValue2,//二象限无功费率2电能示值
    
    hdSecondREValue3,//二象限无功费率3电能示值
    
    hdSecondREValue4,//二象限无功费率4电能示值
    
    
    hdThirdREValueZ,//三象限无功总电能示值
    
    hdThirdREValue1,//三象限无功费率1电能示值
    
    hdThirdREValue2,//三象限无功费率2电能示值
    
    hdThirdREValue3,//三象限无功费率3电能示值
    
    hdThirdREValue4,//三象限无功费率4电能示值
    
    hdPosREValueZG,     //正向无功（组合无功1）总电能示值
    
    hdPosREGroupValueG1,//费率1正向无功（组合无功1）电能示值
    
    hdPosREGroupValueG2,//费率2正向无功（组合无功1）电能示值
    
    hdPosREGroupValueG3,//费率3正向无功（组合无功1）电能示值
    
    hdPosREGroupValueG4,//费率4正向无功（组合无功1）电能示值
    
    
    hdNegREValueZG,//反向无功（组合无功1）总电能示值
    
    hdNegREValueG1,//费率1反向无功（组合无功1）电能示值
    
    hdNegREValueG2,//费率2反向无功（组合无功1）电能示值
    
    hdNegREValueG3,//费率3反向无功（组合无功1）电能示值
    
    hdNegREValueG4,//费率4反向无功（组合无功1）电能示值
    
    hdPosAEPowerValueZ, //日正向有功总电能量
    
    hdPosAEPowerValue1, //日费率1正向有功电能量
    
    hdPosAEPowerValue2, //日费率2正向有功电能量
    
    hdPosAEPowerValue3, //日费率3正向有功电能量
    
    hdPosAEPowerValue4, //日费率4正向有功电能量
    
}MEASURE_DAY_POWERVALUE;


//测量点月电能示值数据
typedef enum measure_month_powervalue
{
    
    //数据时标
    hmDataTime_mmp=0,
    
    hmPosAEValueZ, //正向有功总电能示值
    
    hmPosAEValue1, //正向有功费率1电能示值
    
    hmPosAEValue2, //正向有功费率2电能示值
    
    hmPosAEValue3, //正向有功费率3电能示值
    
    hmPosAEValue4, //正向有功费率4电能示值
    
    
    
    hmPosREValueZ,//正向无功总电能示值
    
    hmPosREValue1,//正向无功费率1电能示值
    
    hmPosREValue2,//正向无功费率2电能示值
    
    hmPosREValue3,//正向无功费率3电能示值
    
    hmPosREValue4,//正向无功费率4电能示值
    
    hmFirstREValueZ,//一象限无功总电能示值
    
    hmFirstREValue1,//一象限无功费率1电能示值
    
    hmFirstREValue2,//一象限无功费率2电能示值
    
    hmFirstREValue3,//一象限无功费率3电能示值
    
    hmFirstREValue4,//一象限无功费率4电能示值
    
    
    hmFourREValueZ,//四象限无功总电能示值
    
    hmFourREValue1,//四象限无功费率1电能示值
    
    hmFourREValue2,//四象限无功费率2电能示值
    
    hmFourREValue3,//四象限无功费率3电能示值
    
    hmFourREValue4,//四象限无功费率4电能示值
    
    
    hmNegAEValueZ,//反向有功总电能示值
    
    hmNegAEValue1,//反向有功费率1电能示值
    
    hmNegAEValue2,//反向有功费率2电能示值
    
    hmNegAEValue3,//反向有功费率3电能示值
    
    hmNegAEValue4,//反向有功费率4电能示值
    
    
    hmNegREValueZ,//反向无功总电能示值
    
    hmNegREValue1,//反向无功费率1电能示值
    
    hmNegREValue2,//反向无功费率2电能示值
    
    hmNegREValue3,//反向无功费率3电能示值
    
    hmNegREValue4,//反向无功费率4电能示值
    
    
    hmSecondREValueZ,//二象限无功总电能示值
    
    hmSecondREValue1,//二象限无功费率1电能示值
    
    hmSecondREValue2,//二象限无功费率2电能示值
    
    hmSecondREValue3,//二象限无功费率3电能示值
    
    hmSecondREValue4,//二象限无功费率4电能示值
    
    
    hmThirdREValueZ,//三象限无功总电能示值
    
    hmThirdREValue1,//三象限无功费率1电能示值
    
    hmThirdREValue2,//三象限无功费率2电能示值
    
    hmThirdREValue3,//三象限无功费率3电能示值
    
    hmThirdREValue4,//三象限无功费率4电能示值
    
    hmPosREValueZG,     //正向无功（组合无功1）总电能示值
    
    hmPosREGroupValueG1,//费率1正向无功（组合无功1）电能示值
    
    hmPosREGroupValueG2,//费率2正向无功（组合无功1）电能示值
    
    hmPosREGroupValueG3,//费率3正向无功（组合无功1）电能示值
    
    hmPosREGroupValueG4,//费率4正向无功（组合无功1）电能示值
    
    
    hmNegREValueZG,//反向无功（组合无功1）总电能示值
    
    hmNegREValueG1,//费率1反向无功（组合无功1）电能示值
    
    hmNegREValueG2,//费率2反向无功（组合无功1）电能示值
    
    hmNegREValueG3,//费率3反向无功（组合无功1）电能示值
    
    hmNegREValueG4,//费率4反向无功（组合无功1）电能示值
    
    hmPosAEPowerValueZ, //正向有功总电能量
    
    hmPosAEPowerValue1, //费率1正向有功电能量
    
    hmPosAEPowerValue2, //费率2正向有功电能量
    
    hmPosAEPowerValue3, //费率3正向有功电能量
    
    hmPosAEPowerValue4, //费率4正向有功电能量
    
}MEASURE_MONTH_POWERVALUE;


//测量点日需量数据
typedef enum history_day_powerneeds
{
    
    hdDataTime_hdp,   //数据时标
    
    hdPosADMaxZ,//正向有功总最大需量
    
    hdPosADMax1,//费率1正向有功最大需量
    
    hdPosADMax2,//费率2正向有功最大需量
    
    hdPosADMax3,//费率3正向有功最大需量
    
    hdPosADMax4,//费率4正向有功最大需量
    
    
    hdPosADMaxZTm,//正向有功总最大需量发生时间
    
    hdPosADMax1Tm,//费率1正向有功最大需量发生时间
    
    hdPosADMax2Tm,//费率2正向有功最大需量发生时间
    
    hdPosADMax3Tm,//费率3正向有功最大需量发生时间
    
    hdPosADMax4Tm,//费率4正向有功最大需量发生时间
    
    
    hdPosRDMaxZ,//正向无功总最大需量
    
    hdPosRDMax1,//费率1正向无功最大需量
    
    hdPosRDMax2,//费率2正向无功最大需量
    
    hdPosRDMax3,//费率3正向无功最大需量
    
    hdPosRDMax4,//费率4正向无功最大需量
    
    
    hdPosRDMaxZTm,//正向无功总最大需量发生时间
    
    hdPosRDMax1Tm,//费率1正向无功最大需量发生时间
    
    hdPosRDMax2Tm,//费率2正向无功最大需量发生时间
    
    hdPosRDMax3Tm,//费率3正向无功最大需量发生时间
    
    hdPosRDMax4Tm,//费率4正向无功最大需量发生时间
    
    hdNegADMaxZ,//反向有功总最大需量
    
    hdNegADMax1,//费率1反向有功最大需量
    
    hdNegADMax2,//费率2反向有功最大需量
    
    hdNegADMax3,//费率3反向有功最大需量
    
    hdNegADMax4,//费率4反向有功最大需量
    
    hdNegADMaxZTm,//反向有功总最大需量发生时间
    
    hdNegADMax1Tm,//费率1反向有功最大需量发生时间
    
    hdNegADMax2Tm,//费率2反向有功最大需量发生时间
    
    hdNegADMax3Tm,//费率3反向有功最大需量发生时间
    
    hdNegADMax4Tm,//费率4反向有功最大需量发生时间
    
    
    hdNegRDMaxZ,//反向无功总最大需量
    
    hdNegRDMax1,//费率1反向无功最大需量
    
    hdNegRDMax2,//费率2反向无功最大需量
    
    hdNegRDMax3,//费率3反向无功最大需量
    
    hdNegRDMax4,//费率4反向无功最大需量
    
    
    hdNegRDMaxZTm,//反向无功总最大需量发生时间
    
    hdNegRDMax1Tm,//费率1反向无功最大需量发生时间
    
    hdNegRDMax2Tm,//费率2反向无功最大需量发生时间
    
    hdNegRDMax3Tm,//费率3反向无功最大需量发生时间
    
    hdNegRDMax4Tm,//费率3反向无功最大需量发生时间
    
    
    hdADMaxZ,  //三相总有功最大需量
    
    hdADMaxZTm,//三相总有功最大需量发生时间
    
    hdADMaxA,  //A相有功最大需量
    
    hdADMaxATm,//A相有功最大需量发生时间
    
    hdADMaxB,  //B相有功最大需量
    
    hdADMaxBTm,//B相有功最大需量发生时间
    
    hdADMaxC,  //C相有功最大需量
    
    hdADMaxCTm,//C相有功最大需量发生时间,
    
}HISTORY_DAY_POWERNEEDS;


//测量点月需量数据
typedef enum history_month_powerneeds
{
    
    hmDataTime_hmp,   //数据时标
    
    hmPosADMaxZ,//正向有功总最大需量
    
    hmPosADMax1,//费率1正向有功最大需量
    
    hmPosADMax2,//费率2正向有功最大需量
    
    hmPosADMax3,//费率3正向有功最大需量
    
    hmPosADMax4, //费率4正向有功最大需量
    
    hmPosADMaxZTm,//正向有功总最大需量发生时间
    
    hmPosADMax1Tm,//费率1正向有功最大需量发生时间
    
    hmPosADMax2Tm,//费率2正向有功最大需量发生时间
    
    hmPosADMax3Tm,//费率3正向有功最大需量发生时间
    
    hmPosADMax4Tm,//费率4正向有功最大需量发生时间
    
    hmPosRDMaxZ,//正向无功总最大需量
    
    hmPosRDMax1,//费率1正向无功最大需量
    
    hmPosRDMax2,//费率2正向无功最大需量
    
    hmPosRDMax3,//费率3正向无功最大需量
    
    hmPosRDMax4,//费率4正向无功最大需量
    
    hmPosRDMaxZTm,//正向无功总最大需量发生时间
    
    hmPosRDMax1Tm,//费率1正向无功最大需量发生时间
    
    hmPosRDMax2Tm,//费率2正向无功最大需量发生时间
    
    hmPosRDMax3Tm,//费率3正向无功最大需量发生时间
    
    hmPosRDMax4Tm,//费率4正向无功最大需量发生时间
    
    hmNegADMaxZ,//反向有功总最大需量
    
    hmNegADMax1,//费率1反向有功最大需量
    
    hmNegADMax2,//费率2反向有功最大需量
    
    hmNegADMax3,//费率3反向有功最大需量
    
    hmNegADMax4,//费率4反向有功最大需量
    
    hmNegADMaxZTm,//反向有功总最大需量发生时间
    
    hmNegADMax1Tm,//费率1反向有功最大需量发生时间
    
    hmNegADMax2Tm,//费率2反向有功最大需量发生时间
    
    hmNegADMax3Tm,//费率3反向有功最大需量发生时间
    
    hmNegADMax4Tm,//费率4反向有功最大需量发生时间
    
    
    hmNegRDMaxZ,//反向无功总最大需量
    
    hmNegRDMax1,//费率1反向无功最大需量
    
    hmNegRDMax2,//费率2反向无功最大需量
    
    hmNegRDMax3,//费率3反向无功最大需量
    
    hmNegRDMax4,//费率4反向无功最大需量
    
    
    hmNegRDMaxZTm,//反向无功总最大需量发生时间
    
    hmNegRDMax1Tm,//费率1反向无功最大需量发生时间
    
    hmNegRDMax2Tm,//费率2反向无功最大需量发生时间
    
    hmNegRDMax3Tm,//费率3反向无功最大需量发生时间
    
    hmNegRDMax4Tm,//费率3反向无功最大需量发生时间
    
    hmADMaxZ,  //三相总有功最大需量
    
    hmADMaxZTm,//三相总有功最大需量发生时间
    
    hmADMaxA,  //A相有功最大需量
    
    hmADMaxATm,//A相有功最大需量发生时间
    
    hmADMaxB,  //B相有功最大需量
    
    hmADMaxBTm,//B相有功最大需量发生时间
    
    hmADMaxC,  //C相有功最大需量
    
    hmADMaxCTm,//C相有功最大需量发生时间,
    
}HISTORY_MONTH_POWERNEEDS;

//终端日统计数据
enum terminal_day_sta {
    //数据时标
    hdDataTime_tds = 0,
    
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
    hmDataTime_tms = 0,
    
    //终端月供电时间
    hmPowerOnAccTm,
    
    //终端月复位次数
    hmResetAccCnt,
    
    //终端与主站月通信流量
    hmCommFlow
}TERMINAL_MONTH_STA;


enum eventlist{
    event
}EVENT;


//通讯参数
typedef enum parameter_data_comm
{
    pmRtsDelayTm,  //终端数传机延时时间RTS
    
    pmSendDelayTm, //终端作为启动站允许发送传输延时时间
    
    pmRecvDelayTm, //终端等待从动站响应的超时时间  bin_2
    
    pmRecvRetryTm, //终端等待从动站相应的重发次数  bin_2
    
    pmNeedConfirm1,//1类数据自动上报需要确认
    
    pmNeedConfirm2,//2类数据自动上报需要确认
    
    pmNeedConfirm3,//3类数据自动上报需要确认
    
    pmHeartPeriod, //心跳周期
    
    
    pmMasterPrimeIP,    //主站主用IP
    
    pmMasterPrimePort,  //主站主用端口
    
    pmMasterStandbyIP,  //主站备用IP
    
    pmMasterStandbyPort,//主站备用端口
    
    pmMasterAPN,        //主站APN
    
    pmIP,        //终端IP地址
    
    pmSubnetMask,//终端子网掩码
    
    pmGateWay,   //终端网关
    
    pmProxyType, //终端代理类型
    
    pmProxyAddr, //终端代理服务器地址
    
    pmProxyPort, //终端代理服务器端口
    
    pmProxyConnType,   //终端代理服务器连接方式
    
    pmProxyUserNameLen,//终端代理服务器用户名长度
    
    pmProxyUserName,   //终端代理服务器用户名
    
    pmProxyPassWordLen,//终端代理服务器密码长度
    
    pmProxyPassWord,   //终端代理服务器密码
    
    pmListenPort,      //终端侦听端口
    
    pmVPNUserName,     //虚拟专网用户名
    
    pmVPNPassWord,     //虚拟专网密码
    
    
    //*********************************
    pmWifiSsid,        //Wifi ssid名称
    
    pmWifiPsw,         //Wifi 密码
    
    pmUserName,        //用户名
    
    pmPsw,             //密码
    
}PARAMETER_DATA_COMM;

//测量点参数
typedef enum parameter_data_mtr
{
    
    pmPTRatio,     //电压互感器倍率
    
    pmCTRatio,     //电流互感器倍率
    
    pmRatedVoltage,//额定电压
    
    pmRatedCurrent,//额定电流
    
    pmRatedLoad,   //额定负荷
    
    pmPowerConnWay,//电源接线方式
    
    
    
    pmSingleMeterConnPhase,//单相表接线相
    
    pmVoltRegularHiLmt,    //电压合格上限
    
    pmVoltRegularLoLmt,    //电压合格下限
    
    pmSeverVoltLmt,        //电压断相门限
    
    pmVoltHHLmt,           //电压上上限（过压门限）
    
    pmVoltHHLmtDuration,   //过压越限持续时间
    
    pmVoltOverRecoverFactor,//过压越限恢复系数
    
    pmVoltLLLmt,            //电压下下限（欠压门限）
    
    pmVoltLLLmtDuration,    //欠压越限持续时间
    
    pmVoltUnderRecoverFactor,//欠压越限恢复系数
    
    
    pmCurHHLmt,        //相电流上上限（过流门限）
    
    pmCurHHLmtDuration,//过流越限持续时间
    
    pmCurHHRecoverFactor,//过流越限恢复系数
    
    pmCurHiLmt,          //相电流上限（额定电流门限）
    
    pmCurHiLmtDuration,  //额定电流越限持续时间
    
    pmCurHiRecoverFactor,//额定电流越限恢复系数
    
    pmZeroCurHiLmt,      //零序电流上限
    
    pmZeroCurHiLmtDuration,  //零序电流上限越限持续时间
    
    pmZeroCurHiRecoverFactor,//零序电流上限越限恢复系数
    
    pmAPHHLmt,          //视在功率上上限
    
    pmAPHHDuration,     //视在功率上上限越限持续时间
    
    pmAPHHRecoverFactor,//视在功率上上限越限恢复系数
    
    pmAPHiLmt,     //视在功率上限
    
    pmAPHiDuration,//视在功率上限越限持续时间
    
    pmAPHiRecoverFactor,//视在功率上限越限恢复系数
    
    pmUnbalVoltLmt,     //三相电压不平衡限值
    
    pmUnbalVoltDuration,//越限持续时间
    
    pmUnbalVoltRecoverFactor,//越限恢复系数
    
    pmUnbalCurLmt,           //三相电流不平衡限值
    
    pmUnbalCurDuration,      //越限持续时间
    
    pmUnbalCurRecoverFactor, //越限恢复系数
    
    pmLostVoltTmLmt,         //连续失压时间限值
    
    
    pmRa,//A相电阻RA
    
    pmXa,//A相电抗XA
    
    pmGa,//A相电导GA
    
    pmBa,//A相电纳BA
    
    pmRb,//B相电阻RB
    
    pmXb,//B相电抗XB
    
    pmGb,//B相电导GB
    
    pmBb,//B相电纳BB
    
    
    pmRc,//C相电阻RC
    
    pmXc,//C相电抗XC
    
    pmGc,//C相电导GC
    
    pmBc,//C相电纳BC
    
    pmPfLmt1,//功率因数分段限值1
    
    pmPfLmt2,//功率因数分段限值2
    
}PARAMETER_DATA_MTR;

//终端参数
enum parameter_data_terminal
{
    pmEventEffecFlag,//事件记录有效标志位
    
    pmEventImptFlag,//事件重要性等级标志位
    
    pmStateVariableInter,//状态量接入标志位（对应1～8路状态量）
    
    pmStateVariableAttr,//状态量属性标志位（对应1～8路状态量）
    
    pmCommFlowLmt,//月通信流量门限
    
    pmVoltHarmoRateHiLmtZ,//总畸变电压含有率上限
    
    pmVoltHarmoRateHiLmtOdd,//奇次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmtEven,//偶次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt2,//2次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt4,//4次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt6,//6次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt8,//8次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt10,//10次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt12,//12次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt14,//14次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt16,//16次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt18,//18次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt3,//3次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt5,//5次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt7,//7次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt9,//9次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt11,//11次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt13,//13次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt15,//15次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt17,//17次谐波电压含有率上限
    
    pmVoltHarmoRateHiLmt19,//19次谐波电压含有率上限
    
    pmCurHarmoEffecHiLmtZ,//总畸变电流有效值上限
    
    pmCurHarmoEffecHiLmt2,//2次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt4,//4次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt6,//6次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt8,//8次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt10,//10次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt12,//12次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt14,//14次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt16,//16次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt18,//18次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt3,//3次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt5,//5次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt7,//7次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt9,//9次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt11,//11次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt13,//13次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt15,//15次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt17,//17次谐波电流有效值上限
    
    pmCurHarmoEffecHiLmt19,//19次谐波电流有效值上限
    
    pmDCAnalogInter,//直流模拟量接入参数
    
    pmLongitude,//经度
    
    pmLatitude,//纬度
    
    pmEpId,//设备编号
    
    pmEpType,//设备类型
    
    pmTerminalRatedVoltage,//额定电压
    
    pmTerminalRatedCurrent,//额定电流
    
    pmRatedCapital,//额定容量
    
    pmFullLoadLoss,//满载损耗
    
    pmNoLoadLoss,//空载损耗
    
    pmImpedanceVoltage,//阻抗电压
    
    pmRatedFrequency,//额定频率
    
    pmManufactureDate,//制造日期
    
    pmManufactureNo,//出厂编号
    
    pmConnGroups,//连接组别
    
    pmPhaseNum,//相数
    
    pmInsulationGrade,//绝热耐热等级
    
    pmTempratureRise,//温升
    
    pmCoolingWay,//冷却方式
    
    pmInsulationLevel,//绝缘水平
    
    pmTerminalCTRatio,//CT变比
    
    
}PARAMETER_DATA_TERMINAL;

//测量点通信参数
enum parameter_data_mtr_comm
{
    pmMtrNo,//测量点号
    
    pmMtrDeviceNo,//测量点装置序号
    
    pmCommSpeed,//通信速率
    
    pmCommPort,//通信端口号
    
    pmCommPrtlType,//通信协议类型
    
    pmCommAddr,//通信地址
    
    pmCommPassWord,//通信密码
    
    pmFeeNum,//电能费率个数
    
    pmIntegerNum,//有功电能示值整数位数
    
    pmDecimalNum,//有功电能示值小数位数
    
}PARAMETER_DATA_MTR_COMM;

#endif




