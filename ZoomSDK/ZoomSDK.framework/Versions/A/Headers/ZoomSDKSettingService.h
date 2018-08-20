//
//  ZoomSDKSettingService.h
//  ZoomSDK
//
//  Created by TOTTI on 8/10/16.
//  Copyright © 2016 TOTTI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

typedef enum{
    SettingComponent_AdvancedFeatureButton,
    SettingComponent_AdvancedFeatureTab,
}SettingComponent;


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
@end

@interface ZoomSDKVideoSetting: NSObject
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


@end

@interface ZoomSDKRecordSetting: NSObject
/**
 * @brief This method is used to set default recording saved path for meeting.
 * @param path, default recording saved path for meeting.
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


