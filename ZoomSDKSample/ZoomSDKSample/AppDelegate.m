//
//  AppDelegate.m
//  ZoomSDKSample
//
//  Created by TOTTI on 7/20/16.
//  Copyright © 2016 TOTTI. All rights reserved.
//

#import "AppDelegate.h"
#import "ZoomSDKWindowController.h"
#import <time.h>


#define kZoomSDKDomain      @""
//#define kZoomSDKAppKey      @""
//#define kZoomSDKAppSecret   @""
#define kZoomSDKAppKey      @""
#define kZoomSDKAppSecret   @""
@interface AppDelegate ()
- (void) switchToZoomUserTab;
- (void) switchToMeetingTab;
@end

@implementation AppDelegate

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
    [_logoView setImage:[[NSBundle mainBundle] imageForResource:@"ZoomLogo"]];
    [_devZoomAuth setHidden:NO];
    [_authResultField setHidden:YES];
    [_authResultFieldWelcome setHidden:YES];
    [_recordConvertFinishLabel setHidden:YES];
    [_mainWindow setLevel:NSPopUpMenuWindowLevel];
    _mainWindow.delegate = self;
    [_chatButton setEnabled:NO];
    [_recordButton setEnabled:NO];
    [_shareButton setEnabled:NO];
    [_mainWindowButton setEnabled:NO];
    [_endMeeting setEnabled:NO];
    [_revokeRemoteControl setEnabled:NO];
    [_declineRemoteControl setEnabled:NO];
    [_preMeetingError setHidden:YES];
    [_listMeetingError setHidden:YES];
    [_preMeetingButton setEnabled:NO];
    [_logoutButton setEnabled:NO];
    [_H323Button setEnabled:NO];
    [_waitingRoomButton setEnabled:NO];
    [_calloutButton setEnabled:NO];
    [_boButton setEnabled:NO];
    [_participantsButton setEnabled:NO];
    [_multiShareButton setEnabled:NO];
    [_deviceTypeButton removeAllItems];
    [_ssoTokenField setEnabled:NO];
    NSArray* deviceTypeArray = [NSArray arrayWithObjects:@"H323",@"SIP",@"Unknow", nil];
    for (NSString* key in deviceTypeArray) {
        [_deviceTypeButton.menu addItemWithTitle:key action:@selector(onH323DeviceTypeSelect:) keyEquivalent:@""];
    }
    [_screenTypeSelectButton removeAllItems];
    NSArray* screenTypeArray = [NSArray arrayWithObjects:@"First",@"Second", nil];
    for (NSString* key in screenTypeArray) {
        [_screenTypeSelectButton.menu addItemWithTitle:key action:@selector(onScreenTypeSelected:) keyEquivalent:@""];
    }
    
    _hasLogined = NO;
    _selectDeviceType = H323DeviceType_H323;
    _screenType = ScreenType_First;
    NSString *bundlePath = [[NSBundle mainBundle] bundlePath];
    [[ZoomSDK sharedSDK] setCustomBundlePath:bundlePath fileName:@"ZoomSDK_Test"];
    ZoomSDKNetworkService* networkService = [[ZoomSDK sharedSDK] getNetworkService];
    networkService.delegate = self;
}
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    signal(SIGPIPE, processSignal);
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

//for pipe error
void processSignal(int num)
{
    if ( SIGPIPE == num ) {
    
    }
}

-(IBAction)clickSDKUser:(id)sender
{
    [self switchToMeetingTab];
}
-(IBAction)clickZoomUser:(id)sender
{
    [self switchToZoomUserTab];
}

-(IBAction)clickChat:(id)sender
{
    [self switchToChatTab];
}

-(IBAction)clickShare:(id)sender
{
    [self switchToShareTab];
}

-(IBAction)clickRecord:(id)sender
{
    [self switchToRecordTab];
}


-(IBAction)showSettingDlg:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller showMeetingComponent:MeetingComponent_Setting window:nil show:YES InPanel:YES frame:NSZeroRect];
    ZoomSDKSettingService* setting = [[ZoomSDK sharedSDK] getSettingService];
    [[setting getGeneralSetting] setCustomFeedbackURL:@"www.baidu.com"];
}

-(IBAction)clickAuthDevZoom:(id)sender
{
    [[ZoomSDK sharedSDK] setZoomDomain:kZoomSDKDomain];
    [self authSDK:kZoomSDKAppKey appSecret:kZoomSDKAppSecret];
    [_connectLabel setStringValue:@"Start Authing..."];
    [self switchToConnectingTab];

}

-(IBAction)sdkAuth:(id)sender
{
    if (!_webDomainField.stringValue.length || !_appKeyField.stringValue.length || !_appSecretField.stringValue.length) {
        [_authResultFieldWelcome setHidden:NO];
        [_authResultFieldWelcome setStringValue:@"Invalid Input Parameter!"];
        return;

    }
    [[ZoomSDK sharedSDK] setZoomDomain:_webDomainField.stringValue];
    [self authSDK:_appKeyField.stringValue appSecret:_appSecretField.stringValue];
    [_connectLabel setStringValue:@"Start Authing..."];
    [self switchToConnectingTab];
}

-(IBAction)loginZoom:(id)sender
{
    [_authResultField setHidden:YES];
    ZoomSDKAuthService *authService = [[ZoomSDK sharedSDK] getAuthService];
    if (authService)
    {
        if(NSOnState == [_enableSSOButton state])
        {
            [authService loginSSO:[_ssoTokenField stringValue]];
        }
        else
        {
            BOOL remember = [_rememberMeButton state]== NSOnState? YES:NO;
            [authService login: [_userNameField stringValue] Password:[_passwordField stringValue] RememberMe:remember];
        }
        [self switchToConnectingTab];
    }
}

-(IBAction)enableSSO:(id)sender{
    if (NSOnState == [_enableSSOButton state]) {
        [_userNameField setEnabled:NO];
        [_passwordField setEnabled:NO];
        [_ssoTokenField setEnabled:YES];
    }else{
        [_userNameField setEnabled:YES];
        [_passwordField setEnabled:YES];
        [_ssoTokenField setEnabled:NO];
    }
    
}
-(IBAction)clickPremeeting:(id)sender
{
    [self switchToPreMeetingTab];
    ZoomSDKPremeetingService *premeetingService = [[ZoomSDK sharedSDK] getPremeetingService];
    premeetingService.delegate = self;
    
}

-(IBAction)clickMainWindow:(id)sender
{
    [self switchToMainWindowTab];
}

-(IBAction)clickH323:(id)sender
{
    [self switchToH323Tab];
}
-(IBAction)clickModifyParticipants:(id)sender
{
    [_tabView selectTabViewItemWithIdentifier:@"Participants"];
}

-(IBAction)clickMultiShare:(id)sender
{
     [_tabView selectTabViewItemWithIdentifier:@"MultiShare"];
}

-(IBAction)clickWaitingRoom:(id)sender
{
    [_tabView selectTabViewItemWithIdentifier:@"WaitingRoom"];
}

-(IBAction)clickPhoneCallout:(id)sender
{
     [_tabView selectTabViewItemWithIdentifier:@"Callout"];
}

-(IBAction)clickBO:(id)sender
{
     [_tabView selectTabViewItemWithIdentifier:@"BO"];
}

-(IBAction)onBackClicked:(id)sender
{
    [self switchToMeetingTab];
}

-(IBAction)onBackToUserClicked:(id)sender
{
    [self switchToUserTab];
    [_authResultField setHidden:YES];
}

-(IBAction)onBackToLoginClicked:(id)sender
{
    [self switchToZoomUserTab];
}


-(IBAction)logout:(id)sender
{
    ZoomSDKAuthService* authService = [[ZoomSDK sharedSDK] getAuthService];
    [authService logout];
}

