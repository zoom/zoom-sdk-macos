//
//  ZMSDKUserHelper.m
//  ZoomSDKSample
//
//  Created by derain on 2018/12/5.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import "ZMSDKUserHelper.h"
#import "ZMSDKConfUIMgr.h"

@implementation ZMSDKUserHelper

- (id)initWithWindowController:(ZMSDKMeetingMainWindowController*)meetingMainWindowController
{
    self = [super init];
    if(self)
    {
        _meetingService = [[ZoomSDK sharedSDK] getMeetingService];
        if(_meetingService)
        {
            _meetingActionController = [_meetingService getMeetingActionController];
            _meetingActionController.delegate = self;
        }
        _meetingMainWindowController = meetingMainWindowController;
        return self;
    }
    return nil;
}

-(void)cleanUp
{
    if(_meetingService)
    {
        _meetingActionController = [_meetingService getMeetingActionController];
        _meetingActionController.delegate = nil;
    }
}
- (void)dealloc
{
    [self cleanUp];
    [super dealloc];
}

- (void)onUserJoin:(NSArray*)array
{
    if(!array)
        return;
    for (NSNumber* item in array)
    {
        unsigned int userID = [item unsignedIntValue];
        [[[ZMSDKConfUIMgr sharedConfUIMgr] getMeetingMainWindowController] onUserJoin:userID];
    }
}

- (void)onUserLeft:(NSArray*)array
{
    if(!array)
        return;
    for (NSNumber* item in array)
    {
        unsigned int leftUserID = [item unsignedIntValue];
        [[[ZMSDKConfUIMgr sharedConfUIMgr] getMeetingMainWindowController] onUserleft:leftUserID];
    }
}

- (void)onUserInfoUpdate:(unsigned int)userID
{
    [[[ZMSDKConfUIMgr sharedConfUIMgr] getMeetingMainWindowController] onUserJoin:userID];
}

- (void)onHostChange:(unsigned int)userID
{
    return;
}

- (void)onCoHostChange:(unsigned int)userID
{
    return;
}

- (void)onSpotlightVideoUserChange:(BOOL)spotlight User:(unsigned int)userID
{
    return;
}
- (void)onVideoStatusChange:(BOOL)videoOn UserID:(unsigned int)userID
{
    [[[ZMSDKConfUIMgr sharedConfUIMgr] getMeetingMainWindowController] onUserVideoStatusChange:videoOn UserID:userID];
}
- (void)onActiveSpeakerChanged:(unsigned int)userID
{
    return;
}
- (void)onUserAudioStatusChange:(NSArray*)userAudioStatusArray
{
    [[[ZMSDKConfUIMgr sharedConfUIMgr] getMeetingMainWindowController] onUserAudioStatusChange:userAudioStatusArray];
}
- (void)onChatMessageNotification:(ZoomSDKChatInfo*)chatInfo
{
    return;
}
- (void)onLowOrRaiseHandStatusChange:(BOOL)raise UserID:(unsigned int)userID
{
    return;
}
- (void)onJoinMeetingResponse:(ZoomSDKJoinMeetingHelper*)joinMeetingHelper
{
    return;
}
- (void)onMultiToSingleShareNeedConfirm:(ZoomSDKMultiToSingleShareConfirmHandler*)confirmHandle
{
    NSLog(@"onMultiToSingleShareNeedConfirm in ZMSDKUserHelper");
    ZoomSDKMultiToSingleShareConfirmHandler* handle = confirmHandle;
    //[handle confirmSwitch];
    [handle cancelSwitch];
}
@end
