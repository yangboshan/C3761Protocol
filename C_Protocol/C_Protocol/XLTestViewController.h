//
//  XLTestViewController.h
//  C_Protocol
//
//  Created by JY on 14-1-21.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface XLTestViewController : UIViewController

@property (weak, nonatomic) IBOutlet UITextField *afnType;
@property (weak, nonatomic) IBOutlet UITextField *pn;
@property (weak, nonatomic) IBOutlet UITextField *fn;
 
- (IBAction)sendData:(id)sender;
- (IBAction)home:(id)sender;
@property (weak, nonatomic) IBOutlet UITextField *year;
@property (weak, nonatomic) IBOutlet UITextField *month;
@property (weak, nonatomic) IBOutlet UITextField *day;
@property (weak, nonatomic) IBOutlet UISegmentedControl *dataType;


@property (weak, nonatomic) IBOutlet UITextView *textView;

@property (weak, nonatomic) IBOutlet UIScrollView *scrollView;
- (IBAction)clear:(id)sender;

@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *indicatorView;

@property (weak, nonatomic) IBOutlet UITextView *frameOriginal;

@end
