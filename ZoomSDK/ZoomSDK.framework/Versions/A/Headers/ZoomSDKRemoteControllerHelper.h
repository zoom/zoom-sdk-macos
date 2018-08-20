//
//  ZoomSDKRemoteControllerHelper.h
//  ZoomSDK
//
//  Created by TOTTI on 12/07/2018.
//  Copyright © 2018 TOTTI. All rights reserved.
//  [Used for Customized UI]

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"
@protocol ZoomSDKRemoteControllerDelegate <NSObject>
/**
 * @brief Designated for SDK notify the remote control status.
 * @param status the remote controll user's status.
 * @param userID the remote controll user's identity.
 *
 */
- (void)onRemoteControlStatus:(ZoomSDKRemoteControlStatus)status User:(unsigned int)userID;
@end

@interface ZoomSDKRemoteControllerHelper : NSObject
{
    id<ZoomSDKRemoteControllerDelegate> _delegate;
    
}
@property(nonatomic, assign) id<ZoomSDKRemoteControllerDelegate> delegate;
/**
 * @brief Designated for SDK to check whether u can request remote control of specific user or not.
 * @param userid the user's identity u want request remote controll.
 * @return return ZoomSDKError_Success if u can request remote control the specific user, else means failed.
 */
- (ZoomSDKError)canRequestRemoteControl:(unsigned int)userid;

/**
 * @brief Designated for SDK to check whether u have remote controll privilege of specific user or not.
 * @param userid the user's identity u want to check.
 * @return return ZoomSDKError_Success if u have remote controll privilege the specific user, else means failed.
 */
- (ZoomSDKError)haveRemoteControlPrivilege:(unsigned int)userid;

/**
 * @brief Designated for SDK to check whether u are now remote controlling specific user's pc or not.
 * @param userid the user's identity u want to check.
 * @return return ZoomSDKError_Success if u are remote controlling the specific user, else mean not.
 */
- (ZoomSDKError)isInRemoteControlling:(unsigned int)userid;

/**
 * @brief Designated for SDK to start remote control specific user's pc.
 * @param userid the user's identity u want to start remote controll.
 * @return return ZoomSDKError_Success if u start remote control the specific user successfully, else mean failed.
 */
- (ZoomSDKError)startRemoteControl:(unsigned int)userid;

/**
 * @brief Designated for SDK to stop remote controll specific user's pc, still have the privilege to remote control.
 * @param userid the user's identity u want to stop remote controll.
 * @return return ZoomSDKError_Success if u stop remote control the specific user successfully, else mean failed.
 */
- (ZoomSDKError)stopRemoteControl:(unsigned int)userid;

/**
 * @brief Designated for SDK to request remote control privilege of specific user
 * @param userid the user's identity u want to request remote control.
 * @return return ZoomSDKError_Success if u request remote control the specific user successfully, else mean failed.
 */
- (ZoomSDKError)requestRemoteControl:(unsigned int)userid;

/**
 * @brief Designated for SDK to give up remote controll privilege of specific user
 * @param userid the user's identity u are now remote contolling.
 * @return return ZoomSDKError_Success if u give up remote control the specific user successfully, else mean failed.
 */
- (ZoomSDKError)giveUpRemoteControl:(unsigned int)userid;

/**
 * @brief Designated for SDK to give remote control privilege to specific user
 * @param userid the user's identity u want to give remote control privilege to.
 * @return return ZoomSDKError_Success if u give remote control to the specific user successfully, else mean failed.
 */
- (ZoomSDKError)giveRemoteControlPrivilegeTo:(unsigned int)userid;

/**
 * @brief Designated for SDK to decline remote control request from specific user
 * @param userid the user's identity who want to get your desktop remote control privilege.
 * @return return ZoomSDKError_Success if u decline remote control request from the specific user successfully, else mean failed.
 */
- (ZoomSDKError)declineRemoteControlRequest:(unsigned int)userid;

/**
 * @brief Designated for SDK to revoke remote control privilege to yourself.
 * @return return ZoomSDKError_Success if u revoke remote control successfully, else mean failed.
 */
- (ZoomSDKError)revokeRemoteControl;

/**
 * @brief Designated for SDK to get current remote controller's identity.
 * @param userid a unsigned int pointer.
 * @return return ZoomSDKError_Success if function call successfully and the userid will be assigned the identity of current user, else mean failed.
 */
- (ZoomSDKError)getCurrentRemoteController:(unsigned int*)userid;

- (ZoomSDKError)sendRemoteControlEvent:(NSEvent *)theEvent ShareView:(NSView*)shareView;
@end
