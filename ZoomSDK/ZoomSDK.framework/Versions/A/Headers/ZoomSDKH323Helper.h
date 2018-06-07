//
//  ZoomSDKH323Helper.h
//  ZoomSDK
//
//  Created by TOTTI on 1/3/17.
//  Copyright © 2017 TOTTI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

@interface H323DeviceInfo : NSObject
{
    NSString* _name;
    NSString* _ip;
    NSString* _e164num;
    H323DeviceType _type;
    EncryptType  _encryptType;
}

@property(nonatomic, retain)NSString* name;
@property(nonatomic, retain)NSString* ip;
@property(nonatomic, retain)NSString* e164num;
@property(nonatomic, assign)H323DeviceType type;
@property(nonatomic, assign)EncryptType encryptType;
@end

@protocol ZoomSDKH323HelperDelegate <NSObject>
@optional
/**
 * @brief Designated for ZoomSDK support H323 Device callout response.
 * @param calloutStatus tell user when the callout status changed.
 *
 */
- (void) onCalloutStatusReceived:(H323CalloutStatus)calloutStatus;

/**
 * @brief Designated for ZoomSDK support H323 Device pair meeting response.
 * @param pairResult tell user when the pair status changed.
 *
 */
- (void) onPairCodeResult:(H323PairingResult)pairResult;
@end


@interface ZoomSDKH323Helper : NSObject
{
    id<ZoomSDKH323HelperDelegate> _delegate;
}
@property (assign, nonatomic) id<ZoomSDKH323HelperDelegate> delegate;
/**
 * @brief This method is used to Get h323 address for current meeting.
 * @return A NSArray contains addresses if function call successfully.
 */
- (NSArray*)getH323DeviceAddress;

 /**
 * @brief This method is used to Get h323 password for current meeting.
 * @return A NSString contains h323 password if function call successfully.
 */
- (NSString*)getH323Password;

/**
 * @brief This method is used to send Meeting paring code.
 * @param pairCode pair code for specified meeting.
 * @param meetingNum the meeting number u want to pair.
 * @return A ZoomSDKError to tell client whether send pair code successfully or not.
 */
- (ZoomSDKError)sendMeetingPairingCode:(NSString*)pairCode meetingNum:(long long)meetingNum;

/**
 * @brief This method is used to call out a H323 device.
 * @param deviceInfo H323DeviceInfo object specified the H323 device u want to callout.
 * @return A ZoomSDKError to tell client whether callout H323 device successfully or not.
 */
- (ZoomSDKError)calloutH323Device:(H323DeviceInfo*)deviceInfo;

/**
 * @brief This method is used to get Room H323 device list for current meeting.
 * @return A NSArray contains H323DeviceInfo objects for current meeting.
 */
- (NSArray*)getRoomH323DeviceArray;

/**
 * @brief This method is used to cancel last callout to a H323 device.
 * @return A ZoomSDKError to tell client whether cancel callout H323 device successfully or not.
 */
- (ZoomSDKError)cancelCallOutH323;

@end
