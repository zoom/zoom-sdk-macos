//
//  ZoomSDKSettingService.h
//  ZoomSDK
//
//  Created by TOTTI on 8/10/16.
//  Copyright © 2016 TOTTI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

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
@end



@interface ZoomSDKSettingService : NSObject
{
    ZoomSDKAudioSetting* _audioSetting;
    ZoomSDKVideoSetting* _videoSetting;
    ZoomSDKRecordSetting* _recordSetting;
    ZoomSDKGeneralSetting* _generalSetting;
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


@end


