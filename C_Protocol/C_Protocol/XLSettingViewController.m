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
    
    PACKITEM_P array[6];
    
    PACKITEM_P item = BuildPackItem([self.m1.text integerValue], 2, 0, nil, 0, 0, 0);
//    item.value1 = [self.m1.text integerValue];
//    item.value1blen = 2;
//    item.value1dlen = 0;
//    item.shouldUseValue2 = 0;
//    item.shouldUseBcd = 0;
    array[0] = item;
    
    
    PACKITEM_P item1 = BuildPackItem([self.m2.text integerValue], 2, 0, nil, 0, 0, 0);
//    item1.value1 = [self.m2.text integerValue];
//    item1.value1blen = 2;
//    item1.value1dlen = 0;
//    item1.shouldUseValue2 = 0;
//    item1.shouldUseBcd = 0;
    array[1] = item1;
    
    
    PACKITEM_P item2 = BuildPackItem([self.v.text doubleValue], 2, 1, nil, 0, 0, 1);
//    item2.value1 = [self.v.text doubleValue];
//    item2.value1blen = 2;
//    item2.value1dlen = 1;
//    item2.shouldUseValue2 = 0;
//    item2.shouldUseBcd = 1;
    array[2] = item2;
    
    
    PACKITEM_P item3 = BuildPackItem([self.c.text doubleValue], 1, 1, nil, 0, 0, 1);
//    item3.value1 = [self.c.text doubleValue];
//    item3.value1blen = 1;
//    item3.value1dlen = 1;
//    item3.shouldUseValue2 = 0;
//    item3.shouldUseBcd = 1;
    array[3] = item3;
    
    PACKITEM_P item4 = BuildPackItem([self.l.text doubleValue], 3, 4, nil, 0, 0, 1);
//    item4.value1 = [self.l.text doubleValue];
//    item4.value1blen = 3;
//    item4.value1dlen = 4;
//    item4.shouldUseValue2 = 0;
//    item4.shouldUseBcd = 1;
    array[4] = item4;
    
    XL_UINT8  value[64];value[0] = 0x06;
    
    PACKITEM_P item5 = BuildPackItem(0, 0, 0, value, 1, 1, 0);
//    item5.value2blen = 1;
//    item5.value2[0] = 0x06;
//    item5.shouldUseValue2 = 1;
    array[5] = item5;
    
    self.frame = PackFrameForAfn04(0x04, 1, 25, array, 6, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}
@end
