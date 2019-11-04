# CHANGELOG

## 2019-11-04 @ [v4.4.56627.1029](https://github.com/zoom/zoom-sdk-macos/releases/tag/v4.4.56627.1029)

## Added
* Add a new interface for ‘back to meeting’
  * `- (ZoomSDKError)backToMeeting` in `ZoomSDKMeetingUIController.h`
* Add a new interface for user to hide the “show keypad” button
  * Property `hideShowKeypadButton` in `ZoomSDKMeetingConfiguration.h`
* Add a new meeting status callback for user to join/leave breakout room meeting
  * `ZoomSDKMeetingStatus_Join_Breakout_Room` and `ZoomSDKMeetingStatus_Leave_Breakout_Room` in `ZoomSDKMeetingStatus`
* Add a new interface for the user to hide each setting item
  * `- (void)hideSettingComponent:(SettingComponent)component hide:(BOOL)hide` in  `ZoomSDKSettingService.h`
* Add a new interface for user to hide the “Copy URL” and the "Copy Invitation" button on the invite window
  * Property `hideCopyURLButtonWhenInviteOthers` in ZoomSDKMeetingConfiguration.h
  * Property `hideCopyInvitationButtonWhenInviteOthers` in ZoomSDKMeetingConfiguration.h
* Add a new interface for user to hide the items in the chat menu
  * Property `hideChatItemInMeeting` in ZoomSDKMeetingConfiguration.h
* Add a new interface for user to hide the items in remote control menu
  * Property `hideRemoteControlItemOnMoreMenu` in ZoomSDKMeetingConfiguration.h
* Add a new interface for the user to hide the Q&A button and the Polling button
  * `- (ZoomSDKError)hideSDKButtons:(BOOL)hide ButtonType:(SDKButton)button` with param `button` is `ToolBarQandAButton` and `ToolBarPollingButton` in ZoomSDKMeetingConfiguration.h
* Add a new interface to config external proxy
  * `- (ZoomSDKError)ConfigureProxy:(ZoomSDKProxySettings)settings` in ZoomSDKNetworkService.h
* Refactoring the logic of hiding the account tab and the feedback tab on the setting window by default


## Changed & Fixed
* Fixed an issue that the “Reclaim host” button displays unexpectedly

## 2019-09-04 @ [v4.4.55968.0904](https://github.com/zoom/zoom-sdk-macos/releases/tag/v4.4.55968.0904)

## Added
*  Add a new callback to notify attendees when the host is requesting to enable the microphone
* `- (void)onHostAskUnmute` in ZoomSDKMeetingActionControllerDelegate
*  Add a new interface to disable the warning alerts/popups for status "Bad Network" and "System Busy"
* property `hideMeetingStaticBadNetWorkWaring` and `hideMeetingStaticSystemBusyWaring` in ZoomSDKMeetingConfiguration.h
*  Add a new interface to hide the "switch camera" button in meeting window when sharing camera
* property `hideSwitchCameraButton` in ZoomSDKMeetingConfiguration.h
*  Add a new interface to switch share to next camera when sharing the camera
* `- (ZoomSDKError)switchToShareNextCamera` and `- (BOOL)canSwitchToShareNextCamera` in ZoomSDKASController.h
*  Add a new interface to hide the "Chat" button in Zoom UI
* `- (ZoomSDKError)hideSDKButtons:(BOOL)hide ButtonType:(SDKButton)button` with param button is `ChatButton`
*  Add new interface to allow user to disable the auto opening Finder window after recording a meeting
* property `disableOpenRecordFileWhenMeetingEnd` in ZoomSDKMeetingConfiguration.h


