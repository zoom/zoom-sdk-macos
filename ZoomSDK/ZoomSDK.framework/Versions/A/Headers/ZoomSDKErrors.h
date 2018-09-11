//
//  ZoomSDKErrors.h
//  ZoomSDK
//
//  Created by TOTTI on 7/18/16.
//  Copyright (c) 2016 Zoom Video Communications, Inc. All rights reserved.
//
#pragma once

//Client Key or Secret is empty
#define kSDKAuthKeyOrSecretEmpty        300
//Client Key or Secret is wrong
#define kSDKAuthKeyOrSecretWrong        3023
//Account does not support SDK feature
#define kSDKAuthAccountNotSupport       3024
//Account has not enabled SDK feature
#define kSDKAuthAccountNotEnableSDK     3025

/** 
 @enum: different user type for sdk
 */
typedef enum {
    //API user type
    ZoomSDKUserType_APIUser     = 99,
    //Work email user type
    ZoomSDKUserType_ZoomUser    = 100,
    //Single-sign-on user type
    ZoomSDKUserType_SSOUser     = 101,
}ZoomSDKUserType;


typedef enum {
    SDKUserType_APIUser,
    SDKUserType_EmailLogin,
    SDKUserType_FaceBook,
    SDKUserType_GoogleOAuth,
    SDKUserType_SSO,
    SDKUserType_Unknown,
}SDKUserType;
/**
 @enum: leave meeting action command
 */
typedef enum {
    //Leave meeting
    LeaveMeetingCmd_Leave,
    //End Meeting
    LeaveMeetingCmd_End,
}LeaveMeetingCmd;

/**
 @enum: action meetting command
 */
typedef enum{
    //video cmd
    ActionMeetingCmd_MuteVideo,
    ActionMeetingCmd_UnMuteVideo,
    //audio cmd
    ActionMeetingCmd_MuteAudio,
    ActionMeetingCmd_UnMuteAudio,
    //can unmute by self when mute by host
    ActionMeetingCmd_EnableUnmuteBySelf,
    ActionMeetingCmd_DisableUnmuteBySelf,
    //mute/unmute all only for host
    ActionMeetingCmd_MuteAll,
    ActionMeetingCmd_UnmuteAll,
    //lock meeting cmd
    ActionMeetingCmd_LockMeeting,
    ActionMeetingCmd_UnLockMeeting,
    //remote control cmd
    ActionMeetingCmd_RequestRemoteControl,
    ActionMeetingCmd_GiveUpRemoteControl,
    ActionMeetingCmd_GiveRemoteControlTo,
    ActionMeetingCmd_DeclineRemoteControlRequest,
    ActionMeetingCmd_RevokeRemoteControl,
    //lock share cmd
    ActionMeetingCmd_LockShare,
    ActionMeetingCmd_UnlockShare,
    //lower all hands
    ActionMeetingCmd_LowerAllHands,
    //switch share mode
    ActionMeetingCmd_ShareFitWindowMode,
    ActionMeetingCmd_ShareOriginSizeMode,
    //Pin video
    ActionMeetingCmd_PinVideo,
    ActionMeetingCmd_UnPinVideo,
    //spotlight video
    ActionMeetingCmd_SpotlightVideo,
    ActionMeetingCmd_UnSpotlightVideo,
    //pause share
    ActionMeetingCmd_PauseShare,
    //resume share
    ActionMeetingCmd_ResumeShare,
    //Join Voip
    ActionMeetingCmd_JoinVoip,
    //Leave Voip
    ActionMeetingCmd_LeaveVoip,
    
}ActionMeetingCmd;

/**
 @enum: get meeting default info command (NSString type)
 */
typedef enum {
    MeetingPropertyCmd_Topic,
    MeetingPropertyCmd_InviteEmailTemplate,
    MeetingPropertyCmd_InviteEmailTitle,
    MeetingPropertyCmd_JoinMeetingUrl,
    MeetingPropertyCmd_DefaultRecordPath,
    MeetingPropertyCmd_MeetingNumber,
    MeetingPropertyCmd_HostTag,
    MeetingPropertyCmd_MeetingID,
}MeetingPropertyCmd;

