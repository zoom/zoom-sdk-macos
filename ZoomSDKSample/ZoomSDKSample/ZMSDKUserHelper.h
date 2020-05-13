//
//  ZMSDKUserHelper.h
//  ZoomSDKSample
//
//  Created by derain on 2018/12/5.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDK.h"
#import "ZMSDKMeetingMainWindowController.h"
#import "ZoomSDKWindowController.h"

@interface ZMSDKUserHelper : NSObject <ZoomSDKMeetingActionControllerDelegate>
{
    ZMSDKMeetingMainWindowController*        _meetingMainWindowController;
    ZoomSDKMeetingService*                   _meetingService;
    ZoomSDKMeetingActionController*          _meetingActionController;

}

- (id)initWithWindowController:(ZMSDKMeetingMainWindowController*)meetingMainWindowController;

@end
