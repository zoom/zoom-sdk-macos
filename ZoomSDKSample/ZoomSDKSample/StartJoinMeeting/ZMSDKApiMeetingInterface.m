//
//  ZMSDKApiMeetingInterface.m
//  ZoomSDKSample
//
//  Created by derain on 2018/11/29.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import "ZMSDKApiMeetingInterface.h"
#import "ZMSDKMainWindowController.h"

@implementation ZMSDKApiMeetingInterface
- (id)initWithWindowController:(ZMSDKMainWindowController*)mainWindowController
{
    self = [super init];
    if(self)
    {
        _mainWindowController = mainWindowController;
        return self;
    }
    return nil;
}

-(void)cleanUp
{
    if(_mainWindowController)
    {
        _mainWindowController = nil;
    }
}
- (void)dealloc
{
    [self cleanUp];
    [super dealloc];
}
- (ZoomSDKError)startVideoMeetingForApiUser;
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    if (meetingService && _mainWindowController.apiUserInfo)
    {
        ZoomSDKError ret = [meetingService startMeetingWithZAK:_mainWindowController.apiUserInfo.zak userType:SDKUserType_APIUser userID:_mainWindowController.apiUserInfo.userID userToken:_mainWindowController.apiUserInfo.userToken displayName:@"ee" meetingNumber:0 isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO vanityID:nil];
        return ret;
    }
    return ZoomSDKError_Failed;
}
- (ZoomSDKError)startAudioMeetingForApiUser
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    if (meetingService && _mainWindowController.apiUserInfo)
    {
        ZoomSDKError ret = [meetingService startMeetingWithZAK:_mainWindowController.apiUserInfo.zak userType:SDKUserType_APIUser userID:_mainWindowController.apiUserInfo.userID userToken:_mainWindowController.apiUserInfo.userToken displayName:@"tt" meetingNumber:0 isDirectShare:NO sharedApp:0 isVideoOff:YES isAuidoOff:NO vanityID:nil];
        return ret;
    }
    return ZoomSDKError_Failed;
}
- (ZoomSDKError)joinMeetingForApiUser:(NSString*)meetingNumber displayName:(NSString*)name password:(NSString*)psw
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    if (meetingService && meetingNumber.length > 0)
    {
        ZoomSDKError ret = [meetingService joinMeeting:ZoomSDKUserType_APIUser toke4enfrocelogin:nil webinarToken:nil participantId:nil meetingNumber:meetingNumber displayName:name password:psw isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO vanityID:nil];
        return ret;
    }
    return ZoomSDKError_Failed;
}

@end
