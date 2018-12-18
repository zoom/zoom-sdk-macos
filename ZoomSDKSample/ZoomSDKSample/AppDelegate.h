//
//  AppDelegate.h
//  ZoomSDKSample
//
//  Created by TOTTI on 7/20/16.
//  Copyright © 2016 zoom.us. All rights reserved.
//
#import <Cocoa/Cocoa.h>
#import "ZoomSDK.h"
#import "ZSDKSettingWindowController.h"

@class ZoomSDKWindowController;
@class ZoomSDKScheduleWindowCtr;

@interface AppDelegate : NSObject <NSApplicationDelegate,NSWindowDelegate,ZoomSDKAuthDelegate, ZoomSDKMeetingServiceDelegate, ZoomSDKPremeetingServiceDelegate, ZoomSDKH323HelperDelegate,ZoomSDKRemoteControllerDelegate, ZoomSDKWaitingRoomDelegate, ZoomSDKPhoneHelperDelegate, ZoomSDKNetworkSeviceDelegate, ZoomSDKASControllerDelegate, ZoomSDKMeetingUIControllerDelegate, ZoomSDKMeetingActionControllerDelegate, ZoomSDKCustomizedAnnotationCtrlDelegate, ZoomSDKMeetingRecordDelegate, ZoomSDKOutlookPluginDelegate, ZoomSDKDirectShareHelperDelegate, ZoomSDKWebinarControllerDelegate>

{
    IBOutlet NSWindow* _mainWindow;
    IBOutlet NSTextField* _authResultField;
    IBOutlet NSTextField*  _authResultFieldWelcome;
    IBOutlet NSButton*    _sdkUserButton;
    IBOutlet NSButton*    _zoomUserButton;
    IBOutlet NSButton*    _devZoomAuth;
    //auth
    IBOutlet NSTextField* _webDomainField;
    IBOutlet NSTextField* _appKeyField;
    IBOutlet NSTextField* _appSecretField;
    
    //main window
    IBOutlet NSButton*    _startMeeting;
    IBOutlet NSButton*    _endMeeting;
    IBOutlet NSButton*    _preMeetingButton;
    IBOutlet NSButton*    _chatButton;
    IBOutlet NSButton*    _shareButton;
    IBOutlet NSButton*    _recordButton;
    IBOutlet NSButton*    _mainWindowButton;
    IBOutlet NSButton*    _logoutButton;
    IBOutlet NSButton*   _H323Button;
    IBOutlet NSButton*   _waitingRoomButton;
    IBOutlet NSButton*    _calloutButton;
    IBOutlet NSButton*    _videoContainerButton;
    IBOutlet NSButton*   _multiShareButton;
    IBOutlet NSButton*   _participantsButton;
    
    //login
    IBOutlet NSTabView*   _tabView;
    IBOutlet NSTextField* _userNameField;
    IBOutlet NSTextField* _passwordField;
    IBOutlet NSTextField* _loginErrorField;
    IBOutlet NSButton*    _loginButton;
    IBOutlet NSButton*    _rememberMeButton;
    IBOutlet NSTextField* _connectLabel;
    IBOutlet NSTextField* _ssoTokenField;
    IBOutlet NSButton*    _enableSSOButton;
    //remote control
    IBOutlet NSTextField* _remoteControlMsgField;

    IBOutlet NSButton*    _revokeRemoteControl;
    IBOutlet NSButton*    _declineRemoteControl;
    //pre meeting
    IBOutlet NSButton*    _scheduleMeeting;
    IBOutlet NSButton*    _updateMeeting;
    IBOutlet NSButton*    _deleteMeeting;
    IBOutlet NSButton*    _listMeeting;
    IBOutlet NSTextField* _meetingNumber;
    IBOutlet NSTextView*  _meetingListContent;
    IBOutlet NSTextField* _preMeetingError;
    IBOutlet NSTextField* _listMeetingError;
    
    //start && join meeting
    IBOutlet NSTextField* _startMeetingNum;
    IBOutlet NSTextField* _sdkUserID;
    IBOutlet NSTextField* _sdkUserToken;
    IBOutlet NSTextField* _startUserName;
    IBOutlet NSTextField* _zak;
    IBOutlet NSTextField* _joinMeetingNum;
    IBOutlet NSTextField* _joinUserName;
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
    IBOutlet NSTextView*  _audioInfoView;
    
    IBOutlet NSImageView* _logoView;
    IBOutlet NSProgressIndicator* _indicator;
    IBOutlet NSProgressIndicator* _recordIndicator;
    IBOutlet NSTextField* _recordConvertFinishLabel;
    IBOutlet NSTextField* _receivedMsgContent;
    IBOutlet NSTextField* _sendMsgContent;

    //share
    IBOutlet NSTextField* _selectedScreenField;
    IBOutlet NSTextView*  _shareStatusMsgView;
    
    //multi-share
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
    
    //Message Info
    IBOutlet NSTextView* _meetingActionInfo;
    //Waiting Room
    IBOutlet NSTextView* _waitingRoomUserInfo;
    IBOutlet NSTextView* _waitingRoomStatusInfo;
    IBOutlet NSTextField* _selectedWaitingUser;
    
    //Phone Call out
    IBOutlet NSTextField*  _countryCode;
    IBOutlet NSTextField*  _phoneNumber;
    IBOutlet NSTextField*  _userName;
    IBOutlet NSTextView*  _calloutStatusInfo;
    
