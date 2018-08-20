//
//  ZoomSDKMeetingActionController.h
//  ZoomSDK
//
//  Created by TOTTI on 9/1/17.
//  Copyright © 2017 TOTTI. All rights reserved.
//
#import "ZoomSDKErrors.h"
#import "ZoomSDKBuildType.h"

@interface ZoomSDKChatInfo : NSObject
{
    unsigned int _sendID;
    unsigned int _receiverID;
    NSString*    _sendName;
    NSString*    _receiverName;
    NSString*    _content;
    time_t       _timestamp;
}
- (unsigned int)getSenderUserID;
- (NSString*)getSenderDisplayName;
- (unsigned int)getReceiverUserID;
- (NSString*)getReceiverDisplayName;
- (NSString*)getMsgContent;
- (time_t)getTimeStamp;
@end

@interface ZoomSDKUserAudioStauts : NSObject
{
    unsigned int _userID;
    ZoomSDKAudioStatus _status;
    ZoomSDKAudioType _type;
}
- (unsigned int)getUserID;
- (ZoomSDKAudioStatus)getStatus;
- (ZoomSDKAudioType)getType;
@end

@interface ZoomSDKUserInfo :NSObject
{
    unsigned int _userID;
}
- (BOOL)isMySelf;
- (NSString*)getUserName;
- (NSString*)getEmail;
- (unsigned int)getUserID;
- (BOOL)isHost;
- (BOOL)isVideoOn;
- (BOOL)isAudioMuted;
- (UserRole)getUserRole;
- (BOOL)isPurePhoneUser;
- (BOOL)canBeCoHost;
@end

@interface ZoomSDKJoinMeetingHelper :NSObject
{
    JoinMeetingReqInfoType   _reqInfoType;
}
-(JoinMeetingReqInfoType)getReqInfoType;
-(ZoomSDKError)inputPassword:(NSString*)password;
-(ZoomSDKError)cancel;
@end


@protocol ZoomSDKMeetingActionControllerDelegate <NSObject>

/**
 * @brief Designated for Zoom Meeting User Audio status Change notify.
 * @param userAudioStatusArray a array contains ZoomSDKUserAudioStauts elements tell client audio stauts change of each user.
 *
 */
#ifdef BUILD_FOR_ELECTRON
- (void)onUserAudioStatusChange:(NSString*)userAudioStatusJasonString;
#else
- (void)onUserAudioStatusChange:(NSArray*)userAudioStatusArray;
#endif

/**
 * @brief Designated for Zoom Meeting User receive chat message notify.
 * @param chatInfo tell client the info of the chat message info user received.
 *
 */
- (void)onChatMessageNotification:(ZoomSDKChatInfo*)chatInfo;

/**
 * @brief Designated for Zoom Meeting new user join notify.
 * @param array tell client the joined user array.
 *
 */
#ifdef BUILD_FOR_ELECTRON
- (void)onUserJoin:(NSString*)arrayJsonString;
#else
- (void)onUserJoin:(NSArray*)array;
#endif

/**
 * @brief Designated for Zoom Meeting user left notify.
 * @param array tell client the left user array.
 *
 */
#ifdef BUILD_FOR_ELECTRON
- (void)onUserLeft:(NSString*)arrayJsonString;
#else
- (void)onUserLeft:(NSArray*)array;
#endif

/**
 * @brief Designated for Zoom Meeting notify the specific user info change.
 * @param userID user's identity whose info changed.
 *
 */
- (void)onUserInfoUpdate:(unsigned int)userID;

/**
 * @brief Designated for Zoom Meeting notify the host change.
 * @param userID user's identity who becomes host.
 *
 */
#ifdef BUILD_FOR_ELECTRON
- (void)onHostChange:(NSNumber*)userID;
#else
- (void)onHostChange:(unsigned int)userID;
#endif

/**
 * @brief Designated for Zoom Meeting notify the co-host change.
 * @param userID user's identity who becomes co-host.
 *
 */
- (void)onCoHostChange:(unsigned int)userID;

/**
 * @brief Designated for Zoom Meeting notify spotlight video user change .
 * @param spotlight YES mean get spotlight No means not.
 * @param userID user's identity whose spotlight status change.
 *
 */
- (void)onSpotlightVideoUserChange:(BOOL)spotlight User:(unsigned int)userID;

