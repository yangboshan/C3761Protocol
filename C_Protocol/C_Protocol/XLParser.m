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
        NSLog(@"%2x",bytes[i]);
    }
    
    _offset = 0;
    
    
    while (_offset<len) {
        NSMutableDictionary *subdic = [NSMutableDictionary dictionary];
        
        NSString *pStr = [NSString stringWithFormat:@"P%d",bytes[_offset++]];
        NSString *fStr = [NSString stringWithFormat:@"F%d",bytes[_offset++]];
        NSString *key = [NSString stringWithFormat:@"%@%@",pStr,fStr];
        _type = bytes[_offset];_offset++;
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

-(void)parse20{
    NSString *day =[NSString stringWithFormat:@"%d",bytes[_offset]];    _offset++;
    NSString *month =[NSString stringWithFormat:@"%d",bytes[_offset]];  _offset++;
    NSString *year =[NSString stringWithFormat:@"%d",bytes[_offset]];   _offset++;
    NSString *tdd = [NSString stringWithFormat:@"%@年%@月%@日",year,month,day];
    
    [_subdic setObject:tdd
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
}

-(void)parse30{
    NSInteger ivalue = *(unsigned short*)(bytes + _offset);  _offset+=2;
    
    [_subdic setObject:[NSNumber numberWithInteger:ivalue]
                forKey:[NSString stringWithFormat:@"%d",_identifier]];
}

@end
