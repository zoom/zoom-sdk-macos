//
//  ZoomSDKPremeetingService.h
//  ZoomSDK
//
//  Created by TOTTI on 8/23/16.
//  Copyright © 2016 zoom.us. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

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
-(void)onDirectShareStatusReceived:(DirectShareStatus)status DirectShareReceived:(ZoomSDKDirectShareHandler*)handler;
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

@interface IMeetingDateOption : NSObject
-(time_t) getMeetingStartTime;
-(unsigned int)getMeetingDuration;
-(BOOL) isRecurringMeeting;
@end

@interface ScheduleMeetingDateOption : IMeetingDateOption
- (void)setMeetingStartTime:(time_t)starttime;
- (void)setMeetingDuration:(unsigned int)duration;
- (void)enableRecurringMeeting:(BOOL)recurring;
@end

@interface IMeetingAudioOption: NSObject
- (ScheduleMeetingAudioType)getScheduleMeetingAudioType:(int*)availableAudioType;
- (BOOL)canGetDialinInfo;
/*
 * @return a NSArray contains NSString of country code
*/
- (NSArray*)getAvailableDialinCountry;
- (NSArray*)getSelectedDialinCountry;
- (BOOL)enableIncludeTollFreeNum;
@end

@interface ScheduleMeetingAudioOption :IMeetingAudioOption

- (ZoomSDKError)setScheduleMeetingAudioType:(ScheduleMeetingAudioType)type;
- (ZoomSDKError)selectDialinCountry:(NSArray*)array;
- (ZoomSDKError)selectIncludeTollFreeNum:(BOOL)include;
@end

@interface IMeetingVideoOption :NSObject
- (BOOL)isHostVideoOn;
- (BOOL)isParticipantVideoOn;
@end

@interface ScheduleMeetingVideoOption: IMeetingVideoOption
- (void)setHostVideoOn:(BOOL)on;
- (void)setParticipantVideoOn:(BOOL)on;
@end

@interface IScheduleForUser: NSObject
{
    NSString* _email;
    NSString* _displayName;
}
@property(nonatomic, readwrite, retain) NSString* email;
@property(nonatomic, readwrite, retain) NSString* displayName;
@end

@interface IMeetingConfigOption : NSObject
-(NSString*)getMeetingTopic;
-(BOOL)enableRequiredPassword;
-(NSString*)getMeetingPassword;
-(BOOL)enableJBH;
-(BOOL)enableMuteOnEntry;
-(BOOL)enableUsePMI;
-(BOOL)enableHostInChina:(BOOL*)canModify;
-(BOOL)enableOnlySignedUserJoin:(BOOL*)canModify;
-(BOOL)enableSpecialDomainUserJoin:(BOOL*)canModify;
-(NSString*)getSpecialDomains;
-(BOOL)enableAutoRecord:(int*)supportRecordType;
-(ScheduleMeetingRecordType)getMeetingRecordType;
-(NSArray*)getScheduleForUser:(BOOL*)canModify; // return a array contains IScheduleForUser object
@end

@interface ScheduleMeetingConfigOption: IMeetingConfigOption
-(void)setMeetingTopic:(NSString*)topic;
-(void)setRequirePassword:(BOOL)require;
-(void)setMeetingPassword:(NSString*)password;
-(void)setEnableJBH:(BOOL)enable;
-(void)setEnableMuteOnEntry:(BOOL)enable;
-(void)setUsePMI:(BOOL)use;
-(ZoomSDKError)setEnableHostInChina:(BOOL)enable;
-(ZoomSDKError)setEnableOnlySignedUserJoin:(BOOL)enable;
-(ZoomSDKError)setEnableSpecialDomainUserJoin:(BOOL)enable;
-(ZoomSDKError)selectSpecialDomains:(NSString*)domains;
-(ZoomSDKError)setEnableAutoRecord:(BOOL)enable;
-(ZoomSDKError)setRecordType:(ScheduleMeetingRecordType)type;
-(ZoomSDKError)selectScheduleForUser:(NSArray*)users;
@end

@interface ZoomSDKScheduleMeetingItem : NSObject
{
    ScheduleMeetingDateOption* _dateOption;
    ScheduleMeetingAudioOption* _audioOption;
    ScheduleMeetingVideoOption* _videoOption;
    ScheduleMeetingConfigOption* _configOption;
}
@property(nonatomic, retain) ScheduleMeetingDateOption* dateOption;
@property(nonatomic, retain) ScheduleMeetingAudioOption* audioOption;
@property(nonatomic, retain) ScheduleMeetingVideoOption* videoOption;
@property(nonatomic, retain) ScheduleMeetingConfigOption* configOption;
@end

@interface ZoomSDKMeetingItem : NSObject
{
    IMeetingDateOption*  _dateOption;
    IMeetingAudioOption*  _audioOption;
    IMeetingVideoOption*  _videoOption;
    IMeetingConfigOption* _configOption;
    long long             _meetingUniqueID;
}
-(IMeetingDateOption*)getDateOption;
-(IMeetingAudioOption*)getAudioOption;
-(IMeetingVideoOption*)getVideoOption;
-(IMeetingConfigOption*)getConfigOption;
-(long long)getMeetingUniqueID;
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
- (ZoomSDKScheduleMeetingItem*)createScheduleMeetingItem;

- (ZoomSDKError)destoryScheduleMeetingItem:(ZoomSDKScheduleMeetingItem*)meetingItem;
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
 * @brief Enable force auto start my video when join meeting, default is follow meeting behavior.
 * @param enable means enable or not.
 */
- (void)enableForceAutoStartMyVideoWhenJoinMeeting:(BOOL)enable;

/**
 * @brief Enable force auto stop to send video when join meeting, default is follow meeting behavior.
 * @param enable means enable or not.
 */
- (void)enableForceAutoStopMyVideoWhenJoinMeeting:(BOOL)enable;

/**
 * @brief Disable auto show select join audio select dialog when join meeting, default is enabled.
 * @param disable means disable or not.
 */
- (void)disableAutoShowSelectJoinAudioDlgWhenJoinMeeting:(BOOL)disable;

/**
 * @brief This method is used to get user's option of force start video when join meeting is enabled or not.
 * @return A BOOL to tell user whether user's video is forced started when join meeting.
 */
- (BOOL)isUserForceStartMyVideoWhenInMeeting;

/**
 * @brief This method is used to get user's option of force stop video when join meeting is enabled or not.
 * @return A BOOL to tell user whether user's video is forced stopped when join meeting.
 */
- (BOOL)isUserForceStopMyVideoWhenInMeeting;

/**
 * @brief This method is used to get user's option of show join audio dialog when join meeting is disabled or not.
 * @return A BOOL to tell user whether the join audio dialog is disabled.
 */
- (BOOL)isUserForceDisableShowJoinAudioDlgWhenInMeeting;

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
