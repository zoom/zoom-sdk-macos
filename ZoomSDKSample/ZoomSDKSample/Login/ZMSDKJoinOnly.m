//
//  ZMSDKJoinOnly.m
//  ZoomSDKSample
//
//  Created by derain on 2018/11/19.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import "ZMSDKJoinOnly.h"

@implementation ZMSDKJoinOnly

- (id)initWithWindowController:(ZMSDKLoginWindowController*)loginWindowController
{
    self = [super init];
    if(self)
    {
        _loginWindowController = loginWindowController;
        return self;
    }
    return nil;
}

-(void)cleanUp
{
}
- (void)dealloc
{
    [self cleanUp];
    [super dealloc];
}
- (ZoomSDKError)joinMeetingOnly:(NSString*)meetingNumber displayName:(NSString*)userName meetingPSW:(NSString*)pwd
{
    if(meetingNumber.length <= 0)
        return ZoomSDKError_InvalidPrameter;
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [_loginWindowController createMainWindow];
    [_loginWindowController.mainWindowController.window close];
    ZoomSDKError ret = [meetingService joinMeeting:ZoomSDKUserType_APIUser toke4enfrocelogin:nil webinarToken:nil participantId:nil meetingNumber:meetingNumber displayName:userName password:pwd isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO vanityID:nil];
    return ret;
}

@end
