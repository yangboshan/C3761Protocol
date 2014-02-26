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

- (IBAction)setF36:(id)sender {
    
    [self.activityView setHidden:NO];
    
    PACKITEM_P array[1] = {
        BuildPackItem([self.v1.text integerValue], 4, 0, 0, 0, 0, 1),
    };
    
    self.frame = PackFrameForAfn04(0x04, 0, 36, array, 1, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)setF60:(id)sender {
    [self.activityView setHidden:NO];
    NSLog(@"%.1f",[self.v1.text floatValue]);
    
    PACKITEM_P array[40] = {
        BuildPackItem([self.v1.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v2.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v3.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v4.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v5.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v6.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v7.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v8.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v9.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v10.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v11.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v12.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v13.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v14.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v15.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v16.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v17.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v18.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v19.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v20.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v21.text floatValue], 2, 1, 0, 0, 0, 1),
        BuildPackItem([self.v22.text floatValue], 2, 2, 0, 0, 0, 1),
        BuildPackItem([self.v23.text floatValue], 2, 2, 0, 0, 0, 1),
        BuildPackItem([self.v24.text floatValue], 2, 2, 0, 0, 0, 1),
        BuildPackItem([self.v25.text floatValue], 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        BuildPackItem(0, 2, 2, 0, 0, 0, 1),
        
    };
    
    self.frame = PackFrameForAfn04(0x04, 0, 60, array, 40, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)setF61:(id)sender {
    [self.activityView setHidden:NO];

    
    PACKITEM_P array[1] = {
        BuildPackItem([self.v1.text integerValue], 1, 0, 0, 0, 0, 0),
    };
    
    self.frame = PackFrameForAfn04(0x04, 0, 61, array, 1, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)setF91:(id)sender {
    
    [self.activityView setHidden:NO];
    
    PACKITEM_P array[6] = {
        BuildPackItem([self.v1.text floatValue], 2, 2, 0, 0, 0, 1),//秒
        BuildPackItem([self.v2.text integerValue], 1, 0, 0, 0, 0, 1),//分
        BuildPackItem([self.v3.text integerValue]&0x8FFF, 2, 0, 0, 0, 0, 1),//度
        BuildPackItem([self.v4.text floatValue], 2, 2, 0, 0, 0, 1),//秒
        BuildPackItem([self.v5.text integerValue], 1, 0, 0, 0, 0, 1),//分
        BuildPackItem([self.v6.text integerValue]&0x8FFF, 2, 0, 0, 0, 0, 1),//度
    };
    
    
    self.frame = PackFrameForAfn04(0x04, 0, 91, array, 6, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)setF172:(id)sender {
    [self.activityView setHidden:NO];
    
    NSString *userName1 = self.v1.text;
    NSString *psw1 = self.v2.text;
    XL_UINT8  userName1_[16];
    XL_UINT8  psw1_[16];
    
    for(int i = 0;i<16;i++){
        if ([userName1 length]-1<i) {
            userName1_[i] = '\0';
        }else{
            userName1_[i] = (XL_UINT8)[userName1 characterAtIndex:i];
        }
        if ([psw1 length]-1<i) {
            psw1_[i] = '\0';
        }else{
            psw1_[i] = (XL_UINT8)[psw1 characterAtIndex:i];
        }
    }
    
    NSString *userName2 = self.v3.text;
    NSString *psw2 = self.v4.text;
    XL_UINT8  userName2_[16];
    XL_UINT8  psw2_[16];
    
    for(int i = 0;i<16;i++){
        if ([userName2 length]-1<i) {
            userName2_[i] = '\0';
        }else{
            userName2_[i] = (XL_UINT8)[userName2 characterAtIndex:i];
        }
        if ([psw2 length]-1<i) {
            psw2_[i] = '\0';
        }else{
            psw2_[i] = (XL_UINT8)[psw2 characterAtIndex:i];
        }
    }
    
    
    NSString *userName3 = self.v5.text;
    NSString *psw3 = self.v6.text;
    XL_UINT8  userName3_[16];
    XL_UINT8  psw3_[16];
    
    for(int i = 0;i<16;i++){
        if ([userName3 length]-1<i) {
            userName3_[i] = '\0';
        }else{
            userName3_[i] = (XL_UINT8)[userName3 characterAtIndex:i];
        }
        if ([psw3 length]-1<i) {
            psw3_[i] = '\0';
        }else{
            psw3_[i] = (XL_UINT8)[psw3 characterAtIndex:i];
        }
    }
    
    
    NSString *userName4 = self.v7.text;
    NSString *psw4 = self.v8.text;
    XL_UINT8  userName4_[16];
    XL_UINT8  psw4_[16];
    
    for(int i = 0;i<16;i++){
        if ([userName4 length]-1<i) {
            userName4_[i] = '\0';
        }else{
            userName4_[i] = (XL_UINT8)[userName4 characterAtIndex:i];
        }
        if ([psw4 length]-1<i) {
            psw4_[i] = '\0';
        }else{
            psw4_[i] = (XL_UINT8)[psw4 characterAtIndex:i];
        }
    }
    
    PACKITEM_P array[8] = {
        BuildPackItem(0, 0, 0, userName1_, 16, 1, 0),
        BuildPackItem(0, 0, 0, psw1_, 16, 1, 0),
        BuildPackItem(0, 0, 0, userName2_, 16, 1, 0),
        BuildPackItem(0, 0, 0, psw2_, 16, 1, 0),
        BuildPackItem(0, 0, 0, userName3_, 16, 1, 0),
        BuildPackItem(0, 0, 0, psw3_, 16, 1, 0),
        BuildPackItem(0, 0, 0, userName4_, 16, 1, 0),
        BuildPackItem(0, 0, 0, psw4_, 16, 1, 0),
    };
    
    self.frame = PackFrameForAfn04(0x04, 0, 172, array, 8, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
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
        BuildPackItem(0, 0, 0, class17_, 1, 1, 0),
        
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
        
        //用户名长度
        BuildPackItem(userNameLen, 1, 0, 0, 0, 0, 0),
        //用户名
        BuildPackItem(0, 0, 0, userName_, userNameLen, 1, 0),
        //密码长度
        BuildPackItem(pswLen, 1, 0, 0, 0, 0, 0),
        //密码
        BuildPackItem(0, 0, 0, psw_, pswLen, 1, 0),
        
        BuildPackItem([self.v24.text integerValue], 2, 0, 0, 0, 0, 0),
        
    };
    
    self.frame = PackFrameForAfn04(0x04, 0, 7, array, 24, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)setF9:(id)sender {
    [self.activityView setHidden:NO];
    
    XL_UINT8 index=0;
    
    XL_UINT8 apn_[8];
    int inTemp = [self.v1.text integerValue];
    apn_[index++] = inTemp;
    inTemp =[self.v2.text integerValue];
    apn_[index++] = inTemp;
    inTemp =[self.v3.text integerValue];
    apn_[index++] = inTemp;
    inTemp =[self.v4.text integerValue];
    apn_[index++] = inTemp;
    inTemp =[self.v5.text integerValue];
    apn_[index++] = inTemp;
    inTemp =[self.v6.text integerValue];
    apn_[index++] = inTemp;
    inTemp =[self.v7.text integerValue];
    apn_[index++] = inTemp;
    inTemp =[self.v8.text integerValue];
    apn_[index++] = inTemp;
    
    XL_UINT8 apn1_[8];
    index = 0;
    inTemp =[self.v9.text integerValue];
    apn1_[index++] = inTemp;
    inTemp =[self.v10.text integerValue];
    apn1_[index++] = inTemp;
    inTemp =[self.v11.text integerValue];
    apn1_[index++] = inTemp;
    inTemp =[self.v12.text integerValue];
    apn1_[index++] = inTemp;
    inTemp =[self.v13.text integerValue];
    apn1_[index++] = inTemp;
    inTemp =[self.v14.text integerValue];
    apn1_[index++] = inTemp;
    inTemp =[self.v15.text integerValue];
    apn1_[index++] = inTemp;
    inTemp =[self.v16.text integerValue];
    apn1_[index++] = inTemp;
    
    
    
    PACKITEM_P array[2] = {
        BuildPackItem(0, 0, 0, apn_, 8, 1, 0),
        BuildPackItem(0, 0, 0, apn1_, 8, 1, 0),
        
    };
    
    self.frame = PackFrameForAfn04(0x04, 0, 9, array, 2, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)setF10:(id)sender {
    [self.activityView setHidden:NO];
    
    XL_UINT8 commSpeedPort = 0;
    switch ([self.v3.text integerValue]) {
        case 600:
            commSpeedPort |= 0x20;
            break;
        case 1200:
            commSpeedPort |= 0x40;
            break;
        case 2400:
            commSpeedPort |= 0x60;
            break;
        case 4800:
            commSpeedPort |= 0x80;
            break;
        case 7200:
            commSpeedPort |= 0xA0;
            break;
        case 9600:
            commSpeedPort |= 0xC0;
            break;
        case 19200:
            commSpeedPort |= 0xE0;
            break;
            
        default:
            break;
    }
    XL_UINT8 commPort = [self.v4.text integerValue];
    if(commPort > 31 || commPort <=0)
    {
        commPort = 0;
    }
    commSpeedPort |= commPort;
    
    printf("密码=%d\n",[self.v7.text integerValue]);
    
    PACKITEM_P array[11] = {
        BuildPackItem(1, 2, 0, 0, 0, 0, 0),//设置测量点个数
        BuildPackItem([self.v1.text integerValue], 2, 0, 0, 0, 0, 0),//装置序号
        BuildPackItem([self.v2.text integerValue], 2, 0, 0, 0, 0, 0),//测量点号
        BuildPackItem(commSpeedPort, 1, 0, 0, 0, 0, 0),//通信速率和端口号
        BuildPackItem([self.v5.text integerValue], 1, 0, 0, 0, 0, 0),//通信协议类型
        BuildPackItem([self.v6.text integerValue], 6, 0, 0, 0, 0, 1),//通信地址
        BuildPackItem([self.v7.text integerValue], 6, 0, 0, 0, 0, 0),//通信密码
        BuildPackItem([self.v8.text integerValue], 1, 0, 0, 0, 0, 0),//电能费率个数
        BuildPackItem([self.v9.text integerValue], 1, 0, 0, 0, 0, 0),//有功电能示值整数和小数位数
        BuildPackItem([self.v10.text integerValue], 6, 0, 0, 0, 0, 1),//所属采集器通信地址
        BuildPackItem([self.v11.text integerValue], 1, 0, 0, 0, 0, 0),//大类号和小类号
        
        
    };
    
    self.frame = PackFrameForAfn04(0x04, 0, 10, array, 11, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)setF1:(id)sender {
    [self.activityView setHidden:NO];
    
    
    PACKITEM_P array[6] = {
        BuildPackItem([self.v1.text integerValue], 1, 0, 0, 0, 0, 0),//数传机延时时间
        BuildPackItem([self.v2.text integerValue], 1, 0, 0, 0, 0, 0),//终端作为启动站发送传输延时时间
        BuildPackItem([self.v3.text integerValue], 1, 0, 0, 0, 0, 0),//终端等待从动站相应延时时间
        BuildPackItem(([self.v4.text integerValue]<<4) & 0x30, 1, 0, 0, 0, 0, 0),//重发次数
        BuildPackItem([self.v5.text integerValue], 1, 0, 0, 0, 0, 0),//需要主站确认的通信通知服务标志
        BuildPackItem([self.v6.text integerValue], 1, 0, 0, 0, 0, 0),//心跳周期
        
    };
    
    self.frame = PackFrameForAfn04(0x04, 0, 1, array, 6, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)setF12:(id)sender {
    [self.activityView setHidden:NO];
    
    PACKITEM_P array[2] = {
        BuildPackItem([self.v1.text integerValue], 1, 0, 0, 0, 0, 0),//状态量接入标志位
        BuildPackItem([self.v2.text integerValue], 1, 0, 0, 0, 0, 0),//状态量变位标志位
        
    };
    
    self.frame = PackFrameForAfn04(0x04, 0, 12, array, 2, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)setF16:(id)sender {
    [self.activityView setHidden:NO];
    
    NSString *vpnUserName = self.v1.text;
    XL_UINT8 vpnUserName_[32];
    
    for(int i = 0;i<32;i++){
        if ([vpnUserName length]-1<i) {
            vpnUserName_[i] = '\0';
        }else{
            vpnUserName_[i] = (XL_UINT8)[vpnUserName characterAtIndex:i];
        }
    }
    NSString *vpnPw = self.v2.text;
    XL_UINT8 vpnPw_[32];
    
    for(int i = 0;i<32;i++){
        if ([vpnPw length]-1<i) {
            vpnPw_[i] = '\0';
        }else{
            vpnPw_[i] = (XL_UINT8)[vpnPw characterAtIndex:i];
        }
    }
    
    PACKITEM_P array[2] = {
        BuildPackItem(0, 0, 0, vpnUserName_, 32, 1, 0),
        BuildPackItem(0, 0, 0, vpnPw_, 32, 1, 0),
        
    };
    
    
    self.frame = PackFrameForAfn04(0x04, 0, 16, array, 2, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}
@end
