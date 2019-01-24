//
//  ZoomSDKSettingService.h
//  ZoomSDK
//
//  Created by TOTTI on 8/10/16.
//  Copyright © 2016 zoom.us. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

typedef enum{
    SettingComponent_AdvancedFeatureButton,
    SettingComponent_AdvancedFeatureTab,
}SettingComponent;

@protocol ZoomSDKSettingTestAudioDelegate <NSObject>
@optional
/**
 * @brief Designated for Zoom Meeting notify the microphone level changed in setting test.
 * @param level the microphone level.
 */
- (void)onMicLevelChanged:(unsigned int)level;
/**
 * @brief Designated for Zoom Meeting notify the speaker level changed in setting test.
 * @param level the speaker level.
 */
- (void)onSpeakerLevelChanged:(unsigned int)level;
/**
 * @brief Designated for Zoom Meeting notify the microphone test status has changed.
 * @param status the microphone test status.
 */
- (void)onMicTestStatusChanged:(ZoomSDKTestMicStatus)status;
/**
 * @brief Designated for Zoom Meeting notify the speaker test status has changed.
 * @param isTesting means the speaker is in testing or not.
 */
- (void)onSpeakerTestStatusChanged:(BOOL)isTesting;
@end

@protocol ZoomSDKSettingAudioDeviceDelegate <NSObject>
@optional
/**
 * @brief Designated for Zoom Meeting notify the microphone device status has changed.
 * @param status the microphone device status.
 */
- (void)onMicDeviceStatusChanged:(ZoomSDKDeviceStatus)status;
/**
 * @brief Designated for Zoom Meeting notify the speaker device status has changed.
 * @param status the speaker device status.
 */
- (void)onSpeakerDeviceStatusChanged:(ZoomSDKDeviceStatus)status;
/**
 * @brief Designated for Zoom Meeting notify the selected microphone device has changed.
 */
- (void)onSelectedMicDeviceChanged;
/**
 * @brief Designated for Zoom Meeting notify the selected speaker device has changed.
 */
- (void)onSelectedSpeakerDeviceChanged;
@end


@protocol ZoomSDKSettingVideoDelegate <NSObject>
@optional
/**
 * @brief Designated for Zoom Meeting notify the camera device status has changed.
 * @param status the camera device status.
 */
- (void)onCameraStatusChanged:(ZoomSDKDeviceStatus)status;
/**
 * @brief Designated for Zoom Meeting notify the selected camera device has changed.
 * @param deviceID the camera device id that selected.
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
 * @brief This method is used to start play speaker.
 * @param deviceID, the speaker device id.
 * @return A ZoomSDKError to tell client whether start playing speaker successful or not.
 */
- (ZoomSDKError)SpeakerStartPlaying:(NSString*)deviceID;
/**
 * @brief This method is used to stop playing speaker.
 * @return A ZoomSDKError to tell client whether stop playing speaker successful or not..
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
 * @brief This method is used to start recording microphone.
 * @param deviceID, the microphone device id.
 * @return A ZoomSDKError to tell client whether start recording microphone successful or not.
 */
- (ZoomSDKError)startRecordingMic:(NSString*)deviceID;
/**
 * @brief This method is used to stop recording microphone.
 * @return A ZoomSDKError to tell client whether stop recording microphone successful or not.
 */
- (ZoomSDKError)stopRecrodingMic;
/**
 * @brief This method is used to play recorded microphone.
 * @return A ZoomSDKError to tell client whether play recorded microphone successful or not.
 */
- (ZoomSDKError)playRecordedMic;
/**
 * @brief This method is used to stop play recorded microphone.
 * @return A ZoomSDKError to tell client whether stop play recorded microphon successful or not.
 */
- (ZoomSDKError)stopPlayRecordedMic;
/**
 * @brief This method is used to get the testing microphone status.
 * @return A ZoomSDKTestMicStatus to tell client the testing microphone status.
 */
- (ZoomSDKTestMicStatus)getTestMicStatus;
@end



