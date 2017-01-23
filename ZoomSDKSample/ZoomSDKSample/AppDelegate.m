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

#define kZoomSDKAppKey      @""
#define kZoomSDKAppSecret   @""
#define kZoomSDKDomain      @""


#define kSDKUserID      @""
#define kSDKUserName    @""
#define kSDKUserToken   @""
#define kSDKMeetNumber  @""
#define kZoomPMINumber  @""
const unsigned int displayMainID = 69731458;
const unsigned int  displayAuxID = 724838613;

@interface AppDelegate ()
- (void) switchToZoomUserTab;
- (void) switchToMeetingTab;
@end

@implementation AppDelegate

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
    [_logoView setImage:[[NSBundle mainBundle] imageForResource:@"ZoomLogo"]];
    [_authResultField setHidden:YES];
    [_authResultFieldWelcome setHidden:YES];
    [_recordConvertFinishLabel setHidden:YES];
    [_mainWindow setLevel:NSPopUpMenuWindowLevel];
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
    [_deviceTypeButton removeAllItems];
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
    NSString *bundlePath = [[NSBundle mainBundle] privateFrameworksPath];
    bundlePath = [bundlePath stringByAppendingPathComponent:@"/ZoomSDK.framework"];
    [[ZoomSDK sharedSDK] setCustomBundlePath:bundlePath fileName:@"ZoomSDK"];

}
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    [[ZoomSDK sharedSDK] setZoomDomain:kZoomSDKDomain];
    
    

   
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
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
}
-(IBAction)sdkAuth:(id)sender
{
    [self authSDK:kZoomSDKAppKey appSecret:kZoomSDKAppSecret];
    [_connectLabel setStringValue:@"Start Authing..."];
    [self switchToConnectingTab];
}
-(IBAction)loginZoom:(id)sender
{
    [_authResultField setHidden:YES];
    ZoomSDKAuthService *authService = [[ZoomSDK sharedSDK] getAuthService];
    if (authService)
    {
        BOOL remember = [_rememberMeButton state]== NSOnState? YES:NO;
        [authService login: [_userNameField stringValue] Password:[_passwordField stringValue] RememberMe:remember];
        [self switchToConnectingTab];
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
    config.floatVideoPoint =  NSMakePoint(300, 300);
    config.mainToolBarVisible = YES;
    config.mainVideoPoint = NSMakePoint(200, 200);
    ZoomSDKError ret = ZoomSDKError_UnKnow;
    config.enableChime = YES;
    config.enableMuteOnEntry = YES;
    
    ZoomSDKSettingService* setting = [[ZoomSDK sharedSDK] getSettingService];
    [setting enableMeetingSetting:NO SettingCmd:MeetingSettingCmd_AutoFitToWindowWhenViewShare];
    [setting enableMeetingSetting:NO SettingCmd:MeetingSettingCmd_AutoFullScreenWhenJoinMeeting];
    [setting enableMeetingSetting:YES SettingCmd:MeetingSettingCmd_AutoJoinAudio];
    [setting enableMeetingSetting:YES SettingCmd:MeetingSettingCmd_DualScreenMode];
    if(meetingService)
    {
         if ([authService isAuthorized])
         {
              meetingService.delegate = self;
             if (_hasLogined) {
                 //for zoom user
                 ret =[meetingService startMeeting:ZoomSDKUserType_ZoomUser userID:nil userToken:nil displayName:nil meetingNumber:(NSString*)kZoomPMINumber isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO];
             }else{
                 //for api user
                 ret =[meetingService startMeeting:ZoomSDKUserType_APIUser userID:kSDKUserID userToken:kSDKUserToken displayName:kSDKUserName meetingNumber:kSDKMeetNumber isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO];
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
    config.mainVideoPoint = NSMakePoint(200, 200);
    config.enableChime = YES;
    config.enableMuteOnEntry = YES;
    ZoomSDKError ret = ZoomSDKError_UnKnow;
    if(meetingService)
    {
        if ([authService isAuthorized])
        {   meetingService.delegate = self;
            ret =[meetingService joinMeeting:ZoomSDKUserType_ZoomUser toke4enfrocelogin:nil webinarToken:nil  participantId:@"10" meetingNumber:@"7171717171" displayName:@"TOTTI" password:@"" isDirectShare:NO sharedApp:0 isVideoOff:NO isAuidoOff:NO];
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

-(IBAction)showFitToolBar:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
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
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    if ([_shareOnSecondScreenButton state] == NSOnState) {
        [controller showMeetingComponent:MeetingComponent_AuxShareToolBar window:nil show:NO InPanel:NO frame:NSZeroRect];
    }else{
        [controller showMeetingComponent:MeetingComponent_MainShareToolBar window:nil show:NO InPanel:NO frame:NSZeroRect];
    }
}


-(IBAction)requestRemoteControl:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_RequestRemoteControl userID:0 onScreen:_screenType];
    

}

-(IBAction)giveupRemoteControl:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_GiveUpRemoteControl userID:0 onScreen:_screenType];
    
    unsigned int userID;
   [meetingService getCurrentRemoteController:&userID];
    NSLog(@"Remote control ID:%d",userID);
}

-(IBAction)revokeRemoteControl:(id)sender
{
     ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_RevokeRemoteControl userID:_userID onScreen:_screenType];
}

-(IBAction)declineRemoteControl:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_DeclineRemoteControlRequest userID:_userID onScreen:_screenType];
}

