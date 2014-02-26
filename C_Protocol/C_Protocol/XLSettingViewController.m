//
//  XLSettingViewController.m
//  C_Protocol
//
//  Created by JY on 14-2-11.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import "XLSettingViewController.h"
#import "XLSocketManager.h"
#import "XL3761PackFrame.h"
#import "UIView+UIView___FindAndResignFirstResponder.h"
#import  "XLDataItem.h"


@interface XLSettingViewController ()

@property(nonatomic,assign) Byte* frame;
@property(nonatomic,strong) NSData *data;
@property(nonatomic,assign) XL_UINT16 outlen;

@end

@implementation XLSettingViewController

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
        
        NSData *data = [[NSUserDefaults standardUserDefaults] objectForKey:@"data"];
        if (data) {
//            NSString *desc = [NSString stringWithFormat:@"返回报文:%@",[data description]];
//            self.frameOriginal.text = desc;
        }
        
        NSDictionary* dcs = notify.userInfo;
        NSString *value = [dcs valueForKey:@"key"];
        
        if ([value isEqualToString:@"1"]) {
            self.textView.text = @"确认帧";
        }
        
        if ([value isEqualToString:@"2"]) {
            self.textView.text = @"否认帧";
        }
        
        if ([value isEqualToString:@"-1"]) {
            self.textView.text = @"出现错误";
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
    
    [self.activityView setHidden:NO];
    XL_UINT8  value[64];value[0] = 0x06;
    
    XL_UINT8 type = 0;
    NSRange range = [self.type.text rangeOfString:@"四"];
    if(range.length > 0)//三相四线
    {
        type |= 0x02;
    }
    else if([self.type.text rangeOfString:@"单"].length >0)
    {
        type |= 0x03;
    }
    else if([self.type.text rangeOfString:@"三"].length > 0)
    {
        type |= 0x01;
    }
    
    if([self.type.text rangeOfString:@"A"].length > 0)
    {
        type |= 0x4;
    }
    else if([self.type.text rangeOfString:@"B"].length > 0)
    {
        type |= 0x8;
    }
    else if([self.type.text rangeOfString:@"C"].length > 0)
    {
        type |= 0xC;
    }
    
    PACKITEM_P array[6] = {BuildPackItem([self.m1.text integerValue], 2, 0, nil, 0, 0, 0),
        BuildPackItem([self.m2.text integerValue], 2, 0, nil, 0, 0, 0),
        BuildPackItem([self.v.text doubleValue], 2, 1, nil, 0, 0, 1),
        BuildPackItem([self.c.text doubleValue], 1, 1, nil, 0, 0, 1),
        BuildPackItem([self.l.text doubleValue], 3, 4, nil, 0, 0, 1),
        BuildPackItem(type, 1, 0, 0, 0, 0, 0),
    };
    
    self.frame = PackFrameForAfn04(0x04, 1, 25, array, 6, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}
@end
