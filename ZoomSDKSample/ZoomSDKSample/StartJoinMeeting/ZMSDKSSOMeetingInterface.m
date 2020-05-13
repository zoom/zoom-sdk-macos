//
//  ZMSDKSSOMeetingInterface.m
//  ZoomSDKSample
//
//  Created by derain on 2018/11/26.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import "ZMSDKSSOMeetingInterface.h"

@implementation ZMSDKSSOMeetingInterface
- (id)init
{
    self = [super init];
    if(self)
    {
        return self;
    }
    return nil;
}

-(void)cleanUp
{
    return;
}
- (void)dealloc
{
    [self cleanUp];
    [super dealloc];
}
- (ZoomSDKError)startVideoMeetingForSSOUser
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    if (meetingService)
    {
        ZoomSDKError ret = [meetingService startMeeting:ZoomSDKUserType_SSOUser userID:nil userToken:nil displayName:nil meetingNumber:0 isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO vanityID:nil];
        return ret;
    }
    return ZoomSDKError_Failed;
}
- (ZoomSDKError)startAudioMeetingForSSOUser
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    if (meetingService)
    {
        ZoomSDKError ret = [meetingService startMeeting:ZoomSDKUserType_SSOUser userID:nil userToken:nil displayName:nil meetingNumber:0 isDirectShare:NO sharedApp:0 isVideoOff:YES isAuidoOff:NO vanityID:nil];
        return ret;
    }
    return ZoomSDKError_Failed;
}
- (ZoomSDKError)joinMeetingForSSOUser:(NSString*)meetingNumber displayName:(NSString*)name password:(NSString*)psw
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    if (meetingService && meetingNumber.length > 0)
    {
        ZoomSDKError ret = [meetingService joinMeeting:ZoomSDKUserType_SSOUser toke4enfrocelogin:nil webinarToken:nil participantId:@"" meetingNumber:meetingNumber displayName:name password:psw isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO vanityID:nil];
        return ret;
    }
    return ZoomSDKError_Failed;
}

@end
