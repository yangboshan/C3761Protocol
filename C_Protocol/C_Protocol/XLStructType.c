//
//  XLStructType.c
//  C_Protocol
//
//  Created by JY on 14-1-13.
//  Copyright (c) 2014年 XLDZ. All rights reserved.
//

#include <stdio.h>
#include "XLStructType.h"


CMSTRUCT buildstruct(int type){
    
    CMSTRUCT cmstruct;
    
    switch (type) {
        case 49:{
            AFNDF49 afndf49;
            cmstruct._size = sizeof(afndf49);
            cmstruct._struct = &afndf49;
        }
            break;
        case 51:{
 
        }
            break;
        default:
            break;
    }
    return cmstruct;
}