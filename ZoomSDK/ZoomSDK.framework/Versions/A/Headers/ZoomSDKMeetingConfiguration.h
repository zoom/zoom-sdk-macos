//
//  ZoomSDKMeetingConfiguration.h
//  ZoomSDK
//
//  Created by TOTTI on 8/4/17.
//  Copyright © 2017 TOTTI. All rights reserved.
//
#import "ZoomSDKErrors.h"
@interface ZoomSDKMeetingConfiguration :NSObject
{
    //app ID for share
    CGDirectDisplayID  _displayAppID;
    //monitor ID for share
    CGDirectDisplayID  _monitorID;
    //floatVideo position
    NSPoint            _floatVideoPoint;
    //sharing ToolBar Visible
    BOOL               _shareToolBarVisible;
    // main toolbar visible
    BOOL               _mainToolBarVisible;
    //main video position
    NSPoint            _mainVideoPoint;
    //waiting for host window visible
    BOOL               _jbhWindowVisible;
    //mute on entry
    BOOL               _enableMuteOnEntry;
    //play chime or not
    BOOL               _enableChime;
    //direct share desktop or not
    BOOL               _isDirectShareDesktop;
    //Enable auto adjust the volume of the speaker when you join audio
    BOOL               _enableAutoAdjustSpeakerVolume;
    //Enable auto adjust the volume of the mic when you join audio.
    BOOL                _enableAutoAdjustMicVolume;
    //Hide Meeting Info on Main window title
    BOOL                _hideMainWindowMeetingInfo;
    //new meeting number u want to set
    unsigned int        _newMeetingID;
    //disable join meeting popup wrong password window
    BOOL                _disablePopupWrongPasswordWindow;
    //Auto adjust speaker volume when join audio after meeting launched
    BOOL                _autoAdjustSpeakerVolumeWhenJoinAudio;
    //Auto adjust mic volume when join audio after meeting launched
    BOOL                _autoAdjustMicVolumeWhenJoinAudio;
    //disable end other meeting alert u start meeting when u have a meeting aleady in progress
    BOOL                _disableEndOtherMeetingAlert;
    //disable join meeting popup input password window
    BOOL                _disableInputPasswordWindow;
    //disable double click to EnterFull screen
    BOOL                _disableDoubleClickToFullScreen;
    //hide thumbnail video
    BOOL                _hideThumbnailVideoWindow;
    //huawei security app name
    NSString*           _securityAppName;
    //disable rename in meeting
    BOOL                _disableRenameInMeeting;
    //disable share button origin click action
    BOOL                _disableShareButtonClickOriginAction;
    //need prefill webinar Join Info
    BOOL                _needPrefillWebinarJoinInfo;
    //hide leave/end meeting confirm window
    BOOL                _hideLeaveMeetingWindow;
    //disable participants button origin click action
    BOOL                _disableParticipantButtonClickOriginAction;
    //JD hide full phone number for pure call in user
    BOOL _hideFullPhoneNumber4PureCallinUser;
    //hide telephone in audio info window
    BOOL _hideTelephoneInAudiowWindow;
    //hide call me in audio info window
    BOOL _hideCallMeInAudioWindow;
    //JD add an option to disable Multi-Share
    BOOL                _forceDisableMultiShare;
    //enable global shortcuts in confui
    BOOL                _enableGlobalShortcuts;
    BOOL                _disableCustomLiveStreamAction;
    //free user
    BOOL                _disableFreeUserOriginAction;
}
@property(nonatomic, assign)CGDirectDisplayID displayAppID;
@property(nonatomic, assign)CGDirectDisplayID monitorID;
@property(nonatomic, assign)NSPoint floatVideoPoint;
@property(nonatomic, assign)NSPoint mainVideoPoint;
@property(nonatomic, assign)BOOL shareToolBarVisible;
@property(nonatomic, assign)BOOL jbhWindowVisible;
@property(nonatomic, assign)BOOL enableMuteOnEntry;
@property(nonatomic, assign)BOOL isDirectShareDesktop;
@property(nonatomic, assign)BOOL enableChime;
@property(nonatomic, assign)BOOL mainToolBarVisible;
@property(nonatomic, assign)BOOL hideMainWindowMeetingInfo;
@property(nonatomic, assign)unsigned int newMeetingID;
@property(nonatomic, assign)BOOL disablePopupWrongPasswordWindow;
@property(nonatomic, assign)BOOL autoAdjustSpeakerVolumeWhenJoinAudio;
@property(nonatomic, assign)BOOL autoAdjustMicVolumeWhenJoinAudio;
@property(nonatomic, assign)BOOL disableEndOtherMeetingAlert;
@property(nonatomic, assign)BOOL disableInputPasswordWindow;
@property(nonatomic, assign)BOOL disableDoubleClickToFullScreen;
@property(nonatomic, assign)BOOL hideThumbnailVideoWindow;
@property(nonatomic, retain)NSString* securityAppName;
@property(nonatomic, assign)BOOL disableRenameInMeeting;
@property(nonatomic, assign)BOOL disableShareButtonClickOriginAction;
@property(nonatomic, assign)BOOL needPrefillWebinarJoinInfo;
@property(nonatomic, assign)BOOL hideLeaveMeetingWindow;
@property(nonatomic, assign)BOOL disableParticipantButtonClickOriginAction;
@property(nonatomic, assign)BOOL hideFullPhoneNumber4PureCallinUser;
@property(nonatomic, assign)BOOL hideTelephoneInAudiowWindow;
@property(nonatomic, assign)BOOL hideCallMeInAudioWindow;
@property(nonatomic, assign)BOOL forceDisableMultiShare;
@property(nonatomic, assign)BOOL enableGlobalShortcuts;
@property(nonatomic, assign)BOOL disableCustomLiveStreamAction;
@property(nonatomic, assign)BOOL disableFreeUserOriginAction;

- (ZoomSDKError)prefillWebinarUserName:(NSString*)userName Email:(NSString*)email;
- (ZoomSDKError)hideSDKButtons:(BOOL)hide ButtonType:(SDKButton)button;

/**
 @note
 @param modify Set YES if u want to change meeting number of window title
 @meetingnumber  specific number you want to replace
 set newMeetingNum = 0 if u want to hide the window title just show Zoom, set else num to replace.
 */
- (ZoomSDKError)modifyWindowTitle:(BOOL)modify NewMeetingNum:(unsigned int)meetingnumber;

/**
 @note need both input the videoDSCP and audioDSCP if u want to modify.
 @param videoDSCP Set int value if u want to change Video DSCP
 @param audioDSCP Set int value if u want to change Audio DSCP
 */
- (ZoomSDKError)modifyVideoDSCP:(int)videoDSCP AudioDSCP:(int)audioDSCP;

- (void)reset;

@end


