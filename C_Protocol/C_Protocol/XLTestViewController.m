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

#define NoPara 0
#define YearMonth 1
#define YearMonthDay 2
#define CurveData 3
#define EventData 4

#define DataType1 @"1"
#define DataType2 @"2"
#define DataType3 @"3"

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
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(afn0:) name:@"SPEHANDLE" object:nil];
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(touch)];
    [tap setNumberOfTouchesRequired:1];
    [self.view addGestureRecognizer:tap];
    [self.indicatorView setHidden:YES];
}

-(void)afn0:(NSNotification*)notify{
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        NSData *data = [[NSUserDefaults standardUserDefaults] objectForKey:@"data"];
        if (data) {
            NSString *desc = [NSString stringWithFormat:@"返回报文:%@",[data description]];
            self.frameOriginal.text = desc;
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
 
        [self.indicatorView stopAnimating];
        [self.indicatorView setHidden:YES];
    });
}

-(void) touch{
    [self.view findAndResignFirstResponder];
}


-(void)response:(NSNotification*)notify{
    

    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        NSData *data = [[NSUserDefaults standardUserDefaults] objectForKey:@"data"];
        if (data) {
            NSString *desc = [NSString stringWithFormat:@"返回报文:%@",[data description]];
            self.frameOriginal.text = desc;
        }
        
        NSDictionary* dcs = notify.userInfo;
        NSString *key = [[dcs allKeys] objectAtIndex:0];
        NSDictionary *dic = [dcs valueForKey:key];
        self.textView.text = [dic description];
        
        [self.indicatorView stopAnimating];
        [self.indicatorView setHidden:YES];
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
    if (type == NoPara) {
        self.frame = PackFrameWithDadt(afn, pn, fn, &_outlen);
        
    }else if(type == YearMonth){
        self.frame = PackFrameWithTdm(afn, pn, fn, year, month, &_outlen);
        
    }else if(type == YearMonthDay){
        self.frame = PackFrameWithTdd(afn, pn, fn, year, month, day,&_outlen);
        
    }else if(type == CurveData){
        self.frame = PackFrameWithTdc(afn, pn, fn, year, month, day, 0, 0, 1, 60, &_outlen);
        
    } else {
        self.frame = PackFrameForEvent(afn, pn, fn, 0, 5, &_outlen);
        
    }
}

- (IBAction)sendData:(id)sender {
    
    [self.indicatorView setHidden:NO];
    [self.indicatorView startAnimating];
    self.textView.text = @"";
    self.frameOriginal.text = @"";
    
    [[NSUserDefaults standardUserDefaults] setObject:nil forKey:@"data"];
 
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
    
    if ([self.afnType.text isEqualToString:DataType1]) {
        afn = AFN0C;
    }
    if ([self.afnType.text isEqualToString:DataType2]) {
        afn = AFN0D;
    }
    if ([self.afnType.text isEqualToString:DataType3]) {
        afn = AFN0E;
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