-(IBAction)giveRemoteControlTo:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_GiveRemoteControlTo userID:_userID onScreen:_screenType];
}



-(IBAction)lockShare:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_LockShare userID:0 onScreen:ScreenType_First];
}

-(IBAction)enterShareFitWindowMode:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_ShareFitWindowMode userID:0 onScreen:_screenType];
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
        NSArray* userlist = [meetingService getParticipantsList];
        for (NSNumber*user in userlist) {
            NSLog(@"ATTEND USERID:%d", [user unsignedIntValue]);
            ZoomSDKUserInfo* userInfo = [meetingService getUserByUserID:[user unsignedIntValue]];
            if (![userInfo isHost]) {
                ZoomSDKError result = [meetingService sendChat:sendContent toUser:[user unsignedIntValue]];
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
    [meetingService startRecording:&starttimestamp saveFilePath:@"/Users/totti/Documents/record"];
    NSLog(@"record start time, %ld", starttimestamp);
}
-(IBAction)stopRecording:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    time_t stoptimestamp;
    [meetingService stopRecording:&stoptimestamp];
    NSLog(@"record stop time, %ld", stoptimestamp);
}

-(IBAction)startAnnotation:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    BOOL annotateSelf =[_annotationSelf state] == NSOnState? YES: NO;
   [meetingService startAnnotation:annotateSelf Position:NSMakePoint(1000, 500) onScreen:_screenType];
   // [meetingService startAnnotation:NSMakePoint(800, 500) onScreen:ScreenType_First];
    ZoomSDKAnnotationController* controller = [meetingService getAnnotationController:_screenType];
    [controller setColor:0.8f Green:0.8f Black:0.8f onScreen:_screenType];
    [controller setLineWidth: 5 onScreen:_screenType];
    
}

-(IBAction)stopAnnotation:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    BOOL annotateSelf =[_annotationSelf state] == NSOnState? YES: NO;

    [meetingService stopAnnotation:annotateSelf onScreen:_screenType];
}

-(IBAction)showNoVideoUserOnWall:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    
    [meetingService hideOrShowNoVideoUserOnVideoWall:NO];
}

-(IBAction)hideNoVideoUserOnWall:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    
    [meetingService hideOrShowNoVideoUserOnVideoWall:YES];
}


-(IBAction)startShare:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    if ([_shareOnSecondScreenButton state] == NSOnState) {
        [meetingService startMonitorShare:displayAuxID];
    }else
    {
         [meetingService startMonitorShare:displayMainID];
    }
    
    
}

-(IBAction)setEraser:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController:_screenType];
    [annotation setTool:AnnotationToolType_ERASER onScreen:_screenType];
}

-(IBAction)setPen:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController:_screenType];
    [annotation setTool:AnnotationToolType_Pen onScreen:_screenType];
}
-(IBAction)setNone:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController:_screenType];
    [annotation setTool:AnnotationToolType_None onScreen:_screenType];
}

