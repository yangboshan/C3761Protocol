//
//  XLViewController.m
//  C_Protocol
//
//  Created by JY on 14-1-6.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//
#import "XLViewController.h"
#import "XL3761UnPack.h"
#import "XLParser.h"


@interface XLViewController ()

@end

@implementation XLViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    //测试报文 AFND F49
    Byte revbytes[] = {0x68,0x56,0x00,0x56,0x00,0x68,
        0xA8,
        0x25,0x25,
        0x01,0x00,
        0x04,
        0x0D,
        0x60,
        0x00,0x00,
        0x01,0x06,
        0x03,0x07,0x12,
        0x95,0x05,
        0x25,0x00,
        0x12,0x00,
        0x58,0x16};
    
    unsigned short type = 0;
    unsigned short inlen = 29;
    unsigned short outlen = 0;
    Byte *outbuff = NULL;
    int  multiFrameFlag = 0;    //多帧标志
    
    NSMutableData *recvdata = [NSMutableData data];
    
    if(UnPackFrame(&type,inlen, revbytes, &outlen, &outbuff,&multiFrameFlag)){
        
        recvdata = [NSMutableData dataWithBytes: outbuff length: outlen];

        if (!multiFrameFlag) {
            XLParser *parser = [[XLParser alloc] init];
            [parser initWithNSData:recvdata];
        } else {
            [recvdata appendBytes:outbuff length:outlen];
        }
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
@end
