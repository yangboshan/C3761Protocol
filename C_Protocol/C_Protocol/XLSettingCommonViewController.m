//
//  XLSettingCommonViewController.m
//  C_Protocol
//
//  Created by admin on 14-2-18.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import "XLSettingCommonViewController.h"
#import "XLSocketManager.h"
#import "XL3761PackFrame.h"
#import "UIView+UIView___FindAndResignFirstResponder.h"
#import  "XLDataItem.h"

@interface XLSettingCommonViewController ()

@property(nonatomic,assign) Byte* frame;
@property(nonatomic,strong) NSData *data;
@property(nonatomic,assign) XL_UINT16 outlen;
@end

@implementation XLSettingCommonViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(afn0:) name:@"SPEHANDLE" object:nil];
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(touch)];
    [tap setNumberOfTouchesRequired:1];
    [self.view addGestureRecognizer:tap];
    [self.activityView setHidden:YES];
	// Do any additional setup after loading the view.
}

-(void)afn0:(NSNotification*)notify{
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        NSData *data = [[NSUserDefaults standardUserDefaults] objectForKey:@"data"];
        if (data) {
            //            NSString *desc = [NSString stringWithFormat:@"返回报文:%@",[data description]];
            //            self.frameOriginal.text = desc;
        }
        
        NSDictionary* dcs = notify.userInfo;
        NSString *value = [dcs valueForKey:@"key"];
        
        if ([value isEqualToString:@"1"]) {
            self.showResult.text = @"确认帧";
        }
        
        if ([value isEqualToString:@"2"]) {
            self.showResult.text = @"否认帧";
        }
        
        if ([value isEqualToString:@"-1"]) {
            self.showResult.text = @"出现错误";
        }
        
        [self.activityView stopAnimating];
        [self.activityView setHidden:YES];
    });
}

-(void) touch{
    [self.view findAndResignFirstResponder];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)home:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)set:(id)sender {
}

