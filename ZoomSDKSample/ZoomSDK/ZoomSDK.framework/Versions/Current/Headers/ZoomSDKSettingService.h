//
//  ZoomSDKSettingService.h
//  ZoomSDK
//
//  Created by TOTTI on 8/10/16.
//  Copyright © 2016 TOTTI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

@interface CameraInfo : NSObject
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
 * @return An array contains CameraInfo element when function call successfully, or return nil.
 */
- (NSArray*)getCameraList;

/**
 * This method is used to select an camera device to use.
 *
 * @param deviceID, the device indentity of camera u want to select.
 * @return A ZoomSDKError to tell client whether select camera successfully or not.
 */
- (ZoomSDKError)selectCamera:(NSString*)deviceID;

/**
 * This method is used to set default recording saved path for meeting.
 *
 * @param path, default recording saved path for meeting.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)setRecordingPath:(NSString*)path;

/**
 * This method is used to enable or disable setting by command.
 *
 * @param enable, set YES to enable or NO to disable selected setting.
 * @param cmd, a enum specify the setting you want to modify.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)enableMeetingSetting:(BOOL)enable SettingCmd:(MeetingSettingCmd)cmd;

@end