## Changed & Fixed
*   Fixed an issue that the annotation feature shows up when sharing camera
*  Fixed an issue that the callback `onHostAskUnmute` is not triggered when the host unmutes a participant
*  Fixed an issue that the user who is sharing content cannot clear the annotation
*  Fixed an issue that the host cannot grant or revoke the participant's local recording privilege
*  Optimized the callbacks to handle the scenario when a device has multiple mics or speakers and switching among the microphones or speaker devices
* `- (void)onSelectedMicDeviceChanged` and `- (void)onSelectedSpeakerDeviceChanged` in ZoomSDKSettingAudioDeviceDelegate
*  Optimized the callbacks to handle the scenario when changing the default camera in Settings
* `- (void)onSelectedCameraChanged:(NSString*)deviceID` in ZoomSDKSettingVideoDelegate

## 2019-07-15 @ [v4.4.55130.0712](https://github.com/zoom/zoom-sdk-macos/releases/tag/v4.4.55130.0712)

**Added**

* Add a new interface for setting general and recording items
  * `- (ZoomSDKError)enableShowOriginalSoundOptionInMeetingUI:(BOOL)enable;`
  * `- (BOOL)isShowOriginalSoundOptionInMeetingUIOn;`
  * `- (BOOL)isSupportShowOriginalSoundOptionInMeetingUI;`
  * `- (ZoomSDKError)enableEchoCancellation:(BOOL)enable;`
  * `- (BOOL)isEchoCancellationOn;`
  * `- (BOOL)isSupportEchoCancellation;`
  * `- (BOOL)isEnableChooseRecordingPathWhenMeetingEnd;`
  * `- (ZoomSDKError)chooseRecordingPathWhenMeetingEnd:(BOOL)enable;`
  * `- (BOOL)isEnableRecordAudioForEveryAttendeeIndividually;`
  * `- (ZoomSDKError)recordAudioForEveryAttendeeIndividually:(BOOL)enable;`
  * `- (BOOL)isEnableOptimizeFor3PartyVideoEditor;`
  * `- (ZoomSDKError)OptimizeFor3PartyVideoEditor:(BOOL)enable;`
  * `- (BOOL)isEnableAddTimestampForRecording;`
  * `- (ZoomSDKError)addTimestampForRecording:(BOOL)enable;`
  * `- (BOOL)isEnableRecordDuringScreenSharing;`
  * `- (ZoomSDKError)recordDuringScreenSharing:(BOOL)enable;`
  * `- (BOOL)isEnableDisplayVideoNextToShareContentsInRecordingFile;`
  * `- (ZoomSDKError)displayVideoNextToShareContentsInRecordingFile:(BOOL)enable;`
  * `- (BOOL)canGetCloudRecordingStorageInfo;`
  * `- (ZoomSDKError)getCloudRecordingStorageInfo;`
  * `- (BOOL)canGetRecordingManagementURL;`
  * `- (NSString*)getRecordingManagementURL;`
  * `-(ZoomSDKError)enableSetShareScreen:(BOOL)enable  SettingCmd:(shareSettingCmd)shareCmd;`
  * `-(BOOL)isEnableToSettingShare:(shareSettingCmd)sharingCmd;`
  * `- (BOOL)isShowLockMeetingTime;`
  * `-(ZoomSDKError)enableToShowMeetingTime:(BOOL)enable;`
  * `- (int)getLimitFPSValue;`
  * `- (ZoomSDKError)setLimitFPSValue:(int)value;`
  * `- (BOOL)isEnableToSetLimitFPS;`
  * `- (ZoomSDKError)setEnableLimitFPS:(BOOL)enable;`
  * `- (BOOL)isEnableCopyInviteURL;`
  * `- (ZoomSDKError)setCopyMeetingInviteURL:(BOOL)enable;`
  * `- (BOOL)isEnableConfirmLeavingMeeting;`
  * `- (ZoomSDKError)setConfirmLeavingMeeting:(BOOL)enable;`
* Add a new interface to customize the log size
  * `- (void)enableDefaultLog:(BOOL)enable fileSize:(unsigned int)size`
* Add a new interface to show/hide the video button on meeting toolbar
  * `enum SDKButton of ToolBarVideoButton`
* Add new error codes for auth failure due to overtime and network issue
  * `ZoomSDKAuthError_Timeout`
  * `ZoomSDKAuthError_NetworkIssue`
