//
//  XLSettingF26ViewController.m
//  C_Protocol
//
//  Created by admin on 14-2-12.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import "XLSettingF26ViewController.h"
#import "XLSocketManager.h"
#import "XL3761PackFrame.h"
#import "UIView+UIView___FindAndResignFirstResponder.h"
#import  "XLDataItem.h"

@interface XLSettingF26ViewController ()

@property(nonatomic,assign) Byte* frame;
@property(nonatomic,strong) NSData *data;
@property(nonatomic,assign) XL_UINT16 outlen;
@end

@implementation XLSettingF26ViewController

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
}

-(void)afn0:(NSNotification*)notify{
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
//        NSData *data = [[NSUserDefaults standardUserDefaults] objectForKey:@"data"];
//        if (data) {
//            NSString *desc = [NSString stringWithFormat:@"返回报文:%@",[data description]];
//            self.frameOriginal.text = desc;
//        }
        
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
}

- (IBAction)setF26:(id)sender {
    
    PACKITEM_P array[31] = {
        BuildPackItem([self.v1.text doubleValue], 2, 1, nil, 0, 0, 1),
        BuildPackItem([self.v2.text doubleValue], 2, 1, nil, 0, 0, 1),
        BuildPackItem([self.v3.text doubleValue], 2, 1, nil, 0, 0, 1),
        
        BuildPackItem([self.v4.text doubleValue], 2, 1, nil, 0, 0, 1),
        BuildPackItem([self.v5.text integerValue],1, 0, nil, 0, 0, 0),
        BuildPackItem([self.v6.text doubleValue],2, 1, nil, 0, 0, 1),
        
        BuildPackItem([self.v7.text doubleValue], 2, 1, nil, 0, 0, 1),
        BuildPackItem([self.v8.text integerValue],1, 0, nil, 0, 0, 0),
        BuildPackItem([self.v9.text doubleValue],2, 1, nil, 0, 0, 1),
        
        BuildPackItem([self.v10.text doubleValue], 3, 3 , nil, 0, 0, 1),
        BuildPackItem([self.v11.text integerValue],1, 0, nil, 0, 0, 0),
        BuildPackItem([self.v12.text doubleValue],2, 1, nil, 0, 0, 1),
        
        BuildPackItem([self.v13.text doubleValue], 3, 3 , nil, 0, 0, 1),
        BuildPackItem([self.v14.text integerValue],1, 0, nil, 0, 0, 0),
        BuildPackItem([self.v15.text doubleValue],2, 1, nil, 0, 0, 1),
        
        BuildPackItem([self.v16.text doubleValue], 3, 3 , nil, 0, 0, 1),
        BuildPackItem([self.v17.text integerValue],1, 0, nil, 0, 0, 0),
        BuildPackItem([self.v18.text doubleValue],2, 1, nil, 0, 0, 1),
        
        BuildPackItem([self.v19.text doubleValue], 3, 4 , nil, 0, 0, 1),
        BuildPackItem([self.v20.text integerValue],1, 0, nil, 0, 0, 0),
        BuildPackItem([self.v21.text doubleValue],2, 1, nil, 0, 0, 1),
        
        BuildPackItem([self.v22.text doubleValue], 3, 4 , nil, 0, 0, 1),
        BuildPackItem([self.v23.text integerValue],1, 0, nil, 0, 0, 0),
        BuildPackItem([self.v24.text doubleValue],2, 1, nil, 0, 0, 1),
        
        BuildPackItem([self.v25.text doubleValue], 2, 1 , nil, 0, 0, 1),
        BuildPackItem([self.v26.text integerValue],1, 0, nil, 0, 0, 0),
        BuildPackItem([self.v27.text doubleValue],2, 1, nil, 0, 0, 1),
        
        BuildPackItem([self.v28.text doubleValue], 2, 1 , nil, 0, 0, 1),
        BuildPackItem([self.v29.text integerValue],1, 0, nil, 0, 0, 0),
        BuildPackItem([self.v30.text doubleValue],2, 1, nil, 0, 0, 1),
        
        BuildPackItem([self.v31.text integerValue],1, 0, nil, 0, 0, 0),
    };
 
//    XL_UINT8  value[64];value[0] = 0x06;
//    PACKITEM_P item5 = BuildPackItem(0, 0, 0, value, 1, 1, 0);

    self.frame = PackFrameForAfn04(0x04, 1, 26, array, 31, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)return:(id)sender {
     [self dismissViewControllerAnimated:YES completion:nil];
}
@end
