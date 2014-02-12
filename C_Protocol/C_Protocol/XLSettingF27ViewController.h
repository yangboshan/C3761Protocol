//
//  XLSettingF27ViewController.h
//  C_Protocol
//
//  Created by admin on 14-2-12.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface XLSettingF27ViewController : UIViewController
@property (strong, nonatomic) IBOutlet UITextField *Ra;
@property (strong, nonatomic) IBOutlet UITextField *Xa;
@property (strong, nonatomic) IBOutlet UITextField *Ga;
@property (strong, nonatomic) IBOutlet UITextField *Ba;
@property (strong, nonatomic) IBOutlet UITextField *Rb;
@property (strong, nonatomic) IBOutlet UITextField *Xb;
@property (strong, nonatomic) IBOutlet UITextField *Gb;
@property (strong, nonatomic) IBOutlet UITextField *Bb;
@property (strong, nonatomic) IBOutlet UITextField *Rc;
@property (strong, nonatomic) IBOutlet UITextField *Xc;
@property (strong, nonatomic) IBOutlet UITextField *Gc;
@property (strong, nonatomic) IBOutlet UITextField *Bc;
- (IBAction)set27:(id)sender;
@property (strong, nonatomic) IBOutlet UITextView *ShowResult;
- (IBAction)return:(id)sender;

@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *activityView;

@end
