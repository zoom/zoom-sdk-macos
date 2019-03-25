//
//  ZoomSDKSettingService.h
//  ZoomSDK
//
//  Created by TOTTI on 8/10/16.
//  Copyright © 2016 Zoom Video Communications,Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

typedef enum{
    SettingComponent_AdvancedFeatureButton,
    SettingComponent_AdvancedFeatureTab,
}SettingComponent;

typedef enum{
    SettingComponent_VirtualBackground_Leran_More,
    SettingComponent_VirtualBackground_Help,
}SDKURLType;

@protocol ZoomSDKSettingTestAudioDelegate <NSObject>
@optional
/**
 * @brief Notification of microphone level changes when testing.
 * @param level The level of microphone.
 */
- (void)onMicLevelChanged:(unsigned int)level;
/**
 * @brief Notification of speaker level changes when testing.
 * @param level The speaker level.
 */
- (void)onSpeakerLevelChanged:(unsigned int)level;
/**
 * @brief Notify the microphone test status has changed.
 * @param status Test status of microphone.
 */
- (void)onMicTestStatusChanged:(ZoomSDKTestMicStatus)status;
/**
 * @brief Notification of speaker status changes when testing.
 * @param isTesting YES means the speaker is in process of test, otherwise not.
 */
- (void)onSpeakerTestStatusChanged:(BOOL)isTesting;
@end

@protocol ZoomSDKSettingAudioDeviceDelegate <NSObject>
@optional
/**
 * @brief Notify the microphone device status has changed in the meeting.
 * @param status The microphone device status.
 */
- (void)onMicDeviceStatusChanged:(ZoomSDKDeviceStatus)status;
/**
 * @brief Notify the speaker device status has changed in the meeting.
 * @param status The speaker device status.
 */
- (void)onSpeakerDeviceStatusChanged:(ZoomSDKDeviceStatus)status;
/**
 * @brief Notification that the selected microphone device is changed.
 */
- (void)onSelectedMicDeviceChanged;
/**
 * @brief Notification that the selected speaker device is changed.
 */
- (void)onSelectedSpeakerDeviceChanged;
@end


@protocol ZoomSDKSettingVideoDelegate <NSObject>
@optional
/**
 * @brief Notification of camera status changes in the meeting.
 * @param status The camera device status.
 */
- (void)onCameraStatusChanged:(ZoomSDKDeviceStatus)status;
/**
 * @brief Notification that the selected camera device is changed.
 * @param deviceID The ID of camera.
 */
- (void)onSelectedCameraChanged:(NSString*)deviceID;
@end

@interface ZoomSDKSettingTestSpeakerDeviceHelper: NSObject
{
    id<ZoomSDKSettingTestAudioDelegate>     _delegate;
    BOOL                                    _isSpeakerInTesting;
    NSString*                               _speakerID;
}
@property (nonatomic, readwrite, assign)BOOL                    isSpeakerInTesting;
@property(nonatomic, assign)id<ZoomSDKSettingTestAudioDelegate> delegate;

/**
 * @brief This method is used to start playing when testing speaker. 
 * @param deviceID The ID of the speaker device.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)SpeakerStartPlaying:(NSString*)deviceID;
/**
 * @brief This method is used to stop playing when testing speaker.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)SpeakerStopPlaying;
@end

@interface ZoomSDKSettingTestMicrophoneDeviceHelper: NSObject
{
    id<ZoomSDKSettingTestAudioDelegate>         _delegate;
    ZoomSDKTestMicStatus         _testMicStatus;
    NSString*                    _microphoneID;
}
@property(nonatomic, assign)id<ZoomSDKSettingTestAudioDelegate> delegate;
/**
 * @brief This method is used to start recording when testing microphone.
 * @param deviceID The ID of the microphone device.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)startRecordingMic:(NSString*)deviceID;
/**
 * @brief This method is used to stop recording when testing microphone.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)stopRecrodingMic;
/**
 * @brief This method is used to play recorded sounds when testing microphone.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)playRecordedMic;
/**
 * @brief This method is used to stop playing recorded sounds when testing microphone.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)stopPlayRecordedMic;
/**
 * @brief This method is used to get the status when testing microphone.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKTestMicStatus)getTestMicStatus;
@end



@interface ZoomSDKSettingTestVideoDeviceHelper: NSObject
{
    id<ZoomSDKSettingVideoDelegate>       _delegate;
}
@property(nonatomic, assign)id<ZoomSDKSettingVideoDelegate> delegate;
/**
 * @brief This method is used to set the frame of video preview and tell Zoom client the parent view where the video preview will be drawn. 
 * @param parentView The parent view where the video preview will be drawn.
 * @param containerRect The frame displaying video preview.
 * @return If the function succeeds, it will return ZoomSDKError_success, otherwise failed.
 */