/**
 @enum: Annotation tool selected command
 */
typedef enum{
    AnnotationToolType_None,
    AnnotationToolType_Pen,
    AnnotationToolType_HighLighter,
    AnnotationToolType_AutoLine,
    AnnotationToolType_AutoRectangle,
    AnnotationToolType_AutoEllipse,
    AnnotationToolType_AutoArrow,
    AnnotationToolType_AutoRectangleFill,
    AnnotationToolType_AutoEllipseFill,
    AnnotationToolType_SpotLight,
    AnnotationToolType_Arrow,
    AnnotationToolType_ERASER,
}AnnotationToolType;

/**
 @enum: Annotation clear type selected command
 */
typedef enum{
    AnnotationClearType_All,
    AnnotationClearType_Self,
    AnnotationClearType_Other,
}AnnotationClearType;

/**
 @enum: In meeting UI component selected command
 */
typedef enum{
    MeetingComponent_MainWindow,
    MeetingComponent_Audio,
    MeetingComponent_Chat,
    MeetingComponent_Participants,
    MeetingComponent_MainToolBar,
    MeetingComponent_MainShareToolBar,
    MeetingComponent_AuxShareToolBar,
    MeetingComponent_Setting,
    MeetingComponent_JBHWindow,
    MeetingComponent_ShareOptionWindow,
    MeetingComponent_ThumbnailVideo,
}MeetingComponent;

/**
 @enum: meeting setting command
 */
typedef enum{
    MeetingSettingCmd_DualScreenMode,
    MeetingSettingCmd_AutoJoinAudio,
    MeetingSettingCmd_AutoFitToWindowWhenViewShare,
    MeetingSettingCmd_AutoFullScreenWhenJoinMeeting,
    MeetingSettingCmd_EnableAutoAdjustMic,
    MeetingSettingCmd_EnableMuteOnEntry,
    MeetingSettingCmd_EnablePlayChimeWhenEnterOrExit,
}MeetingSettingCmd;

/**
 @enum: ZoomSDK common error
 */
typedef enum{
    ZoomSDKError_Success,
    ZoomSDKError_Failed,
    ZoomSDKError_Uninit,
    ZoomSDKError_ServiceFailed,
    ZoomSDKError_WrongUsage,
    ZoomSDKError_InvalidPrameter,
    ZoomSDKError_NoPermission,
    ZoomSDKError_NoRecordingInProgress,
    ZoomSDKError_UnKnow,
}ZoomSDKError;

/**
 @enum: ZoomSDKAuthService auth sdk error
 */
typedef enum {
    //Auth Success
    ZoomSDKAuthError_Success,
    //Key or Secret is wrong
    ZoomSDKAuthError_KeyOrSecretWrong,
    //Client Account does not support
    ZoomSDKAuthError_AccountNotSupport,
    //Client account does not enable SDK
    ZoomSDKAuthError_AccountNotEnableSDK,
    //Auth Unknown error
    ZoomSDKAuthError_Unknown,
}ZoomSDKAuthError;

/**
 @enum: ZoomSDKPreMeetingService error
 */
typedef enum {
    //Success
    ZoomSDKPremeetingError_Success,
    //Failed
    ZoomSDKPremeetingError_Failed,
    //time out
    ZoomSDKPremeetingError_TimeOut,
    //Unknown
    ZoomSDKPremeetingError_Unknown,
    
}ZoomSDKPremeetingError;

