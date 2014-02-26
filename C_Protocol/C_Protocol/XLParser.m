//
//  XLParser.m
//  C_Protocol
//
//  Created by JY on 14-1-14.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import "XLParser.h"
#import "XLDataTypeDic.h"
#import "XLDataItem.h"


@interface XLParser()

@end


@implementation XLParser

Byte *bytes;
NSInteger len;
int _offset;
int begin;
int end;

NSInteger _type;
int _identifier;

int curveIdentifier;
bool isCurve = NO;


NSMutableDictionary *_subdic;
NSMutableArray *array;


-(void)initWithNSData:(NSData*)data{
    
    end = 0;
    begin = 0;
    curveIdentifier = 0;
    isCurve = NO;
    
    NSMutableDictionary *dic = [NSMutableDictionary dictionary];
 
    bytes = (Byte*)[data bytes];
    len = [data length];
    
//    for(int i =0;i<len;i++){
//        NSLog(@"%02x",bytes[i]);
//    }
    
    _offset = 0;
    
    array = [NSMutableArray array];
    while (_offset<len) {
        NSMutableDictionary *subdic = [NSMutableDictionary dictionary];
        
        NSString *pStr = [NSString stringWithFormat:@"测量点%d",bytes[_offset++]];
        NSString *fStr = [NSString stringWithFormat:@"F项%d",bytes[_offset++]];
        
        _type = bytes[_offset];_offset++;
        
        NSString *key =  [NSString stringWithFormat:@"%@ %@",pStr,fStr];
        [dic setObject:subdic forKey:key];
        
        _subdic = subdic;
        
        NSInteger sublen = *(unsigned short*)(bytes + _offset);_offset += 2;
        begin = _offset;
        
        while (sublen>(end - begin)) {
            
            _identifier = *(unsigned short*)(bytes + _offset); _offset += 2;
            [self setKeyForDic];
            end = _offset;
        }
    }
    
    [_subdic setObject:array forKey:@"key"];
    NSLog(@"字典完成");
    [[NSNotificationCenter defaultCenter] postNotificationName:@"test"
                                                        object:Nil
                                                      userInfo:dic];
}

COMPLEX_ITEM dtype;
-(void)setKeyForDic{
    
//    int  dtype=0;
    
    switch (_type) {
        case 0:{
            dtype = terminal_day_sta[_identifier];
        }
            break;
        case 1:{
            dtype = terminal_month_sta[_identifier];
        }
            break;
        case 2:{
            dtype = measure_day_powervalue[_identifier];
        }
            break;
        case 3:{
            dtype = measure_month_powervalue[_identifier];
        }
            break;
        case 4:{
            dtype = history_day_powerneeds[_identifier];
        }
            break;
        case 5:{
            dtype = history_month_powerneeds[_identifier];
        }
            break;
        case 6:{
            dtype = measure_day_sta[_identifier];
        }
            break;
        case 7:{
            dtype = measure_month_sta[_identifier];
        }
            break;
        case 8:{
            dtype = measure_curve_data[_identifier];
            isCurve = YES;
            curveIdentifier++;
        }
            break;
        case 9:{
            dtype = daily_data_charmonic[_identifier];
        }
            break;
        case 10:{
            dtype = daily_data_vharmonic[_identifier];
        }
            break;
        case 11:{
            dtype = dcanalog_day_data[_identifier];
        }
            break;
        case 12:{
            dtype = dcanalog_month_data[_identifier];
        }
            break;
        case 13:{
            dtype = terminal_rt_basic_sta[_identifier];
        }
            break;
        case 14:{
            dtype = mtr_rt_basic_sta[_identifier];
        }
            break;
        case 15:{
            dtype = rt_power_value_sta[_identifier];
        }
            break;
        case 16:{
            dtype = rt_power_needs_sta[_identifier];
        }
            break;
        case 17:{
            dtype = rt_dc_analog[_identifier];
        }
            break;
        case 18:{
            dtype = mtr_rt_harmonic[_identifier];
        }
            break;
        case 19:{
            dtype = eventlist[_identifier];
        }
            break;
            
        case 20:{
            dtype  = parameter_data_comm[_identifier];

        }
            break;
        case 21:{
            dtype  = parameter_data_mtr[_identifier];
        }
            break;
        case 22:{
            dtype  = parameter_data_terminal[_identifier];
        }
            break;
        case 23:{
            dtype  = parameter_data_mtr_comm[_identifier];
        }
            break;
        default:
            break;
    }
    
//    NSLog(@"-----------执行方法前offset:%d",_offset);
    
    NSString *method = [NSString stringWithFormat:@"parse%d",dtype.datatype + 1];
    SEL selecter = NSSelectorFromString(method);
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored  "-Warc-performSelector-leaks"
    [self performSelector:selecter withObject:nil];
#pragma clang diagnostic pop
}

