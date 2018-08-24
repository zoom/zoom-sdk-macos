//
//  ZoomSDKMeetingService.h
//  ZoomSDK
//
//  Created by TOTTI on 7/18/16.
//  Copyright (c) 2016 Zoom Video Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"
#import "ZoomSDKH323Helper.h"
#import "ZoomSDKPhoneHelper.h"
#import "ZoomSDKWaitingRoomController.h"
#import "ZoomSDKMeetingUIController.h"
#import "ZoomSDKBreakoutRoomsController.h"
#import "ZoomSDKMeetingConfiguration.h"
#import "ZoomSDKASController.h"
#import "ZoomSDKMeetingActionController.h"
#import "ZoomSDKLiveStreamHelper.h"
#import "ZoomSDKVideoContainer.h"
#import "ZoomSDKMeetingRecordController.h"
#import "ZoomSDKUpgradeAccountHelper.h"
@interface ZoomSDKSecuritySessionKey : NSObject
{
    SecuritySessionComponet _component;
    NSData*               _sessionKey;
    NSData*               _iv;
}
@property(nonatomic, assign) SecuritySessionComponet component;
@property(nonatomic, retain) NSData* iv;
@property(nonatomic, retain) NSData* sessionKey;

@end

@protocol ZoomSDKMeetingServiceDelegate <NSObject>

@optional

/**
 * @brief Designated for Zoom Meeting State Change notify.
 * @param state tell client meeting state change.
 *
 */
#ifdef BUILD_FOR_ELECTRON
- (void)onMeetingStatusChange:(NSNumber*)state meetingError:(NSNumber*)error EndReason:(NSNumber*)reason;
#else
- (void)onMeetingStatusChange:(ZoomSDKMeetingStatus)state meetingError:(ZoomSDKMeetingError)error EndReason:(EndMeetingReason)reason;
#endif

/**
 * @brief Designated for Zoom Meeting wait external session key notify.
 * @param state tell client need wait session key.
 *
 */
- (void)onWaitMeetingSessionKey:(NSData*)key;

/**
 * @brief Designated for notify statistic warning of Zoom Meeting.
 * @param type: tell client statistic type.
 *
 */
- (void)onMeetingStatisticWarning:(StatisticWarningType)type;

/**
 * @brief Designated for notify should upgrade account.
 * @param upgradeHelper: tell client can upgrade account
 *
 */
- (void)onPaymentReminder:(ZoomSDKUpgradeAccountHelper*)upgradeHelper;
@end

/**
 * @brief ZoomSDKMeetingService is an implementation for client to start/join Zoom Meetings.
 * This meeting service assumes there is only one concurrent operation at a time. This means
 * that at any given time, only one API call will be in progress.
 */
@interface ZoomSDKMeetingService : NSObject
{
    id<ZoomSDKMeetingServiceDelegate> _delegate;
    ZoomSDKMeetingUIController* _meetingUIController;
    ZoomSDKMeetingConfiguration* _meetingConfiguration;
    ZoomSDKBreakoutRoomsController*  _boController;
    ZoomSDKH323Helper*           _h323Helper;
    ZoomSDKWaitingRoomController* _waitingRoomController;
    ZoomSDKPhoneHelper*           _phoneHelper;
    ZoomSDKASController*          _asController;
    ZoomSDKMeetingActionController*  _actionController;
    ZoomSDKLiveStreamHelper*         _liveStreamHelper;
    //customized UI
    ZoomSDKVideoContainer*           _videoContainer;
    ZoomSDKMeetingRecordController*  _recordController;
}
/**
 * The object that acts as the delegate of the receiving meeting events.
 */
@property (assign, nonatomic) id<ZoomSDKMeetingServiceDelegate> delegate;

/**
 * @brief This method is used to get main meeting UI controller.
 * @return A meeting UI controller interface when function call successful, or return nil when failed.
 */
- (ZoomSDKMeetingUIController*)getMeetingUIController;

/**
 * @brief This method is used to get meeting configuration.
 * @return A meeting configuration when function call successful, or return nil when failed.
 */
- (ZoomSDKMeetingConfiguration*)getMeetingConfiguration;

/**
 * @brief This method is used to get the Zoom meeting service default H323 Helper
 * @return a ZoomSDKH323Helper object of H323 Helper
 */
