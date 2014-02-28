//
//  XLParserNew.m
//  XLApp
//
//  Created by JY on 14-2-25.
//  Copyright (c) 2014年 Pixel-in-Gene. All rights reserved.
//

#import "XLParser.h"
#import "XLDataTypeDic.h"
#import "XLDataItem.h"

@interface XLParser()

@property(nonatomic,assign) Byte* bytes;
@property(nonatomic,assign) NSInteger offset;
@property(nonatomic,assign) NSInteger identifierType;
@property(nonatomic,assign) NSInteger identifier;
@property(nonatomic,assign) COMPLEX_ITEM dtype;

@property(nonatomic,assign) BOOL isCurve;
@property(nonatomic,assign) NSInteger curveCounter;

@property(nonatomic,assign) NSInteger keyCounter;
@property(nonatomic,strong) NSMutableDictionary *subSet;
@property(nonatomic,strong) NSMutableDictionary *finalSet;


@end

@implementation XLParser


-(void)initWithNSData:(NSData*)data{
    
    self.finalSet = [NSMutableDictionary dictionary];
    self.bytes = (Byte*)[data bytes];
    
    NSInteger len = [data length];
    NSString* pointsId;
    
    NSInteger ifunctionId;
    NSString* functionId;
    
    NSInteger begin = 0;
    NSInteger end = 0;
    NSInteger sublen = 0;
    
    _offset = 0;
    
    while (_offset<len) {
        
        self.isCurve = NO;
        self.curveCounter = 0;
        
        self.subSet = [NSMutableDictionary dictionary];
        
        pointsId   = [NSString stringWithFormat:@"P%d",_bytes[_offset++]];
        
        ifunctionId = _bytes[_offset++];
        functionId = [NSString stringWithFormat:@"F%d",ifunctionId];
        
        if ([[self.finalSet allKeys] containsObject:functionId]) {
            
            if (![[self.finalSet allKeys] containsObject:[NSString stringWithFormat:@"%@#",functionId]])
                self.keyCounter = 0;
            
            self.keyCounter++;
            functionId = [NSString stringWithFormat:@"%@#%d",functionId,self.keyCounter];
        }
        
        [self.finalSet setObject:self.subSet forKey:functionId];
        
        self.identifierType = _bytes[_offset++];
        
        sublen = *(unsigned short*)(_bytes+_offset);
        _offset += 2;
        
        begin = _offset;
        
        while (sublen>(end - begin)) {
            
            _identifier = *(unsigned short*)(_bytes+_offset);
            _offset += 2;
            
            [self setParseValue];
            end = _offset;
        }
    }
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"user"
                                                        object:nil
                                                      userInfo:self.finalSet];
    NSLog(@"发送通知");
}

-(void)setParseValue{
    
    switch (self.identifierType) {
        case 0:{
            self.dtype = terminal_day_sta[_identifier];
        }
            break;
        case 1:{
            self.dtype = terminal_month_sta[_identifier];
        }
            break;
        case 2:{
            self.dtype = measure_day_powervalue[_identifier];
        }
            break;
        case 3:{
            self.dtype = measure_month_powervalue[_identifier];
        }
            break;
        case 4:{
            self.dtype = history_day_powerneeds[_identifier];
        }
            break;
        case 5:{
            self.dtype = history_month_powerneeds[_identifier];
        }
            break;
        case 6:{
            self.dtype = measure_day_sta[_identifier];
        }
            break;
        case 7:{
            self.dtype = measure_month_sta[_identifier];
        }
            break;
        case 8:{
            self.dtype = measure_curve_data[_identifier];
            self.isCurve = YES;
            self.curveCounter++;
        }
            break;
        case 9:{
            self.dtype = daily_data_charmonic[_identifier];
        }
            break;
        case 10:{
            self.dtype = daily_data_vharmonic[_identifier];
        }
            break;
        case 11:{
            self.dtype = dcanalog_day_data[_identifier];
        }
            break;
        case 12:{
            self.dtype = dcanalog_month_data[_identifier];
        }
            break;
        case 13:{
            self.dtype = terminal_rt_basic_sta[_identifier];
        }
            break;
        case 14:{
            self.dtype = mtr_rt_basic_sta[_identifier];
        }
            break;
        case 15:{
            self.dtype = rt_power_value_sta[_identifier];
        }
            break;
        case 16:{
            self.dtype = rt_power_needs_sta[_identifier];
        }
            break;
        case 17:{
            self.dtype = rt_dc_analog[_identifier];
        }
            break;
        case 18:{
            self.dtype = mtr_rt_harmonic[_identifier];
        }
            break;
        case 19:{
            self.dtype = eventlist[_identifier];
        }
            break;
            
        case 20:{
            self.dtype  = parameter_data_comm[_identifier];
            
        }
            break;
        case 21:{
            self.dtype  = parameter_data_mtr[_identifier];
        }
            break;
        case 22:{
            self.dtype  = parameter_data_terminal[_identifier];
        }
            break;
        default:
            break;
    }
    
    //    NSLog(@"-----------执行方法前offset:%d",_offset);
    
    NSString *method = [NSString stringWithFormat:@"parse%d",self.dtype.datatype + 1];
    SEL selecter = NSSelectorFromString(method);
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored  "-Warc-performSelector-leaks"
    [self performSelector:selecter withObject:nil];
#pragma clang diagnostic pop
}