//
-(void)parse2{
    NSInteger mi = *(XL_SINT8*)(bytes+_offset); _offset+=1;
    NSInteger dishu = *(XL_UINT16*)(bytes+_offset); _offset+=2;
    
    NSString *results = [NSString stringWithFormat:@"%.3f",pow(dishu, mi)];
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
//    [_subdic setObject:results
//                forKey:key];
}


//2字节 1位小数 带符号
-(void)parse5{
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/10.0;
    
    NSString *results = [NSString stringWithFormat:@"%.1f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
//    if (isCurve) {
//        [_subdic setObject:results
//                    forKey:[NSString stringWithFormat:@"%d",curveIdentifier]];
//    }else{
//    [_subdic setObject:results
//                forKey:key];
//    }
}

//2字节 2位小数 带符号
-(void)parse6{
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/100.0;
    
    NSString *results = [NSString stringWithFormat:@"%.2f",result];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
//    [_subdic setObject:results
//                forKey:key];
    
}

//2字节 1位小数
-(void)parse7{
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/10.0;
    
    NSString *results = [NSString stringWithFormat:@"%.1f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
    
//    if (isCurve) {
//        [_subdic setObject:results
//                    forKey:[NSString stringWithFormat:@"%d",curveIdentifier]];
//    }else{
//    [_subdic setObject:results
//                forKey:key];
//    }
}

//3字节 4位小数

-(void)parse9{
    
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/10000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.4f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
    
//    if (isCurve) {
//        [_subdic setObject:results
//                    forKey:[NSString stringWithFormat:@"%d",curveIdentifier]];
//    }else {
//        [_subdic setObject:results
//                    forKey:key];
//    }
}


//4字节 2位小数
-(void)parse11{
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/100.0;
    
    NSString *results = [NSString stringWithFormat:@"%.2f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
//    [_subdic setObject:results
//                forKey:key];
    
}

//4字节 4位小数
-(void)parse13{
    
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/10000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.4f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
    
    //    [_subdic setObject:results
    //                forKey:key];
    
}

//5字节 4位小数
-(void)parse14{
    
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/10000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.4f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
//    [_subdic setObject:results
//                forKey:key];
    
}

//5字节 分时日月年
-(void)parse15{
    
    NSString *minute =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        minute=@"";
    }
    _offset++;
    
    NSString *hour =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        hour=@"";
    }
    _offset++;
    
    NSString *day =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        day=@"";
    }
    _offset++;
    
    NSString *month =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        month=@"";
    }
    _offset++;
    
    NSString *year =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        year=@"";
    }
    _offset++;
    
    NSString *tdd = [NSString stringWithFormat:@"%@年%@月%@日%@时%@分",year,month,day,hour,minute];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = tdd;
    [array addObject:item];
    
//    [_subdic setObject:tdd
//                forKey:key];
    
}

//分时日月
-(void)parse17{
    
  
    NSString *minute =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        minute=@"";
    }
    _offset++;
 
    NSString *hour =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        hour=@"";
    }
    _offset++;

    NSString *day =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        day=@"";
    }
    _offset++;
    
    NSString *month =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        month=@"";
    }
    _offset++;
    
    NSString *tdd = [NSString stringWithFormat:@"%@月%@日%@时%@分",month,day,hour,minute];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = tdd;
    [array addObject:item];
    
    
    
//    [_subdic setObject:tdd
//                forKey:key];
    
}

//分时日
-(void)parse18{
    NSString *minute =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        minute=@"";
    }
    _offset++;
    
    NSString *hour =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        hour=@"";
    }
    _offset++;
    
    NSString *day =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        day=@"";
    }
    _offset++;
    
    NSString *tdd = [NSString stringWithFormat:@"%@日%@时%@分",day,hour,minute];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = tdd;
    [array addObject:item];
    
//    [_subdic setObject:tdd
//                forKey:key];
}


//日月年
-(void)parse20{
    NSString *day =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        day=@"";
    }
    _offset++;
    
    NSString *month =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        month=@"";
    }
    _offset++;
    
    NSString *year =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        year=@"";
    }
    _offset++;
    
    NSString *tdd = [NSString stringWithFormat:@"%@年%@月%@日",year,month,day];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = tdd;
    [array addObject:item];
    
    
//    [_subdic setObject:tdd
//                forKey:key];
}