- (ZoomSDKH323Helper*)getH323Helper;

/**
 * @brief This method is used to get the Zoom meeting service default Breakout Rooms Helper
 * @return a ZoomSDKBreakoutRoomsController object of Breakout Rooms Helper
 */
- (ZoomSDKBreakoutRoomsController*)getBreakoutRoomsController;

/**
 * @brief get the Zoom meeting service default Waiting Room Controller
 *
 * @return a ZoomSDKWaitingRoomController object of Waiting Room Controller
 */
- (ZoomSDKWaitingRoomController*)getWaitingRoomController;

/**
 * @brief get the Zoom meeting service default AS Controller
 *
 * @return a ZoomSDKASController object controll share/annotation/remotecontroller
 */
- (ZoomSDKASController*)getASController;

/**
 * @brief get the Zoom meeting service default Phone Callout Helper
 * @return a ZoomSDKPhoneHelper object of Phone Callout Helper
 */
- (ZoomSDKPhoneHelper*)getPhoneHelper;

/**
 * @brief get the Zoom meeting service default action controller(mute audio/video etc)
 * @return a ZoomSDKMeetingActionController object of Meeting Action Controller
 */
- (ZoomSDKMeetingActionController*)getMeetingActionController;

/**
 * @brief get the Zoom meeting service default live stream helper
 * @return a ZoomSDKLiveStreamHelper object u can use to share live stream
 */
- (ZoomSDKLiveStreamHelper*)getLiveStreamHelper;

/**
 * @brief get the Zoom SDK customized video container
 * @return a ZoomSDKVideoContainer object u can use to customized your inmeeting UI.
 */
- (ZoomSDKVideoContainer*)getVideoContainer;

/**
 * @brief get the Zoom SDK customized recording object
 * @return a ZoomSDKMeetingRecordController object u can use to customized record your meeting.
 */
- (ZoomSDKMeetingRecordController*)getRecordController;
/**
 * @brief This method is used to start a Zoom meeting with meeting number.
 * @note  userId\userToken\username is for API user.
 * @param userType The userType depends on what the client account is.
 * @param userId The userId received as a result client user account from Zoom site.
 * @param userToken The userToken received as a result client user account from Zoom site.
 * @param username The username will be used as display name in the Zoom meeting.
 * @param meetingNumber The meetingNumber may be generated from a scheduled meeting or a Personal Meeting ID, if u want to start a instant meeting, set meetingNumber to nil.
 * @param directShare set YES will start share desktop directly when meeting started.
 * @param displayID set the display ID of the app you want share.
 * @param noVideo set YES if u want to join a meeting with video off.
 * @param noAuido set YES if u want to join a meeting with audio off.
 * @param sdkVanityID set meetingNumber to nil if u want to start meeting with vanityID.
 * @return A ZoomSDKError to tell client whether the meeting started or not.
 */
- (ZoomSDKError)startMeeting:(ZoomSDKUserType)userType userID:(NSString*)userId userToken:(NSString*)userToken displayName:(NSString*)username meetingNumber:(NSString*)meetingNumber isDirectShare:(BOOL)directShare sharedApp:(CGDirectDisplayID)displayID isVideoOff:(BOOL)noVideo isAuidoOff:(BOOL)noAuido vanityID:(NSString*)sdkVanityID;

/**
 * @brief This method is used to start a Zoom meeting with ZAK.
 * @note  this interface just for user isn't login yet.
 * @param ZAK  security session key for a user get from web.
 * @param type the user type how to get the ZAK
 * @param userId The userId received as a result client user account from Zoom site.
 * @param username The username will be used as display name in the Zoom meeting.
 * @param meetingNumber The meetingNumber may be generated from a scheduled meeting or a Personal Meeting ID, if u want to start a instant meeting, set meetingNumber to nil.
 * @param directShare set YES will start share desktop directly when meeting started.
 * @param displayID set the display ID of the app you want share.
 * @param noVideo set YES if u want to join a meeting with video off.
 * @param noAuido set YES if u want to join a meeting with audio off.
 * @param sdkVanityID set meetingNumber to nil if u want to start meeting with vanityID.
 * @return A ZoomSDKError to tell client whether the meeting started or not.
 */