/**
 * @brief Designated for Zoom Meeting notify specific user video status change.
 * @param videoOn mean specific user video is On or not.
 * @param userID user's identity whose video status change.
 *
 */
#ifdef BUILD_FOR_ELECTRON
- (void)onVideoStatusChange:(NSNumber*)videoOn UserID:(NSNumber*)userID;
#else
- (void)onVideoStatusChange:(BOOL)videoOn UserID:(unsigned int)userID;
#endif

/**
 * @brief Designated for Zoom Meeting notify specific user raise hand or lower hand status change.
 * @param raise YES mean specific user raise hand ,No means lower hand.
 * @param userID user's identity who raise hand or lower hand.
 *
 */
- (void)onLowOrRaiseHandStatusChange:(BOOL)raise UserID:(unsigned int)userID;

/**
 * @brief Designated for Zoom Meeting notify join meeting response
 * @param joinMeetingHelper object your received, u can select in put password or not.
 */
- (void)onJoinMeetingResponse:(ZoomSDKJoinMeetingHelper*)joinMeetingHelper;

/**
 * @brief Designated for Zoom Meeting notify active speaker change in meeting.
 * @param userID mean active speaker's user identity.
 */
- (void)onActiveSpeakerChanged:(unsigned int)userID;

@end

@interface ZoomSDKMeetingActionController : NSObject
{
    id<ZoomSDKMeetingActionControllerDelegate> _delegate;
    NSMutableArray*             _participantsArray;
}
@property(nonatomic, assign) id<ZoomSDKMeetingActionControllerDelegate> delegate;

/**
 * @brief This method is used to get participant list.
 * @return An array contains participant id.
 */
- (NSArray*)getParticipantsList;
/**
 * @brief This method is used to modify an ongoing meeting.
 * @param cmd, modify the meeting with different command.
 * @param userID, user can modify the himself, set 0, only host can modify other participants,set the userID of the participant to be modified.
 * @param screen, select the specific screen u want to do action with.
 * @return A ZoomSDKError to tell client whether modify meeting successful or not.
 */
- (ZoomSDKError)actionMeetingWithCmd:(ActionMeetingCmd)cmd userID:(unsigned int)userID onScreen:(ScreenType)screen;

/**
 * @brief This method is used to send a chat message.
 * @param content, message content u want to send.
 * @param userID, userID of the user u want to send chat to.
 * @return A ZoomSDKError to tell client whether send message successful or not.
 */
- (ZoomSDKError)sendChat:(NSString*)content toUser:(unsigned int)userID;

/**
 * @brief This method is used to get user info by the selecetd user.
 * @param userID, userID of the selected user.
 * @return A user info interface when function call successful, or return nil when failed.
 */
- (ZoomSDKUserInfo*)getUserByUserID:(unsigned int)userID;

/**
 * @brief This method is used to change user name.
 * @param userID, userID of the selected user whose name u want to change, host can rename attendee, attendee only can rename himself.
 * @param name, new name u want to rename with.
 * @return A ZoomSDKError to tell client function call successful or not.
 */
- (ZoomSDKError)changeUserName:(unsigned int)userID newName:(NSString*)name;

/**
 * @brief This method is used for making a participant to be a new host or orignal host to recliam host
 * @param userID, the identity of the user, set userid = 0 to reclaim host.
 * @return A ZoomSDKError to tell client function call successful or not.
 */
- (ZoomSDKError)makeHost:(unsigned int)userID;

/**
 * @brief This method is used to mention client can reclaim host or not.
 * @return A BOOL, YES means can reclaim NO means not.
 */
- (BOOL)canReclaimHost;
/**
 * @brief This method is used for participant to claim host by hostkey.
 * @param hostKey, the host key of the meeting host.
 * @return A ZoomSDKError to tell client function call successful or not.
 */
- (ZoomSDKError)claimHostByKey:(NSString*)hostKey;
/**
 * @brief This method is used for host to assign cohost to one participant.
 * @param userid, the user id of the participant u want to make cohost.
 * @return A ZoomSDKError to tell client function call successful or not.
 */
-(ZoomSDKError)assignCoHost:(unsigned int)userid;

/**
 * @brief This method is used for host to revoke cohost privilege from a specific participant.
 * @param userid, the user id of the participant u want to make cohost.
 * @return A ZoomSDKError to tell client function call successful or not.
 */
-(ZoomSDKError)revokeCoHost:(unsigned int)userid;

@end
