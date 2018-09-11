//
//  ZoomSDKPremeetingService.h
//  ZoomSDK
//
//  Created by TOTTI on 8/23/16.
//  Copyright © 2016 TOTTI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"
#import "ZoomSDKBuildType.h"

@interface ZoomSDKDirectShareHandler: NSObject
/**
 * @brief Designated to input meeting number to direct share
 * @return an ZoomSDKError to tell client whether fuction call successfully.
 */
-(ZoomSDKError)inputMeetingNumber:(NSString*)meetingNumber;
/**
 * @brief Designated to input sharing key in Rooms to direct share
 * @return an ZoomSDKError to tell client whether fuction call successfully.
 */
-(ZoomSDKError)inputSharingKey:(NSString*)shareKey;
/**
 * @brief Designated to cancel input action.
 */
-(ZoomSDKError)cancel;
@end

@protocol ZoomSDKDirectShareHelperDelegate<NSObject>
/**
 * @brief Designated notify directshare status change.
 * @param status: direct share status
 * @param handler: a ZoomSDKDirectShareHandler object only work when status is DirectShareStatus_NeedMeetingIDOrSharingKey or DirectShareStatus_WrongMeetingIDOrSharingKey
 */
#ifdef BUILD_FOR_ELECTRON
-(void)onDirectShareStatusReceived:(NSNumber*)status DirectShareReceived:(ZoomSDKDirectShareHandler*)handler;
#else
-(void)onDirectShareStatusReceived:(DirectShareStatus)status DirectShareReceived:(ZoomSDKDirectShareHandler*)handler;
#endif
@end

@interface ZoomSDKDirectShareHelper: NSObject
{
    id<ZoomSDKDirectShareHelperDelegate> _delegate;
}
@property(nonatomic, assign) id<ZoomSDKDirectShareHelperDelegate> delegate;
/**
 * @brief Designated to notify whether can start direct share by ultrasonic or not.
 * @return an ZoomSDKError to tell client whether can start direct share, ZoomSDKError_Success means can, else means can't.
 */
-(ZoomSDKError)canDirectShare;
/**
 * @brief Designated to start direct share by ultrasonic.
 * @return an ZoomSDKError to tell client whether start direct share successfully or not.
 */
-(ZoomSDKError)startDirectShare;
/**
 * @brief Designated to stop direct share.
 * @return an ZoomSDKError to tell client whether stop direct share successfully or not.
 */
-(ZoomSDKError)stopDirectShare;
@end

@protocol ZoomSDKOutlookPluginDelegate <NSObject>
/**
 * @brief Designated outlookplugin request login notification.
 */
-(void)onOutlookPluginNeedLoginRequest;

/**
 * @brief Designated outlookplugin request schedule meeting notification.
 */
-(void)onOutlookPluginScheduleMeetingRequest;

/**
 * @brief Designated outlookplugin request defalut meeting topic notification.
 * @param scheduleForEmail: schedule for email if have
 * @param topic: if can change default meeting topic in this callback.
 */
-(void)onOutlookPluginDefaultMeetingTopicRequest:(NSString*)scheduleForEmail DefaultMeetingTopic:(NSString**)topic;
@end


@interface ZoomSDKOutlookPluginHelper : NSObject
{
    id<ZoomSDKOutlookPluginDelegate> _delegate;
}
@property(nonatomic, assign)id<ZoomSDKOutlookPluginDelegate> delegate;
/**
 * @brief Designated to start outlook plugin helper service.
 * @param ipcName ipc Name used to connect to outlookplugin
 * @param ipcNoti ipc notification used by outlookplugin connect with sdk.
 * @param appName your app name.
 * @param identity your app identity.
 * @return an ZoomSDKError to tell client whether fuction call successfully or not.
 */
-(ZoomSDKError)start:(NSString*)ipcName IPCNoti:(NSString*)ipcNoti AppName:(NSString*)appName AppIdentity:(NSString*)identity;
/**
 * @brief Designated to stop outlook plugin helper service.
 * @return an ZoomSDKError to tell client whether fuction call successfully or not.
 */
-(ZoomSDKError)stop;
@end

@interface ZoomSDKScheduleMeetingItem : NSObject
{
    NSString*  _meetingTopic;
    NSString*  _meetingPassword;
    time_t     _meetingStartTime;
    time_t     _meetingDuration;
    BOOL       _joinBeforeHost;
    BOOL       _usePMI;
    BOOL       _turnOffVideoForHost;
    BOOL       _turnOffVideoForAttendee;
}
@property(nonatomic, retain) NSString* meetingTopic;
@property(nonatomic, retain) NSString* meetingPassword;
@property(nonatomic, assign) time_t    meetingStartTime;
@property(nonatomic, assign) time_t    meetingDuration;
@property(nonatomic, assign) BOOL      joinBeforeHost;
@property(nonatomic, assign) BOOL      usePMI;
@property(nonatomic, assign) BOOL      turnOffVideoForHost;
@property(nonatomic, assign) BOOL      turnOffVideoForAttendee;

@end