-(void)parse2{
    NSInteger mi = *(XL_SINT8*)(_bytes+_offset); _offset+=1;
    NSInteger dishu = *(XL_UINT16*)(_bytes+_offset); _offset+=2;
    
    NSString *results = [NSString stringWithFormat:@"%.3f",pow(dishu, mi)];
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    [self.subSet setValue:results forKey:key];
}


//2字节 1位小数 带符号
-(void)parse5{
    long long  ivalue = *(XL_SINT64*)(_bytes+_offset); _offset+=8;
    double result = ivalue/10.0;
    
    NSString *results = [NSString stringWithFormat:@"%.1f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    
    if (self.isCurve) {
        [self.subSet setObject:results
                        forKey:[NSString stringWithFormat:@"%d",self.curveCounter]];
    }else{
        [self.subSet setObject:results forKey:key];
    }
}

//2字节 2位小数 带符号
-(void)parse6{
    long long  ivalue = *(XL_SINT64*)(_bytes+_offset); _offset+=8;
    double result = ivalue/100.0;
    
    NSString *results = [NSString stringWithFormat:@"%.2f",result];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    
    [self.subSet setObject:results forKey:key];
}

//2字节 1位小数
-(void)parse7{
    long long  ivalue = *(XL_SINT64*)(_bytes+_offset); _offset+=8;
    double result = ivalue/10.0;
    
    NSString *results = [NSString stringWithFormat:@"%.1f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    
    if (self.isCurve) {
        [self.subSet setObject:results
                        forKey:[NSString stringWithFormat:@"%d",self.curveCounter]];
    }else{
        [self.subSet setObject:results forKey:key];
    }
}

//3字节 4位小数

-(void)parse9{
    
    long long  ivalue = *(XL_SINT64*)(_bytes+_offset); _offset+=8;
    double result = ivalue/10000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.4f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    
    if (self.isCurve) {
        [self.subSet setObject:results
                        forKey:[NSString stringWithFormat:@"%d",self.curveCounter]];
    }else{
        [self.subSet setObject:results forKey:key];
    }
}


//4字节 2位小数
-(void)parse11{
    long long  ivalue = *(XL_SINT64*)(_bytes+_offset); _offset+=8;
    double result = ivalue/100.0;
    
    NSString *results = [NSString stringWithFormat:@"%.2f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    
    [self.subSet setObject:results forKey:key];
}

//3字节 4位小数
-(void)parse13{
    
    long long  ivalue = *(XL_SINT64*)(_bytes+_offset); _offset+=8;
    double result = ivalue/10000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.4f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    [self.subSet setObject:results forKey:key];
}


//5字节 4位小数
-(void)parse14{
    
    long long  ivalue = *(XL_SINT64*)(_bytes+_offset); _offset+=8;
    double result = ivalue/10000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.4f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    [self.subSet setObject:results forKey:key];
}

//5字节 分时日月年
-(void)parse15{
    
    NSString *minute =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        minute=@"";
    }
    _offset++;
    
    NSString *hour =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        hour=@"";
    }
    _offset++;
    
    NSString *day =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        day=@"";
    }
    _offset++;
    
    NSString *month =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        month=@"";
    }
    _offset++;
    
    NSString *year =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        year=@"";
    }
    _offset++;
    
    NSString *tdd = [NSString stringWithFormat:@"%@年%@月%@日%@时%@分",year,month,day,hour,minute];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    [self.subSet setObject:tdd forKey:key];
    
}

//分时日月
-(void)parse17{
    
    
    NSString *minute =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        minute=@"";
    }
    _offset++;
    
    NSString *hour =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        hour=@"";
    }
    _offset++;
    
    NSString *day =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        day=@"";
    }
    _offset++;
    
    NSString *month =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        month=@"";
    }
    _offset++;
    
    NSString *tdd = [NSString stringWithFormat:@"%@月%@日%@时%@分",month,day,hour,minute];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    [self.subSet setObject:tdd forKey:key];
}

//分时日
-(void)parse18{
    NSString *minute =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        minute=@"";
    }
    _offset++;
    
    NSString *hour =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        hour=@"";
    }
    _offset++;
    
    NSString *day =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        day=@"";
    }
    _offset++;
    
    NSString *tdd = [NSString stringWithFormat:@"%@日%@时%@分",day,hour,minute];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    [self.subSet setObject:tdd forKey:key];
}