@interface ZoomSDKSettingTestVideoDeviceHelper: NSObject
{
    id<ZoomSDKSettingVideoDelegate>       _delegate;
}
@property(nonatomic, assign)id<ZoomSDKSettingVideoDelegate> delegate;
/**
 * @brief This method is used to set the video preview view frame and tell Zoom client the parent view that the video preview view will be draw on.
 * @param parentView, the the parent view that the preview video view will draw on.
 * @param containerRect, the frame that will display the prew video.
 * @return A ZoomSDKError to tell client whether set frame and parent view successful or not.
 */
- (ZoomSDKError)SetVideoParentView:(NSView*)parentView VideoContainerRect:(NSRect)containerRect;
/**
 * @brief This method is used to start preview video.
 * @param deviceID, the camera device id.
 * @return A ZoomSDKError to tell client whether start preview video successful or not.
 */
- (ZoomSDKError)StartPreview:(NSString*)deviceID;
/**
 * @brief This method is used to stop preview video.
 * @return A ZoomSDKError to tell client whether stop preview video successful or not.
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
- (int)getFrequency:(BOOL)isSend;
- (int)getLatency:(BOOL)isSend;
- (int)getJitter:(BOOL)isSend;
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
- (int)getLatency:(BOOL)isSend;
- (int)getJitter:(BOOL)isSend;
- (float)getPackageLoss:(BOOL)isSend Max:(BOOL)isMax;
- (int)getResolution:(BOOL)isSend;
- (int)getFPS:(BOOL)isSend;
@end

@interface SDKDeviceInfo : NSObject
{
    NSString* _deviceID;
    NSString* _deviceName;
    BOOL      _isSelected;
}
- (NSString*)getDeviceID;
- (NSString*)getDeviceName;
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
 * @brief This method is used to get ZoomSDKSettingTestSpeakerDeviceHelper object.
 * @return ZoomSDKSettingTestSpeakerDeviceHelper object when function call successful, or return nil when failed.
 */
- (ZoomSDKSettingTestSpeakerDeviceHelper*)getSettingSpeakerTestHelper;
/**
 * @brief This method is used to get ZoomSDKSettingTestMicrophoneDeviceHelper object.
 * @return ZoomSDKSettingTestMicrophoneDeviceHelper object when function call successful, or return nil when failed.
 */
- (ZoomSDKSettingTestMicrophoneDeviceHelper*)getSettingMicrophoneTestHelper;
/**
 * @brief This method is used to get audio device list.
 * @param mic, YES means mic device No means speaker device
 * @return An array contains SDKDeviceInfo element when function call successfully, or return nil.
 */
- (NSArray*)getAudioDeviceList:(BOOL)mic;

/**
 * @brief This method is used to get audio device volume.
 * @param mic, YES means mic device No means speaker device
 * @return An int value (0-100) mentions the selected mic or speaker volume when function call successfully, or return nil.
 */
- (int)getAudioDeviceVolume:(BOOL)mic;

/**
 * @brief This method is used to set audio device volume.
 * @param mic, YES means mic device No means speaker device
 * @param volume, an int value(0-100) device volume you want to set
 * @return A ZoomSDKError to tell client whether set audio device volume successfully or not.
 */
- (ZoomSDKError)setAudioDeviceVolume:(BOOL)mic Volume:(int)volume;

/**
 * @brief This method is used to select an Audio device to use.
 * @param mic, YES means mic device No means speaker device
 * @param deviceID, the device indentity of camera u want to select.
 * @param deviceName, the device name of camera u want to select.
 * @return A ZoomSDKError to tell client whether select audio device successfully or not.
 */
- (ZoomSDKError)selectAudioDevice:(BOOL)mic DeviceID:(NSString *)deviceID DeviceName:(NSString*)deviceName;

/**
 * @brief This method is used to Enable Stero in meeting.
 * @param enable, YES means Enable Stero No means disable.
 * @return A ZoomSDKError to tell client whether enable stero successfully or not.
 */
- (ZoomSDKError)enableStero:(BOOL)enable;

/**
 * @brief This method is used to Enable using original sound in meeting.
 * @param enable, YES means enable using original sound No means disable.
 * @return A ZoomSDKError to tell client whether enable using original sound successfully or not.
 */
- (ZoomSDKError)enableUseOriginalSound:(BOOL)enable;


/**
 * @brief This method is used to enable auto join audio by computer.
 * @param enable, YES means enable NO means disable.
 * @return A ZoomSDKError to tell client whether enable auto join voip successfully or not.
 */