/*
 * @enum: ZoomSDKMeetingError
 * ============================
 * - ZoomSDKMeetingError_Success: start/join meeting successfully.
 * - ZoomSDKMeetingError_NetworkUnavailable: start/join meeting failed for network issue.
 * - ZoomSDKMeetingError_MeetingClientIncompatible: cannot start/join meeting for the client is too old.
 * - ZoomSDKMeetingError_UserFull: cannot start/join meeting for the meeting has reached a maximum of participant.
 * - ZoomSDKMeetingError_MeetingOver: cannot start/join meeting for the meeting is over.
 * - ZoomSDKMeetingError_MeetingNotExist: cannot start/join meeting for the meeting doest not exist.
 * - ZoomSDKMeetingError_MeetingLocked: cannot start/join meeting for the meeting was locked by host.
 * - ZoomSDKMeetingError_MeetingRestricted: cannot start/join meeting for the meeting restricted.
 * - ZoomSDKMeetingError_MeetingJBHRestricted: cannot start/join meeting for the meeting restricted for joining before host.
 */
typedef enum {
    //Success
    ZoomSDKMeetingError_Success                         = 0,
    //Network Unavailable
    ZoomSDKMeetingError_NetworkUnavailable              = 1,
    //Reconnect Fail
    ZoomSDKMeetingError_ReconnectFailed                 = 2,
    // MMR Erorr
    ZoomSDKMeetingError_MMRError                        = 3,
    // Password Error
    ZoomSDKMeetingError_PasswordError                   = 4,
    // Create Seession Error
    ZoomSDKMeetingError_SessionError                    = 5,
    //Meeting is over
    ZoomSDKMeetingError_MeetingOver                     = 6,
    //Meeting haven't start
    ZoomSDKMeetingError_MeetingNotStart                 = 7,
    //Meeting does not exist
    ZoomSDKMeetingError_MeetingNotExist                 = 8,
    //User is Full
    ZoomSDKMeetingError_UserFull                        = 9,
    //Client Version less than Min Version
    ZoomSDKMeetingError_ClientIncompatible              = 10,
    //No MMR ready for service
    ZoomSDKMeetingError_NoMMR                           = 11,
    //Meeting has been locked
    ZoomSDKMeetingError_MeetingLocked                   = 12,
    //Meeting Restricted
    ZoomSDKMeetingError_MeetingRestricted               = 13,
    //JBH Meeting Restricted
    ZoomSDKMeetingError_MeetingJBHRestricted            = 14,
    //Failed to send create meeting command to our web server. HTTP post fail
    ZoomSDKMeetingError_EmitWebRequestFailed            = 15,
    //identity token send from client expired
    ZoomSDKMeetingError_StartTokenExpired               = 16,
    //
    ZoomSDKMeetingError_VideoSessionError               = 17,
    ZoomSDKMeetingError_AudioAutoStartError             = 18,
    ZoomSDKMeetingError_RegisterWebinarFull             = 19,
    //Webinar
    ZoomSDKMeetingError_RegisterWebinarHostRegister     = 20,
    ZoomSDKMeetingError_RegisterWebinarPanelistRegister = 21,
    ZoomSDKMeetingError_RegisterWebinarDeniedEmail      = 22,
    ZoomSDKMeetingError_RegisterWebinarEnforceLogin     = 23,
    //ZC certificate changed
    ZoomSDKMeetingError_ZCCertificateChanged            = 24,
    //Failed to write to config file
    ZoomSDKMeetingError_ConfigFileWriteFailed           = 50,
    //Unknown error
    ZoomSDKMeetingError_Unknown                         = 100,
    ZoomSDKMeetingError_None                            = 101,
}ZoomSDKMeetingError;



/**
 @enum: ZoomSDK login status
 */
typedef enum {
    ZoomSDKLoginStatus_Idle, // Not login yet
    ZoomSDKLoginStatus_Success, // Login Success
    ZoomSDKLoginStatus_Failed,// Login Failed
    ZoomSDKLoginStatus_Processing // Login in progress
}ZoomSDKLoginStatus;


 /*
 @enum: ZoomSDKMeetingStatus
 * ============================
 * - ZoomSDKMeetingStatus_Idle: idle now, client can start/join meeting if wanted.
 * - ZoomSDKMeetingStatus_Connecting: the client is starting/joining meeting.
 * - ZoomSDKMeetingStatus_InMeeting: the client is a meeting now.
 */