//日月年
-(void)parse20{
    NSString *day =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        day=@"";
    }
    _offset++;
    
    NSString *month =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        month=@"";
    }
    _offset++;
    
    NSString *year =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        year=@"";
    }
    _offset++;
    
    NSString *tdd = [NSString stringWithFormat:@"%@年%@月%@日",year,month,day];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    [self.subSet setObject:tdd forKey:key];
}

//月年
-(void)parse21{
    NSString *month =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        month=@"";
    }
    _offset++;
    
    NSString *year =[NSString stringWithFormat:@"%d",_bytes[_offset]];
    if(_bytes[_offset]==0xff)
    {
        year=@"";
    }
    _offset++;
    
    NSString *tdd = [NSString stringWithFormat:@"%@年%@月",year,month];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    [self.subSet setObject:tdd forKey:key];
}

//1字节 1位小数
-(void)parse22{
    
    long long  ivalue = *(XL_SINT64*)(_bytes+_offset); _offset+=8;
    double result = ivalue/10.0;
    
    NSString *results = [NSString stringWithFormat:@"%.1f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    
    [self.subSet setObject:results forKey:key];
}


//3字节 4位小数
-(void)parse23{
    
    long long  ivalue = *(XL_SINT64*)(_bytes+_offset); _offset+=8;
    double result = ivalue/10000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.4f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    
    [self.subSet setObject:results forKey:key];
    
}


//3字节 3位小数
-(void)parse25{
    
    long long  ivalue = *(XL_SINT64*)(_bytes+_offset); _offset+=8;
    double result = ivalue/1000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.3f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    
    if (self.isCurve) {
        [self.subSet setObject:results
                        forKey:[NSString stringWithFormat:@"%d",self.curveCounter]];
    }else{
        [self.subSet setObject:results forKey:key];
    }
}

//2字节 3位小数
-(void)parse26{
    
    long long  ivalue = *(XL_SINT64*)(_bytes+_offset); _offset+=8;
    double result = ivalue/1000.0;
    
    NSString *results = [NSString stringWithFormat:@"%.3f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    if (self.isCurve) {
        [self.subSet setObject:results
                        forKey:[NSString stringWithFormat:@"%d",self.curveCounter]];
    }else{
        [self.subSet setObject:results forKey:key];
    }
}

//BIN 1字节
-(void)parse29{
    NSInteger ivalue = *(Byte*)(_bytes + _offset);  _offset+=1;
    
    NSString *results = [NSString stringWithFormat:@"%d",ivalue];
    
    
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    [self.subSet setObject:results forKey:key];
    
}


//BIN 2字节
-(void)parse30{
    NSInteger ivalue = *(XL_UINT16*)(_bytes + _offset);  _offset+=2;
    
    NSString *results = [NSString stringWithFormat:@"%d",ivalue];
    
    
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    [self.subSet setObject:results forKey:key];
}

//BIN 4字节
-(void)parse32{
    NSInteger ivalue = *(XL_UINT32*)(_bytes + _offset);  _offset+=4;
    
    NSString *results = [NSString stringWithFormat:@"%d",ivalue];
    
    
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    [self.subSet setObject:results forKey:key];
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
    
    NSInteger len = *(XL_UINT16*)(_bytes + _offset);  _offset+=2;
    
    NSString *results = [[NSString alloc] initWithBytes:(const char*)(_bytes + _offset) length:len encoding:NSUTF8StringEncoding];
    
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    [self.subSet setObject:results forKey:key];
    
    _offset += len;
}

//变长ascii
-(void)parse36{
    NSInteger len = *(Byte*)(_bytes + _offset);  _offset+=1;
    _offset += len;
}

//32字节ascii
-(void)parse37{
    _offset+=32;
}

//16字节ascii
-(void)parse39{
    _offset+=16;
}

//6字节BIN
-(void)parse40{
    XL_UINT64 ivalue = *(XL_UINT64*)(_bytes + _offset);  _offset+=8;
    
    NSString *results = [NSString stringWithFormat:@"%llu",ivalue];
    
    
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    
    [self.subSet setObject:results forKey:key];
    
}

//3字节1位小数
-(void)parse41{
    long long  ivalue = *(XL_SINT64*)(_bytes+_offset); _offset+=8;
    double result = ivalue/10.0;
    
    NSString *results = [NSString stringWithFormat:@"%.1f",result];
    NSString *key = [NSString stringWithUTF8String:(const char*)self.dtype.desc];
    if (ivalue == ERRORDATA) {
        results = @"";
    }
    
    [self.subSet setObject:results forKey:key];
}
@end