* Add a new interface to get the meeting number for a specific meeting
  * `-(long long)getMeetingNumber`
* Add a new interface to switch between active video view and share content view
  * `- (ZoomSDKError)swapToShowShareViewOrVideo:(BOOL)share;`
  * `- (BOOL)canSwapToShowShareViewOrVideo;`
  * `- (BOOL)isDisplayingShareViewOrVideo;`
  * `enum SDKButton of SwapShareContentAndVideoButton`
* Add a new interface to get share setting type
  * `- (ZoomSDKError)getShareSettingType:(ZoomSDKShareSettingType*)type`
* Add a new interface to email contents and join meeting URL for a scheduled meeting
  * `-(NSString*)getInviteEmailContent`
  * `-(NSString*)getJoinMeetingUrl`
* Add a new interface to specify the file name of the localizable string resource files
  * `- (void)setCustomLocalizationFileName:(NSString*)fileName`
* Add a new interface to invite others into the meeting via emails
  * `- (ZoomSDKError)inviteToMeetingByDefaultMail;`
  * `- (ZoomSDKError)inviteToMeetingByGmail;`
  * `- (ZoomSDKError)inviteToMeetingByYahooMail`
* Add a new interface to disable the viewer’s ability to annotate in custom UI
  * `- (ZoomSDKError)disableViewerAnnotation:(ZoomSDKCustomizedAnnotation*)annotation disable:(BOOL)disable;`
  * `- (ZoomSDKError)isViewerAnnotationLocked:(ZoomSDKCustomizedAnnotation*)annotation isLocked:(BOOL*)locked;`
  * `- (ZoomSDKError)canDisableViewerAnnotation:(ZoomSDKCustomizedAnnotation*)annotation canDisabled:(BOOL*)canDisable;`
  * `- (ZoomSDKError)canDoAnnotation:(ZoomSDKCustomizedAnnotation*)annotation canAnnotate:(BOOL*)canAnnotate;`
  * `- (void)onAnnotationSupportPropertyChangedForCustom:(BOOL)isSupportAnnotation shareSourceUserID:(unsigned int)userID`
* Add a new interface to hide upgrade account tip in the schedule window
  * `- (void)hideScheduleComponent:(ScheduleComponent)component hide:(BOOL)hide`


**Changed & Fixed**

* Fixed an issue that hiding the sharing toolbar and thumbnail video window does not work
* Fixed an issue that sometimes the SDK crashes when calling the join meeting API in auth callback delegate
  * `- (void)onZoomSDKAuthReturn:(ZoomSDKAuthError)returnValue`
* Fixed an issue that cannot set meeting configs while editing a meeting in custom UI mode.

**Deprecated**

* Remove: ActionMeetingCmd_LockShare/ActionMeetingCmd_UnlockShare
* - (void)enableDefaultLog:(BOOL)enable in ZoomSDK.h
* - (ZoomSDKError)enableUseOriginalSound:(BOOL)enable in ZoomSDKSettingService.h
* - (BOOL)isSupportUseOriginalSound in ZoomSDKSettingService.h
* - (BOOL)isUseOriginalSoundOn in ZoomSDKSettingService.h


## 2019-03-25 @ [v4.3.1.47193.0321](https://github.com/zoom/zoom-sdk-macos/releases/tag/v4.3.1.47193.0321)

**Added**

* Introduce new Zoom meeting UI## 2019-07-15 @ []()

Added

