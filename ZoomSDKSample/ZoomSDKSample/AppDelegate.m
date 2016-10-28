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

#define kZoomSDKAppKey      @"AO7Bg3SRPvUAABrhuOq4lVx9dDKzBVn0wCg4"
#define kZoomSDKAppSecret   @"SxPKrykwDPQIg9Bj4iy4yCnBE6WX9XOUO8BJ"
#define kZoomSDKDomain      @"dev.zoom.us"


#define kSDKUserID      @"0yVqVIaPRfq1E-auyi4YVA"
#define kSDKUserName    @"Totti Totti"
#define kSDKUserToken   @"R0wiSccvNPKjVAqbed7AJDjvLUc_bCLVW_o-tbCHCFA.BgMgQTYyYzlZdldJWkdaRFRXekZOb3c3QTlzYks0M1BFRVoAAAwzQ0JBdW9pWVMzcz0"
#define kSDKMeetNumber  @"2486572073"

@interface AppDelegate ()
- (void) switchToZoomUserTab;
- (void) switchToMeetingTab;
@end

@implementation AppDelegate

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
    [_logoView setImage:[[NSBundle mainBundle] imageForResource:@"ZoomLogo"]];
    [_authResultField setHidden:YES];
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

-(IBAction)onBackClicked:(id)sender
{
    [self switchToMeetingTab];
}

-(IBAction)onBackToUserClicked:(id)sender
{
    [self switchToUserTab];
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
    config.mainToolBarVisible = NO;
    config.mainVideoPoint = NSMakePoint(200, 200);
    ZoomSDKError ret = ZoomSDKError_UnKnow;
    config.enableChime = YES;
    config.enableMuteOnEntry = YES;
    
    ZoomSDKSettingService* setting = [[ZoomSDK sharedSDK] getSettingService];
    [setting enableMeetingSetting:YES SettingCmd:MeetingSettingCmd_AutoFitToWindowWhenViewShare];
    [setting enableMeetingSetting:YES SettingCmd:MeetingSettingCmd_AutoFullScreenWhenJoinMeeting];
    [setting enableMeetingSetting:YES SettingCmd:MeetingSettingCmd_AutoJoinAudio];
    [setting enableMeetingSetting:YES SettingCmd:MeetingSettingCmd_DualScreenMode];
    if(meetingService)
    {
         if ([authService isAuthorized])
         {
              meetingService.delegate = self;
             //for zoom user
             //ret =[meetingService startMeeting:ZoomSDKUserType_ZoomUser userID:nil userToken:nil displayName:nil meetingNumber:(NSString*)kSDKMeetNumber isDirectShare:NO sharedApp:0];
             //for api user
               ret =[meetingService startMeeting:ZoomSDKUserType_APIUser userID:kSDKUserID userToken:kSDKUserToken displayName:kSDKUserName meetingNumber:kSDKMeetNumber isDirectShare:NO sharedApp:0];
             
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
            ret =[meetingService joinMeeting:ZoomSDKUserType_ZoomUser toke4enfrocelogin:nil participantId:@"10" meetingNumber:@"7171717171" displayName:@"TOTTI" password:@"" isDirectShare:NO sharedApp:0];
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
    [controller showMeetingComponent:MeetingComponent_ShareToolBar window:nil show:YES InPanel:NO frame:NSZeroRect];
}
-(IBAction)hideFitToolBar:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKMeetingUIController* controller = [meetingService getMeetingUIController];
    [controller showMeetingComponent:MeetingComponent_ShareToolBar window:nil show:NO InPanel:NO frame:NSZeroRect];
}


-(IBAction)requestRemoteControl:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_RequestRemoteControl userID:0];
    

}

-(IBAction)giveupRemoteControl:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_GiveUpRemoteControl userID:0];
    
    unsigned int userID;
   [meetingService getCurrentRemoteController:&userID];
    NSLog(@"Remote control ID:%d",userID);
}

-(IBAction)revokeRemoteControl:(id)sender
{
     ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_RevokeRemoteControl userID:_userID];
}

-(IBAction)declineRemoteControl:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_DeclineRemoteControlRequest userID:_userID];
}

-(IBAction)giveRemoteControlTo:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_GiveRemoteControlTo userID:_userID];
}



-(IBAction)lockShare:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_LockShare userID:0];
}

-(IBAction)enterShareFullWindowMode:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    [meetingService actionMeetingWithCmd:ActionMeetingCmd_ShareFitWindowMode userID:0];
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

    [meetingService startAnnotation:NSMakePoint(800, 500)];
    ZoomSDKAnnotationController* controller = [meetingService getAnnotationController];
    [controller setColor:0.8f Green:0.8f Black:0.8f];
    [controller setLineWidth: 5];
    
}

-(IBAction)stopAnnotation:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    
    [meetingService stopAnnotation];
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
    [meetingService startMonitorShare:69731458];
}

-(IBAction)setEraser:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController];
    [annotation setTool:AnnotationToolType_ERASER];
}

-(IBAction)setPen:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController];
    [annotation setTool:AnnotationToolType_Pen];
}
-(IBAction)setNone:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController];
    [annotation setTool:AnnotationToolType_None];
}

-(IBAction)clearAll:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController];
    [annotation clear:AnnotationClearType_All];
}
-(IBAction)clearMine:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController];
   [annotation clear:AnnotationClearType_Self];
}
-(IBAction)redo:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController];
    [annotation redo];
}
-(IBAction)undo:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
    ZoomSDKAnnotationController* annotation = [meetingService getAnnotationController];
    [annotation undo];
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
    [_authResultField setHidden:NO];
    if(returnValue == ZoomSDKMeetingError_Success)
    {
        [self switchToUserTab];
    }else{
        [self switchToWelcomeTab];
        [_authResultField setStringValue:[NSString stringWithFormat:@"Auth Faild, Error:%d", returnValue]];
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
        }
            break;
        case ZoomSDKLoginStatus_Failed:
            [self switchToZoomUserTab];
            [_loginErrorField setHidden:NO];
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
    switch (status) {
        case ZoomSDKRemoteControlStatus_Request:
        {
            [_remoteControlMsgField setStringValue:[NSString stringWithFormat:@"User:%d is request Remote Control Now!", userID]];
               [_revokeRemoteControl setEnabled:YES];
               [_declineRemoteControl setEnabled:YES];
            _userID = userID;
            NSLog(@"Remote control Request ID:%d", _userID);
        }
           break;
        case ZoomSDKRemoteControlStatus_Accept:
        {
            
        }
            break;
        default:
            break;
    }
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




@end