- (ZoomSDKError)enableAutoJoinVoip:(BOOL)enable;

/**
 * @brief This method is used to enable mute mic when join meeting.
 * @param enable, YES means enable NO means disable.
 * @return A ZoomSDKError to tell client whether enable mute mic successfully or not.
 */
- (ZoomSDKError)enableMuteMicJoinVoip:(BOOL)enable;
/**
 * @brief This method is used to enable push to talk in meeting.
 * @param enable, YES means enable NO means disable.
 * @return A ZoomSDKError to tell client whether enable push to talk successfully or not.
 */
- (ZoomSDKError)enablePushToTalk:(BOOL)enable;

/**
 * @brief This method is used to disable prompt join audio dialog when use 3rd party audio.
 * @param enable, YES means disable NO means enable.
 * @return A ZoomSDKError to tell client whether disable prompt join audio dialog successfully or not.
 */
- (ZoomSDKError)disablePromptJoinAudioDialogWhenUse3rdPartyAudio:(BOOL)disable;

/**
 * @brief This method is used to get whether support prompt join audio dialog when use 3rd party audio feature.
 * @return A ZoomSDKError to tell client whether support prompt join audio dialog or not.
 */
- (BOOL)isSupportPromptJoinAudioDialogWhenUse3rdPartyAudio;

/**
 * @brief This method is get the whether prompt join audio dialog when use 3rd party audio is disabled or not.
 * @return A BOOL value to tell client whether prompt join audio dialog when use 3rd party audio is disabled or not.
 */
- (BOOL)isPromptJoinAudioDialogWhenUse3rdPartyAudioDiable;

/**
 * @brief This method is used to enable auto adjust microphone.
 * @param enable, YES means enable NO means disable.
 * @return A ZoomSDKError to tell client whether enable auto adjust microphone successfully or not.
 */
- (ZoomSDKError)enableAutoAdjustMic:(BOOL)enable;

/**
 * @brief This method is used to get whether auto adjust microphone option is enabled or not.
 * @return BOOL value to tell client whether auto adjust microphone option is enabled or not.
 */
- (BOOL)isAutoAdjustMicOn;
/**
 * @brief This method is used to get whether auto join audio when join meeting option is enabled or not.
 * @return BOOL value to tell client whether auto join audio when join meeting is enabled or not.
 */
- (BOOL)isJoinAudoWhenJoinMeetingOn;
/**
 * @brief This method is used to get whether mute microphone when join meeting is enabled or not.
 * @return BOOL value to tell client whether mute microphone when join meeting is enabled or not.
 */
- (BOOL)isMuteMicWhenJoinMeetingOn;
/**
 * @brief This method is used to get whether support stereo feature or not.
 * @return BOOL value to tell client whether support stereo feature or not, YES mean support, NO means not.
 */
- (BOOL)isSupportStereo;
/**
 * @brief This method is used to get whether stereo feature is enabled or not.
 * @return BOOL value to tell client whether stereo feature is enabled or not.
 */
- (BOOL)isEnableStereoOn;
/**
 * @brief This method is used to get whether support use original sound feature or not.
 * @return BOOL value to tell client whether support use original sound feature or not, YES mean support, NO means not.
 */
- (BOOL)isSupportUseOriginalSound;
/**
 * @brief This method is used to get whether use original sound is enabled or not.
 * @return BOOL value to tell client whether use original sound is enabled or not.
 */
- (BOOL)isUseOriginalSoundOn;
/**
 * @brief This method is used to get whether temporarily unmute myself is enabled or not.
 * @return BOOL value to tell client whether temporarily unmute myself is enabled or not.
 */
- (BOOL)isTemporarilyUnmuteOn;

@end

@interface ZoomSDKVideoSetting: NSObject
{
    ZoomSDKSettingTestVideoDeviceHelper* settingVideoTestHelper;
}
/**
 * @brief This method is used to get ZoomSDKSettingTestVideoDeviceHelper object.
 * @return ZoomSDKSettingTestVideoDeviceHelper object when function call successful, or return nil when failed.
 */
- (ZoomSDKSettingTestVideoDeviceHelper*)getSettingVideoTestHelper;