* Add a new interface for setting general and recording items
** - (ZoomSDKError)enableShowOriginalSoundOptionInMeetingUI:(BOOL)enable;
** - (BOOL)isShowOriginalSoundOptionInMeetingUIOn;
** - (BOOL)isSupportShowOriginalSoundOptionInMeetingUI;
** - (ZoomSDKError)enableEchoCancellation:(BOOL)enable;
** - (BOOL)isEchoCancellationOn;
** - (BOOL)isSupportEchoCancellation;
** - (BOOL)isEnableChooseRecordingPathWhenMeetingEnd;
** - (ZoomSDKError)chooseRecordingPathWhenMeetingEnd:(BOOL)enable;
** - (BOOL)isEnableRecordAudioForEveryAttendeeIndividually;
** - (ZoomSDKError)recordAudioForEveryAttendeeIndividually:(BOOL)enable;
** - (BOOL)isEnableOptimizeFor3PartyVideoEditor;
** - (ZoomSDKError)OptimizeFor3PartyVideoEditor:(BOOL)enable;
** - (BOOL)isEnableAddTimestampForRecording;
** - (ZoomSDKError)addTimestampForRecording:(BOOL)enable;
** - (BOOL)isEnableRecordDuringScreenSharing;
** - (ZoomSDKError)recordDuringScreenSharing:(BOOL)enable;
** - (BOOL)isEnableDisplayVideoNextToShareContentsInRecordingFile;
** - (ZoomSDKError)displayVideoNextToShareContentsInRecordingFile:(BOOL)enable;
** - (BOOL)canGetCloudRecordingStorageInfo;
** - (ZoomSDKError)getCloudRecordingStorageInfo;
** - (BOOL)canGetRecordingManagementURL;
** - (NSString*)getRecordingManagementURL;
** -(ZoomSDKError)enableSetShareScreen:(BOOL)enable  SettingCmd:(shareSettingCmd)shareCmd;
** -(BOOL)isEnableToSettingShare:(shareSettingCmd)sharingCmd;
** - (BOOL)isShowLockMeetingTime;
** -(ZoomSDKError)enableToShowMeetingTime:(BOOL)enable;
** - (int)getLimitFPSValue;
** - (ZoomSDKError)setLimitFPSValue:(int)value;
** - (BOOL)isEnableToSetLimitFPS;
** - (ZoomSDKError)setEnableLimitFPS:(BOOL)enable;
** - (BOOL)isEnableCopyInviteURL;
** - (ZoomSDKError)setCopyMeetingInviteURL:(BOOL)enable;
** - (BOOL)isEnableConfirmLeavingMeeting;
** - (ZoomSDKError)setConfirmLeavingMeeting:(BOOL)enable;
* Add a new interface to customize the log size
** - (void)enableDefaultLog:(BOOL)enable fileSize:(unsigned int)size
* Add a new interface to show/hide the video button on meeting toolbar
** enum SDKButton of ToolBarVideoButton
* Add new error codes for auth failure due to overtime and network issue
** ZoomSDKAuthError_Timeout
** ZoomSDKAuthError_NetworkIssue
* Add a new interface to get the meeting number for a specific meeting
** -(long long)getMeetingNumber
* Add a new interface to switch between active video view and share content view
** - (ZoomSDKError)swapToShowShareViewOrVideo:(BOOL)share;
** - (BOOL)canSwapToShowShareViewOrVideo;
** - (BOOL)isDisplayingShareViewOrVideo;
** enum SDKButton of SwapShareContentAndVideoButton
* Add a new interface to get share setting type
** - (ZoomSDKError)getShareSettingType:(ZoomSDKShareSettingType*)type
* Add a new interface to email contents and join meeting URL for a scheduled meeting
** -(NSString*)getInviteEmailContent
** -(NSString*)getJoinMeetingUrl
* Add a new interface to specify the file name of the localizable string resource files
** - (void)setCustomLocalizationFileName:(NSString*)fileName
* Add a new interface to invite others into the meeting via emails
** - (ZoomSDKError)inviteToMeetingByDefaultMail;
** - (ZoomSDKError)inviteToMeetingByGmail;
** - (ZoomSDKError)inviteToMeetingByYahooMail
* Add a new interface to disable the viewer’s ability to annotate in custom UI
** - (ZoomSDKError)disableViewerAnnotation:(ZoomSDKCustomizedAnnotation*)annotation disable:(BOOL)disable;
** - (ZoomSDKError)isViewerAnnotationLocked:(ZoomSDKCustomizedAnnotation*)annotation isLocked:(BOOL*)locked;
** - (ZoomSDKError)canDisableViewerAnnotation:(ZoomSDKCustomizedAnnotation*)annotation canDisabled:(BOOL*)canDisable;
** - (ZoomSDKError)canDoAnnotation:(ZoomSDKCustomizedAnnotation*)annotation canAnnotate:(BOOL*)canAnnotate;
** - (void)onAnnotationSupportPropertyChangedForCustom:(BOOL)isSupportAnnotation shareSourceUserID:(unsigned int)userID
* Add a new interface to hide upgrade account tip in the schedule window
** - (void)hideScheduleComponent:(ScheduleComponent)component hide:(BOOL)hide