- (ZoomSDKError)SetVideoParentView:(NSView*)parentView VideoContainerRect:(NSRect)containerRect;
/**
 * @brief Preview user's video.
 * @param deviceID The ID of camera device.
 * @return If the function succeeds, it will return ZoomSDKError_success, otherwise failed.
 */
- (ZoomSDKError)StartPreview:(NSString*)deviceID;
/**
 * @brief Stop previewing user's video.
 * @return If the function succeeds, it will return ZoomSDKError_success, otherwise failed.
 */
- (ZoomSDKError)StopPreview;
@end



@interface ZoomSDKAudioStatisticsInfo : NSObject
{
    int _frequencySend;
    int _frequencyReceive;
    int _latencySend;
    int _latencyReceive;
    int _jitterSend;
    int _jitterReceive;
    float _packageLossAvgSend;
    float _packageLossAvgReceive;
    float _packageLossMaxSend;
    float _packageLossMaxReceive;
}
/**
 * @brief Get frequency when transferring audio data.
 * @param isSend YES means sending data, NO receiving data.
 */
- (int)getFrequency:(BOOL)isSend;
/**
 * @brief Get latency time when transferring audio data.
 * @param isSend YES means sending data, NO receiving data.
 */
- (int)getLatency:(BOOL)isSend;
/**
 * @brief Get jitter when transferring audio data.
 * @param isSend YES means sending data, NO receiving data.
 */
- (int)getJitter:(BOOL)isSend;
/**
 * @brief Get the rate of losing package when transferring audio data.
 * @param isSend YES means sending data, NO receiving data.
 * @param isMax YES means the max rate of losing package, NO the average rate of losing package.
 */
- (float)getPackageLoss:(BOOL)isSend Max:(BOOL)isMax;
@end

@interface ZoomSDKVideoASStatisticsInfo : NSObject
{
    int _resolutionSend;
    int _resolutionReceive;
    int _fpsSend;
    int _fpsReceive;
    int _latencySend;
    int _latencyReceive;
    int _jitterSend;
    int _jitterReceive;
    float _packageLossAvgSend;
    float _packageLossAvgReceive;
    float _packageLossMaxSend;
    float _packageLossMaxReceive;
}
/**
 * @brief Get latency time when transferring video or sharing data.
 * @param isSend YES means sending data, NO receiving data.
 */
- (int)getLatency:(BOOL)isSend;
/**
 * @brief Get jitter when transferring video or sharing data.
 * @param isSend YES means sending data, NO receiving data.
 */
- (int)getJitter:(BOOL)isSend;
/**
 * @brief Get the rate of losing package when transferring video or sharing data.
 * @param isSend YES means sending data, NO receiving data.
 * @param isMax YES means the max rate of losing package, NO the average rate of losing package.
 */
- (float)getPackageLoss:(BOOL)isSend Max:(BOOL)isMax;
/**
 * @brief Get resolution when transferring video or sharing data.
 * @param isSend YES means sending data, NO receiving data.
 */