-(IBAction)clearAll:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController:_screenType];
    [annotation clear:AnnotationClearType_All onScreen:_screenType];
}
-(IBAction)clearMine:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController:_screenType];
   [annotation clear:AnnotationClearType_Self onScreen:_screenType];
}
-(IBAction)redo:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController:_screenType];
    [annotation redo:_screenType];
}
-(IBAction)undo:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController:_screenType];
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
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService enableMuteOnEntry:YES];

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
            /*[meetingService actionMeetingWithCmd:ActionMeetingCmd_MuteVideo userID:0];
             move main video
             ZoomSDKMeetingUIController* UIController = [meetingService getMeetingUIController];
             if (!UIController) {
             return;
             }
             NSRect mainRect = NSMakeRect(100, 100, 200, 200);
             NSWindow* window = [[NSWindow alloc] init];
             [UIController showMeetingComponent:MeetingComponent_MainWindow window: &window show:YES frame:mainRect];
             
             test for add child window
             NSRect newRect  = NSMakeRect(100, 100, 400, 400);
             [window setLevel:NSPopUpMenuWindowLevel];
             [window setStyleMask:NSBorderlessWindowMask];
             ZoomSDKWindowController* ctrl = [[ZoomSDKWindowController alloc] init];
             [ctrl.window setLevel:NSPopUpMenuWindowLevel + 2];
             [ctrl.window setFrameOrigin:NSMakePoint(100, 100)];
             [ctrl.window addChildWindow:window ordered:NSWindowAbove];
             [window setFrame:newRect display:YES];
             [ctrl showWindow:nil];*/
            
            //test for setting camera list
            ZoomSDKSettingService* settingService = [[ZoomSDK sharedSDK] getSettingService];
            NSArray* array =  [settingService getCameraList];
            for(CameraInfo* info in array)
            {
                NSLog(@"App delegate camera list, deviceID:%@, deviceName:%@, isSelected:%d", [info getDeviceID], [info getDeviceName], [info isSelectedDevice]);
            }
            //h323 delegate
            ZoomSDKH323Helper* h323Helper = [meetingService getH323Helper];
            h323Helper.delegate = self;
        }
        break;
        case ZoomSDKMeetingStatus_AudioReady:
        {

        }
        break;
        default:
        {
            [self switchToMeetingTab];
            [_chatButton setEnabled:NO];
            [_recordButton setEnabled:NO];
            [_shareButton setEnabled:NO];
            [_mainWindowButton setEnabled:NO];
            [_endMeeting setEnabled:NO];
        }
        break;
    }
}

- (void)onUserAudioStatusChange:(NSArray*)userAudioStatusArray
{
    for (ZoomSDKUserAudioStauts* key in userAudioStatusArray) {
        unsigned int userID = [key getUserID];
        ZoomSDKAudioStatus status = [key getStatus];
        NSLog(@"user %d 's audio status changed to %d", userID, status);
    }
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
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    NSArray* participantsList = [meetingService getParticipantsList];
    NSString* listInfo = @"";
    for (NSNumber* user in participantsList) {
        ZoomSDKUserInfo* userInfo = [meetingService getUserByUserID:[user unsignedIntegerValue]];
        NSString* userName = [userInfo getUserName];
        NSString* userString = [NSString stringWithFormat:@"%@ %@ %C", userName, [user stringValue], (unichar)NSParagraphSeparatorCharacter];
        listInfo = [listInfo stringByAppendingString:userString];
    }
    _participantsListView.string = listInfo;
}
//Spotlight Video
- (IBAction)spotLightVideo:(id)sender
{
    
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    NSString* selectedUser = [_selectedUserID stringValue];
    unsigned int userid =(unsigned int)[selectedUser intValue];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_SpotlightVideo userID:userid onScreen:ScreenType_First];

}
- (IBAction)pinVideo:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    NSString* selectedUser = [_selectedUserID stringValue];
    unsigned int userid =(unsigned int)[selectedUser intValue];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_PinVideo userID:userid onScreen:_screenType];
}

- (IBAction)getSharerList:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    NSArray* participantsList = [meetingService getShareSourceList];
    NSString* listInfo = @"";
    for (NSNumber* user in participantsList) {
        ZoomSDKUserInfo* userInfo = [meetingService getUserByUserID:[user unsignedIntegerValue]];
        ZoomSDKShareSource* sharesource = [meetingService getShareSourcebyUserId:[user unsignedIntegerValue]];
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
    [meetingService viewShare:userid onScreen:_screenType];
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


@end