- (ZoomSDKError)startMeetingWithZAK:(NSString*)zak userType:(SDKUserType)type userID:(NSString*)userId userToken:(NSString*)userToken displayName:(NSString*)username meetingNumber:(NSString*)meetingNumber isDirectShare:(BOOL)directShare sharedApp:(CGDirectDisplayID)displayID isVideoOff:(BOOL)noVideo isAuidoOff:(BOOL)noAuido vanityID:(NSString*)sdkVanityID;
/**
 * @brief This method is used to join a Zoom meeting.
 * @note toke4enfrocelogin\participantId is for the API user.
 * @param userType The userType depends on what the client account is.
 * @param toke4enfrocelogin if join a meeting that need login, should set this param.
 * @param webinarToken needed when join a webinar meeting if u want to be a panelist.
 * @param participantId set this ID you want in report.
 * @param meetingNumber The meetingNumber used to join the meeting.
 * @param username The username will be used as display name in the Zoom meeting.
 * @param pwd, The meeting password which used to join the meeting, if there does not exist meeting password, just set pwd to nil or @"".
 * @param directShare set YES will start share desktop directly when meeting started.
 * @param displayID set the display ID of the app you want share.
 * @param noVideo set YES if u want to start instant meeting with video off.
 * @param noAuido set YES if u want to start instant meeting with audio off.
 * @param sdkVanityID set meetingNumber to nil if u want to start meeting with vanityID.
 * @return A ZoomSDKError to tell client whether can join the meeting or not.
 */
- (ZoomSDKError)joinMeeting:(ZoomSDKUserType)userType toke4enfrocelogin:(NSString*)toke4enfrocelogin webinarToken:(NSString*)webinarToken participantId:(NSString*)participantId meetingNumber:(NSString*)meetingNumber displayName:(NSString*)username password:(NSString*)pwd isDirectShare:(BOOL)directShare sharedApp:(CGDirectDisplayID)displayID isVideoOff:(BOOL)noVideo isAuidoOff:(BOOL)noAuido  vanityID:(NSString*)sdkVanityID;

/**
 * @brief method is used to end/leave an ongoing meeting.
 * @param cmd, leave meeting by the command type.
 */
- (void)leaveMeetingWithCmd:(LeaveMeetingCmd)cmd;

/**
 * @brief This method is used to tell the client whether the meeting is ongoing or not.
 * @return A ZoomSDKMeetingStatus to tell client the meeting state currently.
 */
- (ZoomSDKMeetingStatus)getMeetingStatus;

/**
 * @brief This method is used to get meeting property.
 * @param command, user command to get differnt property.
 * @return A NSString of meeting property when function call successful, or return nil when failed.
 */
- (NSString*)getMeetingProperty:(MeetingPropertyCmd)command;

/**
 * @brief This method is used to get meeting Connection Quality.
 * @param component specific service you want to test connection, contains video/audio/share
 * @param sending set YES to get sending status or NO to get reciving status
 * @return A enum that discribe the Connection Quality when function call successful.
 */
- (ZoomSDKConnectionQuality)getConnectionQuality:(ConnectionComponent)component Sending:(BOOL)sending;
/**
 * @brief This method is used to get meeting type of current meeting.
 * @return A MeetingType to tell client which kind of meeting is.
 */
- (MeetingType)getMeetingType;

/**
 * @brief This method is used to find out the current meeting is internal or not, special for HuaWei.
 * @return A BOOL value to tell client the current meeting is internal or not.
 */

-(BOOL)isInternalMeeting;

/**
 * @brief This method is used to find out the current meeting is failover or not, special for HuaWei.
 * @return A BOOL value to tell client the current meeting is failover or not.
 */

-(BOOL)isFailoverMeeting;

/**
 * @brief This method is used to set security session key and iv for auido/video etc, special for HuaWei.
 * @param keyArray, ZoomSDKSecuritySessionKey object array.
 * @param leaveMeeting, notify leave meeting session or not.
 * @@return A ZoomSDKError to tell client whether set security key successfully or not.
 */

-(ZoomSDKError)setSecuritySessionKey:(NSArray*)keyArray isLeaveMeeting:(BOOL)leaveMeeting;
@end