- (void) switchToWelcomeTab
{
    [_tabView selectTabViewItemWithIdentifier:@"Welcome"];
    [_indicator stopAnimation:nil];
}

- (void) switchToUserTab
{
     [_tabView selectTabViewItemWithIdentifier:@"User"];
    [_indicator stopAnimation:nil];
}
- (void) switchToZoomUserTab
{
     [_loginErrorField setHidden:YES];
     [_tabView selectTabViewItemWithIdentifier:@"Login"];
    
}
- (void) switchToMeetingTab
{
    [_tabView selectTabViewItemWithIdentifier:@"Meeting"];
    [_indicator stopAnimation:nil];
}

- (void)switchToMainWindowTab
{
    [_tabView selectTabViewItemWithIdentifier:@"MainWindow"];
}

- (void)switchToH323Tab
{
    [_tabView selectTabViewItemWithIdentifier:@"H323"];
}

- (void) switchToConnectingTab
{
    [_tabView selectTabViewItemWithIdentifier:@"Connecting"];
    [_indicator startAnimation:nil];
}

- (void) switchToShareTab
{
    [_tabView selectTabViewItemWithIdentifier:@"Share"];
}

- (void) switchToChatTab
{
    [_tabView selectTabViewItemWithIdentifier:@"Chat"];
}

- (void) switchToRecordTab
{
    [_tabView selectTabViewItemWithIdentifier:@"Record"];
}

- (void) switchToPreMeetingTab
{
    [_tabView selectTabViewItemWithIdentifier:@"Premeeting"];
}



-(IBAction)startMeeting:(id)sender
{
    ZoomSDKAuthService* authService = [[ZoomSDK sharedSDK] getAuthService];
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingConfiguration* config = [meetingService getMeetingConfiguration];
   // config.floatVideoPoint =  NSMakePoint(300, 300);
    config.mainToolBarVisible = YES;
    config.mainVideoPoint = NSMakePoint(500, 500);
    ZoomSDKError ret = ZoomSDKError_UnKnow;
    config.enableChime = YES;
    config.enableMuteOnEntry = YES;
    config.disableDoubleClickToFullScreen = YES;
    config.disableRenameInMeeting = YES;
    [config hideSDKButtons:FitBarNewShareButton];
   // [config hideSDKButtons:ToolBarInviteButton];
    ZoomSDKGeneralSetting* setting = [[[ZoomSDK sharedSDK] getSettingService] getGeneralSetting];
    if(setting)
    {
    [setting enableMeetingSetting:NO SettingCmd:MeetingSettingCmd_AutoFitToWindowWhenViewShare];
    [setting enableMeetingSetting:NO SettingCmd:MeetingSettingCmd_AutoFullScreenWhenJoinMeeting];
    [setting enableMeetingSetting:YES SettingCmd:MeetingSettingCmd_AutoJoinAudio];
    [setting enableMeetingSetting:YES SettingCmd:MeetingSettingCmd_DualScreenMode];
    [setting setCustomInviteURL:@"Hello TOTTI"];
    }
    if(meetingService)
    {
         if ([authService isAuthorized])
         {
              meetingService.delegate = self;
             if (_hasLogined) {
                 //for zoom user
                 ret =[meetingService startMeeting:ZoomSDKUserType_ZoomUser userID:nil userToken:nil displayName:nil meetingNumber:[_startMeetingNum stringValue] isDirectShare:NO sharedApp:0 isVideoOff:YES isAuidoOff:NO];
             }else{
                 //for api user
                 ret =[meetingService startMeeting:ZoomSDKUserType_APIUser userID:[_sdkUserID stringValue] userToken:[_sdkUserToken stringValue] displayName:[_startUserName stringValue] meetingNumber:[_startMeetingNum stringValue] isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO];
             }
         }
         NSLog(@"startMeeting ret:%d", ret);
    }
}

-(IBAction)joinMeeting:(id)sender
{
    ZoomSDKAuthService* authService = [[ZoomSDK sharedSDK] getAuthService];
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingConfiguration* config = [meetingService getMeetingConfiguration];
    config.floatVideoPoint =  NSMakePoint(300, 300);
    config.mainToolBarVisible = NO;
    config.mainVideoPoint = NSMakePoint(500, 500);
    config.enableChime = YES;
    config.enableMuteOnEntry = YES;
    config.disablePopupWrongPasswordWindow = YES;
    config.disableDoubleClickToFullScreen = YES;
    ZoomSDKError ret = ZoomSDKError_UnKnow;
    if(meetingService)
    {
        if ([authService isAuthorized])
        {   meetingService.delegate = self;
            if (_hasLogined) {
                 ret =[meetingService joinMeeting:ZoomSDKUserType_ZoomUser toke4enfrocelogin:nil webinarToken:nil  participantId:@"10" meetingNumber:[_joinMeetingNum stringValue] displayName:[_joinUserName stringValue] password:@"" isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO];
            }else{
                 ret =[meetingService joinMeeting:ZoomSDKUserType_APIUser toke4enfrocelogin:nil webinarToken:nil  participantId:@"10" meetingNumber:[_joinMeetingNum stringValue]  displayName:[_joinUserName stringValue] password:@"" isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO];
            }
           
        }
        NSLog(@"joinMeeting ret:%d", ret);
    }
}

-(IBAction)joinWebinar:(id)sender
{
    ZoomSDKAuthService* authService = [[ZoomSDK sharedSDK] getAuthService];
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingConfiguration* config = [meetingService getMeetingConfiguration];
    config.floatVideoPoint =  NSMakePoint(300, 300);
    config.mainToolBarVisible = NO;
    config.mainVideoPoint = NSMakePoint(500, 500);
    config.enableChime = YES;
    config.enableMuteOnEntry = YES;
    config.disablePopupWrongPasswordWindow = YES;
    config.disableDoubleClickToFullScreen = YES;
    config.needPrefillWebinarJoinInfo = YES;
    [config prefillWebinarUserName:[_joinUserName stringValue] Email:@"t@t.com"];
    ZoomSDKError ret = ZoomSDKError_UnKnow;
    if(meetingService)
    {
        if ([authService isAuthorized])
        {   meetingService.delegate = self;
            if (_hasLogined) {
                ret =[meetingService joinMeeting:ZoomSDKUserType_ZoomUser toke4enfrocelogin:nil webinarToken:nil  participantId:@"10" meetingNumber:[_joinMeetingNum stringValue] displayName:[_joinUserName stringValue] password:@"" isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO];
            }else{
                ret =[meetingService joinMeeting:ZoomSDKUserType_APIUser toke4enfrocelogin:nil webinarToken:nil  participantId:@"10" meetingNumber:[_joinMeetingNum stringValue]  displayName:[_joinUserName stringValue] password:@"" isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO];
            }
            
        }
        NSLog(@"joinMeeting ret:%d", ret);
    }
}


-(IBAction)endMeeting:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService leaveMeetingWithCmd:(LeaveMeetingCmd_End)];
}

-(IBAction)showChatDlg:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller showMeetingComponent:MeetingComponent_Chat window:nil show:YES InPanel:NO frame:NSMakeRect(500, 500, 0, 0)];
}


-(IBAction)showChatDlgInPanel:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller showMeetingComponent:MeetingComponent_Chat window:nil show:YES InPanel:YES frame:NSZeroRect];
}
-(IBAction)hideChatDlg:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller showMeetingComponent:MeetingComponent_Chat window:nil show:NO InPanel:NO frame:NSZeroRect];
}

-(IBAction)showParticipantsDlg:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller showMeetingComponent:MeetingComponent_Participants window:nil show:YES InPanel:NO frame:NSMakeRect(500, 500, 0, 0)];
}