typedef enum {
    //Idle
    ZoomSDKMeetingStatus_Idle             = 0,
    //Connecting
    ZoomSDKMeetingStatus_Connecting       = 1,
    //waiting for the host
    ZoomSDKMeetingStatus_WaitingForHost   = 2,
    //In Meeting
    ZoomSDKMeetingStatus_InMeeting        = 3,
    //Disconneting
    ZoomSDKMeetingStatus_Disconnecting    = 4,
    //Reconnecting
    ZoomSDKMeetingStatus_Reconnecting     = 5,
    //Connect Failed
    ZoomSDKMeetingStatus_Failed           = 6,
    //Meeting Ended
    ZoomSDKMeetingStatus_Ended            = 7,
    //State
    ZoomSDKMeetingStatus_AudioReady       = 8,
    //has other meeting in progress
    ZoomSDKMeetingStatus_OtherMeetingInProgress = 9,
    ZoomSDKMeetingStatus_InWaitingRoom      = 10,
    //for huawei
    ZoomSDKMeetingStatus_WaitExternalSessionKey =11,

}ZoomSDKMeetingStatus;

/**
 @enum: ZoomSDK share status
 */
typedef enum{
    ZoomSDKShareStatus_None,
    ZoomSDKShareStatus_SelfBegin,
    ZoomSDKShareStatus_SelfEnd,
    ZoomSDKShareStatus_OtherBegin,
    ZoomSDKShareStatus_OtherEnd,
    ZoomSDKShareStatus_ViewOther,
    ZoomSDKShareStatus_Pause,
    ZoomSDKShareStatus_Resume,
    ZoomSDKShareStatus_ContentTypeChange,
}ZoomSDKShareStatus;

/**
 @enum: ZoomSDK audio status
 */
typedef enum{
    ZoomSDKAudioStatus_None,
    ZoomSDKAudioStatus_Muted,
    ZoomSDKAudioStatus_UnMuted,
    ZoomSDKAudioStatus_MutedByHost,
    ZoomSDKAudioStatus_UnMutedByHost,
    ZoomSDKAudioStatus_MutedAllByHost,
    ZoomSDKAudioStatus_UnMutedAllByHost,
}ZoomSDKAudioStatus;

typedef enum{
    ZoomSDKAudioType_None,
    ZoomSDKAudioType_Voip,
    ZoomSDKAudioType_Phone,
    ZoomSDKAudioType_Unknow,
}ZoomSDKAudioType;
/**
 @enum: ZoomSDK remote control status
 */
typedef enum{
    ZoomSDKRemoteControlStatus_None,
    //viewer can request remote controll from sharer
    ZoomSDKRemoteControlStatus_CanRequestFromWho,
    //sharer receive request from viewer
    ZoomSDKRemoteControlStatus_RequestFromWho,
    //sharer decline your remote control request
    ZoomSDKRemoteControlStatus_DeclineByWho,
    //sharer has been remote controlled by viewer
    ZoomSDKRemoteControlStatus_RemoteControlledByWho,
    
    //notify controller changed
    ZoomSDKRemoteControlStatus_StartRemoteControllWho,
    ZoomSDKRemoteControlStatus_EndRemoteControllWho,

    //viewer get remote controll privilege
    ZoomSDKRemoteControlStatus_HasPrivilegeFromWho,
    //viewer lost remote controll privilege
    ZoomSDKRemoteControlStatus_LostPrivilegeFromWho,
}ZoomSDKRemoteControlStatus;

/**
 @enum: ZoomSDK Recording status
 */
typedef enum{
    ZoomSDKRecordingStatus_None,
    ZoomSDKRecordingStatus_Start,
    ZoomSDKRecordingStatus_Stop,
    ZoomSDKRecordingStatus_DiskFull,
}ZoomSDKRecordingStatus;

/**
 @enum: ZoomSDK Connection quality
 */
typedef enum{
    ZoomSDKConnectionQuality_Unknow,
    ZoomSDKConnectionQuality_VeryBad,
    ZoomSDKConnectionQuality_Bad,
    ZoomSDKConnectionQuality_NotGood,
    ZoomSDKConnectionQuality_Normal,
    ZoomSDKConnectionQuality_Good,
    ZoomSDKConnectionQuality_Excellent,
}ZoomSDKConnectionQuality;