- (IBAction)setF170:(id)sender {
    
    [self.activityView setHidden:NO];
    
    NSString *ssid = self.v1.text;
    NSString *psw = self.v2.text;
    XL_UINT8  ssid_[16];
    XL_UINT8  psw_[16];
    
    for(int i = 0;i<16;i++){
        if ([ssid length]-1<i) {
            ssid_[i] = '\0';
        }else{
            ssid_[i] = (XL_UINT8)[ssid characterAtIndex:i];
        }
        if ([psw length]-1<i) {
            psw_[i] = '\0';
        }else{
            psw_[i] = (XL_UINT8)[psw characterAtIndex:i];
        }
    }
    
    PACKITEM_P array[2] = {
        BuildPackItem(0, 0, 0, ssid_, 16, 1, 0),
        BuildPackItem(0, 0, 0, psw_, 16, 1, 0)
    };
    
    self.frame = PackFrameForAfn04(0x04, 0, 170, array, 2, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)setF169:(id)sender {
    
    [self.activityView setHidden:NO];
    
    NSString *deviceNumber1 = self.v1.text;
    NSString *initialNumber11 = self.v11.text;

    NSString *group12 = self.v12.text;
    
    
    XL_UINT8  deviceNumber1_[16];
    XL_UINT8  initialNumber11_[16];
    XL_UINT8  group12_[8];
    
    XL_UINT8  class14_[1];
    class14_[0] =  (XL_UINT8)[self.v14.text characterAtIndex:0];
    
    XL_UINT8  class17_[1];
    class17_[0] =  (XL_UINT8)[self.v17.text characterAtIndex:0];
    
    
    for(int i = 0;i<16;i++){
        if ([deviceNumber1 length]-1<i) {
            deviceNumber1_[i] = '\0';
        }else{
            deviceNumber1_[i] = (XL_UINT8)[deviceNumber1 characterAtIndex:i];
        }
        
        if ([initialNumber11 length]-1<i) {
            initialNumber11_[i] = '\0';
        }else{
            initialNumber11_[i] = (XL_UINT8)[initialNumber11 characterAtIndex:i];
        }
    }
    
    for(int i = 0;i<8;i++){
        if ([group12 length]-1<i) {
            group12_[i] = '\0';
        }else{
            group12_[i] = (XL_UINT8)[group12 characterAtIndex:i];
        }
    }
    
    PACKITEM_P array[20] = {
        BuildPackItem(0, 0, 0, deviceNumber1_, 16, 1, 0),
        BuildPackItem([self.v2.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v3.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v4.text floatValue], 3, 1, 0, 0, 0, 1),
        
        BuildPackItem([self.v5.text integerValue], 2, 0, 0, 0, 0, 0),
        BuildPackItem([self.v6.text integerValue], 2, 0, 0, 0, 0, 0),
        BuildPackItem([self.v7.text integerValue], 2, 0, 0, 0, 0, 0),
        
        BuildPackItem([self.v8.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v9.text floatValue], 2, 1, 0, 0, 0, 1),
        
        //日月年
        BuildPackItem(18, 1, 0, 0, 0, 0, 1),
        BuildPackItem(2, 1, 0, 0, 0, 0, 1),
        BuildPackItem(14, 1, 0, 0, 0, 0, 1),
        
        //出厂编号
        BuildPackItem(0, 0, 0, initialNumber11_, 16, 1, 0),
        
        //连接组别
        BuildPackItem(0, 0, 0, group12_, 8, 1, 0),
        
        //相数
        BuildPackItem([self.v13.text integerValue], 1, 0, 0, 0, 0, 0),
        
        //耐热等级
        BuildPackItem(0, 0, 0, class14_, 1, 1, 0),
        
        //温升
        BuildPackItem([self.v15.text floatValue], 2, 1, 0, 0, 0, 1),
        
        //冷却方式
        BuildPackItem([self.v16.text integerValue], 1, 0, 0, 0, 0, 0),
        
        //绝缘水平
        BuildPackItem([self.v17.text integerValue], 1, 0, 0, 0, 0, 0),
        
        BuildPackItem([self.v18.text integerValue], 2, 0, 0, 0, 0, 0)
    };
    
    self.frame = PackFrameForAfn04(0x04, 0, 169, array, 20, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)setF28:(id)sender {
    [self.activityView setHidden:NO];
    
    PACKITEM_P array[2] = {
        BuildPackItem([self.v1.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v2.text floatValue], 2, 1, 0, 0, 0, 1),
    };
    
    self.frame = PackFrameForAfn04(0x04, 1, 28, array, 2, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)setF3:(id)sender {
    [self.activityView setHidden:NO];
    
    NSString *apn = self.v11.text;
    XL_UINT8 apn_[16];
    
    for(int i = 0;i<16;i++){
        if ([apn length]-1<i) {
            apn_[i] = '\0';
        }else{
            apn_[i] = (XL_UINT8)[apn characterAtIndex:i];
        }
    }
    
    PACKITEM_P array[11] = {
        BuildPackItem([self.v1.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v2.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v3.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v4.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v5.text integerValue], 2, 0, 0, 0, 0, 0),
        BuildPackItem([self.v6.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v7.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v8.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v9.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v10.text integerValue], 2, 0, 0, 0, 0, 0),
        
        BuildPackItem(0, 0, 0, apn_, 16, 1, 0),
    };
    
    self.frame = PackFrameForAfn04(0x04, 0, 3, array, 11, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}


- (IBAction)setF7:(id)sender {
    [self.activityView setHidden:NO];
    
    NSString *apn = self.v11.text;
    XL_UINT8 apn_[16];
    
    for(int i = 0;i<16;i++){
        if ([apn length]-1<i) {
            apn_[i] = '\0';
        }else{
            apn_[i] = (XL_UINT8)[apn characterAtIndex:i];
        }
    }
    
    NSInteger userNameLen = [self.v20.text integerValue];
    NSInteger pswLen = [self.v22.text integerValue];
    
    NSString *userName = self.v21.text;
    XL_UINT8 userName_[userNameLen];
    for(int i = 0;i<userNameLen;i++){
        userName_[i] = (XL_UINT8)[userName characterAtIndex:i];
    }
    
    NSString *psw = self.v23.text;
    XL_UINT8 psw_[pswLen];
    for(int i = 0;i<pswLen;i++){
        psw_[i] = (XL_UINT8)[psw characterAtIndex:i];
    }

    
    PACKITEM_P array[24] = {
        //IP
        BuildPackItem([self.v1.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v2.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v3.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v4.text integerValue], 1, 0, 0, 0, 0, 0),

        //子网掩码
        BuildPackItem([self.v5.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v6.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v7.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v8.text integerValue], 1, 0, 0, 0, 0, 0),
        
        //网关
        BuildPackItem([self.v9.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v10.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v11.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v12.text integerValue], 1, 0, 0, 0, 0, 0),
        
        //代理服务器
        BuildPackItem([self.v13.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v14.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v15.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v16.text integerValue], 1, 0, 0, 0, 0, 0),
        BuildPackItem([self.v17.text integerValue], 1, 0, 0, 0, 0, 0),
        
        //连接方式
        BuildPackItem([self.v18.text integerValue], 2, 0, 0, 0, 0, 0),
        BuildPackItem([self.v19.text integerValue], 1, 0, 0, 0, 0, 0),
        
        BuildPackItem(0, 0, 0, userName_, userNameLen, 1, 0),
        BuildPackItem(0, 0, 0, psw_, pswLen, 1, 0),
        
        BuildPackItem([self.v24.text integerValue], 2, 0, 0, 0, 0, 0),
        
    };
    
    self.frame = PackFrameForAfn04(0x04, 0, 3, array, 11, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)setF9:(id)sender {
}

- (IBAction)setF10:(id)sender {
}
@end