/**
 * @brief This method is used to get camera device list.
 * @return An array contains SDKDeviceInfo element when function call successfully, or return nil.
 */
- (NSArray*)getCameraList;

/**
 * @brief This method is used to select an camera device to use.
 * @param deviceID, the device indentity of camera u want to select.
 * @return A ZoomSDKError to tell client whether select camera successfully or not.
 */
- (ZoomSDKError)selectCamera:(NSString*)deviceID;

/**
 * @brief This method is used to get client‘s video mirror effect enable or not.
 * @return A BOOL to tell client whether client‘s video mirror effect enable or not.
 */
- (BOOL)isMirrorEffectEnabled;

/**
 * @brief This method is used to enable/disable video mirror effect.
 * @param enable, YES means enable , No means disable Mirror effect.
 * @return A BOOL to tell client whether client‘s video mirror effect enable or not.
 */
- (ZoomSDKError)enableMirrorEffect:(BOOL)enable;

/**
 * @brief This method is used to get client‘s video beauty face enable or not.
 * @return A BOOL to tell client whether client‘s video beauty face enable or not.
 */
- (BOOL)isBeautyFaceEnabled;

/**
 * @brief This method is used to enable/disable beauty face.
 * @param enable, YES means enable , No means disable beauty face.
 * @return A BOOL to tell client whether client‘s video beauty face enable or not.
 */
- (ZoomSDKError)enableBeautyFace:(BOOL)enable;

/**
 * @brief This method is used to disable video when join meeting.
 * @param disable, YES means video off NO means video on when join meeting.
 * @return A ZoomSDKError to tell client whether disable video when join meeting successfully or not.
 */
- (ZoomSDKError)disableVideoJoinMeeting:(BOOL)disable;

/**
 * @brief This method is used to display username on their video in meeting.
 * @param display, YES means always show username on video NO means not.
 * @return A ZoomSDKError to tell client whether this set action works or not.
 */
- (ZoomSDKError)displayUserNameOnVideo:(BOOL)display;

/**
 * @brief This method is used to enable catch HD video in meeting.
 * @param enable, YES means enbale catch HD video in meeting, NO means not.
 * @return A ZoomSDKError to tell client whether this action works or not.
 */
- (ZoomSDKError)enableCatchHDVideo:(BOOL)enable;
/**
 * @brief This method is used to set capture original video size or 16:9.
 * @param originalSize, YES means always capture original video size, NO capture 16:9 size.
 * @return A ZoomSDKError to tell client whether this set action works or not.
 */
- (ZoomSDKError)onVideoCaptureOriginalSizeOr16To9:(BOOL)originalSize;
/**
 * @brief This method is used to enable spotlight my video when I speaker in meeting.
 * @param enable, YES means always spotlight my video when I speaker in meeting, NO means not.
 * @return A ZoomSDKError to tell client whether this set action works or not.
 */
- (ZoomSDKError)onSpotlightMyVideoWhenISpeaker:(BOOL)enable;
/**
 * @brief This method is used to set display up to 49 participants in wall view in meeting.
 * @param enable, YES means always display up to 49 participants in wall view in meeting, NO means not.
 * @return A ZoomSDKError to tell client whether this set action works or not.
 */
- (ZoomSDKError)onDisplayUpTo49InWallView:(BOOL)enable;
/**
 * @brief This method is used to set hide no video user in meeting.
 * @param hide, YES means always hide no video user in meeting, NO means not.
 * @return A ZoomSDKError to tell client whether this set action works or not.
 */
- (ZoomSDKError)hideNoVideoUser:(BOOL)hide;
/**
 * @brief This method is used to get client‘s hide no video user enabled or not.
 * @return A BOOL to tell client whether client‘s hide no video user enable or not.
 */
- (BOOL)isHideNoVideoUser;
/**
 * @brief This method is used to get client‘s whether capture original size video enabled or not.
 * @return A BOOL to tell client whether client‘s capture original size video enabled or not.
 */
- (BOOL)isCaptureOriginalSize;
/**
 * @brief This method is used to get client‘s spotlight my videot enabled or not.
 * @return A BOOL to tell client whether client‘s spotlight my videot enabled or not.
 */