- (int)getResolution:(BOOL)isSend;
/**
 * @brief Get the fram rate when transferring video or sharing data.
 * @param isSend YES means sending data, NO receiving data.
 */
- (int)getFPS:(BOOL)isSend;
@end

@interface SDKDeviceInfo : NSObject
{
    NSString* _deviceID;
    NSString* _deviceName;
    BOOL      _isSelected;
}
/**
 * @brief Get the ID of device, such as microphone, speaker, camera.
 */
- (NSString*)getDeviceID;
/**
 * @brief Get the device name.
 */
- (NSString*)getDeviceName;
/**
 * @brief Query if the device is selected.
 */
- (BOOL)isSelectedDevice;
@end

@interface ZoomSDKAudioSetting: NSObject
{
    ZoomSDKSettingTestSpeakerDeviceHelper* _speakerTestHelper;
    ZoomSDKSettingTestMicrophoneDeviceHelper* _micTestHelper;
    id<ZoomSDKSettingAudioDeviceDelegate>       _delegate;
}
@property(nonatomic, assign)id<ZoomSDKSettingAudioDeviceDelegate> delegate;
/**
 * @brief Get the object of ZoomSDKSettingTestSpeakerDeviceHelper.
 * @return If the function succeeds, it will return a ZoomSDKSettingTestSpeakerDeviceHelper object. Otherwise returns nil.  
 */
- (ZoomSDKSettingTestSpeakerDeviceHelper*)getSettingSpeakerTestHelper;
/**
 * @brief Get the object of ZoomSDKSettingTestMicrophoneDeviceHelper.
 * @return If the function succeeds, it will return a ZoomSDKSettingTestMicrophoneDeviceHelper object. Otherwise returns nil.
 */
- (ZoomSDKSettingTestMicrophoneDeviceHelper*)getSettingMicrophoneTestHelper;
/**
 * @brief Get the list of audio device. 
 * @param mic YES means microphone device, No speaker device.
 * @return If the function succeeds, it will return an array containing SDKDeviceInfo elements, otherwise returns nil.
 */
- (NSArray*)getAudioDeviceList:(BOOL)mic;

/**
 * @brief Get the volume of audio device. 
 * @param mic YES means the volume of microphone device, No speaker device.
 * @return If the function succeeds, it will return an int value(0-100), otherwise returns nil. 
 */
- (int)getAudioDeviceVolume:(BOOL)mic;

/**
 * @brief Set the volume of audio device. 
 * @param mic YES means the volume of microphone device, No speaker device.
 * @param volume The volume of device, varies from 0 to 100. 
 * @return If the function succeeds, it will return ZoomSDKError_success, otherwise failed. 
 */
- (ZoomSDKError)setAudioDeviceVolume:(BOOL)mic Volume:(int)volume;

/**
 * @brief Select an audio device.
 * @param mic YES means microphone device, No speaker device.
 * @param deviceID The ID of the device.
 * @param deviceName The name of the device.
 * @return If the function succeeds, it will return ZoomSDKError_success, otherwise failed. 
 */
- (ZoomSDKError)selectAudioDevice:(BOOL)mic DeviceID:(NSString *)deviceID DeviceName:(NSString*)deviceName;

/**
 * @brief Set to enable stereo in the meeting. 
 * @param enable YES means to enable stereo, No to disable.
 * @return If the function succeeds, it will return ZoomSDKError_success, otherwise failed. 
 */
- (ZoomSDKError)enableStero:(BOOL)enable;

/**
 * @brief Set to output original sound of mic in meeting.
 * @param enable YES means using original sound, No disabling.
 * @return If the function succeeds, it will return ZoomSDKError_success, otherwise failed.
 */
- (ZoomSDKError)enableUseOriginalSound:(BOOL)enable;


/**
 * @brief Enable to join meeting with the audio of computer.
 * @param enable YES means enabled, NO disabled.
 * @return If the function succeeds, it will return ZoomSDKError_success, otherwise not.  
 */
