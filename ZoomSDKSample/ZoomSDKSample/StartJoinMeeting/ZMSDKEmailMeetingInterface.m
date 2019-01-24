//
//  ZMSDKEmailMeetingInterface.m
//  ZoomSDKSample
//
//  Created by derain on 2018/11/26.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import "ZMSDKEmailMeetingInterface.h"

@implementation ZMSDKEmailMeetingInterface
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
    
}
- (void)dealloc
{
    [self cleanUp];
    [super dealloc];
}
- (ZoomSDKError)startVideoMeetingForEmailUser
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    if (meetingService)
    {
        ZoomSDKError ret = [meetingService startMeeting:ZoomSDKUserType_ZoomUser userID:nil userToken:nil displayName:nil meetingNumber:0 isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO vanityID:nil];
        return ret;
    }
    return ZoomSDKError_Failed;
}
- (ZoomSDKError)startAudioMeetingForEmailUser
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    if (meetingService)
    {
        ZoomSDKError ret = [meetingService startMeeting:ZoomSDKUserType_ZoomUser userID:nil userToken:nil displayName:nil meetingNumber:0 isDirectShare:NO sharedApp:0 isVideoOff:YES isAuidoOff:NO vanityID:nil];
        return ret;
    }
    return ZoomSDKError_Failed;
}
- (ZoomSDKError)joinMeetingForEmailUser:(NSString*)meetingNumber displayName:(NSString*)name password:(NSString*)psw
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    if (meetingService && meetingNumber.length > 0)
    {
        ZoomSDKError ret = [meetingService joinMeeting:ZoomSDKUserType_ZoomUser toke4enfrocelogin:nil webinarToken:nil participantId:@"" meetingNumber:meetingNumber displayName:name password:psw isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO vanityID:nil];
        return ret;
    }
    return ZoomSDKError_Failed;
}

@end
