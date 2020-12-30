# CHANGELOG

## Obtaining SDK packages from Marketplace

We are pleased to inform you that starting from v5.4.54518.1229, the Zoom SDK packages are moving to the Zoom App Marketplace. The packages are now available in the same location as your SDK Key & Secret. This change aims to provide you with a unified and seamless experience so that you can access the required SDK resources in one place. 

If you have not used Zoom SDK before, please follow the steps in https://marketplace.zoom.us/docs/guides/build/sdk-app to create an SDK app on the Marketplace.

If you already have an SDK app created, login to the **[Zoom App Marketplace](https://marketplace.zoom.us/)** using your developer account, click the **Manage** button on the top-right corner and locate your SDK app.
<img src="https://s3-us-west-1.amazonaws.com/sdk.zoom.us/mkt-01.png" style="margin:1vh 1vw;"/>

Click on your SDK app, you can find the desired SDK packages from the **Download** tab
<img src="https://s3-us-west-1.amazonaws.com/sdk.zoom.us/mkt-02.png" style="margin:1vh 1vw;"/>

## Note
### New SDK Initialization method: Using JWT token
Introducing new SDK initialization method -- JWT token, which is more secure, more convenient, and more versatile.

* How to compose JWT token for SDK initialization

You may generate your JWT token using the online tool https://jwt.io/. **It is highly recommended to generate your JWT token in your backend server.**

JWT is generated with three core parts: Header, Payload, and Signature. When combined, these parts are separated by a period to form a token: aaaaa.bbbbb.cccc.

Please follow this template to compose your payload for SDK initialization:

** Header
```
{
  "alg": "HS256",
  "typ": "JWT"
}
```
** Payload
```
{
	       "appKey": "string", // Your SDK key
         "iat": long, // access token issue timestamp
         "exp": long, // access token expire timestamp, max: iat + 2 days
         "tokenExp": long // token expire timestamp, MIN:30 minutes
}
```
**The minimum value of `tokenExp` should be at least 30 minutes, otherwise, SDK will reject the authentication request.**
** Signature
```
HMACSHA256(
  base64UrlEncode(header) + "." +
  base64UrlEncode(payload),
  "Your SDK secret here"
)
```
You do not need to secret base64 encoded your signature. Once the JWT token is generated, please do not reveal it or publish it. **It is highly recommended to handle your SDK key and secret and generate JWT in a backend server to be consumed by your application. Do not generate JWT in a production application.**

## 2020-11-17 @ v5.2.42037.1112

## Added:
* Added new feature for supporting language interpreters within meetings. For more information regarding this feature, please visit https://support.zoom.us/hc/en-us/articles/360034919791-Language-interpretation-in-meetings-and-webinars  
  * The interface in `ZoomSDKInterpretationController.h`

* Added new interfaces to add/remove a video file as the virtual background.
  * `- (ZoomSDKError)addBGVideo:(NSString*)filePath;`
  * `- (ZoomSDKError)removeBGVideo:(NSString*)filePath;`
  * `- (BOOL)isSupportSmartVirtualBackgroundVideo;`
  * `- (BOOL)isSupportGreenVirtualBackgroundVideo;`
  * `- (BOOL)isAllowAddNewVBItem;`
  * `- (BOOL)isAllowRemoveVBItem;`
  * `- (void)onVBVideoUploadedResult:(BOOL)success failedError:(ZoomSDKSettingVBVideoError)error;`

* Added a new interface to allow user to use the video filter feature.
 * `- (BOOL)isVideoFilterEnabled;`
 * `- (BOOL)isSupportVideoFilter;`
 * `- (NSArray*)getVideoFilterItemList;`
 * `- (ZoomSDKError)useVideoFilterItem:(ZoomSDKVideoEffectType)type index:(int)index;`
 * `- (void)onVideoFilterItemDataDownloaded:(ZoomSDKVideoEffectType)type index:(int)index;`
 * `- (void)onVideoFilterItemDataNeedPrepare:(ZoomSDKVideoEffectType)type index:(int)index;`
 * `- (void)onVideoFilterItemDataReady:(BOOL)ready type:(ZoomSDKVideoEffectType)type index:(int)index;`

* Added new interfaces to configure video settings.
 * `-(int)getBeautyFaceValue;`
 * `-(ZoomSDKError)setBeautyFaceValue:(int)value;`
 * `-(ZoomSDKSettingVideoLightAdaptionModel)getLightAdjustModel:(BOOL*)isDisabled;`
 * `-(ZoomSDKError)setLightAdaptionModel:(ZoomSDKSettingVideoLightAdaptionModel)model LightAdaptionManualValue:(int)value;`
 * `-(int)getLightAdaptionManualValue:(BOOL*)isDisabled;`
 * `-(BOOL)isHardwareAccelerationForVideoReceiveOn:(BOOL*)isDisabled;`
 * `-(ZoomSDKError)enableHardwareAccelerationForVideoReceive:(BOOL)enable;`
 * `-(BOOL)isTemporalDeNoiseOn:(BOOL*)isDisabled;`
 * `-(ZoomSDKError)enableTemporalDeNoise:(BOOL)enable;`

* Added new interfaces to use separate audio device to play ringtone simultaneously
 * `-(BOOL)isAlwaysUseSeparateRingSpkOn:(BOOL*)isDisabled;`
 * `-(ZoomSDKError)enableAlwaysUseSeparateRingSpk:(BOOL)enable;`
 * `-(NSArray *)getRingSpkDeviceList;`
 * `-(float)getRingSpkVolume;`
 * `-(ZoomSDKError)setRingSpkVolume:(float)value;`
 * `-(ZoomSDKError)setRingSpkDevice:(NSString*)deviceId;`

* Added new callback to notify the end-user that their video subscription failed when using Custom Meeting UI
 * `-(void)onCustomVideoSubscribeFail:(ZoomSDKVideoElement*)element error:(int)error;`

* Added a new interface for a button in the floating video view.
 * `- (ZoomSDKError)pagingToPreOrNextViewWhenSharing:(BOOL)nextPage` in `ZoomSDKMeetingUIController.h` file.

* Added a new interface for SDK initialization.
 * `- (ZoomSDKError)initSDKWithParams:(ZoomSDKInitParams*)initParams`

* Added a new interface to change the app's appearance
 * `- (ZoomSDKError)setUIAppearance:(ZoomSDKUIAppearance)appearance;`

* Removed the watermark by default. If you wish to retain the Zoom watermark, please contact us via developersupport@zoom.us.

## Changed && Fixed:
* Fixed an issue that the attendee can still hear chime when a participant joins the meeting even though the corresponding setting is disabled.
* Fixed an issue that the `carStartShare` method returns an incorrect result.

## Deprecated
* `-(void)initSDK:(BOOL)customizedFlag`

## 2020-10-26 @ v5.2.41751.1026

## Changed & Fixed
* Fixed an issue that the virtual background does not work after re-signing the SDK libraries.
  * SDK will verify the signature of all libraries. When the SDK libraries have been resigned, please call the interface `- (void)setTeamIdentifier:(NSString*)identifier` to set the organization unit of the signature before calling `- (void)initSDK:(BOOL)customizedFlag` in the app.
  ```
     [[ZoomSDK sharedSDK] setTeamIdentifier:@“the ou of certificate”];
  ```

* Fixed an issue that the keychain popup dialog contains 'Zoom', the new keychain pops up will use the app's name instead.

## 2020-10-09 @ v5.2.41735.0929

## Added
* Upgraded Zoom default UI to match Zoom client 5.2.1.
* Added a new callback for the event when the host has asked to start the video.
  * `- (void)onHostAskStartVideo` in `ZoomSDKMeetingActionController.h`
* Added a new callback to redirect the leave button action on the toolbar.
  * `- (void)onClickLeaveMeeting:(unsigned int)participantID` in `ZoomSDKMeetingUIController.h`
* Added a new interface isH323User to check whether the user is an H.323 user.
  * `- (BOOL)isH323User` in  `ZoomSDKMeetingActionController.h`
* Added a new callback for the event when the user is being asked to mute/unmute the video by the host/co-host.
  * `- (void)onVideoStatusChange:(ZoomSDKVideoStatus)videoStatus UserID:(unsigned int)userID` in `ZoomSDKMeetingActionController.h`
* Added a new interfaces to get participant ID.
  * `- (NSString *)getParticipantID` in `ZoomSDKMeetingActionController.h`.
* Added Vietnamese and Italian language support.
* Added a new interface for the feature "Allow participants to rename Themselves"
  * `-(BOOL)isParticipantsRenameAllowed`
  * `- (ZoomSDKError)allowParticipantsToRename:(BOOL)allow` in `ZoomSDKMeetingActionController.h`
* Added a new interface for the feature "Allow participants to share screen".
  * `- (ZoomSDKError)allowParticipantsToShare:(BOOL)allow`
  * `-(BOOL)isParticipantsShareAllowed` in `ZoomSDKMeetingActionController.h`.
* Added a new interface for the feature "Allow participants to chat"
  * `-(BOOL)isParticipantsChatAllowed`
  * `- (ZoomSDKError)allowParticipantsToChat:(BOOL)allow` in `ZoomSDKMeetingActionController.h`
* Added new interfaces and callbacks to delete questions and answers in the webinar Q&A.
  * `-(ZoomSDKError)deleteQuestion:(NSString *)questionID`
  * `-(void)onDeleteQuestions:(NSArray *)questions`
  * `-(ZoomSDKError)deleteAnswer:(NSString *)answerID`
  * `-(void)onDeleteAnswers:(NSArray *)answer` in `ZoomSDKQAController.h` file
* Refactored the callback event for waiting room user to receive a chat message
  * `-(ZoomSDKChatMessageType)getChatMessageType` in `ZoomSDKMeetingActionController.h`
* Added a new interface to allow user to set the suppress background noise level.
   * `- (ZoomSDKSuppressBackgroundNoiseLevel)getSuppressBackgroundNoiseLevel” and `
   * `- (ZoomSDKError)setSuppressBackgroundNoise:(ZoomSDKSuppressBackgroundNoiseLevel)level` in `ZoomSDKSettingService.h`

## Changed & Fixed
* Refined the hide claim host button.
* Refined the breakout room interfaces
  * In `ZoomSDKNewBreakoutRoomController.h `file.
* Fixed an issue that unable to receive the meeting status "Reconnecting".
* Fixed an issue that unable to receive the meeting status "InWaitingRoom"
* Fixed an issue that the watermark is shown in the incorrect position after resizing the video view size.
* Fixed an issue that the cloud recording cannot be stopped.
* Fixed an issue that the user is not able to join the meeting again after join the meeting failed.
* Fixed an issue that the app crashes when the H.323's IP address is not standard format.
* Fixed an issue that the password dialog is not able to exit in Custom UI mode.
* Fixed an issue that the virtual background does not apply on the video when starting a meeting twice.
* Fixed an issue that the free meeting alert is showing incorrectly.
* Fixed an issue that the video sometimes freezes in Custom UI.

## 2020-06-30 @ v5.0.24433.0616

## Added:
* Upgraded Zoom default UI to match Zoom client 5.0.
* Added a new interface to modify the 'meeting topic' in the 'meeting information' page.
  * `- (ZoomSDKError)setMeetingTopicOnMeetingInfo:(NSString *)topic" on ZoomSDKMeetingActionController.h`
* Added new options to hide the share button.
  * Added new enumeration value `ToolBarShareButton`
* Added new interfaces to pause/resume the recording.
  * `-(ZoomSDKError)pauseCloudRecording;`
  * `-(ZoomSDKError)resumeCloudRecording;`
  * `-(ZoomSDKError)pauseLocalRecording;`
  * `-(ZoomSDKError)resumeLocalRecording;`
* Added a new callback for the event when the username has changed
  * `-(void)onUserNameChanged:(unsigned int)userid  userName:(NSString *)userName;`
* Added new interfaces related to setting 'Always show video preview when joining a video meeting' feature.
  * `- (BOOL)showVideoPreviewWhenJoinMeeting;`
  * `- (ZoomSDKError)isShowVideoPreviewWhenJoinMeeting:(BOOL)isShow;`
* Added new interfaces to check whether the PMI option is enabled on the account.
  * `- (BOOL)isDisabledPMI.`
* Added new meeting fail reason
  * `ZoomSDKMeetingError_RegisterWebinarDeniedEmail`
* Added a new interface to get audio status and audio type
  * `- (ZoomSDKAudioStatus)getAudioStatus;`
  * `- (ZoomSDKAudioType)getAudioType;`
* Added new interfaces for switching between float video view to other views.
  * `- (ZoomSDKError)switchFloatVideoToMinimizeMode;`
  * `- (ZoomSDKError)switchFloatVideoToWallMode;`

## Changed & Fixed:

* Updated the `ZoomAudioDevice.driver` and removed `ZoomAudioDevice.kext`
* Redefine the start/join meeting interfaces
  * `-(ZoomSDKError)startMeeting:(ZoomSDKStartMeetingElements *)context;`
  * `-(ZoomSDKError)startMeetingWithZAK:(ZoomSDKStartMeetingUseZakElements *)context;`
  * `-(ZoomSDKError)joinMeeting:(ZoomSDKJoinMeetingElements *)context;`
* Fixed an issue that the share toolbar does not present for the remote controller.
* Fixed an issue that the host/co-host cannot mute/unmute others.
* Fixed an issue that the change user name interface does not work as expected.
* Fixed an issue that the user ID returns in the audio status callback are incorrect.
* Fixed an issue that the "remember me" option is not working
* Temporary remove the "Unmute all" interfaces.

## Deprecated
* `- (BOOL)isAudioMuted`
* `- (ZoomSDKError)minimizeShareFloatVideoWindow:(BOOL)bMin`
* `- (ZoomSDKError)modifyWindowTitle:(BOOL)modify NewMeetingNum:(unsigned int)meetingnumber`

## 2020-04-27 @ v4.6.21666.0427

## Added:
* Added support for AES 256-bit GCM encryption.
  * **Please plan to upgrade your SDK accordingly. See the announcement in [README](https://github.com/zoom/zoom-sdk-macos) for more information**

## Changed & Fixed:
* Upgraded OpenSSL to version 1.1.1e
* Fixed an issue that user is unable to send a chat message occasionally

## Deprecated
* Deprecated the interface to get user's email: `ZoomSDKUserInfo.getEmail`

## 2020-04-04 @ v4.6.15798.0403

## Added:
* Add new interfaces for customizing [breakout room](https://support.zoom.us/hc/en-us/articles/206476093-Getting-Started-with-Breakout-Rooms)
  * Interfaces can be found in `ZoomSDKNewBreakoutRoomController.h`
* Add new interfaces and options for schedule meeting
 * The interfaces are in `ZoomSDKPremeetingService.h`
* Add new callbacks for breakout room button events
  * The property `disableBreakoutRoomsButtonClickOriginAction` in `ZoomSDKMeetingConfiguration.h`.
  * The callback `-(void)onBreakoutRoomsButtonClick` in `ZoomSDKMeetingUIController.h`
* Add new tips when the screen sharing feature does not have the proper privilege granted
* Add a new interface to check whether a user is talking or not
  * The interface `- (BOOL)isTalking` in `ZoomSDKMeetingActionController.h`
* Add a new callback for the events when the active audio of a user has changed
  * The interface `- (void)onUserActiveAudioChanage:(NSArray *)useridArray` in  `ZoomSDKMeetingActionController.h`.
* Add a new interface to hide the Reaction button
  * Added enumeration element `ToolBarReactionsButton`
* Add a new interface to hide the meeting info button
  * The property `hideMeetingInfoButtonOnVideo` in `ZoomSDKMeetingConfiguration.h`.
* Add support for [hardened Runtime](https://developer.apple.com/documentation/security/hardened_runtime) for macOS app notarization
* Add new interfaces for the `Limit FPS when share` feature
 * The interface `- (ZoomSDKError)setLimitedFPSValue:(ZoomSDKFPSValue)value` in `ZoomSDKSettingService.h`.


## Changed & Fixed:
* Enhanced the experience when screen recording permission is not granted on MacOS 10.15
* Fixed the UNC link issue
* Fixed an issue that the meeting configuration does not apply while reconnecting
* Fixed an issue that the Virtual Background is not available for non-login user
* Fixed an issue that the feature "Push to talk / Hold space key to speak" cannot be disabled
* Fixed an issue that certain features could still be available via short-cuts even if the corresponding button has hidden
* Fixed an issue that user could not join a meeting with vanityID
* Fixed an issue that the user could not mute himself/herself using `actionMeetingWithCmd`

## 2020-02-10 @ v4.6.15088.0210

## Added:
* **Add support for Xcode 10.**
* Add new features in Zoom default UI
  * Allow Call-In Attendees to unmute in the webinar
  * Closed captioning in breakout sessions
  * Fully minimize toolbar when screen sharing
  * Notification when no sound is detected from the microphone
  * Annotation enhancements
  * Do not disturb automatically enabled when screen sharing
  * Reduced volume for entering/exiting chime
  * Rename meeting hosted with personal meeting ID
  * Rename webinar attendees
  * Send a message to participants in a waiting room
  * Merge participant's video and Audio
  * Option to select keyboard layout during remote control
  * Advanced noise suppression
  * View all participants' video in gallery view while screen sharing
  * Enable/Disable dual monitor mode in meeting
  * Virtual background selection within video preview
  * Meeting reactions
  * View other participant's audio status
* Add support for the Korean language.
* Add a new recording status `Recording_Pause` in `RecordingStatus`.
* Add a new interface to set support the dark mode. (Available for MacOS 10.14 and above)
 * `- (ZoomSDKError)setSupportDarkModel:(BOOL)isSupport` in `ZoomSDK.h`
* Enhanced the struct type `ZoomSDKAuthContext` in `ZoomSDKAuthService.h` for ARC
  * The interface `- (ZoomSDKError)sdkAuth:(ZoomSDKAuthContext *)jwttoken` has changed in `ZoomSDKAuthService.h`
* Enhanced the struct type `ZoomSDKProxySettings` in `ZoomSDKNetworkService.h` for ARC
  * The interface `- (ZoomSDKError)ConfigureProxy:(ZoomSDKProxySettings*)settings` has changed in `ZoomSDKNetworkService.h`

## Changed & Fixed:
* Enhanced security and upgraded OpenSSL to 1.0.2u.

## 2019-12-16 @ v4.4.57220.1210

## Added:
* Add new interfaces for SDK initialization with JWT token.
   * The interface `- (ZoomSDKError)sdkAuth:(ZoomSDKAuthContext)jwttoken`
   * The callback `- (void)onZoomAuthIdentityExpired` in  `zoomSDKAuthService.h`
* Add new interfaces for the Q&A feature in webinar.
     * The interfaces in `ZoomSDKQAController.h`.
* Add new callbacks for the event when the audio button/menu is clicked
   * Property `disableAudioButtonClickOriginAction` in `ZoomSDKMeetingConfiguration.h`
   * The callback `-(void)onAudioButtonClicked:(unsigned int)userid audioSession:(ZoomSDKAudioAction)info` in `ZoomSDKMeetingUIController.h`.
   * Property `disableAudioSettingMenuButtonClickOriginAction` in `ZoomSDKMeetingConfiguration.h`
   * The callback `-(void)onAudioSettingMenuButtonClicked` in `ZoomSDKMeetingUIController.h`.
* Add a new interface to hide the window of save recording path
   * Property `hideChooseSaveRecordingFilePathWindow` in `ZoomSDKMeetingConfiguration.h`.
* Add a new interface to access virtual background.
   * Add a object `ZoomSDKVirtualBackgroundSetting`  in `ZoomSDKSettingService.h`
* Add a new interface to disable the show join meeting window.
   * Property `hideLoadingWindow` in `ZoomSDKMeetingConfiguration.h` .

## Changed & Fixed:
* Fixed an issue that the H.323 callout returns incorrect status in the callback.
* Fixed an issue that the meeting restarts for a few times after pressing the end meeting button.
* Fixed an issue that the computer audio is not working while screen sharing.
* Fixed an issue that the progress indicator stays at 0 when clicking 'Save' button for the first time.

## 2019-11-04 @ v4.4.56627.1029

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

## 2019-09-04 @ v4.4.55968.0904

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

## 2019-07-15 @ v4.4.55130.0712

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


## 2019-03-25 @ v4.3.1.47193.0321

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

## 2019-01-23 @ v4.3.0.53914.0121

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



## 2018-10-29 @ v4.1.34180.1026

* Support schedule meeting feature
* Support custom live stream strings
* Support to pair a non-active meeting to H323-mac
* Support advanced share feature
* Support webinar common feature
* Support setting audio/video feature
* Bug fixes

## 2018-9-11 @ v4.1.32152.0910

* Support Direct share / Outlook plugin integration / Audio Share

* Pre-meeting service interface
1. Support to direct share use ultrasonic
2. Support to integrate with outlook plugin

* New files added
1. Folder Plugins: ZoomAudioDevice.driver and ZoomAudioDevice.kext added for share audio
2. Folder SDK Resources:  String resources files used for multi-language support

* Bugs fixed

## 2018-8-24 @ v4.1.30730.0824

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

## 2018-8-20 @ v4.1.30458.0820

* Custom Meeting UI (support basic meeting function, except for Webinar and Breakout Session)

* Interface Changes:
1. Customized video interface: ZoomSDKVideoContainer.h (support customized video view layout)
2. Customized share interface: ZoomSDKShareElement.h/ZoomSDKShareContainer.h (support customized share view layout)
3. Customized remote controller interface: ZoomSDKRemoteControllerHelper.h (support common feature of remote control in sdk layer)
4. Customized recording interface: ZoomSDKMeetingRecordController.h (support common feature of recording in sdk layer)
5. Customized recording interface: ZoomSDKCustomizedAnnotationCtr.h (support common feature of annotation in sdk layer)

* Bug fixes

## 2018-07-26 @ v4.1.28807.0726

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

## 2018-05-29 @ v4.1.25472.0529

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

## 2017-11-02 @ v4.1.12430.1102

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

## 2017-06-19 @ v4.0.22051.0122

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

## 2017-01-23 @ v3.6.11922.1111

### Added

1. Support to join Webinar meeting with as Panelist;

2. Support to pin/spotlight video;

3. Support H.323/SIP callout directly

4. Add watermark “Powered by Zoom”

5. Support to start/join meeting without audio;

6. Support to start/join meeting without video;

7. Support Multi-share;