- (ZoomSDKError)enableAutoJoinVoip:(BOOL)enable;

/**
 * @brief Mute user's microphone when he joins the meeting with the audio of computer.
 * @param enable YES means enabled, NO disabled.
 * @return If the function succeeds, it will return ZoomSDKError_success, otherwise not. 
 */
- (ZoomSDKError)enableMuteMicJoinVoip:(BOOL)enable;
/**
 * @brief Enable the feature that attendee can speak by pressing the Spacebar when he is muted.
 * @param enable YES means enabled, NO disabled.
 * @return If the function succeeds, it will return ZoomSDKError_success, otherwise not.
 */
- (ZoomSDKError)enablePushToTalk:(BOOL)enable;

/**
 * @brief Set whether to disable the prompt dialog of joining meeting with third party audio. 
 * @param enable YES means disabled, NO enabled.
 * @return If the function succeeds, it will return ZoomSDKError_success, otherwise not.
 */
- (ZoomSDKError)disablePromptJoinAudioDialogWhenUse3rdPartyAudio:(BOOL)disable;

/**
 * @brief Determine if the meeting supports to pop up the dialog when user joins meeting with third party audio. 
 * @return YES means supported, otherwise not.
 */
- (BOOL)isSupportPromptJoinAudioDialogWhenUse3rdPartyAudio;

/**
 * @brief Determine if the dialog pops up when user joins meeting with third party audio. 
 * @return YES means that the dialog will not pop up, otherwise not. 
 */
- (BOOL)isPromptJoinAudioDialogWhenUse3rdPartyAudioDiable;

/**
 * @brief Enable auto-adjust microphone.
 * @param enable YES means enabled, NO disabled.
 * @return If the function succeeds, it will return ZoomSDKError_success, otherwise not.
 */
- (ZoomSDKError)enableAutoAdjustMic:(BOOL)enable;

/**
 * @brief Determine if auto-adjust microphone is enabled or not. 
 * @return YES means enabled, otherwise not.
 */
- (BOOL)isAutoAdjustMicOn;
/**
 * @brief Determine if user joins meeting with audio on. 
 * @return YES means to enable the audio, otherwise not.
 */
- (BOOL)isJoinAudoWhenJoinMeetingOn;
/**
 * @brief Determine if user joins meeting with microphone muted. 
 * @return YES means muted, otherwise not. 
 */
- (BOOL)isMuteMicWhenJoinMeetingOn;
/**
 * @brief Determine if the meeting supports stereophonic sound. 
 * @return YES means supported, otherwise not.  
 */
- (BOOL)isSupportStereo;
/**
 * @brief Determine if stereophonic sound is enabled. 
 * @return YES means enabled, otherwise not. 
 */
- (BOOL)isEnableStereoOn;
/**
 * @brief Determine if the meeting supports user's original sound. 
 * @return YES means supported, otherwise not.  
 */
- (BOOL)isSupportUseOriginalSound;
/**
 * @brief Determine if user's original sound is enabled.  
 * @return YES means enabled, otherwise not.
 */
- (BOOL)isUseOriginalSoundOn;
/**
 * @brief Set whether to enable the feature that attendee can speak by pressing the Spacebar when he is muted.
 * @return YES means enabled, otherwise not.
 */
- (BOOL)isTemporarilyUnmuteOn;

@end

@interface ZoomSDKVideoSetting: NSObject
{
    ZoomSDKSettingTestVideoDeviceHelper* settingVideoTestHelper;
}
/**
 * @brief Get the object to test video device.  
 * @return If the function succeeds, it will return a ZoomSDKSettingTestVideoDeviceHelper object, otherwise failed, returns nil.
 */
- (ZoomSDKSettingTestVideoDeviceHelper*)getSettingVideoTestHelper;

/**
 * @brief Get the list of camera device.
 * @return If the function succeeds, it will return an array containing SDKDeviceInfo element.
 */
- (NSArray*)getCameraList;