@interface ZoomSDKMeetingItem : NSObject
{
    long long _meetingUniqueID;
}
- (BOOL)isValidMeeting;
- (BOOL)isPersonalMeeting;
- (BOOL)isWebinarMeeting;
- (BOOL)isRecurringMeeting;
- (BOOL)isAllowJoinBeforeHost;
- (BOOL)isUsePMIAsMeetingID;
- (long long) getMeetingUniqueID;
- (long long) getMeetingNumber;
- (time_t) getMeetingStartTime;
- (time_t) getMeetingDuration;
- (NSString*) getMeetingTopic;
- (NSString*) getMeetingPassword;
@end

@protocol ZoomSDKPremeetingServiceDelegate;
@interface ZoomSDKPremeetingService : NSObject
{
    id<ZoomSDKPremeetingServiceDelegate> _delegate;
    ZoomSDKOutlookPluginHelper* _outlookPluginHelper;
    ZoomSDKDirectShareHelper* _directShareHelper;
}

/**
 * The object that acts as the delegate of the premeeting events.
 */
@property (assign, nonatomic) id<ZoomSDKPremeetingServiceDelegate> delegate;

/**
 * @brief This method is used to schedule a Zoom meeting with meeting item you created.
 * @param meetingItem the specified meeting user want to schedule.
 * @return A ZoomSDKError to tell client whether the meeting has been scheudled successfully or not.
 */
- (ZoomSDKError)scheduleMeeting:(ZoomSDKScheduleMeetingItem*)meetingItem;

/**
 * @brief This method is used to edit a existed Zoom meeting with specified meeting unique ID..
 * @param meetingItem the user create to edit meeting.
 * @param meetingUniqueID the specified meeting Unique ID user want to edit.
 * @return A ZoomSDKError to tell client whether the meeting has been scheudled successfully or not.
 */
- (ZoomSDKError)editMeeting:(ZoomSDKScheduleMeetingItem*)meetingItem MeetingUniqueID:(long long)meetingUniqueID;

/**
 * @brief This method is used to delete a existed Zoom meeting with specified meeting unique ID.
 * @param meetingUniqueID the specified meeting Unique ID user want to delete.
 * @return A ZoomSDKError to tell client whether the meeting has been deleted successfully or not.
 */
- (ZoomSDKError)deleteMeeting:(long long)meetingUniqueID;

/**
 * @brief This method is used to list all meetings.
 * @return A ZoomSDKError to tell client whether list meeting successfully or not.
 */
- (ZoomSDKError)listMeeting;

/**
 * @brief This method is used to get meeting item info from a existed Zoom meeting with specified meeting unique ID.
 * @param meetingUniqueID the specified meeting Unique ID user want to get.
 * @return A ZoomSDKMeetingItem object with meeeting info if function call successfully.
 */
- (ZoomSDKMeetingItem*)getMeetingItem:(long long)meetingUniqueID;

/**
 * @brief This method is used to show schedule or edit meeting window
 * @note  not support edit pmi and webinar meeting.
 * @param show BOOL value specified u want to show or hide schedule/edit window, 1 means show, 0 means hide.
 * @param window the specified NSWindow point of the schedule/edit window if this fuction call successfully.
 * @param meetingUniqueID the specified meeting item user want to edit, set 0 to schedule window.
 * @return A ZoomSDKError to tell client whether list meeting successfully or not.
 */
- (ZoomSDKError)showScheduleEditMeetingWindow:(BOOL)show Window:(NSWindow**)window MeetingID:(long long)meetingUniqueID;

/**
 * @brief Designated get a ZoomSDKOutlookPluginHelper object
 * @return ZoomSDKOutlookPluginHelper object
 */
- (ZoomSDKOutlookPluginHelper*)getOutlookPluginHelper;

/**
 * @brief Designated get a ZoomSDKDirectShareHelper object
 * @return ZoomSDKDirectShareHelper object
 */
- (ZoomSDKDirectShareHelper*)getDirectShareHelper;
@end


@protocol ZoomSDKPremeetingServiceDelegate <NSObject>

@optional
/**
 * @brief Designated for Zoom PreMeeting Response.
 * @param error tell client related to this premeeting event whether list meeting success or not.
 * @param meetingList A NSArray contains elements of ZoomSDKMeetingItem.
 *
 */
- (void)onListMeeting:(ZoomSDKPremeetingError)error MeetingList:(NSArray*)meetingList;

/**
 * @brief Designated for Zoom PreMeeting Schedule or edit meeting notify.
 * @param error tell client related to this premeeting event whether schedule or edit meeting successfully or not.
 * @param meetingUniqueID the unique id of the meeting you schedule or edit.
 *
 */
- (void)onScheduleOrEditMeeting:(ZoomSDKPremeetingError)error MeetingUniqueID:(long long)meetingUniqueID;

/**
 * @brief Designated for Zoom PreMeeting delete meeting notify.
 * @param error tell client related to this premeeting event whether delete meeting successfully or not.
 *
 */
- (void)onDeleteMeeting:(ZoomSDKPremeetingError)error;
@end
