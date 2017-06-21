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

@interface ZoomSDKSettingService : NSObject

/**
 * This method is used to get camera device list.
 *
 * @return An array contains SDKDeviceInfo element when function call successfully, or return nil.
 */
- (NSArray*)getCameraList;

/**
 * This method is used to get audio device list.
 *
 * @param mic, YES means mic device No means speaker device
 * @return An array contains SDKDeviceInfo element when function call successfully, or return nil.
 */
- (NSArray*)getAudioDeviceList:(BOOL)mic;

/**
 * This method is used to get audio device volume.
 *
 * @param mic, YES means mic device No means speaker device
 * @return An int value (0-100) mentions the selected mic or speaker volume when function call successfully, or return nil.
 */
- (int)getAudioDeviceVolume:(BOOL)mic;

/**
 * This method is used to set audio device volume.
 *
 * @param mic, YES means mic device No means speaker device
 * @param volume, an int value(0-100) device volume you want to set
 * @return A ZoomSDKError to tell client whether set audio device volume successfully or not.
 */
- (ZoomSDKError)setAudioDeviceVolume:(BOOL)mic Volume:(int)volume;

/**
 * This method is used to select an camera device to use.
 *
 * @param deviceID, the device indentity of camera u want to select.
 * @return A ZoomSDKError to tell client whether select camera successfully or not.
 */
- (ZoomSDKError)selectCamera:(NSString*)deviceID;

/**
 * This method is used to select an Audio device to use.
 * @param mic, YES means mic device No means speaker device
 * @param deviceID, the device indentity of camera u want to select.
 * @param deviceName, the device name of camera u want to select.
 * @return A ZoomSDKError to tell client whether select audio device successfully or not.
 */

- (ZoomSDKError)selectAudioDevice:(BOOL)mic DeviceID:(NSString *)deviceID DeviceName:(NSString*)deviceName;
/**
 * This method is used to set default recording saved path for meeting.
 *
 * @param path, default recording saved path for meeting.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)setRecordingPath:(NSString*)path;

/**
 * This method is used to get current recording path for meeting.
 *
 * @return A NSString specify the current recording path.
 */
- (NSString*)getRecordingPath;

/**
 * This method is used to enable or disable setting by command.
 *
 * @param enable, set YES to enable or NO to disable selected setting.
 * @param cmd, a enum specify the setting you want to modify.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)enableMeetingSetting:(BOOL)enable SettingCmd:(MeetingSettingCmd)cmd;

/**
 * This method is used to set default invite URL.
 *
 * @param inviteURL, default default invite URL for meeting.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)setCustomInviteURL:(NSString*)inviteURL;

@end


