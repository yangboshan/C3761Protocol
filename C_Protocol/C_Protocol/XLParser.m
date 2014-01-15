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


NSMutableDictionary *_subdic;

-(void)initWithNSData:(NSData*)data{
    
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
        
        NSString *typeStr = [NSString stringWithUTF8String:type_desc[_type]];
        NSString *key =  [NSString stringWithFormat:@"%@ %@ %@",typeStr,pStr,fStr];
        [dic setObject:subdic forKey:key];
        
        _subdic = subdic;
        
        NSInteger sublen = *(unsigned short*)(bytes + _offset);_offset += 2;
        begin = _offset;
        
        while (sublen>(end - begin)) {
//            NSInteger type = bytes[_offset];_offset++;
            _identifier = *(unsigned short*)(bytes + _offset);_offset += 2;
            [self setKeyForDic];
            end = _offset;
        }
    }
    NSLog(@"字典完成");
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
   
        default:
            break;
    }
    
    NSString *method = [NSString stringWithFormat:@"parse%d",dtype + 1];
    SEL selecter = NSSelectorFromString(method);
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored  "-Warc-performSelector-leaks"
    [self performSelector:selecter withObject:nil];
#pragma clang diagnostic pop
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

//BIN 2字节
-(void)parse30{
    NSInteger ivalue = *(unsigned short*)(bytes + _offset);  _offset+=2;
    
    [_subdic setObject:[NSNumber numberWithInteger:ivalue]
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
}

@end
