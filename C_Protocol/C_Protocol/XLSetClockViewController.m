//
//  XLSetClockViewController.m
//  C_Protocol
//
//  Created by JY on 14-2-14.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import "XLSetClockViewController.h"
#import "XLSocketManager.h"
#import "XL3761PackFrame.h"
#import "UIView+UIView___FindAndResignFirstResponder.h"
#import  "XLDataItem.h"

@interface XLSetClockViewController ()

@property(nonatomic,assign) Byte* frame;
@property(nonatomic,strong) NSData *data;
@property(nonatomic,assign) XL_UINT16 outlen;
@end

@implementation XLSetClockViewController

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
	// Do any additional setup after loading the view.
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

- (IBAction)setClock:(id)sender {
    [self.activityView setHidden:NO];
    NSCalendar *calendar = [NSCalendar currentCalendar];
    
    NSDateComponents *components = [calendar components:(NSYearCalendarUnit|NSMonthCalendarUnit|
                                                         NSDayCalendarUnit|NSHourCalendarUnit|
                                                         NSMinuteCalendarUnit|NSSecondCalendarUnit|
                                                         NSWeekdayCalendarUnit)
                                               fromDate:[NSDate date]];

    //self.frame = PackFrameForClock(0x05, 0, 31, [components year]%2000,[components month], [components day], [components weekday]-1, [components hour], [components minute], [components second], &_outlen);
    self.frame = PackFrameForClock(0x05, 0, 31, [self.year.text integerValue],[self.month.text integerValue], [self.day.text integerValue], 3, [self.hour.text integerValue], [self.minute.text integerValue], [self.second.text integerValue], &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}

- (IBAction)home:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}
@end