/**
 @enum: ZoomSDK H323 device Callout Status
 */
typedef enum
{
    H323CalloutStatus_Unknown,
    H323CalloutStatus_Success,
    H323CalloutStatus_Ring,
    H323CalloutStatus_Timeout,
    H323CalloutStatus_Failed,
}H323CalloutStatus;

/**
 @enum: ZoomSDK H323 device pair Status
 */
typedef enum
{
    H323PairingResult_Unknown,
    H323PairingResult_Success,
    H323PairingResult_Meeting_Not_Exist,
    H323PairingResult_Paringcode_Not_Exist,
    H323PairingResult_No_Privilege,
    H323PairingResult_Other_Error,
}H323PairingResult;

/**
 @enum: ZoomSDK H323 device type
 */
typedef enum
{
    H323DeviceType_Unknown,
    H323DeviceType_H323,
    H323DeviceType_SIP,
}H323DeviceType;

/**
 @enum: ZoomSDK screen type for multi-share
 */
typedef enum
{
  ScreenType_First,
  ScreenType_Second,
}ScreenType;

/**
 @enum: ZoomSDK Meeting video UI Type
 */
typedef enum
{
   MeetingUIType_None,
   MeetingUIType_VideoWall,
   MeetingUIType_ActiveRender,
}MeetingUIType;

/**
 @enum: Join meeting requrire info type
 */
typedef enum
{
    JoinMeetingReqInfoType_None,
    JoinMeetingReqInfoType_Password,
    JoinMeetingReqInfoType_Password_Wrong,
}JoinMeetingReqInfoType;

/**
 @enum: Meeting type
 */
typedef enum
{
    MeetingType_None,
    MeetingType_Normal,
    MeetingType_BreakoutRoom,
    MeetingType_Webinar,
}MeetingType;

/**
 @enum: User Role type
 */
typedef enum
{
    UserRole_None,
    UserRole_Host,
    UserRole_CoHost,
    UserRole_Attendee,
    UserRole_Panelist,
    UserRole_BreakoutRoom_Moderator,
}UserRole;

/**
 @enum: Phone call status
 */
typedef enum
{
    PhoneStatus_None,
    PhoneStatus_Calling,
    PhoneStatus_Ringing,
    PhoneStatus_Accepted,
    PhoneStatus_Success,
    PhoneStatus_Failed,
    PhoneStatus_Canceling,
    PhoneStatus_Canceled,
    PhoneStatus_Cancel_Failed,
    PhoneStatus_Timeout,
}PhoneStatus;

/**
 @enum: Phone call failed reason
 */
typedef enum
{
    PhoneFailedReason_None,
    PhoneFailedReason_Busy,
    PhoneFailedReason_Not_Available,
    PhoneFailedReason_User_Hangup,
    PhoneFailedReason_Other_Fail,
    PhoneFailedReason_No_Answer,
    PhoneFailedReason_Block_No_Host,
    PhoneFailedReason_Block_High_Rate,
    PhoneFailedReason_Block_Too_Frequent,
}PhoneFailedReason;

/**
 @enum: share content type enum
 */
typedef enum
{
    ZoomSDKShareContentType_UNKNOWN, //unknown share
    ZoomSDKShareContentType_AS,	//application share
    ZoomSDKShareContentType_DS,	//desktop share
    ZoomSDKShareContentType_WB,	//whiteboard share
    ZoomSDKShareContentType_AIRHOST,	//mobile device from PC
    ZoomSDKShareContentType_CAMERA,	//camera share
    ZoomSDKShareContentType_DATA,	//data share
    ZoomSDKShareContentType_WIRED_DEVICE //wired device, connect between Mac and iPhone
}ZoomSDKShareContentType;

/*
@enum: call in number type
*/
typedef enum
{
    CallInNumberType_None,
    CallInNumberType_Toll,
    CallInNumberType_TollFree,
}CallInNumberType;

