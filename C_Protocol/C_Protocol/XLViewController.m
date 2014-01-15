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

@property (nonatomic,strong) NSMutableData *recvdata;

@end

@implementation XLViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.recvdata = [NSMutableData data];
    [self didReceiveBytes];

}

-(void)didReceiveBytes{
    //测试报文 AFND F49
//    Byte revbytes[] = {0x68,0x56,0x00,0x56,0x00,0x68,
//        0xA8,
//        0x25,0x25,
//        0x01,0x00,
//        0x04,
//        0x0D,
//        0x60,
//        0x00,0x00,
//        0x01,0x06,
//        0x03,0x07,0x12,
//        0x95,0x05,
//        0x25,0x00,
//        0x12,0x00,
//        0x58,0x16};
    
    
    //测试报文AFND F49 F51
    Byte revbytes[] = {0x68,0x76,0x00,0x76,0x00,0x68,
        0x88,
        0x00,0x25,
        0x01,0x00,
        0x04,
        0x0D,
        0x64,
        0x00,0x00,0x04,0x06,
        0x01,0x14,0xCB,0x00,0x03,0x00,
        0x00,0x00,0x01,0x06,
        0x15,0x01,0x14,0x33,0x00,0x01,0x00,
        0x75,0x16};
    
    unsigned short type = 0;
    unsigned short inlen = 37;
    unsigned short outlen = 0;
    Byte *outbuff = NULL;
    int  multiFrameFlag = 0;    //多帧标志
    
    if(UnPackFrame(&type,inlen, revbytes, &outlen, &outbuff,&multiFrameFlag)){
        
        [self.recvdata appendBytes:outbuff length:outlen];
        
        if (!multiFrameFlag) {
            XLParser *parser = [[XLParser alloc] init];
            [parser initWithNSData:self.recvdata];
        }
    } else {
        
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
@end
