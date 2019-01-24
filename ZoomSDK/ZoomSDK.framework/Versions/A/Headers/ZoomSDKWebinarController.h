//
//  ZoomSDKWebinarController.h
//  ZoomSDK
//
//  Created by derain on 2018/7/27.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

@interface ZoomSDKWebinarMeetingStatus : NSObject
{
    BOOL _allowPanellistStartVideo;
    BOOL _allowAttendeeChat;
    BOOL _allowRaiseHand;
    BOOL _isSupportAttendeeTalk;
}
- (BOOL)isAllowPanellistStartVideo;
- (BOOL)isAllowAttendeeChat;
- (BOOL)isAllowRaiseHand;
- (BOOL)isSupportAttendeeTalk;
@end

@interface ZoomSDKWebinarRegisterHelper :NSObject
{
    WebinarRegisterType   _webinarRegisterType;
}
-(WebinarRegisterType)getWebinarRegisterType;
-(NSURL*)getWebinarRegisterURL;
-(ZoomSDKError)inputEmail:(NSString*)email screenName:(NSString*)name;
-(ZoomSDKError)cancel;
@end


@protocol ZoomSDKWebinarControllerDelegate <NSObject>
@optional
/**
 * @brief Designated for Zoom Meeting notify specific the user's own allow talk status changed, the user's own is allowed to talk.
 */
- (void)onSelfAllowTalkNoti;
/**
 * @brief Designated for Zoom Meeting notify specific the user's own allow talk status changed, the user's own is disallowed to talk.
 */
- (void)onSelfDisallowTalkNoti;
/**
 * @brief Designated for Zoom Meeting notify specific the user's action result for prompt attendee to panelist.
 * @param result mean user prompt attendee to panelist successfully or not.
 */
- (void)onPromoteAttendee2PanelistResultNoti:(unsigned int)result;
/**
 * @brief Designated for Zoom Meeting notify specific the user's action result for deprompt panelist to attendee.
 * @param result mean user prompt attendee to panelist successfully or not.
 */
- (void)onDepromotePanelist2AttendeeResultNoti:(unsigned int)result;
/**
 * @brief Designated for Zoom Meeting notify specific the meeting is allowed attendee chat.
 */
- (void)onAllowAttendeeChatStatusChangedNoti;
/**
 * @brief Designated for Zoom Meeting notify specific the meeting is disallowed attendee chat.
 */
- (void)onDisAllowAttendeeChatStatusChangedNoti;
/**
 * @brief Designated for Zoom Meeting notify specific the meeting is allowed panelist start video.
 */
- (void)onAllowPanelistStartVideoNoti;
/**
 * @brief Designated for Zoom Meeting notify specific the meeting is disallowed panelist start video.
 */
- (void)onDisAllowPanelistStartVideoNoti;
/**
 * @brief Designated for Zoom Meeting notify pnaelist the attendee audio status is changed, viewonly meeting will not receive this notifiy.
 * @param userid mean user's id, can_talk means this user can talk or not, is_muted means this user is muted or not.
 */
- (void)onAttendeeAudioStatusNoti:(unsigned int)userid canTalk:(BOOL)can_talk isMuted:(BOOL)is_muted;
/**
 * @brief Designated for Zoom Meeting notify webinar need register response
 * @param webinarRegisterHelper object, can be used to handle the webinar register actions.
 */
- (ZoomSDKError)onWebinarNeedRegisterResponse:(ZoomSDKWebinarRegisterHelper*)webinarRegisterHelper;
@end


/**
 * @brief ZoomSDKWebinarController is an implementation for client to control Webinar Meetings.
 */
@interface ZoomSDKWebinarController : NSObject
{
    id<ZoomSDKWebinarControllerDelegate> _delegate;
    ZoomSDKWebinarMeetingStatus* _webinarMeetingStatus;
}
@property(nonatomic, assign)id<ZoomSDKWebinarControllerDelegate> delegate;
@property(nonatomic, retain)ZoomSDKWebinarMeetingStatus* webinarMeetingStatus;

/**
 * @brief This method is used to promote one attendee to panelist.
 * @param userId is the user ID of the user you want to handle.
 * @return A ZoomSDKError, ZoomSDKError_Success means can, other will tell failed reason.
 */
-(ZoomSDKError)PromoteAttendee2Panelist:(unsigned int)userId;

/**
 * @brief This method is used to depromote one panelist to attendee.
 * @param userId is the user ID of the user you want to handle.
 * @return A ZoomSDKError, ZoomSDKError_Success means can, other will tell failed reason.
 */
-(ZoomSDKError)DepromotePanelist2Attendee:(unsigned int)userId;

/**
 * @brief This method is used to allow one attendee can talk in meeting.
 * @param userId is the user ID of the user you want to handle.
 * @return A ZoomSDKError, ZoomSDKError_Success means can, other will tell failed reason.
 */
-(ZoomSDKError)AllowAttendeeTalk:(unsigned int)userId;

/**
 * @brief This method is used to disallow one attendee can talk in meeting.
 * @param userId is the user ID of the user you want to handle.
 * @return A ZoomSDKError, ZoomSDKError_Success means can, other will tell failed reason.
 */
-(ZoomSDKError)DisallowAttendeeTalk:(unsigned int)userId;

/**
 * @brief This method is used to allow one panelist can start his video in meeting.
 * @return A ZoomSDKError, ZoomSDKError_Success means can, other will tell failed reason.
 */
-(ZoomSDKError)AllowPanelistStartVideo;

/**
 * @brief This method is used to disallow one panelist can start his video in meeting.
 * @return A ZoomSDKError, ZoomSDKError_Success means can, other will tell failed reason.
 */
-(ZoomSDKError)DisallowPanelistStartVideo;

/**
 * @brief This method is used to allow one attendee can chat with others when in meeting.
 * @return A ZoomSDKError, ZoomSDKError_Success means can, other will tell failed reason.
 */
-(ZoomSDKError)AllowAttendeeChat;

/**
 * @brief This method is used to disallow one attendee can chat with others when in meeting.
 * @return A ZoomSDKError, ZoomSDKError_Success means can, other will tell failed reason.
 */
-(ZoomSDKError)DisallowAttendeeChat;

/**
 * @brief This method is used to get the object ZoomSDKWebinarMeetingStatus.
 * @return An object of ZoomSDKWebinarMeetingStatus.
 */
-(ZoomSDKWebinarMeetingStatus*)getZoomSDKWebinarMeetingStatus;

/**
 * @brief This method is used to get the attendee list in meeting.
 * @return An NSArray for attendee list.
 */
- (NSArray*)getAttendeeList;

@end
