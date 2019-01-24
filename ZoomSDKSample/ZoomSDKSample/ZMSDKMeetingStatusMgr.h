//
//  ZMSDKMeetingStatusMgr.h
//  ZoomSDKSample
//
//  Created by derain on 2018/11/20.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDK.h"
#import "ZMSDKMainWindowController.h"
#import "ZoomSDKWindowController.h"

@interface ZMSDKMeetingStatusMgr : NSObject  <ZoomSDKMeetingServiceDelegate>
{
    ZMSDKMainWindowController* _mainWindowController;
    ZoomSDKMeetingService* _meetingService;
}
- (id)initWithWindowController:(ZMSDKMainWindowController*)mainWindowController;
@end