-(IBAction)showParticipantsDlgInPanel:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller showMeetingComponent:MeetingComponent_Participants window:nil show:YES InPanel:YES frame:NSZeroRect];
}
-(IBAction)hideParticipantsDlg:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller showMeetingComponent:MeetingComponent_Participants window:nil show:NO InPanel:NO frame:NSZeroRect];
}

-(IBAction)showAudioDlg:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller showMeetingComponent:MeetingComponent_Audio window:nil show:YES InPanel:NO frame:NSMakeRect(650, 650, 0, 0)];
}

-(IBAction)hideAudioDlg:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller showMeetingComponent:MeetingComponent_Audio window:nil show:NO InPanel:NO frame:NSZeroRect];
}

-(IBAction)showConfToolbar:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller showMeetingComponent:MeetingComponent_MainToolBar window:nil show:YES InPanel:NO frame:NSZeroRect];
}
-(IBAction)hideConfToolbar:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller showMeetingComponent:MeetingComponent_MainToolBar window:nil show:NO InPanel:NO frame:NSZeroRect];
}

-(IBAction)switchMiniVideoMode:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    BOOL isInMiniMode = [controller isInMiniVideoMode];
    if(isInMiniMode)
    {
        [controller switchMiniVideoModeUI];
    }
}

-(IBAction)showFitToolBar:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    //[[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_MuteVideo userID:0 onScreen:ScreenType_First];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    if ([_shareOnSecondScreenButton state] == NSOnState) {
         [controller showMeetingComponent:MeetingComponent_AuxShareToolBar window:nil show:YES InPanel:NO frame:NSZeroRect];
    }else{
         [controller showMeetingComponent:MeetingComponent_MainShareToolBar window:nil show:YES InPanel:NO frame:NSZeroRect];
    }
   
}
-(IBAction)hideFitToolBar:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
  //  [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_UnMuteVideo userID:0 onScreen:ScreenType_First];
   ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    if ([_shareOnSecondScreenButton state] == NSOnState) {
        [controller showMeetingComponent:MeetingComponent_AuxShareToolBar window:nil show:NO InPanel:NO frame:NSZeroRect];
    }else{
        [controller showMeetingComponent:MeetingComponent_MainShareToolBar window:nil show:NO InPanel:NO frame:NSZeroRect];
    }
    
}

-(IBAction)showThumbnailVideo:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [[meetingService getMeetingUIController] showMeetingComponent:MeetingComponent_ThumbnailVideo window:nil show:YES InPanel:NO frame:NSZeroRect];
}
-(IBAction)hideThumbnailVideo:(id)sender{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [[meetingService getMeetingUIController] showMeetingComponent:MeetingComponent_ThumbnailVideo window:nil show:NO InPanel:NO frame:NSZeroRect];
}
-(IBAction)requestRemoteControl:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_RequestRemoteControl userID:0 onScreen:_screenType];
    

}

-(IBAction)giveupRemoteControl:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_GiveUpRemoteControl userID:0 onScreen:_screenType];
    ZoomSDKASController* asController = [meetingService getASController];
    unsigned int userID;
   [asController getCurrentRemoteController:&userID];
    NSLog(@"Remote control ID:%d",userID);
}

-(IBAction)revokeRemoteControl:(id)sender
{
     ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_RevokeRemoteControl userID:_userID onScreen:_screenType];
}

-(IBAction)declineRemoteControl:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_DeclineRemoteControlRequest userID:_userID onScreen:_screenType];
}

-(IBAction)giveRemoteControlTo:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_GiveRemoteControlTo userID:_userID onScreen:_screenType];
}

-(IBAction)getScreenID:(id)sender
{
    NSString* info = [self getScreenDisplayID];
    _shareStatusMsgView.string = info;
}

-(IBAction)lockShare:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_LockShare userID:0 onScreen:ScreenType_First];
}

-(IBAction)enterShareFitWindowMode:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_ShareFitWindowMode userID:0 onScreen:_screenType];
}

-(IBAction)minimizeFloatWnd:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller minimizeShareFloatVideoWindow:YES];

}

-(IBAction)maxFloatWnd:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller minimizeShareFloatVideoWindow:NO];
}

-(IBAction)swithFloatWndToActiveSpk:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller switchFloatVideoToActiveSpeakerMode];
}

-(IBAction)swithFloatWndToGallery:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller switchFloatVideoToGalleryMode];
}


-(IBAction)sendHello:(id)sender;
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    
    NSString* sendContent = [[_sendMsgContent stringValue] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    if ([sendContent length] != 0) {
        NSArray* userlist = [[meetingService getMeetingActionController] getParticipantsList];
        for (NSNumber*user in userlist) {
            NSLog(@"ATTEND USERID:%d", [user unsignedIntValue]);
            ZoomSDKUserInfo* userInfo = [[meetingService getMeetingActionController] getUserByUserID:[user unsignedIntValue]];
            if (![userInfo isHost]) {
                ZoomSDKError result = [[meetingService getMeetingActionController] sendChat:sendContent toUser:[user unsignedIntValue]];
                NSLog(@"send chat result:%d", result);
            }
        }
    }
    [_sendMsgContent setStringValue:@""];
}

-(IBAction)startRecording:(id)sender
{
     [_recordConvertFinishLabel setHidden:YES];
    _recordIndicator.doubleValue = 0.0f;
     ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    time_t starttimestamp;
    [[meetingService getMeetingActionController] startRecording:&starttimestamp saveFilePath:@"/Users/totti/Documents/record"];
    NSLog(@"record start time, %ld", starttimestamp);
}
-(IBAction)stopRecording:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    time_t stoptimestamp;
    [[meetingService getMeetingActionController] stopRecording:&stoptimestamp];
    NSLog(@"record stop time, %ld", stoptimestamp);
}

-(IBAction)startAnnotation:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKASController* asController = [meetingService getASController];
    BOOL annotateSelf =[_annotationSelf state] == NSOnState? YES: NO;
   [asController startAnnotation:annotateSelf Position:NSMakePoint(1000, 500) onScreen:_screenType];
   // [meetingService startAnnotation:NSMakePoint(800, 500) onScreen:ScreenType_First];
    ZoomSDKAnnotationController* controller = [asController getAnnotationController:_screenType];
    [controller setColor:0.8f Green:0.8f Black:0.8f onScreen:_screenType];
    [controller setLineWidth: 5 onScreen:_screenType];
    
}

-(IBAction)stopAnnotation:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    BOOL annotateSelf =[_annotationSelf state] == NSOnState? YES: NO;
    ZoomSDKASController* asController = [meetingService getASController];
    [asController stopAnnotation:annotateSelf onScreen:_screenType];
}

-(IBAction)showNoVideoUserOnWall:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* uiController = [meetingService getMeetingUIController];
    [uiController hideOrShowNoVideoUserOnVideoWall:NO];
}

-(IBAction)hideNoVideoUserOnWall:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* uiController = [meetingService getMeetingUIController];
    [uiController hideOrShowNoVideoUserOnVideoWall:YES];
}


-(IBAction)startShare:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKASController* asController = [meetingService getASController];
    [asController startMonitorShare:[[_selectedScreenField stringValue] intValue]];
  /*  NSNumberFormatter* f = [[[NSNumberFormatter alloc] init] autorelease];
    f.numberStyle = NSNumberFormatterDecimalStyle;
    NSNumber* number =[f numberFromString:[_selectedScreenField stringValue]];
   [meetingService startMonitorShare:[number unsignedIntValue]];*/
}

-(IBAction)setEraser:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKASController* asController = [meetingService getASController];
    ZoomSDKAnnotationController* annotation = [asController getAnnotationController:_screenType];
    [annotation setTool:AnnotationToolType_ERASER onScreen:_screenType];
}