/**
 * @brief Select a camera.
 * @param deviceID The ID of camera.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)selectCamera:(NSString*)deviceID;

/**
 * @brief Determine if mirror effect is enabled. 
 * @return YES means enabled, otherwise not. 
 */
- (BOOL)isMirrorEffectEnabled;

/**
 * @brief Set to enable/disable mirror effect. 
 * @param enable YES means enabled, No disabled.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)enableMirrorEffect:(BOOL)enable;

/**
 * @brief Determine if facial beauty effect is enabled. 
 * @return YES means enabled, otherwise not. 
 */
- (BOOL)isBeautyFaceEnabled;

/**
 * @brief Enable/disable facial beauty effect.
 * @param enable YES means enabled, No disabled.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)enableBeautyFace:(BOOL)enable;

/**
 * @brief Turn off the participant's video when he joins meeting. 
 * @param disable YES means that the video is turned off, otherwise not. 
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)disableVideoJoinMeeting:(BOOL)disable;

/**
 * @brief Display/Hide username on the video window. 
 * @param display YES means showing always username on the video window, otherwise not.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)displayUserNameOnVideo:(BOOL)display;

/**
 * @brief Enable or disable HD video. 
 * @param enable YES means enabled, NO disabled. 
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)enableCatchHDVideo:(BOOL)enable;
/**
 * @brief Set to capture video ratio: original or 16:9. 
 * @param originalSize YES means original video, NO 16:9.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)onVideoCaptureOriginalSizeOr16To9:(BOOL)originalSize;
/**
 * @brief Enable to spotlight the current user's video in the main interface when he speaks in the meeting. 
 * @param enable YES means spotlighting always the current user's video, NO not.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)onSpotlightMyVideoWhenISpeaker:(BOOL)enable;
/**
 * @brief Enable or disable to show the participants in Gallery View up to 49 per screen.
 * @param enable YES indicates to show the participants in Gallery View up to 49 per screen, otherwise not.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)onDisplayUpTo49InWallView:(BOOL)enable;
/**
 * @brief Enable or disable to hide the non-video participants.
 * @param hide YES means hiding, NO means displaying.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)hideNoVideoUser:(BOOL)hide;
/**
 * @brief Determine if non-video participant is hided or not. 
 * @return YES means enabled, otherwise not. 
 */
- (BOOL)isHideNoVideoUser;
/**
 * @brief Query if original size of video is enabled.  
 * @return YES means enabled, otherwise not. 
 */
- (BOOL)isCaptureOriginalSize;
/**
 * @brief Determine if it is enabled to spotlight the current user's video. 
 * @return YES means enabled, otherwise not. 
 */
- (BOOL)isSpotlightMyVideoOn;
/**
 * @brief Determine if the current user's video is muted when he joins meeting. 
 * @return YES means muted, otherwise not. 
 */
- (BOOL)isMuteMyVideoWhenJoinMeetingOn;
/**
 * @brief Determine if it is enabled to display user's screen name.
 * @return YES means enaled, otherwise not. 
 */
- (BOOL)isdisplayUserNameOnVideoOn;
/**
 * @brief Determine if it is able to display up to 49 participants in video wall mode.
 * @return YES means able, otherwise not.  
 */
- (BOOL)isCanDisplayUpTo49InWallView;
/**
 * @brief Determine whether to display up to 49 participants in video wall mode. 
 * @return YES means enabled, otherwise not. 
 */
- (BOOL)isDisplayUpTo49InWallViewOn;
/**
 * @brief Determine if HD video is enabled. 
 * @return YES means enabled, otherwise not. 
 */
- (BOOL)isCatchHDVideoOn;

@end

