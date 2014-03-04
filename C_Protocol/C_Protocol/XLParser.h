//
//  XLParser.h
//  C_Protocol
//
//  Created by JY on 14-1-14.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface XLParser : NSObject
@property(nonatomic,strong) NSMutableDictionary *finalSet;
-(void)initWithNSData:(NSData*)data;

@end