-(IBAction)setPen:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKASController* asController = [meetingService getASController];
    ZoomSDKAnnotationController* annotation = [asController getAnnotationController:_screenType];
    [annotation setTool:AnnotationToolType_Pen onScreen:_screenType];
}
-(IBAction)setNone:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKASController* asController = [meetingService getASController];
    ZoomSDKAnnotationController* annotation = [asController getAnnotationController:_screenType];
    [annotation setTool:AnnotationToolType_None onScreen:_screenType];
}

-(IBAction)clearAll:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKASController* asController = [meetingService getASController];
    ZoomSDKAnnotationController* annotation = [asController getAnnotationController:_screenType];
    [annotation clear:AnnotationClearType_All onScreen:_screenType];
}
-(IBAction)clearMine:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKASController* asController = [meetingService getASController];
    ZoomSDKAnnotationController* annotation = [asController getAnnotationController:_screenType];
   [annotation clear:AnnotationClearType_Self onScreen:_screenType];
}
-(IBAction)redo:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKASController* asController = [meetingService getASController];
    ZoomSDKAnnotationController* annotation = [asController getAnnotationController:_screenType];
    [annotation redo:_screenType];
}
-(IBAction)undo:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKASController* asController = [meetingService getASController];
    ZoomSDKAnnotationController* annotation = [asController getAnnotationController:_screenType];
    [annotation undo:_screenType];
}

-(IBAction)switchToActiveSpkView:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* UIController = [meetingService getMeetingUIController];
    [UIController switchToActiveSpeakerView];

}
-(IBAction)switchToWallView:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* UIController = [meetingService getMeetingUIController];
    [UIController switchToVideoWallView];
}


-(IBAction)enableMuteOnEntry:(id)sender
{
    ZoomSDKSettingService* settingService = [[ZoomSDK sharedSDK] getSettingService];
    [[settingService getGeneralSetting] enableMeetingSetting:YES SettingCmd:MeetingSettingCmd_EnableMuteOnEntry];
}

-(IBAction)hideSettingDlg:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* uiController = [meetingService getMeetingUIController];
    [uiController showMeetingComponent:MeetingComponent_Setting window:nil show:NO InPanel:NO frame:NSZeroRect];
}


- (void)authSDK:(NSString*)key appSecret:(NSString*)secret
{
    ZoomSDKAuthService *authService = [[ZoomSDK sharedSDK] getAuthService];
    if (authService)
    {
        authService.delegate = self;
        [authService sdkAuth:key appSecret:secret];
    }
}

#pragma auth delegate
- (void)onZoomSDKAuthReturn:(ZoomSDKAuthError)returnValue
{
    NSLog(@"onZoomSDKAuthReturn %d", returnValue);
    if(returnValue == ZoomSDKAuthError_Success)
    {
        ZoomSDKSettingService* setService = [[ZoomSDK sharedSDK] getSettingService];
        [[setService getRecordSetting] setRecordingPath:@"/Users/totti/Documents/record"];
        [_authResultField setHidden:NO];
        [_authResultField setTextColor:[NSColor blueColor]];
        [_authResultField setStringValue:@"Auth SDK Success!"];
        [self switchToUserTab];
    }else{
        [self switchToWelcomeTab];
        [_authResultFieldWelcome setHidden:NO];
        [_authResultFieldWelcome setStringValue:[NSString stringWithFormat:@"Auth Faild, Error:%d", returnValue]];
    }

    
}

- (void)onZoomSDKLogin:(ZoomSDKLoginStatus)loginStatus failReason:(NSString *)reason
{
    switch (loginStatus) {
        case ZoomSDKLoginStatus_Processing:
            [_connectLabel setStringValue:@"Start Logining..."];
            [self switchToConnectingTab];
            break;
        case ZoomSDKLoginStatus_Success:
        {
            ZoomSDKPremeetingService* premeeting = [[ZoomSDK sharedSDK] getPremeetingService];
            premeeting.delegate = self;
            [_preMeetingButton setEnabled:YES];
            [_logoutButton setEnabled:YES];
            [self switchToMeetingTab];
            _hasLogined = YES;
        }
            break;
        case ZoomSDKLoginStatus_Failed:
        {
            [self switchToZoomUserTab];
            [_loginErrorField setHidden:NO];
            if ([_authResultField isHidden]) {
                [_loginErrorField setStringValue:@"Login Failed!"];
            }else{
                [_loginErrorField setStringValue:@"Auto Login Failed!"];
            }
        }
            break;
        default:
            break;
    }
}

- (void)onRemoteControlStatus:(ZoomSDKRemoteControlStatus)status User:(unsigned int)userID
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    if (!meetingService) {
        return;
    }
    NSString* info = @"";
    switch (status) {
        case ZoomSDKRemoteControlStatus_RequestFromWho:
        {
            info = [NSString stringWithFormat:@"User:%d is request Remote Control Now!", userID];
               [_revokeRemoteControl setEnabled:YES];
               [_declineRemoteControl setEnabled:YES];
            _userID = userID;
        }
           break;
        case ZoomSDKRemoteControlStatus_CanRequestFromWho:
        {
            info = [NSString stringWithFormat:@" Can Request Remote control Privilege from ID:%d", userID];
        }
            break;
        case ZoomSDKRemoteControlStatus_DeclineByWho:
        {
            info = [NSString stringWithFormat:@" Your Remote control Request Privilege Declined by ID:%d", userID];
        }
            break;
        case ZoomSDKRemoteControlStatus_RemoteControlledByWho:
        {
            info = [NSString stringWithFormat:@" You are now controlled by ID:%d", userID];
        }
            break;
        case ZoomSDKRemoteControlStatus_StartRemoteControllWho:
        {
            info = [NSString stringWithFormat:@"Now U are controlling %d's Screen", userID];
        }
            break;
        case ZoomSDKRemoteControlStatus_EndRemoteControllWho:
        {
            info = [NSString stringWithFormat:@"Now U are not controlling %d's Screen", userID];
        }
            break;
        case ZoomSDKRemoteControlStatus_HasPrivilegeFromWho:
        {
            info = [NSString stringWithFormat:@"Now U has remote controll privilege of %d's Screen", userID];
        }
           break;
         case ZoomSDKRemoteControlStatus_LostPrivilegeFromWho:
        {
             info = [NSString stringWithFormat:@"Now U lost remote controll privilege of %d's Screen", userID];
        }
            break;
        default:
            break;
    }
    [_remoteControlMsgField setStringValue:info];
}


#pragma meetingservice delegate

