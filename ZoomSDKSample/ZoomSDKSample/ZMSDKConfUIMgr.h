//
//  ZMSDKConfUIMgr.h
//  ZoomSDKSample
//
//  Created by derain on 2018/12/5.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZMSDKMeetingMainWindowController.h"
#import "ZMSDKUserHelper.h"
@class ZoomSDKWindowController;

@interface ZMSDKConfUIMgr : NSObject
{
    ZMSDKMeetingMainWindowController* _meetingMainWindowController;
    ZMSDKUserHelper* _userHelper;
}
@property(nonatomic, retain, readwrite)ZMSDKMeetingMainWindowController *meetingMainWindowController;
@property(nonatomic, retain, readwrite)ZMSDKUserHelper *userHelper;

+ (ZMSDKConfUIMgr*)sharedConfUIMgr;
+ (void)initConfUIMgr;
+ (void)uninitConfUIMgr;
- (void)createMeetingMainWindow;
- (ZMSDKUserHelper*)getUserHelper;
- (ZMSDKMeetingMainWindowController*)getMeetingMainWindowController;
- (int)getSystemVersion;
@end
