//
//  XLParser.m
//  C_Protocol
//
//  Created by JY on 14-1-14.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import "XLParser.h"
#import "XLDataTypeDic.h"


@interface XLParser()

@end


@implementation XLParser

Byte *bytes;
NSInteger len;
NSInteger _offset;
NSInteger begin;
NSInteger end;

NSInteger _type;
NSInteger _identifier;

NSInteger curveIdentifier;
bool isCurve = NO;


NSMutableDictionary *_subdic;

-(void)initWithNSData:(NSData*)data{
    
    end = 0;
    begin = 0;
    curveIdentifier = 0;
    isCurve = NO;
    
    NSMutableDictionary *dic = [NSMutableDictionary dictionary];
 
    bytes = (Byte*)[data bytes];
    len = [data length];
    
    for(int i =0;i<len;i++){
        NSLog(@"%02x",bytes[i]);
    }
    
    _offset = 0;
    
    
    while (_offset<len) {
        NSMutableDictionary *subdic = [NSMutableDictionary dictionary];
        
        NSString *pStr = [NSString stringWithFormat:@"测量点%d",bytes[_offset++]];
        NSString *fStr = [NSString stringWithFormat:@"F项%d",bytes[_offset++]];
        
        _type = bytes[_offset];_offset++;
        
//        NSString *typeStr = [NSString stringWithUTF8String:type_desc[_type]];
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
    NSLog(@"字典完成");
    [[NSNotificationCenter defaultCenter] postNotificationName:@"test"
                                                        object:Nil
                                                      userInfo:dic];
}


-(void)setKeyForDic{
    
    NSInteger dtype=0;
    
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
        default:
            break;
    }
    
    NSLog(@"-----------执行方法前offset:%d",_offset);
    
    NSString *method = [NSString stringWithFormat:@"parse%d",dtype + 1];
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
    
    [_subdic setObject:results
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
}


//2字节 1位小数 带符号
-(void)parse5{
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/10.0;
    
    NSString *results = [NSString stringWithFormat:@"%.1f",result];
    
    if (isCurve) {
        [_subdic setObject:results
                    forKey:[NSString stringWithFormat:@"%d",curveIdentifier]];
    }else{
    [_subdic setObject:results
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
    }
}

//2字节 2位小数 带符号
-(void)parse6{
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/100.0;
    
    NSString *results = [NSString stringWithFormat:@"%.2f",result];
    
    [_subdic setObject:results
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
    
}

//2字节 1位小数
-(void)parse7{
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/10.0;
    
    NSString *results = [NSString stringWithFormat:@"%.1f",result];
    
    if (isCurve) {
        [_subdic setObject:results
                    forKey:[NSString stringWithFormat:@"%d",curveIdentifier]];
    }else{
    [_subdic setObject:results
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
    }
}

//3字节 4位小数

-(void)parse9{
    
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/10000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.4f",result];
    
    if (isCurve) {
        [_subdic setObject:results
                    forKey:[NSString stringWithFormat:@"%d",curveIdentifier]];
    }else {
        [_subdic setObject:results
                    forKey:[NSString stringWithFormat:@"%d",_identifier]];
    }
}


//4字节 2位小数
-(void)parse11{
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/100.0;
    
    NSString *results = [NSString stringWithFormat:@"%.2f",result];

    [_subdic setObject:results
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
    
}

//5字节 4位小数
-(void)parse14{
    
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/10000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.4f",result];

    [_subdic setObject:results
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
    
}

//5字节 分时日月年
-(void)parse15{
    
    NSString *minute =[NSString stringWithFormat:@"%d",bytes[_offset]];    _offset++;
    NSString *hour =[NSString stringWithFormat:@"%d",bytes[_offset]];  _offset++;
    NSString *day =[NSString stringWithFormat:@"%d",bytes[_offset]];    _offset++;
    NSString *month =[NSString stringWithFormat:@"%d",bytes[_offset]];  _offset++;
    NSString *year =[NSString stringWithFormat:@"%d",bytes[_offset]];   _offset++;
    NSString *tdd = [NSString stringWithFormat:@"%@年%@月%@日%@时%@分",year,month,day,hour,minute];
    
    [_subdic setObject:tdd
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
    
}

//分时日月
-(void)parse17{
    
    NSString *minute =[NSString stringWithFormat:@"%d",bytes[_offset]];    _offset++;
    NSString *hour =[NSString stringWithFormat:@"%d",bytes[_offset]];  _offset++;
    NSString *day =[NSString stringWithFormat:@"%d",bytes[_offset]];    _offset++;
    NSString *month =[NSString stringWithFormat:@"%d",bytes[_offset]];  _offset++;
    NSString *tdd = [NSString stringWithFormat:@"%@月%@日%@时%@分",month,day,hour,minute];
    
    [_subdic setObject:tdd
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
    
}

//分时日
-(void)parse18{
    NSString *minute =[NSString stringWithFormat:@"%d",bytes[_offset]];    _offset++;
    NSString *hour =[NSString stringWithFormat:@"%d",bytes[_offset]];  _offset++;
    NSString *day =[NSString stringWithFormat:@"%d",bytes[_offset]];   _offset++;
    NSString *tdd = [NSString stringWithFormat:@"%@日%@时%@分",day,hour,minute];
    
    [_subdic setObject:tdd
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
}


//日月年
-(void)parse20{
    NSString *day =[NSString stringWithFormat:@"%d",bytes[_offset]];    _offset++;
    NSString *month =[NSString stringWithFormat:@"%d",bytes[_offset]];  _offset++;
    NSString *year =[NSString stringWithFormat:@"%d",bytes[_offset]];   _offset++;
    NSString *tdd = [NSString stringWithFormat:@"%@年%@月%@日",year,month,day];
    
    [_subdic setObject:tdd
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
}

//月年
-(void)parse21{
    NSString *month =[NSString stringWithFormat:@"%d",bytes[_offset]];  _offset++;
    NSString *year =[NSString stringWithFormat:@"%d",bytes[_offset]];   _offset++;
    NSString *tdd = [NSString stringWithFormat:@"%@年%@月",year,month];
    
    [_subdic setObject:tdd
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
}

//3字节 4位小数
-(void)parse23{
    
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/10000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.4f",result];
    
    [_subdic setObject:results
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
    
}


//3字节 3位小数
-(void)parse25{
    
    long long  ivalue = *(XL_SINT64*)(bytes+_offset); _offset+=8;
    double result = ivalue/1000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.3f",result];
    
    if (isCurve) {
        [_subdic setObject:results
                    forKey:[NSString stringWithFormat:@"%d",curveIdentifier]];
    }else{
    [_subdic setObject:results
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
    }
}


//BIN 1字节
-(void)parse29{
    NSInteger ivalue = *(Byte*)(bytes + _offset);  _offset+=1;
    
    [_subdic setObject:[NSNumber numberWithInteger:ivalue]
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
}


//BIN 2字节
-(void)parse30{
    NSInteger ivalue = *(XL_UINT16*)(bytes + _offset);  _offset+=2;
    
    [_subdic setObject:[NSNumber numberWithInteger:ivalue]
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
}

//BIN 4字节
-(void)parse32{
    NSInteger ivalue = *(XL_UINT32*)(bytes + _offset);  _offset+=4;
    
    [_subdic setObject:[NSNumber numberWithInteger:ivalue]
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
}

//31字节 状态量
-(void)parse33{
    _offset+=31;
}

//1字节状态量
-(void)parse34{
    _offset+=1;
}

//事件字符串
-(void)parse35{
    
    NSInteger len = *(Byte*)(bytes + _offset);  _offset+=1;
    //    NSLog(@"%d",len);
    
    NSString *eventDesc = [NSString stringWithUTF8String:(const char*)(bytes + _offset)];
    
    
    NSStringEncoding enc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_2312_80);
    NSData   *data = [NSData dataWithBytes:(bytes + _offset) length:len];
    NSString *desc = [[NSString alloc] initWithData: data encoding:enc];
    NSLog(@"%@",desc);
    
    [_subdic setObject:eventDesc
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
    
    NSLog(@"%@",eventDesc);
    _offset += len;
}

@end