- (void)onMeetingStatusChange:(ZoomSDKMeetingStatus)state meetingError:(ZoomSDKMeetingError)error
{
    NSLog(@"MeetingStatus change %d", state);
    switch (state) {
        case ZoomSDKMeetingStatus_InMeeting:
        {
            ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
            if (!meetingService) {
                return;
            }
            
            
            [_chatButton setEnabled:YES];
            [_recordButton setEnabled:YES];
            [_shareButton setEnabled:YES];
            [_mainWindowButton setEnabled:YES];
            [_endMeeting setEnabled:YES];
            [_H323Button setEnabled:YES];
            [_waitingRoomButton setEnabled:YES];
            [_calloutButton setEnabled:YES];
            [_boButton setEnabled:YES];
            [_participantsButton setEnabled:YES];
            [_multiShareButton setEnabled:YES];
            //[meetingService actionMeetingWithCmd:ActionMeetingCmd_MuteVideo userID:0];
             //move main video
             ZoomSDKMeetingUIController* UIController = [meetingService getMeetingUIController];
             if (!UIController) {
             return;
             }
          //   NSRect mainRect = NSMakeRect(100, 100, 200, 200);
          //   NSWindow* w∑indow = [[NSWindow alloc] init];
          //   [UIController showMeetingComponent:MeetingComponent_MainWindow window: &window show:YES frame:mainRect];
          /*
             NSRect newRect  = NSMakeRect(100, 100, 400, 400);
             [window setLevel:NSPopUpMenuWindowLevel];
             [window setStyleMask:NSBorderlessWindowMask];
             ZoomSDKWindowController* ctrl = [[ZoomSDKWindowController alloc] init];
             [ctrl.window setLevel:NSPopUpMenuWindowLevel + 2];
             [ctrl.window setFrameOrigin:NSMakePoint(100, 100)];
             [ctrl.window addChildWindow:window ordered:NSWindowAbove];
             [window setFrame:newRect display:YES];
             [ctrl showWindow:nil];
            */
            //test for setting camera list
            ZoomSDKSettingService* settingService = [[ZoomSDK sharedSDK] getSettingService];
            [[settingService getVideoSetting] enableBeautyFace:YES];
            if(![[settingService getVideoSetting] isMirrorEffectEnabled])
                [[settingService getVideoSetting] enableMirrorEffect:YES];
            NSArray* array =  [[settingService getVideoSetting] getCameraList];
            for(SDKDeviceInfo* info in array)
            {
                NSLog(@"App delegate camera list, deviceID:%@, deviceName:%@, isSelected:%d", [info getDeviceID], [info getDeviceName], [info isSelectedDevice]);
            }
            //action controller delegate
            ZoomSDKMeetingActionController* actionCtr = [meetingService getMeetingActionController];
            actionCtr.delegate = self;
            //h323 delegate
            ZoomSDKH323Helper* h323Helper = [meetingService getH323Helper];
            h323Helper.delegate = self;
            //waiting room delegate
            ZoomSDKWaitingRoomController* waitController = [meetingService getWaitingRoomController];
            waitController.delegate = self;
            //Phone Helper
            ZoomSDKPhoneHelper* phoneHelper = [meetingService getPhoneHelper];
            phoneHelper.delegate = self;
            ZoomSDKASController* asController = [meetingService getASController];
            asController.delegate = self;
        }
        break;
        case ZoomSDKMeetingStatus_AudioReady:
        {
         
        }
        break;
        case ZoomSDKMeetingStatus_Failed:
        {
            if (error == ZoomSDKMeetingError_PasswordError) {
                NSLog(@"Password is Wrong!");
            }
        }
        default:
        {
            [self switchToMeetingTab];
            [_chatButton setEnabled:NO];
            [_recordButton setEnabled:NO];
            [_shareButton setEnabled:NO];
            [_mainWindowButton setEnabled:NO];
            [_endMeeting setEnabled:NO];
            [_H323Button setEnabled:NO];
            [_waitingRoomButton setEnabled:NO];
            [_calloutButton setEnabled:NO];
            [_boButton setEnabled:NO];
            [_participantsButton setEnabled:NO];
            [_multiShareButton setEnabled:NO];
        }
        break;
    }
}

- (void)onUserAudioStatusChange:(NSArray*)userAudioStatusArray
{
    NSString* userAudioString = @"";
    for (ZoomSDKUserAudioStauts* key in userAudioStatusArray) {
        unsigned int userID = [key getUserID];
        ZoomSDKAudioStatus status = [key getStatus];
        ZoomSDKAudioType type = [key getType];
        NSString* statuStr = @"";
        NSString* typeStr = @"";
        switch (status) {
            case ZoomSDKAudioStatus_None:
                statuStr = @"audio status none";
                break;
            case ZoomSDKAudioStatus_Muted:
                 statuStr = @"audio status muted by self";
                break;
            case ZoomSDKAudioStatus_UnMuted:
                statuStr = @"audio status unmuted by self";
                break;
            case ZoomSDKAudioStatus_UnMutedByHost:
                statuStr = @"audio status unmuted by host";
                break;
            case ZoomSDKAudioStatus_MutedByHost:
                statuStr = @"audio status muted by host";
                break;
            case ZoomSDKAudioStatus_MutedAllByHost:
                statuStr = @"audio status muted all by host";
                break;
            case ZoomSDKAudioStatus_UnMutedAllByHost:
                statuStr = @"audio status unmuted all by host";
                break;
            default:
                break;
        }
        switch (type) {
            case ZoomSDKAudioType_None:
                typeStr = @"audio type none";
                break;
            case ZoomSDKAudioType_Voip:
                typeStr = @"audio type computer audio";
                break;
            case ZoomSDKAudioType_Phone:
                typeStr = @"audio type phone";
                break;
            case ZoomSDKAudioType_Unknow:
                typeStr = @"audio type unknow";
                break;
            default:
                break;
        }
       NSLog(@"userID %d status:%d type:%d", userID, status, type);
       userAudioString = [userAudioString stringByAppendingString:[NSString stringWithFormat:@"user %d 's %@,%@ %C", userID, statuStr, typeStr,(unichar)NSParagraphSeparatorCharacter]];
    }
    _audioInfoView.string = userAudioString;
}

-(void)onWaitMeetingSessionKey:(NSData *)key
{
    NSLog(@"Huawei Session key:%@", key);
    ZoomSDKMeetingService* service = [[ZoomSDK sharedSDK] getMeetingService];
    NSString* testVideoSessionKey =@"abcdefghijkmnopr";
    ZoomSDKSecuritySessionKey* sessionkey = [[[ZoomSDKSecuritySessionKey alloc] init] autorelease];
    sessionkey.component = SecuritySessionComponet_Video;
    sessionkey.sessionKey = [NSData dataWithBytes:(const char*)testVideoSessionKey.UTF8String length:16];
    sessionkey.iv = nil;
    NSArray* array = [NSArray arrayWithObjects:sessionkey, nil];
    [service setSecuritySessionKey:array isLeaveMeeting:NO];
}
- (void)onRecord2MP4Progressing:(int)percentage
{
    _recordIndicator.doubleValue = percentage;
}


-(void)onRecord2MP4Done:(BOOL)success Path:(NSString *)recordPath
{
    if (success) {
        [_recordConvertFinishLabel setHidden:NO];
        [_recordConvertFinishLabel setStringValue:[NSString stringWithFormat:@"Record Convert Success, File Path:%@", recordPath]];
    }
}

- (void)onChatMessageNotification:(ZoomSDKChatInfo *)chatInfo
{
    if (chatInfo) {
        NSString* sender = [chatInfo getSenderDisplayName];
        NSString* receiver = [chatInfo getReceiverDisplayName];
        NSString* content = [chatInfo getMsgContent];
        time_t sendtime = [chatInfo getTimeStamp];
        struct tm timeStruct;
        localtime_r(&sendtime, &timeStruct);
        char buffer[20];
        strftime(buffer, 20, "%d-%m-%Y %H:%M:%S", &timeStruct);
        NSString* sendTime = [NSString stringWithUTF8String:buffer];
        [_receivedMsgContent setStringValue:[NSString stringWithFormat:@"%@ send %@ to %@ at %@", sender, content, receiver, sendTime]];
        
    }
}

- (void)onZoomSDKLogout{
    [self switchToUserTab];
    [_preMeetingButton setEnabled:NO];
    [_logoutButton setEnabled:NO];
    _hasLogined = NO;
}
#pragma test share




-(IBAction)enterFullScreen:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
   ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller enterFullScreen:YES firstMonitor:YES DualMonitor:NO];
}
-(IBAction)exitFullScreen:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller enterFullScreen:NO firstMonitor:YES DualMonitor:NO];
}

