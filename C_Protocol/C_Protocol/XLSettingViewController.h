//
//  XLSettingViewController.h
//  C_Protocol
//
//  Created by JY on 14-2-11.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface XLSettingViewController : UIViewController

- (IBAction)home:(id)sender;
- (IBAction)set:(id)sender;
@property (weak, nonatomic) IBOutlet UITextField *m1;
@property (weak, nonatomic) IBOutlet UITextField *m2;
@property (weak, nonatomic) IBOutlet UITextField *v;
@property (weak, nonatomic) IBOutlet UITextField *c;
@property (weak, nonatomic) IBOutlet UITextField *l;
@property (weak, nonatomic) IBOutlet UITextField *type;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *activityView;
@property (weak, nonatomic) IBOutlet UITextView *textView;

@end