- (BOOL)isSpotlightMyVideoOn;
/**
 * @brief This method is used to get client‘s mute my video when join meeting enabled or not.
 * @return A BOOL to tell client whether client‘s mute my video when join meeting enabled or not.
 */
- (BOOL)isMuteMyVideoWhenJoinMeetingOn;
/**
 * @brief This method is used to get client‘s display user name on video enabled or not.
 * @return A BOOL to tell client whether client‘s display user name on video enabled or not.
 */
- (BOOL)isdisplayUserNameOnVideoOn;
/**
 * @brief This method is used to get client‘s whether support display up to 49 participants in wall view.
 * @return A BOOL to tell client whether support display up to 49 participants in wall view.
 */
- (BOOL)isCanDisplayUpTo49InWallView;
/**
 * @brief This method is used to get client‘s display up to 49 participants in wall view enabled or not.
 * @return A BOOL to tell client whether display up to 49 participants in wall view enabled or not.
 */
- (BOOL)isDisplayUpTo49InWallViewOn;
/**
 * @brief This method is used to get client‘s catch HD video enable or not.
 * @return A BOOL to tell client whether client‘s catch HD video enable or not.
 */
- (BOOL)isCatchHDVideoOn;

@end

@interface ZoomSDKRecordSetting: NSObject
/**
 * @brief This method is used to set default recording saved path for meeting.
 * @param path, default recording saved path for meeting.
 * @note the parameter path must already exist, otherwise the path cannot be set successfully.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)setRecordingPath:(NSString*)path;

/**
 * @brief This method is used to get current recording path for meeting.
 * @return A NSString specify the current recording path.
 */
- (NSString*)getRecordingPath;
@end

@interface ZoomSDKGeneralSetting: NSObject
/**
 * @brief This method is used to enable or disable setting by command.
 * @param enable, set YES to enable or NO to disable selected setting.
 * @param cmd, a enum specify the setting you want to modify.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)enableMeetingSetting:(BOOL)enable SettingCmd:(MeetingSettingCmd)cmd;
/**
 * @brief This method is used to set default invite URL.
 * @param inviteURL, default default invite URL for meeting.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)setCustomInviteURL:(NSString*)inviteURL;

/**
 * @brief This method is used to set default feedback URL.
 * @param feedback URL, default feedback URL for client.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)setCustomFeedbackURL:(NSString*)feedbackURL;

/**
 * @brief This method is used to hide some component in setting window.
 * @param component  a enum specify the control
 * @param hide set YES to hide NO means show.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (void)hideSettingComponent:(SettingComponent)component hide:(BOOL)hide;

@end

@interface ZoomSDKStatisticsSetting: NSObject
{
    SettingConnectionType _connectionType;
    SettingNetworkType    _networkType;
    NSString*             _proxyAddress;
}
/**
 * @brief This method is used to get Connection Type of current meeting.
 * @return A connection type Enum.
 */
- (SettingConnectionType)getSettingConnectionType;

/**
 * @brief This method is used to get Network Type of current meeting.
 * @return A network type Enum.
 */
- (SettingNetworkType)getSettingNetworkType;
/**
 * @brief This method is used to get the proxy address of current meeting.
 * @return prxoy address if this meeting use proxy.
 */
- (NSString*)getProxyAddress;
/**
 * @brief This method is used to get Audio statistics info current meeting.
 */
- (ZoomSDKAudioStatisticsInfo*)getAudioStatisticsInfo;

/**
 * @brief This method is used to get Video/AS statistics info current meeting.
 * @param isVideo, get video statistics info set YES, set NO to get the AS statistics info.
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
 * @brief This method is used to get auido setting object
 */
-(ZoomSDKAudioSetting*)getAudioSetting;

/**
 * @brief This method is used to get video setting object
 */
-(ZoomSDKVideoSetting*)getVideoSetting;

/**
 * @brief This method is used to get record setting object
 */
-(ZoomSDKRecordSetting*)getRecordSetting;

/**
 * @brief This method is used to get general setting object
 */
-(ZoomSDKGeneralSetting*)getGeneralSetting;

/**
 * @brief This method is used to get general setting object
 */
-(ZoomSDKStatisticsSetting*)getStatisticsSetting;

@end


