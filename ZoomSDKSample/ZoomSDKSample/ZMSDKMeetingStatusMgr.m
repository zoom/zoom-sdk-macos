//
//  ZMSDKMeetingStatusMgr.m
//  ZoomSDKSample
//
//  Created by derain on 2018/11/20.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import "ZMSDKMeetingStatusMgr.h"
#import "ZMSDKCommonHelper.h"
#import "ZMSDKLoginWindowController.h"
#import "ZMSDKJoinMeetingWindowController.h"
#import "ZMSDKMeetingMainWindowController.h"
#import "ZMSDKConfUIMgr.h"
#import "ZMSDKMeetingMainWindowController.h"

@interface ZMSDKMeetingStatusMgr()
@end

@implementation ZMSDKMeetingStatusMgr
- (id)initWithWindowController:(ZMSDKMainWindowController*)mainWindowController
{
    self = [super init];
    if(self)
    {
        if([ZMSDKCommonHelper sharedInstance].isUseCutomizeUI)
            [ZMSDKConfUIMgr initConfUIMgr];
        _meetingService = [[ZoomSDK sharedSDK] getMeetingService];
        _meetingService.delegate = self;
        _mainWindowController = mainWindowController;
        return self;
    }
    return nil;
}

-(void)cleanUp
{
    _meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    _meetingService.delegate = nil;
}
- (void)dealloc
{
    [self cleanUp];
    [super dealloc];
}

/**************ZoomSDKMeetingServiceDelegate***********/
- (void)onMeetingStatusChange:(ZoomSDKMeetingStatus)state meetingError:(ZoomSDKMeetingError)error EndReason:(EndMeetingReason)reason
{
    NSLog(@"MeetingStatus change %d", state);
    switch (state) {
        case ZoomSDKMeetingStatus_Connecting:
        {
            if([ZMSDKCommonHelper sharedInstance].isUseCutomizeUI)
            {
                [[ZMSDKConfUIMgr sharedConfUIMgr] createMeetingMainWindow];
            }
        }
            break;
        case ZoomSDKMeetingStatus_InMeeting:
        {
            if([ZMSDKCommonHelper sharedInstance].isUseCutomizeUI)
            {
                [[[ZMSDKConfUIMgr sharedConfUIMgr] getMeetingMainWindowController] updateInMeetingUI];
            }
            
            if(_mainWindowController)
            {
                if([_mainWindowController.loginWindowController.window isVisible])
                {
                    [_mainWindowController.loginWindowController close];
                }
                if([_mainWindowController.joinMeetingWindowController.window isVisible])
                {
                    [_mainWindowController.joinMeetingWindowController close];
                }
            }
            ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
            if (meetingService)
            {
                ZoomSDKMeetingActionController* meetingActionController = [meetingService getMeetingActionController];
                if(meetingActionController)
                {
                    [meetingActionController setShareSettingType:ShareSettingType_AnyoneCanGrab];
                }
            }
        }
            break;
        case ZoomSDKMeetingStatus_Webinar_Promote:
        case ZoomSDKMeetingStatus_Webinar_Depromote:
        case ZoomSDKMeetingStatus_AudioReady:
            break;
        case ZoomSDKMeetingStatus_Failed:
        {
            if (error == ZoomSDKMeetingError_PasswordError) {
                NSLog(@"Password is Wrong!");
            }
            else if(error == ZoomSDKMeetingError_RemovedByHost)
            {
                NSLog(@"Has been removed by host!");
            }
            if([ZMSDKCommonHelper sharedInstance].hasLogin)
            {
                [_mainWindowController showWindow:nil];
            }
            else
            {
                [_mainWindowController.loginWindowController showSelf];
            }
            [ZMSDKConfUIMgr uninitConfUIMgr];
        }
            break;
        case ZoomSDKMeetingStatus_Ended:
        {
            if([ZMSDKCommonHelper sharedInstance].isUseCutomizeUI)
            {
                [ZMSDKConfUIMgr uninitConfUIMgr];
            }
            if([ZMSDKCommonHelper sharedInstance].hasLogin)
            {
                [_mainWindowController showWindow:nil];
            }
            else
            {
                [_mainWindowController.loginWindowController showSelf];
            }
            switch (reason) {
                case EndMeetingReason_KickByHost:
                    NSLog(@"leave meeting kicked by host");
                    break;
                    
                case EndMeetingReason_EndByHost:
                    NSLog(@"leave meeting end by host");
                    break;
                default:
                    break;
            }
        }
        default:
        {
            
        }
            break;
    }
    [_mainWindowController updateMainWindowUIWithMeetingStatus:state];
}

- (void)onWaitMeetingSessionKey:(NSData*)key
{
    NSLog(@"Huawei Session key:%@", key);
    NSString* testVideoSessionKey =@"abcdefghijkmnopr";
    ZoomSDKSecuritySessionKey* sessionkey = [[[ZoomSDKSecuritySessionKey alloc] init] autorelease];
    sessionkey.component = SecuritySessionComponet_Video;
    sessionkey.sessionKey = [NSData dataWithBytes:(const char*)testVideoSessionKey.UTF8String length:16];
    sessionkey.iv = nil;
    NSArray* array = [NSArray arrayWithObjects:sessionkey, nil];
    [_meetingService setSecuritySessionKey:array isLeaveMeeting:NO];
}
- (void)onMeetingStatisticWarning:(StatisticWarningType)type
{
    
}

- (void)onPaymentReminder:(ZoomSDKUpgradeAccountHelper*)upgradeHelper
{
    
}

- (void)onFreeMeetingRemainTime:(unsigned int)seconds
{
    
}

@end
