//
//  XLMenuViewController.m
//  C_Protocol
//
//  Created by JY on 14-2-11.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#import "XLMenuViewController.h"

@interface XLMenuViewController ()

@end

@implementation XLMenuViewController

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
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)query:(id)sender {
    
    [self performSegueWithIdentifier:@"menutodetail" sender:nil];
}

- (IBAction)set:(id)sender {
    [self performSegueWithIdentifier:@"setting" sender:nil];
}

- (IBAction)setF27:(id)sender {
        [self performSegueWithIdentifier:@"setF27" sender:nil];
}

- (IBAction)setF26:(id)sender {
          [self performSegueWithIdentifier:@"setF26" sender:nil];
    
}
@end