Changed & Fixed

* Fixed an issue that hiding the sharing toolbar and thumbnail video window does not work
* Fixed an issue that sometimes the SDK crashes when calling the join meeting API in auth callback delegate
** - (void)onZoomSDKAuthReturn:(ZoomSDKAuthError)returnValue
* Fixed an issue that cannot set meeting configs while editing a meeting in custom UI mode.

Deprecated

* Remove: ActionMeetingCmd_LockShare/ActionMeetingCmd_UnlockShare
* - (void)enableDefaultLog:(BOOL)enable in ZoomSDK.h
* - (ZoomSDKError)enableUseOriginalSound:(BOOL)enable in ZoomSDKSettingService.h
* - (BOOL)isSupportUseOriginalSound in ZoomSDKSettingService.h
* - (BOOL)isUseOriginalSoundOn in ZoomSDKSettingService.h

* Add new interfaces to control share viewer’s annotate privilege
* Add 1080p video support
* Add new interfaces to customize the sub-tab pages in H323 invite page
* Add a new interface to open the share select window
* Add new interfaces to hide the upgrade button in free meeting remain time tooltip view
* Add a callback to alert the user when the 40-min free meeting is automatically ended

**Changed & Fixed**

* Fix an issue that the setting option ‘always show meeting controls’ does not work
* Remove unexpected log info in meeting window
* Refine the meeting window’s title by showing 'Zoom' label on meetings window when using dual mode
* Fix an issue that the participant side SDK quit automatically without any message if the meeting is locked by the host
* Fix an issue that the audio status cannot update to other participants

**Deprecated**

* (void)onPaymentReminder
* Class ZoomSDKUpgradeAccountHelper
* Enum SDKReminderType

## 2019-01-23 @ [v4.3.0.53914.0121](https://github.com/zoom/zoom-sdk-macos/releases/tag/v4.3.0.53914.0121)

**Added**
*	A new refactorized demo project that provides clear instructions on how to implement major features.
*	Support for multi-share setting
*	Support for closed caption
*	Proper error message for the case when a participant has been removed by the host at joining the meeting
*	Support for hiding “Claim Host” button in the meeting.
*	New logging feature that stores logs with the maximum size of 5MB.
*	A new method to join/start meeting directly via url, such as zoommtg://zoom.us/join?action=....

**Changed & Fixed**
*	An issue that the transcode does not work when enable setting of “Choose a location for recorded files when meeting ends”
*	Audio/Video does not work on Mac OS 10.14
*	Setting preferred language feature does not work
*	Waiting for host window does not show when joining a meeting that hasn’t started yet.
*	Loading tab always displayed when scheduling a meeting twice

**Deprecated**
*	- (ZoomSDKError)canStartRecording:(BOOL)isCloud User:(unsigned int)userid NS_DEPRECATED_MAC(4.1, 4.3);
*	- (ZoomSDKError)canStartRecording:(BOOL)isCloud NS_AVAILABLE_MAC(4.3); in ZoomSDKMeetingRecordController.h
*	- (ZoomSDKError)loginSSO:(NSString*)ssoToken NS_DEPRECATED_MAC(1.0, 4.3);
*	- (ZoomSDKError)loginSSO:(NSString*)ssoToken RememberMe:(BOOL)rememberMe NS_AVAILABLE_MAC(4.3);



