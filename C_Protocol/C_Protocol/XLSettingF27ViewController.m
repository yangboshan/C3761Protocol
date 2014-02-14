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
     PACKITEM_P array[12];
    
    
    PACKITEM_P item;
    
    item.value1 = [self.Ra.text integerValue];
    item.value1blen = 2;//字节长度
    item.value1dlen = 3;//小数长度
    item.shouldUseValue2 = 0;
    item.shouldUseBcd = 1; //是否bcd编码 0：十六进制 1:bcd
    array[0] = item;
    
    PACKITEM_P item1;
    item1.value1 = [self.Xa.text integerValue];
    item1.value1blen = 2;//字节长度
    item1.value1dlen = 3;//小数长度
    item1.shouldUseValue2 = 0;
    item1.shouldUseBcd = 1;
    array[1] = item1;
    
    PACKITEM_P item2;
    item2.value1 = [self.Ga.text integerValue];
    item2.value1blen = 2;//字节长度
    item2.value1dlen = 3;//小数长度
    item2.shouldUseValue2 = 0;
    item2.shouldUseBcd = 1;
    array[2] = item2;
    
    PACKITEM_P item3;
    item3.value1 = [self.Ba.text integerValue];
    item3.value1blen = 2;//字节长度
    item3.value1dlen = 3;//小数长度
    item3.shouldUseValue2 = 0;
    item3.shouldUseBcd = 1;
    array[3] = item3;
    
    
    
    PACKITEM_P item4;
    item4.value1 = [self.Rb.text integerValue];
    item4.value1blen = 2;//字节长度
    item4.value1dlen = 3;//小数长度
    item4.shouldUseValue2 = 0;
    item4.shouldUseBcd = 1;
    array[4] = item4;
    
    
    PACKITEM_P item5;
    item5.value1 = [self.Xb.text integerValue];
    item5.value1blen = 2;//字节长度
    item5.value1dlen = 3;//小数长度
    item5.shouldUseValue2 = 0;
    item5.shouldUseBcd = 1;
    array[5] = item5;
    
    
    PACKITEM_P item6;
    item6.value1 = [self.Gb.text integerValue];
    item6.value1blen = 2;//字节长度
    item6.value1dlen = 3;//小数长度
    item6.shouldUseValue2 = 0;
    item6.shouldUseBcd = 1;
    array[6] = item6;
    
    PACKITEM_P item7;
    item7.value1 = [self.Bb.text integerValue];
    item7.value1blen = 2;//字节长度
    item7.value1dlen = 3;//小数长度
    item7.shouldUseValue2 = 0;
    item7.shouldUseBcd = 1;
    array[7] = item7;
    
    
    PACKITEM_P item8;
    item8.value1 = [self.Rc.text integerValue];
    item8.value1blen = 2;//字节长度
    item8.value1dlen = 3;//小数长度
    item8.shouldUseValue2 = 0;
    item8.shouldUseBcd = 1;
    array[8] = item8;
    
    
    PACKITEM_P item9;
    item9.value1 = [self.Xc.text integerValue];
    item9.value1blen = 2;//字节长度
    item9.value1dlen = 3;//小数长度
    item9.shouldUseValue2 = 0;
    item9.shouldUseBcd = 1;
    array[9] = item9;
    
    
    PACKITEM_P item10;
    item10.value1 = [self.Gc.text integerValue];
    item10.value1blen = 2;//字节长度
    item10.value1dlen = 3;//小数长度
    item10.shouldUseValue2 = 0;
    item10.shouldUseBcd = 1;
    array[10] = item10;
    
    
    
    PACKITEM_P item11;
    item11.value1 = [self.Bc.text integerValue];
    item11.value1blen = 2;//字节长度
    item11.value1dlen = 3;//小数长度
    item11.shouldUseValue2 = 0;
    item11.shouldUseBcd = 1;
    array[11] = item11;
    
    
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
