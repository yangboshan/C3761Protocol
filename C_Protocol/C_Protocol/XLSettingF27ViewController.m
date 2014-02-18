//
//  XLSettingF27ViewController.m
//  C_Protocol
//
//  Created by admin on 14-2-12.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import "XLSettingF27ViewController.h"
#import "XLSocketManager.h"
#import "XL3761PackFrame.h"
#import "UIView+UIView___FindAndResignFirstResponder.h"
#import  "XLDataItem.h"
@interface XLSettingF27ViewController ()

@property(nonatomic,assign) Byte* frame;
@property(nonatomic,strong) NSData *data;
@property(nonatomic,assign) XL_UINT16 outlen;


@end

@implementation XLSettingF27ViewController

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
            self.ShowResult.text = @"确认帧";
        }
        
        if ([value isEqualToString:@"2"]) {
            self.ShowResult.text = @"否认帧";
        }
        
        if ([value isEqualToString:@"-1"]) {
            self.ShowResult.text = @"出现错误";
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

- (IBAction)set27:(id)sender {
    
    [self.activityView setHidden:NO];
    //设置参数
    PACKITEM_P array[12] = {
        BuildPackItem([self.Ra.text doubleValue], 2, 3, 0, 0, 0, 1),
        BuildPackItem([self.Xa.text doubleValue], 2, 3, 0, 0, 0, 1),
        BuildPackItem([self.Ga.text doubleValue], 2, 3, 0, 0, 0, 1),
        BuildPackItem([self.Ba.text doubleValue], 2, 3, 0, 0, 0, 1),
        
        BuildPackItem([self.Rb.text doubleValue], 2, 3, 0, 0, 0, 1),
        BuildPackItem([self.Xb.text doubleValue], 2, 3, 0, 0, 0, 1),
        BuildPackItem([self.Gb.text doubleValue], 2, 3, 0, 0, 0, 1),
        BuildPackItem([self.Bb.text doubleValue], 2, 3, 0, 0, 0, 1),
        
        BuildPackItem([self.Rc.text doubleValue], 2, 3, 0, 0, 0, 1),
        BuildPackItem([self.Xc.text doubleValue], 2, 3, 0, 0, 0, 1),
        BuildPackItem([self.Gc.text doubleValue], 2, 3, 0, 0, 0, 1),
        BuildPackItem([self.Bc.text doubleValue], 2, 3, 0, 0, 0, 1)
    };
  
    //组帧发送
    self.frame = PackFrameForAfn04(0x04, 1, 27, array, 12, &_outlen);
    self.data = [NSData dataWithBytes:self.frame length:self.outlen];
    NSLog(@"%@",[self.data description]);
    
    free(self.frame);
    [[XLSocketManager sharedXLSocketManager] packRequestFrame:self.data];
    
    
    
    
}
- (IBAction)return:(id)sender {
    //返回
    [self dismissViewControllerAnimated:YES completion:nil];
    
}
@end