## 2018-10-29 @ [v4.1.34180.1026](https://github.com/zoom/zoom-sdk-macos/releases/tag/v4.1.34180.1026)

* Support schedule meeting feature
* Support custom live stream strings
* Support to pair a non-active meeting to H323-mac
* Support advanced share feature
* Support webinar common feature
* Support setting audio/video feature
* Bug fixes

## 2018-9-11 @ [v4.1.32152.0910](https://github.com/zoom/zoom-sdk-macos/releases/tag/v4.1.32152.0910)

* Support Direct share / Outlook plugin integration / Audio Share

* Pre-meeting service interface
1. Support to direct share use ultrasonic
2. Support to integrate with outlook plugin

* New files added
1. Folder Plugins: ZoomAudioDevice.driver and ZoomAudioDevice.kext added for share audio
2. Folder SDK Resources:  String resources files used for multi-language support

* Bugs fixed

## 2018-8-24 @ [v4.1.30730.0824](https://github.com/zoom/zoom-sdk-macos/releases/tag/v4.1.30730.0824)

* This release has patch fixes for the last release v4.1.30458.0820.
* Critical bug fixed - A user can’t select share source by mouse after click share button on main toolbar (with Zoom meeting UI)
* Other interface change
1. -(void)onToolbarInviteButtonClick->  - (void)onToolbarInviteButtonClick:(BOOL*)show
 in ZoomSDKMeetingUIController.h
default shows the origin zoom invite window, if you don't want the original action, you can set *show = N0, and do UI action yourself in this callback

2. New add free user callback in ZoomSDKMeetingService.h;
 - (void)onPaymentReminder:(ZoomSDKUpgradeAccountHelper*)upgradeHelper;

3. New property add for free user callback in ZoomSDKMeetingConfiguration.h
@property(nonatomic, assign)BOOL disableFreeUserOriginAction;
set YES before start meeting if u don't want popup zoom free user UI and you will receive above callback.

## 2018-8-20 @ [v4.1.30458.0820](https://github.com/zoom/zoom-sdk-macos/releases/tag/v4.1.30458.0820)

* Custom Meeting UI (support basic meeting function, except for Webinar and Breakout Session)

* Interface Changes:
1. Customized video interface: ZoomSDKVideoContainer.h (support customized video view layout)
2. Customized share interface: ZoomSDKShareElement.h/ZoomSDKShareContainer.h (support customized share view layout)
3. Customized remote controller interface: ZoomSDKRemoteControllerHelper.h (support common feature of remote control in sdk layer)
4. Customized recording interface: ZoomSDKMeetingRecordController.h (support common feature of recording in sdk layer)
5. Customized recording interface: ZoomSDKCustomizedAnnotationCtr.h (support common feature of annotation in sdk layer)

* Bug fixes

## 2018-07-26 @ [v4.1.28807.0726](https://github.com/zoom/zoom-sdk-macos/releases/tag/v4.1.28807.0726)

The start meeting logic for API users has changed. Please read below before upgrading to this version.

### Added

1. interface change:
We added a new parameter, zoom access token (ZAK), which can be retrieved through REST API:
https://zoom.github.io/api/#retrieve-a-users-permissions

Old API User start meeting logic:
```
(ZoomSDKError)startMeeting:(ZoomSDKUserType)userType userID:
(NSString*)userId userToken:(NSString*)userToken displayName:
(NSString*)username meetingNumber:(NSString*)meetingNumber isDirectShare:
(BOOL)directShare sharedApp:(CGDirectDisplayID)displayID isVideoOff:
(BOOL)noVideo isAuidoOff:(BOOL)noAuido;
```
New API User start meeting logic:
```
-(ZoomSDKError)startMeetingWithZAK:(NSString*)zak userType:
(SDKUserType)type userID:(NSString*)userId userToken:
(NSString*)userToken displayName:(NSString*)username meetingNumber:
(NSString*)meetingNumber isDirectShare:(BOOL)directShare sharedApp:
(CGDirectDisplayID)displayID isVideoOff:(BOOL)noVideo isAuidoOff:
(BOOL)noAuido vanityID:(NSString*)sdkVanityID;
```
Usage:
```
ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService]
API Start Meeting: [meetingService startMeetingWithZAK。。。。]
Login Start Meeting: [meetingService startMeeting...]
```