//月年
-(void)parse21{
    NSString *month =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        month=@"";
    }
    _offset++;
    
    NSString *year =[NSString stringWithFormat:@"%d",bytes[_offset]];
    if(bytes[_offset]==0xff)
    {
        year=@"";
    }
    _offset++;
    
    NSString *tdd = [NSString stringWithFormat:@"%@年%@月",year,month];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = tdd;
    [array addObject:item];
    
    
//    [_subdic setObject:tdd
//                forKey:key];
}

//1字节 1位小数
-(void)parse22{
    
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/10.0;
    
    NSString *results = [NSString stringWithFormat:@"%.1f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
    
    //    [_subdic setObject:results
    //                forKey:key];
    
}


//3字节 4位小数
-(void)parse23{
    
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/10000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.4f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
    
//    [_subdic setObject:results
//                forKey:key];
    
}


//3字节 3位小数
-(void)parse25{
    
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/1000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.3f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
    
//    if (isCurve) {
//        [_subdic setObject:results
//                    forKey:[NSString stringWithFormat:@"%d",curveIdentifier]];
//    }else{
//    [_subdic setObject:results
//                forKey:key];
//    }
}

//2字节 3位小数
-(void)parse26{
    
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/1000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.3f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
    
    //    if (isCurve) {
    //        [_subdic setObject:results
    //                    forKey:[NSString stringWithFormat:@"%d",curveIdentifier]];
    //    }else{
    //    [_subdic setObject:results
    //                forKey:key];
    //    }
}

//BIN 1字节
-(void)parse29{
    NSInteger ivalue = *(Byte*)(bytes + _offset);  _offset+=1;
    
    NSString *results = [NSString stringWithFormat:@"%d",ivalue];
    
    
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
    
//    [_subdic setObject:results
//                forKey:key];
}


//BIN 2字节
-(void)parse30{
    NSInteger ivalue = *(XL_UINT16*)(bytes + _offset);  _offset+=2;
    
    NSString *results = [NSString stringWithFormat:@"%d",ivalue];
    
    
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
    
//    [_subdic setObject:results
//                forKey:key];
}

//BIN 4字节
-(void)parse32{
    NSInteger ivalue = *(XL_UINT32*)(bytes + _offset);  _offset+=4;
    
    NSString *results = [NSString stringWithFormat:@"%d",ivalue];
    
    
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
    
    
//    [_subdic setObject:results
//                forKey:key];
}

//31字节 状态量
-(void)parse33{
    _offset+=31;
}

//1字节状态量
-(void)parse34{
    _offset+=1;
}

//字符串
-(void)parse35{
    
    NSInteger len = *(XL_UINT16*)(bytes + _offset);  _offset+=2;
    //    NSLog(@"%d",len);
    
//    NSString *desc = [NSString stringWithUTF8String:(const char*)(bytes + _offset)];
 
    NSString *desc1 = [[NSString alloc] initWithBytes:(const char*)(bytes + _offset) length:len encoding:NSUTF8StringEncoding];

//    NSLog(@"长度:%d",len);
//    NSLog(@"内容 %@",desc);
    
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = desc1;
    [array addObject:item];
    
    
//    [_subdic setObject:eventDesc1
//                forKey:[NSString stringWithFormat:@"%d",_identifier]];

    _offset += len;
}

//变长ascii
-(void)parse36{
    NSInteger len = *(Byte*)(bytes + _offset);  _offset+=1;
    NSString *result;
    NSData *data = [NSData dataWithBytes:(bytes + _offset) length:len];
    result = [NSString stringWithFormat:@"%@",[data description]];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = result;
    [array addObject:item];
    
     _offset += len;
}

//32字节ascii
-(void)parse37{
    
    NSString *result;
    NSData *data = [NSData dataWithBytes:(bytes + _offset) length:32];
    result = [NSString stringWithFormat:@"%@",[data description]];
 
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = result;
    [array addObject:item];
    
    _offset+=32;
}

//16字节ascii
-(void)parse39{
    _offset+=16;
}

//6字节BIN
-(void)parse40{
    XL_UINT64 ivalue = *(XL_UINT64*)(bytes + _offset);  _offset+=8;
    
    NSString *results = [NSString stringWithFormat:@"%llu",ivalue];
    
    
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
}

//3字节1位小数
-(void)parse41{
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/10.0;
    
    NSString *results = [NSString stringWithFormat:@"%.1f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    
    XLDataItem *item = [[XLDataItem alloc] init];
    item.key = key;
    item.value = results;
    [array addObject:item];
}
@end