//premeeting
-(IBAction)scheduleMeeting:(id)sender
{
    [_preMeetingError setHidden:YES];
    [_listMeetingError setHidden:YES];
    NSDate* now = [NSDate date];
    NSDate* startDate = [self getMeetingStartDateFromDate:now];
    time_t startTime  = (long)[startDate timeIntervalSince1970];
    ZoomSDKPremeetingService* premeetingService = [[ZoomSDK sharedSDK] getPremeetingService];
    ZoomSDKScheduleMeetingItem* scheduleItem = [[[ZoomSDKScheduleMeetingItem alloc]init] autorelease];
    scheduleItem.meetingStartTime = startTime;
    scheduleItem.meetingTopic = [_meetingTopic stringValue];
    scheduleItem.meetingDuration = [[_meetingDuration stringValue] intValue];
    scheduleItem.meetingPassword = [_meetingPassword stringValue];
    scheduleItem.usePMI = ([_usePMI state] == NSOnState)? YES:NO;
    scheduleItem.joinBeforeHost = ([_joinBeforeHost state] == NSOnState)? YES:NO;
    scheduleItem.turnOffVideoForAttendee = ([_turnOffVideoForAttende state] == NSOnState)? YES:NO;
    scheduleItem.turnOffVideoForHost = ([_turnOffVideoForHost state] == NSOnState)? YES:NO;
    [premeetingService  scheduleMeeting:scheduleItem];
}
-(IBAction)deleteMeeting:(id)sender
{
    [_preMeetingError setHidden:YES];
     [_listMeetingError setHidden:YES];
    ZoomSDKPremeetingService* premeetingService = [[ZoomSDK sharedSDK] getPremeetingService];
    [premeetingService deleteMeeting:[[_meetingNumber stringValue] longLongValue]];
}
-(IBAction)updateMeeting:(id)sender
{
    [_preMeetingError setHidden:YES];
    [_listMeetingError setHidden:YES];
    NSDate* now = [NSDate date];
    NSDate* startDate = [self getMeetingStartDateFromDate:now];
    time_t startTime  = (long)[startDate timeIntervalSince1970];
    ZoomSDKPremeetingService* premeetingService = [[ZoomSDK sharedSDK] getPremeetingService];
    ZoomSDKScheduleMeetingItem* scheduleItem = [[[ZoomSDKScheduleMeetingItem alloc]init] autorelease];
    scheduleItem.meetingStartTime = startTime;
    scheduleItem.meetingTopic = [_meetingTopic stringValue];
    scheduleItem.meetingDuration = [[_meetingDuration stringValue] intValue];
    scheduleItem.meetingPassword = [_meetingPassword stringValue];
    scheduleItem.usePMI = ([_usePMI state] == NSOnState)? YES:NO;
    scheduleItem.joinBeforeHost = ([_joinBeforeHost state] == NSOnState)? YES:NO;
    scheduleItem.turnOffVideoForAttendee = ([_turnOffVideoForAttende state] == NSOnState)? YES:NO;
    scheduleItem.turnOffVideoForHost = ([_turnOffVideoForHost state] == NSOnState)? YES:NO;
    [premeetingService editMeeting:scheduleItem MeetingUniqueID:[[_meetingNumber stringValue] longLongValue]];

}
-(IBAction)listMeeting:(id)sender
{
    [_preMeetingError setHidden:YES];
     [_listMeetingError setHidden:YES];
     ZoomSDKPremeetingService* premeetingService = [[ZoomSDK sharedSDK] getPremeetingService];
    [premeetingService listMeeting];
}

-(IBAction)showScheduleWindow:(id)sender
{
     ZoomSDKPremeetingService* premeetingService = [[ZoomSDK sharedSDK] getPremeetingService];
    NSWindow* scheduleWindow = [[NSWindow alloc] init];
    ZoomSDKError error = ZoomSDKError_UnKnow;
    if ([[_meetingNumber stringValue] length] == 0) {
       error = [premeetingService showScheduleEditMeetingWindow:YES Window:&scheduleWindow MeetingID:0];
    }else{
       NSLog(@"Edit meeting ID:%lld",[[_meetingNumber stringValue] longLongValue]);
       error = [premeetingService showScheduleEditMeetingWindow:YES Window:&scheduleWindow MeetingID:[[_meetingNumber stringValue] longLongValue]];
    }
    if(ZoomSDKError_Success == error)
    {
        [scheduleWindow center];
    }
   // ;
}
-(void)onDeleteMeeting:(ZoomSDKPremeetingError)error
{
    [_preMeetingError setHidden:NO];
    if (error == ZoomSDKPremeetingError_Success) {
        [_preMeetingError setStringValue:@"Delete Meeting Success"];
    }else{
        [_preMeetingError setStringValue:[NSString stringWithFormat:@"Delete Meeting Error, Error Code:%d", error]];
    }
}
-(void)onScheduleOrEditMeeting:(ZoomSDKPremeetingError)error MeetingUniqueID:(long long)meetingUniqueID
{
    [_preMeetingError setHidden:NO];
    if (error == ZoomSDKPremeetingError_Success) {
        [_preMeetingError setStringValue:@"Scheduel or Edit Meeting Success"];
        [_meetingNumber setStringValue:[NSString stringWithFormat:@"%lld", meetingUniqueID]];
    }else{
         [_preMeetingError setStringValue:[NSString stringWithFormat:@"Scheduel or Edit Meeting Error, Error Code:%d", error]];
    }
}
- (void)onListMeeting:(ZoomSDKPremeetingError)error MeetingList:(NSArray *)meetingList
{
    [_listMeetingError setHidden:NO];
    NSMutableString* meetingListContent = [NSMutableString string];
     [_listMeeting setHidden:NO];
    if (error == ZoomSDKPremeetingError_Success) {
        int index = 1;
        for(ZoomSDKMeetingItem* item in meetingList)
        {
            time_t startTime = item.getMeetingStartTime;
            NSString* topic = item.getMeetingTopic;
            NSString* password = item.getMeetingPassword;
            time_t duration = item.getMeetingDuration;
            long long meetingNumber = item.getMeetingUniqueID;
            
            struct tm timeStruct;
            localtime_r(&startTime, &timeStruct);
            char buffer[20];
            strftime(buffer, 20, "%d-%m-%Y %H:%M:%S", &timeStruct);
            NSString* start = [NSString stringWithUTF8String:buffer];
            NSString* content = [NSString stringWithFormat:@"%d. Meeting Number:%lld Topic:%@ Password:%@ StartTime:%@ Duration:%ld %C",index, meetingNumber, topic, password, start, duration, (unichar)NSParagraphSeparatorCharacter];
            NSLog(@"Meeting List each Content:%@", content);
            [meetingListContent appendString:content];
            index++;
        }
        NSLog(@"Meeting List Content:%@", meetingListContent);
        [_meetingListContent setString:meetingListContent];
        [_listMeetingError setStringValue:@"List Meeting Success"];
    }else{
       
        [_listMeetingError setStringValue:[NSString stringWithFormat:@"List Meeting Error, Error Code:%d", error]];
    }
}

- (NSDate *)getMeetingStartDateFromDate:(NSDate *)currentDate
{
    
    NSDateComponents *time = [[NSCalendar currentCalendar]
                              components:NSHourCalendarUnit | NSMinuteCalendarUnit | NSSecondCalendarUnit
                              fromDate:currentDate];
    [time setMinute:-[time minute]];
    [time setSecond:-[time second]];
    [time setHour:2];
    
    return [[NSCalendar currentCalendar] dateByAddingComponents:time toDate:currentDate options:0];
}