@interface ZoomSDKRecordSetting: NSObject
/**
 * @brief Set the path for saving the meeting recording file. 
 * @param path The path for saving the meeting recording file.
 * @note The parameter 'path' must already be present, or the path cannot be set successfully.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)setRecordingPath:(NSString*)path;

/**
 * @brief Get the path of the current recorded meeting. 
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (NSString*)getRecordingPath;
@end

@interface ZoomSDKGeneralSetting: NSObject
/**
 * @brief Enable or disable meeting settings by command.
 * @param enable YES means to enable, otherwise not.
 * @param cmd An enumeration of commands that you can enable or disable them in the meeting.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)enableMeetingSetting:(BOOL)enable SettingCmd:(MeetingSettingCmd)cmd;
/**
 * @brief Set custom link for invitation.
 * @param inviteURL The URL for invitation by which user can join meeting.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)setCustomInviteURL:(NSString*)inviteURL;

/**
 * @brief Custom support URL. 
 * @param feedbackURL support URL.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (ZoomSDKError)setCustomFeedbackURL:(NSString*)feedbackURL;

/**
 * @brief Hide setting components. 
 * @param component An enumeration of components for controlling meeting.
 * @param hide YES means to hide, NO to show.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
- (void)hideSettingComponent:(SettingComponent)component hide:(BOOL)hide;

/**
 * @brief This method is used to set default URL for setting components.
 * @param urlType A enum specify the url you want to modify.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)setCustomURL:(SDKURLType)urlType urlString:(NSString*)urlString;
@end

@interface ZoomSDKStatisticsSetting: NSObject
{
    SettingConnectionType _connectionType;
    SettingNetworkType    _networkType;
    NSString*             _proxyAddress;
}
/**
 * @brief Get the connection type of current meeting.
 * @return An enumeration of connection type.
 */
- (SettingConnectionType)getSettingConnectionType;

/**
 * @brief Get network type of current meeting.
 * @return An enumeration of network type. 
 */
- (SettingNetworkType)getSettingNetworkType;
/**
 * @brief Get the proxy address of current meeting.
 * @return Proxy address if the meeting uses a proxy.
 */
- (NSString*)getProxyAddress;
/**
 * @brief Get audio statistic information of the current meeting.
 * @return If the function succeeds, it will return an object of ZoomSDKAudioStatisticsInfo.
 */
- (ZoomSDKAudioStatisticsInfo*)getAudioStatisticsInfo;

/**
 * @brief Get Video/AS statistic information of the current meeting.
 * @param isVideo YES means to get video statistic information, NO to get AS statistics information.
 * @return If the function succeeds, it will return an object of ZoomSDKVideoASStatisticsInfo.
 */
- (ZoomSDKVideoASStatisticsInfo*)getVideoASStatisticsInfo:(BOOL)isVideo;
@end

@interface ZoomSDKSettingService : NSObject
{
    ZoomSDKAudioSetting* _audioSetting;
    ZoomSDKVideoSetting* _videoSetting;
    ZoomSDKRecordSetting* _recordSetting;
    ZoomSDKGeneralSetting* _generalSetting;
    ZoomSDKStatisticsSetting* _statisticsSetting;
}
/**
 * @brief Get the object of audio settings.
 * @return If the function succeeds, it will return an object of ZoomSDKAudioSetting.
 */
-(ZoomSDKAudioSetting*)getAudioSetting;

/**
 * @brief Get the object of video settings.
 * @return If the function succeeds, it will return an object of ZoomSDKVideoSetting.
 */
-(ZoomSDKVideoSetting*)getVideoSetting;

/**
 * @brief Get the object of meeting recording settings.
 * @return If the function succeeds, it will return an object of ZoomSDKRecordSetting.
 */
-(ZoomSDKRecordSetting*)getRecordSetting;

/**
 * @brief Get the object of general settings of SDK.
 * @return If the function succeeds, it will return an object of ZoomSDKGeneralSetting.
 */
-(ZoomSDKGeneralSetting*)getGeneralSetting;

/**
 * @brief Get the object of statistic settings.
 * @return If the function succeeds, it will return an object of ZoomSDKStatisticsSetting.
 */
-(ZoomSDKStatisticsSetting*)getStatisticsSetting;

@end


