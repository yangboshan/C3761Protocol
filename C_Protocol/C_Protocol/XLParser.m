//
//  XLParser.m
//  C_Protocol
//
//  Created by JY on 14-1-14.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import "XLParser.h"
#import "XLDataTypeDic.h"




@implementation XLParser

Byte *bytes;
NSInteger len;
NSInteger _offset;
NSInteger begin;
NSInteger end;

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
        [dic setObject:subdic forKey:key];
        
        NSInteger sublen = *(unsigned short*)(bytes + _offset);_offset += 2;
        begin = _offset;
        
        while (sublen>(end - begin)) {
            NSInteger type = bytes[_offset];_offset++;
            NSInteger identifer = *(unsigned short*)(bytes + _offset);_offset += 2;
            [self setKeyForDic:type :identifer :subdic];
            end = _offset;
        }
    }
    
    NSLog(@"字典完成");
}

-(void)setKeyForDic:(NSInteger)type :(NSInteger)identifer : (NSMutableDictionary*)subdic{
    
    NSInteger dtype=0;
    
    switch (type) {
        case 0:{
            dtype = terminal_day_sta[identifer];
        }
            break;
            
        default:
            break;
    }
    
    switch (dtype) {
        case A20:{
            NSString *day =[NSString stringWithFormat:@"%d",bytes[_offset]];  _offset++;
            NSString *month =[NSString stringWithFormat:@"%d",bytes[_offset]];  _offset++;
            NSString *year =[NSString stringWithFormat:@"%d",bytes[_offset]];  _offset++;
            NSString *tdd = [NSString stringWithFormat:@"%@年%@月%@日",year,month,day];
            
            [subdic setObject:tdd forKey:[NSString stringWithFormat:@"%d",identifer]];
        }
            break;
        case BIN2:{
            NSInteger ivalue = *(unsigned short*)(bytes + _offset);  _offset+=2;
            [subdic setObject:[NSNumber numberWithInteger:ivalue] forKey:[NSString stringWithFormat:@"%d",identifer]];
        }
            break;
        default:
            break;
    }
}
@end