/*
@enum: hide button on fitbar or toolbar
*/
typedef enum
{
    ToolBarInviteButton,
    FitBarAudioButton,
    FitBarVideoButton,
    FitBarParticipantButton,
    FitBarNewShareButton,
    FitBarRemoteControlButton,
    FitBarPauseShareButton,
    FitBarAnnotateButton,
    FitBarQAButton,
    FitBarBroadcastButton,
    FitBarPolling,
    FitBarMoreButton,
    MainExitFullScreenButton,
}SDKButton;

typedef enum
{
    SecuritySessionComponet_Unknown,
    SecuritySessionComponet_Chat,
    SecuritySessionComponet_FT,
    SecuritySessionComponet_Audio,
    SecuritySessionComponet_Video,
    SecuritySessionComponet_AS,
}SecuritySessionComponet;

typedef enum
{
    StatisticWarningType_None,
    StatisticWarningType_NetworkBad,
    StatisticWarningType_CPUHigh,
    StatisticWarningType_SystemBusy,
}StatisticWarningType;


typedef enum{
    ConnectionComponent_None,
    ConnectionComponent_Share,
    ConnectionComponent_Video,
    ConnectionComponent_Audio,
}ConnectionComponent;

typedef enum{
    EndMeetingReason_None,
    EndMeetingReason_KickByHost,
    EndMeetingReason_EndByHost,
    EndMeetingReason_JBHTimeOut,
    EndMeetingReason_NoAttendee,
    EndMeetingReason_HostStartAnotherMeeting,
}EndMeetingReason;

// Huawei setting
typedef enum
{
    EncryptType_NO,
    EncryptType_YES,
    EncryptType_Auto
}EncryptType;

typedef enum{
    SettingConnectionType_Unknow,
    SettingConnectionType_P2P,
    SettingConnectionType_Cloud,
}SettingConnectionType;

typedef enum{
    SettingNetworkType_Unknow,
    SettingNetworkType_Wired,
    SettingNetworkType_WiFi,
    SettingNetworkType_PPP,
    SettingNetworkType_3G,
    SettingNetworkType_Other,
}SettingNetworkType;

// customized sdk
typedef enum{
    VideoRenderElementType_None,
    VideoRenderElementType_Preview,
    VideoRenderElementType_Active,
    VideoRenderElementType_Normal,
}VideoRenderElementType;

typedef enum{
    VideoRenderDataType_None,
    VideoRenderDataType_Video,
    VideoRenderDataType_Avatar,
}VideoRenderDataType;

typedef enum{
    ViewShareMode_FullFill,
    ViewShareMode_LetterBox,
}ViewShareMode;

typedef enum{
    AnnotationStatus_Ready,
    AnnotationStatus_Close,
    AnnotationStatus_None,
}AnnotationStatus;

typedef enum{
    LiveStreamStatus_None,
    LiveStreamStatus_InProgress,
    LiveStreamStatus_Connecting,
    LiveStreamStatus_StartFailedTimeout,
    LiveStreamStatus_StartFailed,
    LiveStreamStatus_Ended,
}LiveStreamStatus;

typedef enum{
    SDKReminderType_CanFreeTrial, // host
    SDKReminderType_CanUpgradeAccount, //host
    SDKReminderType_GuestReminder, //guest
    SDKReminderType_UpgradeSuccess,
    SDKReminderType_UpgradeFailed,
    SDKReminderType_None,
}SDKReminderType;

typedef enum{
    DirectShareStatus_None = 0,
    DirectShareStatus_Connecting,  //trying to start direct share, just waiting
    DirectShareStatus_InProgress, //in diret share mode
    DirectShareStatus_Ended,  //diret share is ended
    DirectShareStatus_NeedMeetingIDOrSharingKey, // need input a meeting id/sharing key
    DirectShareStatus_WrongMeetingIDOrSharingKey,
    DirectShareStatus_NetworkError, // network error. Try again later
    DirectShareStatus_Unknow,
}DirectShareStatus;
