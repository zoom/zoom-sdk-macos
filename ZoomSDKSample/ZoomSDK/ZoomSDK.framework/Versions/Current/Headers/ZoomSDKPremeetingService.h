//
//  ZoomSDKPremeetingService.h
//  ZoomSDK
//
//  Created by TOTTI on 8/23/16.
//  Copyright © 2016 TOTTI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

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
}

/**
 * The object that acts as the delegate of the premeeting events.
 */
@property (assign, nonatomic) id<ZoomSDKPremeetingServiceDelegate> delegate;

/**
 * This method is used to schedule a Zoom meeting with meeting item you created.
 *
 * @param meetingItem the specified meeting user want to schedule.
 * @return A ZoomSDKError to tell client whether the meeting has been scheudled successfully or not.
 */
- (ZoomSDKError)scheduleMeeting:(ZoomSDKScheduleMeetingItem*)meetingItem;

/**
 * This method is used to edit a existed Zoom meeting with specified meeting unique ID..
 *
 * @param meetingItem the user create to edit meeting.
 * @param meetingUniqueID the specified meeting Unique ID user want to edit.
 * @return A ZoomSDKError to tell client whether the meeting has been scheudled successfully or not.
 */
- (ZoomSDKError)editMeeting:(ZoomSDKScheduleMeetingItem*)meetingItem MeetingUniqueID:(long long)meetingUniqueID;

/**
 * This method is used to delete a existed Zoom meeting with specified meeting unique ID.
 *
 * @param meetingUniqueID the specified meeting Unique ID user want to delete.
 * @return A ZoomSDKError to tell client whether the meeting has been deleted successfully or not.
 */
- (ZoomSDKError)deleteMeeting:(long long)meetingUniqueID;

/**
 * This method is used to list all meetings.
 *
 * @return A ZoomSDKError to tell client whether list meeting successfully or not.
 */
- (ZoomSDKError)listMeeting;

/**
 * This method is used to get meeting item info from a existed Zoom meeting with specified meeting unique ID.
 *
 * @param meetingUniqueID the specified meeting Unique ID user want to get.
 * @return A ZoomSDKMeetingItem object with meeeting info if function call successfully.
 */
- (ZoomSDKMeetingItem*)getMeetingItem:(long long)meetingUniqueID;
@end


@protocol ZoomSDKPremeetingServiceDelegate <NSObject>

@optional
/**
 * Designated for Zoom PreMeeting Response.
 *
 * @param error tell client related to this premeeting event whether list meeting success or not.
 * @param meetingList A NSArray contains elements of ZoomSDKMeetingItem.
 *
 */
- (void)onListMeeting:(ZoomSDKPremeetingError)error MeetingList:(NSArray*)meetingList;

/**
 * Designated for Zoom PreMeeting Schedule or edit meeting notify.
 *
 * @param error tell client related to this premeeting event whether schedule or edit meeting successfully or not.
 * @param meetingUniqueID the unique id of the meeting you schedule or edit.
 *
 */
- (void)onScheduleOrEditMeeting:(ZoomSDKPremeetingError)error MeetingUniqueID:(long long)meetingUniqueID;

/**
 * Designated for Zoom PreMeeting delete meeting notify.
 *
 * @param error tell client related to this premeeting event whether delete meeting successfully or not.
 *
 */
- (void)onDeleteMeeting:(ZoomSDKPremeetingError)error;


@end
