//
//  AppDelegate.h
//  ZoomSDKSample
//
//  Created by TOTTI on 7/20/16.
//  Copyright © 2016 TOTTI. All rights reserved.
//
#import <Cocoa/Cocoa.h>
#import "ZoomSDK.h"

@interface AppDelegate : NSObject <NSApplicationDelegate,ZoomSDKAuthDelegate, ZoomSDKMeetingServiceDelegate, ZoomSDKPremeetingServiceDelegate, ZoomSDKH323HelperDelegate>

{
    IBOutlet NSWindow* _mainWindow;
    IBOutlet NSTextField* _authResultField;
    IBOutlet NSTextField*  _authResultFieldWelcome;
    IBOutlet NSButton*    _sdkUserButton;
    IBOutlet NSButton*    _zoomUserButton;
    
    IBOutlet NSButton*    _startMeeting;
    IBOutlet NSButton*    _endMeeting;
    IBOutlet NSButton*    _preMeetingButton;
    IBOutlet NSButton*    _chatButton;
    IBOutlet NSButton*    _shareButton;
    IBOutlet NSButton*    _recordButton;
    IBOutlet NSButton*    _mainWindowButton;
    IBOutlet NSButton*    _logoutButton;
     IBOutlet NSButton*   _H323Button;
    
    IBOutlet NSTabView*   _tabView;
    IBOutlet NSTextField* _userNameField;
    IBOutlet NSTextField* _passwordField;
    IBOutlet NSTextField* _loginErrorField;
    IBOutlet NSButton*    _loginButton;
    IBOutlet NSButton*    _rememberMeButton;
    IBOutlet NSTextField* _connectLabel;
    //remote control
    IBOutlet NSTextField* _remoteControlMsgField;

    IBOutlet NSButton*    _revokeRemoteControl;
    IBOutlet NSButton*    _declineRemoteControl;
    //pre meeting
    IBOutlet NSButton*    _scheduleMeeting;
    IBOutlet NSButton*    _updateMeeting;
    IBOutlet NSButton*    _deleteMeeting;
    IBOutlet NSButton*    _listMeeting;
    IBOutlet NSTextField* _meetingTopic;
    IBOutlet NSTextField* _meetingPassword;
    IBOutlet NSTextField* _meetingDuration;
    IBOutlet NSTextField* _meetingNumber;
    IBOutlet NSTextView*  _meetingListContent;
    IBOutlet NSButton*    _usePMI;
    IBOutlet NSButton*    _turnOffVideoForHost;
    IBOutlet NSButton*    _turnOffVideoForAttende;
    IBOutlet NSButton*    _joinBeforeHost;
    IBOutlet NSTextField* _preMeetingError;
    IBOutlet NSTextField* _listMeetingError;

    //H323
    IBOutlet NSTextField* _pairCode;
    IBOutlet NSTextField* _meetingNum;
    IBOutlet NSTextField* _deviceName;
    IBOutlet NSTextField* _deviceIP;
    IBOutlet NSTextField* _deviceE164Num;
    IBOutlet NSTextView*  _deviceAddress;
    IBOutlet NSButton*    _pairButton;
    IBOutlet NSButton*    _callOutDevice;
    IBOutlet NSButton*    _cancelCallout;
    IBOutlet NSButton*    _getDeviceAddress;
    IBOutlet NSPopUpButton*  _deviceTypeButton;
    //Participants
    IBOutlet NSTextView*  _participantsListView;
    IBOutlet NSTextField* _selectedUserID;
    IBOutlet NSButton*    _getParticipantsButton;
    IBOutlet NSButton*    _pinVideo;
    IBOutlet NSButton*    _spotlightVideo;
    
    IBOutlet NSImageView* _logoView;
    IBOutlet NSProgressIndicator* _indicator;
    IBOutlet NSProgressIndicator* _recordIndicator;
    IBOutlet NSTextField* _recordConvertFinishLabel;
    IBOutlet NSTextField* _receivedMsgContent;
    IBOutlet NSTextField* _sendMsgContent;

    //multi-share
    IBOutlet NSTextView*  _shareStatusMsgView;
    IBOutlet NSTextField* _sharerUserID;
    IBOutlet NSTextView*  _sharerListView;
    IBOutlet NSButton*    _startAnotationButton;
    IBOutlet NSButton*    _viewShareButton;
    IBOutlet NSPopUpButton*  _screenTypeSelectButton;
    IBOutlet NSButton*    _annotationSelf;
    IBOutlet NSButton*    _shareOnSecondScreenButton;
    unsigned int _userID;
    BOOL     _hasLogined;
    H323DeviceType _selectDeviceType;
    ScreenType     _screenType;
}