    //webinar customized ui
    IBOutlet NSTabView*  _webinarTabView;
    IBOutlet NSButton*  _promoteAttendee2Panelist;
    IBOutlet NSButton*  _depromotePanelist2Attendee;
    IBOutlet NSButton*  _allowAttendeeTalk;
    IBOutlet NSButton*  _disallowAttendeeTalk;
    IBOutlet NSButton*  _allowPanelistStartVideo;
    IBOutlet NSButton*  _disallowPanelistStartVideo;
    IBOutlet NSButton*  _allowAttendeeChat;
    IBOutlet NSButton*  _disallowAttendeeChat;
    
    IBOutlet NSButton*  _isSupportAttendeeTalk;
    IBOutlet NSButton*  _isAllowAttendeeChat;
    IBOutlet NSButton*  _isAllowPanelistStartVideo;
    IBOutlet NSTextField*  _selectedUser;
    
    IBOutlet NSTextView*  _panelistListView;
    IBOutlet NSTextView*  _attendeeListView;
    IBOutlet NSTextView*  _waitingRoomListView;
    IBOutlet NSButton*    _WebinarControlButton;
    IBOutlet NSButton*    _refreshUserListButton;

    //test new sdk
    ZoomSDKWindowController* _wndCtrl;
    ZoomSDKWindowController* _shareCtrl;
    ZoomSDKWindowController* _shareCameraWindowCtrl;

    IBOutlet NSTextView*                   _videoInfoView;
    IBOutlet NSTextField*                  _selectedVideoUser;
    
    ZoomSDKPreViewVideoElement* previewElement;
    ZoomSDKNormalVideoElement* newUserVideo1;
    ZoomSDKNormalVideoElement* newUserVideo2;
    ZoomSDKNormalVideoElement* newUserVideo3;
    ZoomSDKActiveVideoElement* activeUserVideo;
    
    ZoomSDKShareElement* _shareElement;
    ZoomSDKDirectShareHandler* _dsHandler;

    //new schedule
    ZoomSDKScheduleWindowCtr*     _scheduleEditWindow;
    
    IBOutlet NSMenuItem*   _settingMenuItem;
    ZSDKSettingWindowController* _sdkSettingWindowController;
}
@property(nonatomic, retain) ZSDKSettingWindowController* sdkSettingWindowController;
-(IBAction)onShowCustomizedSetting:(id)sender;

//webinar
-(IBAction)promoteAttendee2Panelist:(id)sender;
-(IBAction)depromotePanelist2Attendee:(id)sender;
-(IBAction)allowAttendeeTalk:(id)sender;
-(IBAction)disallowAttendeeTalk:(id)sender;
-(IBAction)allowPanelistStartVideo:(id)sender;
-(IBAction)disallowPanelistStartVideo:(id)sender;
-(IBAction)allowAttendeeChat:(id)sender;
-(IBAction)disallowAttendeeChat:(id)sender;
-(IBAction)navigatorToWebinarControTab:(id)sender;
-(IBAction)refreshUserList:(id)sender;


-(IBAction)clickAuthDevZoom:(id)sender;
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
-(IBAction)clickWaitingRoom:(id)sender;
-(IBAction)clickPhoneCallout:(id)sender;
-(IBAction)clickVideoContainer:(id)sender;

-(IBAction)sdkAuth:(id)sender;
-(IBAction)loginZoom:(id)sender;
-(IBAction)enableSSO:(id)sender;
-(IBAction)startMeeting:(id)sender;
-(IBAction)endMeeting:(id)sender;
-(IBAction)joinMeeting:(id)sender;
-(IBAction)joinWebinar:(id)sender;
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
-(IBAction)switchMiniVideoMode:(id)sender;
-(IBAction)showFitToolBar:(id)sender;
-(IBAction)hideFitToolBar:(id)sender;
-(IBAction)showThumbnailVideo:(id)sender;
-(IBAction)hideThumbnailVideo:(id)sender;

//remote control
-(IBAction)requestRemoteControl:(id)sender;
-(IBAction)giveupRemoteControl:(id)sender;
-(IBAction)giveRemoteControlTo:(id)sender;
-(IBAction)revokeRemoteControl:(id)sender;
-(IBAction)declineRemoteControl:(id)sender;

//share
-(IBAction)getScreenID:(id)sender;
-(IBAction)lockShare:(id)sender;
-(IBAction)startShare:(id)sender;
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
-(IBAction)showScheduleWindow:(id)sender;

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

//Waiting Room
- (IBAction)getWaitingRoomUsers:(id)sender;
- (IBAction)admitToMeeting:(id)sender;
- (IBAction)putIntoWaitingRoom:(id)sender;

//Phone Call Out
- (IBAction)callOutInviteUser:(id)sender;
- (IBAction)cancelCallOut:(id)sender;

//video container
- (IBAction)subscribeUser:(id)sender;
- (IBAction)unSubscribeUser:(id)sender;
- (IBAction)hideVideoRender:(id)sender;
- (IBAction)showVideoRender:(id)sender;

//new sdk share
- (IBAction)viewNewShare:(id)sender;
//direct share
- (IBAction)startDS:(id)sender;
- (IBAction)stopDS:(id)sender;
- (IBAction)cancelDS:(id)sender;
- (IBAction)startShareWhiteBoard:(id)sender;
- (IBAction)startShareFrame:(id)sender;
- (IBAction)startShareAudio:(id)sender;
- (IBAction)stopShare:(id)sender;
@end

