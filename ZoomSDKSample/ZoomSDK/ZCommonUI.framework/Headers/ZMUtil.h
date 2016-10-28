//
//  ZMUtil.h
//  ZCommonUI
//
//  Created by John on 10/26/16.
//  Copyright (c) 2016 zoom. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ZMUtil : NSObject

//change key event to mouse event, change menu location
+ (NSEvent*)newEventWithEvent:(NSEvent*)inOldEvent newLocation:(NSPoint)inNewLocation;
@end