-(IBAction)clickSDKUser:(id)sender;
-(IBAction)clickZoomUser:(id)sender;
-(IBAction)clickChat:(id)sender;
-(IBAction)clickShare:(id)sender;
-(IBAction)clickRecord:(id)sender;
-(IBAction)clickPremeeting:(id)sender;
-(IBAction)clickMainWindow:(id)sender;
-(IBAction)clickH323:(id)sender;
-(IBAction)clickModifyParticipants:(id)sender;
-(IBAction)clickMultiShare:(id)sender;

-(IBAction)sdkAuth:(id)sender;
-(IBAction)loginZoom:(id)sender;
-(IBAction)startMeeting:(id)sender;
-(IBAction)endMeeting:(id)sender;
-(IBAction)joinMeeting:(id)sender;
-(IBAction)logout:(id)sender;
//chatWindow
-(IBAction)showChatDlg:(id)sender;
-(IBAction)showChatDlgInPanel:(id)sender;
-(IBAction)hideChatDlg:(id)sender;

//participants window
-(IBAction)showParticipantsDlg:(id)sender;
-(IBAction)showParticipantsDlgInPanel:(id)sender;
-(IBAction)hideParticipantsDlg:(id)sender;

//audio window
-(IBAction)showAudioDlg:(id)sender;
-(IBAction)hideAudioDlg:(id)sender;
//setting window
-(IBAction)showSettingDlg:(id)sender;
-(IBAction)hideSettingDlg:(id)sender;
// toolbar 
-(IBAction)showConfToolbar:(id)sender;
-(IBAction)hideConfToolbar:(id)sender;

-(IBAction)showFitToolBar:(id)sender;
-(IBAction)hideFitToolBar:(id)sender;

//remote control
-(IBAction)requestRemoteControl:(id)sender;
-(IBAction)giveupRemoteControl:(id)sender;
-(IBAction)giveRemoteControlTo:(id)sender;
-(IBAction)revokeRemoteControl:(id)sender;
-(IBAction)declineRemoteControl:(id)sender;

//share
-(IBAction)lockShare:(id)sender;
-(IBAction)startShare:(id)sender;
-(IBAction)enterShareFullWindowMode:(id)sender;
-(IBAction)minimizeFloatWnd:(id)sender;
-(IBAction)maxFloatWnd:(id)sender;
-(IBAction)swithFloatWndToActiveSpk:(id)sender;
-(IBAction)swithFloatWndToGallery:(id)sender;

//annotation
-(IBAction)setEraser:(id)sender;
-(IBAction)setPen:(id)sender;
-(IBAction)setNone:(id)sender;
-(IBAction)clearAll:(id)sender;
-(IBAction)clearMine:(id)sender;
-(IBAction)redo:(id)sender;
-(IBAction)undo:(id)sender;


-(IBAction)sendHello:(id)sender;
-(IBAction)startRecording:(id)sender;
-(IBAction)stopRecording:(id)sender;
-(IBAction)startAnnotation:(id)sender;
-(IBAction)stopAnnotation:(id)sender;
-(IBAction)showNoVideoUserOnWall:(id)sender;
-(IBAction)hideNoVideoUserOnWall:(id)sender;

-(IBAction)enterFullScreen:(id)sender;
-(IBAction)exitFullScreen:(id)sender;
-(IBAction)switchToActiveSpkView:(id)sender;
-(IBAction)switchToWallView:(id)sender;
-(IBAction)enableMuteOnEntry:(id)sender;
-(IBAction)onBackClicked:(id)sender;
-(IBAction)onBackToUserClicked:(id)sender;
-(IBAction)onBackToLoginClicked:(id)sender;


//premeeting

-(IBAction)scheduleMeeting:(id)sender;
-(IBAction)deleteMeeting:(id)sender;
-(IBAction)updateMeeting:(id)sender;
-(IBAction)listMeeting:(id)sender;

//H323 support
- (IBAction)sendPairCode:(id)sender;
- (IBAction)getH323DeviceAddress:(id)sender;
- (IBAction)calloutDevice:(id)sender;
- (IBAction)cancelCalloutDevice:(id)sender;

//Participants
-(IBAction)getParticipantsList:(id)sender;
//Pin Video
- (IBAction)pinVideo:(id)sender;
//Spotlight Video
- (IBAction)spotLightVideo:(id)sender;
//multishare
- (IBAction)viewShare:(id)sender;
- (IBAction)getSharerList:(id)sender;

@end