//H323 support
- (IBAction)sendPairCode:(id)sender
{
    ZoomSDKMeetingService* meetingSevice = [[ZoomSDK sharedSDK] getMeetingService];
    [[meetingSevice getH323Helper] sendMeetingPairingCode:[_pairCode stringValue] meetingNum:[[_meetingNum stringValue] longLongValue]];
}
- (IBAction)getH323DeviceAddress:(id)sender
{
    ZoomSDKMeetingService* meetingSevice = [[ZoomSDK sharedSDK] getMeetingService];
    NSArray* addressArray = [[meetingSevice getH323Helper] getH323DeviceAddress];
    NSString* info = @"";
    for (int i = 0; i < [addressArray count]; i++) {
        NSString* address = [NSString stringWithFormat:@"%@%C", [addressArray objectAtIndex:i], (unichar)NSParagraphSeparatorCharacter];
       info = [info stringByAppendingString:address];
    }
    [_deviceAddress setString:info];
}
- (IBAction)calloutDevice:(id)sender
{
    H323DeviceInfo* info = [[[H323DeviceInfo alloc] init] autorelease];
    info.name = _deviceName.stringValue;
    info.ip = _deviceIP.stringValue;
    info.e164num = _deviceE164Num.stringValue;
    info.type= _selectDeviceType;
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKError result = [[meetingService getH323Helper] calloutH323Device:info];
    if (result != ZoomSDKError_Success) {
        NSLog(@"Call out device failed!");
    }
    
}
- (IBAction)cancelCalloutDevice:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [[meetingService getH323Helper] cancelCallOutH323];
}


//Participants
-(IBAction)getParticipantsList:(id)sender
{
    
    /*NSString *mailtoStr = [NSString stringWithFormat:@"mailto:?subject=%@&body=%@", @"test", @"totti"];
    NSURL* theURL = nil;
    if(mailtoStr && mailtoStr.length>0)
        theURL = [NSURL URLWithString:mailtoStr];
    if(theURL)
        [[NSWorkspace sharedWorkspace] openURL:theURL];*/
    
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    NSArray* participantsList = [[meetingService getMeetingActionController] getParticipantsList];
    NSString* listInfo = @"";
    for (NSNumber* user in participantsList) {
        ZoomSDKUserInfo* userInfo = [[meetingService getMeetingActionController] getUserByUserID:[user unsignedIntValue]];
        NSString* userName = [userInfo getUserName];
        NSString* userString = [NSString stringWithFormat:@"%@ %@ %C", userName, [user stringValue], (unichar)NSParagraphSeparatorCharacter];
        listInfo = [listInfo stringByAppendingString:userString];
    }
    _participantsListView.string = listInfo;
    _waitingRoomUserInfo.string = listInfo;
}
//Spotlight Video
- (IBAction)spotLightVideo:(id)sender
{
    
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    NSString* selectedUser = [_selectedUserID stringValue];
    unsigned int userid =(unsigned int)[selectedUser intValue];
    [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_SpotlightVideo userID:userid onScreen:ScreenType_First];

}
- (IBAction)pinVideo:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    NSString* selectedUser = [_selectedUserID stringValue];
    unsigned int userid =(unsigned int)[selectedUser intValue];
    [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_PinVideo userID:userid onScreen:_screenType];
}

- (IBAction)getSharerList:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKASController* asController = [meetingService getASController];
    NSArray* participantsList = [asController getShareSourceList];
    NSString* listInfo = @"";
    for (NSNumber* user in participantsList) {
        ZoomSDKUserInfo* userInfo = [[meetingService getMeetingActionController] getUserByUserID:[user unsignedIntValue]];
        ZoomSDKShareSource* sharesource = [asController getShareSourcebyUserId:[user unsignedIntValue]];
        NSString* userName = [userInfo getUserName];
        BOOL inFirstScreen = [sharesource isShowInFirstScreen];
        BOOL inSecondScreen = [sharesource isShowInSecondScreen];
        BOOL canbeRemoteContrller = [sharesource canBeRemoteControl];
        NSString* userString = [NSString stringWithFormat:@"%@ %@ inFirstScreen:%d inSecondScreen:%d canbeRemoteControll:%d %C", userName, [user stringValue],inFirstScreen, inSecondScreen,canbeRemoteContrller, (unichar)NSParagraphSeparatorCharacter];
        listInfo = [listInfo stringByAppendingString:userString];
    }
    _sharerListView.string = listInfo;
}

- (IBAction)viewShare:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    unsigned int userid =(unsigned int)[_sharerUserID intValue];
    ZoomSDKASController* asController = [meetingService getASController];
    [asController viewShare:userid onScreen:_screenType];
}

//H323 Helper delegate

- (void) onCalloutStatusReceived:(H323CalloutStatus)calloutStatus
{
    NSString* errorString = @"";
    switch (calloutStatus) {
        case H323CalloutStatus_Unknown:
            errorString = @"call out device error unknow";
            break;
        case H323CalloutStatus_Success:
            errorString = @"call out device successfully";
            break;
        case H323CalloutStatus_Timeout:
            errorString = @"call out device time out";
            break;
        case H323CalloutStatus_Failed:
            errorString = @"call out device failed";
            break;
        case H323CalloutStatus_Ring:
            errorString = @"call out device is ringing";
            break;
        default:
            break;
    }
    [_deviceAddress setString:errorString];
}

- (void) onPairCodeResult:(H323PairingResult)pairResult
{
    NSString* errorString = @"";
    switch (pairResult) {
        case H323PairingResult_Unknown:
            errorString = @"pair meeting unknow";
            break;
        case H323PairingResult_Success:
            errorString = @"pair meeting successfully";
            break;
        case H323PairingResult_Meeting_Not_Exist:
            errorString = @"pair meeting error for meeting not exist";
            break;
        case H323PairingResult_Paringcode_Not_Exist:
            errorString = @"pair meeting error for pair code not exist";
            break;
        case H323PairingResult_No_Privilege:
            errorString = @"pair meeting error for u haven't privilege";
            break;
        case H323PairingResult_Other_Error:
            errorString = @"pair meeting error for other error";
            break;
        default:
            break;
    }
    [_deviceAddress setString:errorString];
}

-(void)onH323DeviceTypeSelect:(id)sender
{
    NSString* title = [sender title];
    if ([title isEqualToString:@"H323"]) {
        _selectDeviceType = H323DeviceType_H323;
    }else if([title isEqualToString:@"SIP"]){
        _selectDeviceType = H323DeviceType_SIP;
    }else{
        _selectDeviceType = H323DeviceType_Unknown;
    }
}

-(void)onScreenTypeSelected:(id)sender
{
    NSString* title = [sender title];
    if ([title isEqualToString:@"First"]) {
        _screenType = ScreenType_First;
    }else if([title isEqualToString:@"Second"]){
        _screenType = ScreenType_Second;
    }
}
// share delegate
- (void)onSharingStatus:(ZoomSDKShareStatus)status User:(unsigned int)userID
{
    NSString* info = @"";
    switch (status) {
        case ZoomSDKShareStatus_SelfBegin:
            info = @"I start share myself";
            break;
        case ZoomSDKShareStatus_SelfEnd:
            info = @"I end share myself";
            break;
        case ZoomSDKShareStatus_OtherBegin:
            info = [NSString stringWithFormat:@"%d start his share now", userID];
            break;
        case ZoomSDKShareStatus_OtherEnd:
             info = [NSString stringWithFormat:@"%d end his share now", userID];
            break;
        case ZoomSDKShareStatus_ViewOther:
            info = [NSString stringWithFormat:@"now u can view %d's share", userID];
            break;
        case ZoomSDKShareStatus_Pause:
            info = [NSString stringWithFormat:@"%d pause his share now", userID];
            break;
        case ZoomSDKShareStatus_Resume:
             info = [NSString stringWithFormat:@"%d resume his share now", userID];
            break;
        case ZoomSDKShareStatus_None:
            break;
        default:
            break;
    }
    _shareStatusMsgView.string = info;
    
}