2. API user start meeting should use ZAK

3. support live stream

4. support make host && cohost

5. some bugs fix

## 2018-05-29 @ [v4.1.25472.0529](https://github.com/zoom/zoom-sdk-macos/releases/tag/v4.1.25472.0529)

### Added

1. This is an SDK release base on 64bit, won't support 32bit anymore.

2. interface change:

1) Meeting Configuration interface

support to config DSCP for audio video session

support to redirect click event of participant list button

support to hide original leave meeting confirm window.

support to enable hide the full phone number for pure call in user

2) H323 helper interface

support to get h323 device for current meeting

3) Setting Service Interface

support to enable or disable auto join Voip when join meeting

support to enable or disable auto mute mic when join Voip.

support to enable or disable turn off video when join meeting

support to enable or disable original input of mic

support to enable or disable stereo audio

add new interface for statistic setting

4) several bug fixed.

Please refer to Interface_change_4.1.25472.0529.docx for more details.

## 2017-11-02 @ [v4.1.12430.1102](https://github.com/zoom/zoom-sdk-macos/releases/tag/v4.1.12430.1102)

### Added

1. add interface to check sharing content

2. add support for split screen during sharing

3. add interface to inform active speaker

4. add support to change in meeting name

5. add support to minimize video

6. add callback interface for clicking toolbar share button

7. add support for webinar join window info prefill

8. for code refactor details, please visit : https://marketplace.zoom.us/docs/sdk/native-sdks/macos

9. add support to hide each individual button on fitbar during sharing.

10. bug fix

## 2017-06-19 @ [v4.0.22051.0122](https://github.com/zoom/zoom-sdk-macos/releases/tag/v4.0.22051.0122)

### Added

1. support query and notify share locking status

   (void)onShareStatusLocked:(BOOL)shareLocked;

2. add switch video wall to next page api

   (ZoomSDKError)showPreOrNextPageWallView:(BOOL)nextPage;

3. add join/leave audio api

   ActionMeetingCmd_JoinVoip

   ActionMeetingCmd_LeaveVoip

4. Custom input meeting password feature

   (ZoomSDKError)inputPassword:(NSString*)password;

5. add config for hide "exit full screen” button and disable double click to enter fullscreen

   BOOL _hideExitFullScreenButton;

   BOOL _disableDoubleClickToFullScreen;

6. add get meeting type api and user role api

   (UserRole)getUserRole;

   (MeetingType)getMeetingType;

7. join/leave bo support

   (ZoomSDKError)joinBreakoutRoom:(NSString*)bID;

   (ZoomSDKError)leaveBreakoutRoom;

8. allow or disallow "can unmute by self if mute by host”config

    //can unmute by self when mute by host

    ActionMeetingCmd_EnableUnmuteBySelf,

    ActionMeetingCmd_DisableUnmuteBySelf,

    //mute/unmute all only for host

    ActionMeetingCmd_MuteAll,

    ActionMeetingCmd_UnmuteAll,

9. Call out/Invite by phone support

   (ZoomSDKError)inviteCalloutUser:(NSString*)userName PhoneNumber:(NSString*)number CountryCode:(NSString*)countryCode;


10. Waiting room:admit attendee into the meeting

    (ZoomSDKError)admitToMeeting:(unsigned int)userid;

11. Bugs fix.

## 2017-01-23 @ [v3.6.11922.1111](https://github.com/zoom/zoom-sdk-macos/releases/tag/v3.6.11922.1111)

### Added

1. Support to join Webinar meeting with as Panelist;

2. Support to pin/spotlight video;

3. Support H.323/SIP callout directly

4. Add watermark “Powered by Zoom”

5. Support to start/join meeting without audio;

6. Support to start/join meeting without video;

7. Support Multi-share;
