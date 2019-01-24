//  ZoomSDKCloseCaptionController.h
//  ZoomSDK
//
//  Created by derain on 2018/12/27.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

@protocol ZoomSDKCloseCaptionControllerDelegate <NSObject>
/**
 * @brief Designated for Zoom Meeting notify specific the user's own get close caption privilege.
 */
- (void)onGetCCPrvilege;

/**
 * @brief Designated for Zoom Meeting notify specific the user's own lost close caption privilege.
 */
- (void)onLostCCPrvilege;

/**
 * @brief Designated for Zoom Meeting notify specific the user's own receive close caption message.
 * @param inString, the string message that received.
 */
- (void)onReceiveCCMessageWithString:(NSString*)inString;

/**
 * @brief Designated for Zoom Meeting notify specific the user's own receive close captio realtime message, realtime means receive the string that user is typing.
 */
- (void)onReceiveCCRealtimeMessage:(NSString *)realtimeMessage;
@end

@interface ZoomSDKCloseCaptionController : NSObject
{
    id<ZoomSDKCloseCaptionControllerDelegate> _delegate;
    
}
@property(nonatomic, assign)id<ZoomSDKCloseCaptionControllerDelegate> delegate;

/**
 * @brief This method is used to get whether this meeting has enabled close caption.
 * @return BOOL value to tell client whether this meeting has enabled close caption.
 */
- (BOOL)isMeetingSupportCloseCaption;

/**
 * @brief This method is used to get whether user can assign others to send close caption.
 * @return BOOL value to tell client whether this user self can assign others to send close caption.
 */
- (BOOL)canAssignOthersToSendCC;

/**
 * @brief This method is used to get whether the user can be assigned to send close caption.
 * @param userID, the id of the user that you want to assigne to send close caption
 * @return BOOL value to tell client whether the user can be assigned to send close caption.
 */
- (BOOL)canBeAssignedToSendCC:(unsigned int)userID;

/**
 * @brief This method is used to get whether the user self can send close caption.
 * @return BOOL value to tell client whether the user self can send close caption..
 */
- (BOOL)canSendClosedCaption;

/**
 * @brief This method is used to get whether the user can save close caption.
 * @return BOOL value to tell client whether the user can save close caption.
 */
- (BOOL)isCanSaveClosedCaption;

/**
 * @brief This method is used to get whether the third party close caption server is available.
 * @return BOOL value to tell client whether the third party close caption server is available.
 */
- (BOOL)is3rdPartCCServerAvailable;

/**
 * @brief This method is used for host to withdraw CC priviledge from user with userID 'userID'.
 * @param userId is the user ID of the user you want to withdraw CC priviledge.
 * @return A ZoomSDKError, ZoomSDKError_Success means success, other will tell failed reason.
 */
- (ZoomSDKError)withdrawCCPriviledgeForUser:(unsigned int)userID;

/**
 * @brief This method is used for host to assign CC priviledge to user with userID 'userID'.
 * @param userId is the user ID of the user you want to assign CC priviledge to.
 * @return A ZoomSDKError, ZoomSDKError_Success means success, other will tell failed reason.
 */
- (ZoomSDKError)assignCCPriviledgeTo:(unsigned int)userID;

/**
 * @brief This method is used for the CC priviledger to send CC message.
 * @param ccString is the CC message you want to send.
 * @return A ZoomSDKError, ZoomSDKError_Success means success, other will tell failed reason.
 */
- (ZoomSDKError)sendClosedCaptionMessage:(NSString*)ccString;

/**
 * @brief This method is used for the CC priviledger to save CC history.
 * @return A ZoomSDKError, ZoomSDKError_Success means success, other will tell failed reason.
 */
- (ZoomSDKError)saveCCHistory;

/**
 * @brief This method is used for the CC priviledger to get CC history save path.
 * @return A NSString for the CC history save path.
 */
- (NSString*)getClosedCaptionHistorySavedPath;

/**
 * @brief This method is used for the CC priviledger to get CC third party url.
 * @param thirdPartyURL, you can get the third party url when pass any NSString variable.
 * @return A ZoomSDKError, ZoomSDKError_Success means success, other will tell failed reason.
 */
- (ZoomSDKError)getClosedCaptionUrlFor3rdParty:(NSString**)thirdPartyURL;

@end
