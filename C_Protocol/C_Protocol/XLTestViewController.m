//
//  XLTestViewController.m
//  C_Protocol
//
//  Created by JY on 14-1-21.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import "XLTestViewController.h"
#import "XLSocketManager.h"
#import "XL3761PackFrame.h"
#import "UIView+UIView___FindAndResignFirstResponder.h"

@interface XLTestViewController ()

@property(nonatomic,assign) Byte* frame;
@property(nonatomic,strong) NSData *data;
@property(nonatomic,assign) XL_UINT16 outlen;
@end

@implementation XLTestViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(response:) name:@"test" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(afn0:) name:@"afn0" object:nil];
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(touch)];
    [tap setNumberOfTouchesRequired:1];
    [self.view addGestureRecognizer:tap];
}

-(void)afn0:(NSNotification*)notify{
    
    dispatch_async(dispatch_get_main_queue(), ^{
        NSDictionary* dcs = notify.userInfo;
        NSString *value = [dcs valueForKey:@"key"];
        
        if ([value isEqualToString:@"2"]) {
            self.textView.text = @"确认帧";
        }
 
        if ([value isEqualToString:@"3"]) {
            self.textView.text = @"否认帧";
        }
 
    });
}

-(void) touch{
    [self.view findAndResignFirstResponder];
}


-(void)response:(NSNotification*)notify{
    
    dispatch_async(dispatch_get_main_queue(), ^{
        NSDictionary* dcs = notify.userInfo;
        NSString *key = [[dcs allKeys] objectAtIndex:0];
        NSDictionary *dic = [dcs valueForKey:key];
        self.textView.text = [dic description];
    });
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

-(void)getframedata:(NSInteger)type
                    :(Byte)afn
                    :(NSInteger)fn
                    :(NSInteger)pn
                    :(NSInteger)year
                    :(NSInteger)month
                    :(NSInteger)day
{
    if (type == 0) {
        self.frame = PackFrameWithDadt(afn, pn, fn, &_outlen);
        
    }else if(type == 1){
        self.frame = PackFrameWithTdm(afn, pn, fn, year, month, &_outlen);
        
    }else if(type == 2){
        self.frame = PackFrameWithTdd(afn, pn, fn, year, month, day,&_outlen);
    }else if(type == 3){
        self.frame = PackFrameWithTdc(afn, pn, fn, year, month, day, 0, 0, 1, 60, &_outlen);
    } else {
        self.frame = PackFrameForEvent(afn, pn, fn, 0, 5, &_outlen);
        
    }
}

- (IBAction)sendData:(id)sender {
    
    self.textView.text = @"";
 
    Byte afn;
    XL_UINT8 fn;
    XL_UINT8 pn;
    XL_UINT8 year;
    XL_UINT8 month;
    XL_UINT8 day;
    
    fn =    [self.fn.text integerValue];
    pn =    [self.pn.text integerValue];
    year =  [self.year.text integerValue];
    month = [self.month.text integerValue];
    day =   [self.day.text integerValue];
    
    if ([self.afnType.text isEqualToString:@"1"]) {
        afn = 0x0c;
    }
    if ([self.afnType.text isEqualToString:@"2"]) {
        afn = 0x0d;
    }
    if ([self.afnType.text isEqualToString:@"3"]) {
        afn = 0x0e;
    }
    
    NSInteger type = self.dataType.selectedSegmentIndex;
    
//    if (type == 0) {
//        self.frame = PackFrameWithDadt(afn, pn, fn, &_outlen);
//        
//    }else if(type == 1){
//        self.frame = PackFrameWithTdm(afn, pn, fn, year, month, &_outlen);
//        
//    }else if(type == 2){
//        self.frame = PackFrameWithTdd(afn, pn, fn, year, month, day,&_outlen);
//        
//    } else {
//        self.frame = PackFrameForEvent(afn, pn, fn, 0, 5, &_outlen);
//        
//    }
    
//    Byte temp[self.outlen];
//    memset(temp, 0, self.outlen);
//    memcpy(temp, self.frame, self.outlen);
    
    [self getframedata:type :afn :fn :pn :year :month :day];
    
  
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
 
    
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
}
- (IBAction)clear:(id)sender {
    self.textView.text = @"";
}
@end
