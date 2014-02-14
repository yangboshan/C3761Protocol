//
//  XLSetClockViewController.h
//  C_Protocol
//
//  Created by JY on 14-2-14.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface XLSetClockViewController : UIViewController

@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *activityView;
@property (weak, nonatomic) IBOutlet UITextView *showResult;

- (IBAction)setClock:(id)sender;
- (IBAction)home:(id)sender;

@end