-(void)onShareContentChanged:(ZoomSDKShareInfo *)shareInfo
{
    ZoomSDKShareContentType type = [shareInfo getShareType];
    NSString* info = @"";
    if (ZoomSDKShareContentType_DS == type) {
        CGDirectDisplayID displayID = 0;
        if (ZoomSDKError_Success == [shareInfo getDisplayID:&displayID]) {
             info = [NSString stringWithFormat:@"Share content Change to Destop, display ID:%d", displayID];
        }
    }else if(ZoomSDKShareContentType_AS == type || ZoomSDKShareContentType_WB == type)
    {
        CGWindowID windowID = 0;
        if (ZoomSDKError_Success == [shareInfo getWindowID:&windowID]) {
            info = [NSString stringWithFormat:@"Share content change to Application or Whiteboard, window ID:%d", windowID];
        }

    }
    _shareStatusMsgView.string = info;
}

- (void)onToolbarInviteButtonClick
{
    NSLog(@"Invite Button Clicked by User, Do something!!!");
}


#pragma mark - Waiting Room
- (IBAction)getWaitingRoomUsers:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKWaitingRoomController* waitController = [meetingService getWaitingRoomController];
    NSArray* waitUserArray = [waitController getWaitRoomUserList];
    if (!waitUserArray || waitUserArray.count == 0)
        return;
    NSString* userString = @"";
    for (int i=0;i< waitUserArray.count;i++) {
        NSNumber* userNum = [waitUserArray objectAtIndex:i];
        userString = [userString stringByAppendingString:[NSString stringWithFormat:@"%@ %C", [userNum stringValue], (unichar)NSParagraphSeparatorCharacter]];
    }
    _waitingRoomUserInfo.string = userString;
}

- (IBAction)admitToMeeting:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKWaitingRoomController* waitController = [meetingService getWaitingRoomController];
    if ([_selectedWaitingUser.stringValue isEqualToString:@""]) {
        return;
    }
    [waitController admitToMeeting: [[_selectedWaitingUser stringValue] intValue]];
}

- (IBAction)putIntoWaitingRoom:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKWaitingRoomController* waitController = [meetingService getWaitingRoomController];
    if ([_selectedWaitingUser.stringValue isEqualToString:@""]) {
        return;
    }
    [waitController putIntoWaitingRoom: [[_selectedWaitingUser stringValue] intValue]];
}

#pragma mark - Waiting Room Delegate
-(void)onUserJoinWaitingRoom:(unsigned int)userid
{
    NSString* statusInfo = [NSString stringWithFormat:@"%d, %@", userid,@"Join Waiting Room"];
    [_waitingRoomStatusInfo setString:statusInfo];
}

-(void)onUserLeftWaitingRoom:(unsigned int)userid
{
    NSString* statusInfo = [NSString stringWithFormat:@"%d, %@", userid,@"Left Waiting Room"];
    [_waitingRoomStatusInfo setString:statusInfo];
}

//Phone Call Out
- (IBAction)callOutInviteUser:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKPhoneHelper* phoneHelper = [meetingService getPhoneHelper];
    if (![_countryCode stringValue].length ||![_phoneNumber stringValue].length ||![_userName stringValue].length)
    return;
    [phoneHelper inviteCalloutUser:[_userName stringValue] PhoneNumber:[_phoneNumber stringValue] CountryCode:[_countryCode stringValue]];
    
}
- (IBAction)cancelCallOut:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKPhoneHelper* phoneHelper = [meetingService getPhoneHelper];
    [phoneHelper cancelCalloutUser];
}

//Phone Helper Delegate
- (void)onInviteCalloutUserStatus:(PhoneStatus)status FailedReason:(PhoneFailedReason)reason
{
    NSString* phoneStatusString =@"";
    NSString* failedString = @"";
    switch (status) {
        case PhoneStatus_Accepted:
        phoneStatusString = @"Phone Call Accepted!";
            break;
        case PhoneStatus_Calling:
            phoneStatusString = @"Phone Call is Calling!";
            break;
        case PhoneStatus_Canceled:
            phoneStatusString = @"Phone Call Canceled";
            break;
        case PhoneStatus_Cancel_Failed:
            phoneStatusString = @"Phone Call Cancel Failed!";
            break;
        case PhoneStatus_Ringing:
            phoneStatusString = @"Phone Call is Ringing!";
            break;
        case PhoneStatus_Canceling:
            phoneStatusString = @"Phone Call is Canceling!";
            break;
        case PhoneStatus_Timeout:
            phoneStatusString = @"Phone Call Time Out!";
            break;
        case PhoneStatus_Success:
            phoneStatusString = @"Phone Call Success!";
        case PhoneStatus_Failed:
        {
            switch (reason) {
                case PhoneFailedReason_Block_High_Rate:
                    failedString = @"Failed: High Rate";
                    break;
                case PhoneFailedReason_Block_No_Host:
                    failedString = @"Failed: Block No Host";
                    break;
                case PhoneFailedReason_Busy:
                    failedString = @"Failed: Busy";
                    break;
                case PhoneFailedReason_No_Answer:
                    failedString = @"Failed: No Answer";
                    break;
                case PhoneFailedReason_Block_Too_Frequent:
                    failedString = @"Failed: Too Frequent";
                    break;
                case PhoneFailedReason_Not_Available:
                    failedString = @"Failed: Not Available";
                    break;
                case PhoneFailedReason_Other_Fail:
                    failedString = @"Failed: Other Fail";
                    break;
                case PhoneFailedReason_User_Hangup:
                    failedString = @"Failed: User Hangup";
                    break;
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }
    
    NSString* info = [phoneStatusString stringByAppendingString:failedString];
    _calloutStatusInfo.string = info;
}


-(NSString*)getScreenDisplayID
{
    NSString* displayScreenStr = @"";
    NSArray* allScreens = [NSScreen screens];
    if(!allScreens || allScreens.count<=0)
        return nil;
    for (int i = 0; i< allScreens.count; i++ ) {
        NSScreen* theScreen = [allScreens objectAtIndex:i];
        NSDictionary *screenDescription = [theScreen deviceDescription];
        NSNumber* screenIDNumber = [screenDescription objectForKey:@"NSScreenNumber"];
        displayScreenStr = [displayScreenStr stringByAppendingString:[NSString stringWithFormat:@"%d, %@ %C", i, [screenIDNumber stringValue],(unichar)NSParagraphSeparatorCharacter]];
    }
    // NSLog(@"First screen display ID:%d", tmpDisplayId);
    return displayScreenStr;
}

#pragma mark - network service delegate
- (void)onProxySettingNotification:(ZoomSDKProxySettingHelper*)proxyHelper
{
    ZoomSDKProxySettingHelper* helper = proxyHelper;
    NSString* host = [helper getProxyHost];
    NSString* desc = [helper getProxyDescription];
    int port = [helper getProxyPort];
    NSLog(@"Proxy setting, Host:%@, description:%@, port:%d", host, desc, port);
    [helper proxyAuth:@"kelvin" password:@"hello"];
    
}

#pragma mark - window delegate
-(void)windowWillClose:(NSNotification *)notification
{
    NSAlert* alert = [NSAlert alertWithMessageText:@"Do U want to quit the ZoomSDK Sample"
                                     defaultButton:@"Quit"
                                   alternateButton:@"Cancel"
                                       otherButton:@""
                         informativeTextWithFormat:@""];
    alert.icon = [[NSBundle mainBundle] imageForResource:@"ZoomLogo"];
    [alert beginSheetModalForWindow:nil
                      modalDelegate:self
                     didEndSelector:@selector(alertDidEnd:returnCode:contextInfo:)
                        contextInfo:(void*)100];
}

- (void)alertDidEnd:(NSAlert *)alert returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo
{
   if(1 == returnCode)
       [[NSApplication sharedApplication] terminate:nil];
   else
       [_mainWindow makeKeyAndOrderFront:nil];
}

@end
