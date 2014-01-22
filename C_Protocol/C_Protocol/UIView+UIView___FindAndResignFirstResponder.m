//
//  UIView+UIView___FindAndResignFirstResponder.m
//  XLDistributionBoxApp
//
//  Created by JY on 13-8-1.
//  Copyright (c) 2013年 XLDZ. All rights reserved.
//

#import "UIView+UIView___FindAndResignFirstResponder.h"

@implementation UIView (UIView___FindAndResignFirstResponder)

- (BOOL)findAndResignFirstResponder
{
    if (self.isFirstResponder) {
        [self resignFirstResponder];
        return YES;
    }
    for (UIView *subView in self.subviews) {
        if ([subView findAndResignFirstResponder])
            return YES;
    }
    return NO;
}
@end

