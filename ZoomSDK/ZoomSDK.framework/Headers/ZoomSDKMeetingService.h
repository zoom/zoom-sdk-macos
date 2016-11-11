//
//  ZoomSDKMeetingService.h
//  ZoomSDK
//
//  Created by TOTTI on 7/18/16.
//  Copyright (c) 2016 Zoom Video Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"
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
}
- (unsigned int)getUserID;
- (ZoomSDKAudioStatus)getStatus;
@end


@interface ZoomSDKUserInfo :NSObject
{
    unsigned int _userID;
}
- (NSString*)getUserName;
- (NSString*)getEmail;
- (unsigned int)getUserID;
- (BOOL)isHost;
- (BOOL)isVideoOn;
- (BOOL)isAudioMuted;

@end

@interface ZoomSDKMeetingConfiguration :NSObject
{
    //app ID for share
    CGDirectDisplayID  _displayAppID;
    //monitor ID for share
    CGDirectDisplayID  _monitorID;
    //floatVideo position
    NSPoint            _floatVideoPoint;
    //sharing ToolBar Visible
    BOOL               _shareToolBarVisible;
    // main toolbar visible
    BOOL               _mainToolBarVisible;
    //main video position
    NSPoint            _mainVideoPoint;
    //waiting for host window visible
    BOOL               _jbhWindowVisible;
    //mute on entry
    BOOL               _enableMuteOnEntry;
    //play chime or not
    BOOL               _enableChime;
    //direct share desktop or not
    BOOL               _isDirectShareDesktop;
    
    
}
@property(nonatomic, assign)CGDirectDisplayID displayAppID;
@property(nonatomic, assign)CGDirectDisplayID monitorID;
@property(nonatomic, assign)NSPoint floatVideoPoint;
@property(nonatomic, assign)NSPoint mainVideoPoint;
@property(nonatomic, assign)BOOL shareToolBarVisible;
@property(nonatomic, assign)BOOL jbhWindowVisible;
@property(nonatomic, assign)BOOL enableMuteOnEntry;
@property(nonatomic, assign)BOOL isDirectShareDesktop;
@property(nonatomic, assign)BOOL enableChime;
@property(nonatomic, assign)BOOL mainToolBarVisible;
- (void)reset;

@end

@interface ZoomSDKAnnotationController :NSObject

- (ZoomSDKError)setTool:(AnnotationToolType)type;
- (ZoomSDKError)clear:(AnnotationClearType)type;
- (ZoomSDKError)setColor:(float)red Green:(float)green Black:(float)black;
- (ZoomSDKError)setLineWidth:(long)lineWidth;
- (ZoomSDKError)undo;
- (ZoomSDKError)redo;

@end

@interface ZoomSDKMeetingUIController :NSObject

//normal
- (ZoomSDKError)showMeetingComponent:(MeetingComponent)component window:(NSWindow**)window show:(BOOL)show InPanel:(BOOL)inPanel frame:(NSRect)componentFrame;
//main video
- (ZoomSDKError)enterFullScreen:(BOOL)fullScreen firstMonitor:(BOOL)firstView DualMonitor:(BOOL)secondView;
- (ZoomSDKError)switchToVideoWallView;
- (ZoomSDKError)switchToActiveSpeakerView;
//share video
- (ZoomSDKError)moveFloatVideoWindow:(NSPoint)position;
- (ZoomSDKError)minimizeShareFloatVideoWindow:(BOOL)bMin;
- (ZoomSDKError)switchFloatVideoToActiveSpeakerMode;
- (ZoomSDKError)switchFloatVideoToGalleryMode;

@end

@protocol ZoomSDKMeetingServiceDelegate;

/**
 * ZoomSDKMeetingService is an implementation for client to start/join Zoom Meetings.
 * This meeting service assumes there is only one concurrent operation at a time. This means
 * that at any given time, only one API call will be in progress.
 */
@interface ZoomSDKMeetingService : NSObject
{
    id<ZoomSDKMeetingServiceDelegate> _delegate;
    ZoomSDKAnnotationController* _annotationController;
    ZoomSDKMeetingUIController* _meetingUIController;
    ZoomSDKMeetingConfiguration* _meetingConfiguration;
    NSArray*             _participantsArray;

}
/**
 * The object that acts as the delegate of the receiving meeting events.
 */
@property (assign, nonatomic) id<ZoomSDKMeetingServiceDelegate> delegate;

/**
 * This method is used to start a Zoom meeting with meeting number.
 * @param userType The userType depends on what the client account is.
 * userId\userToken\username is for API user.
 * @param userId The userId received as a result client user account from Zoom site.
 * @param userToken The userToken received as a result client user account from Zoom site.
 * @param username The username will be used as display name in the Zoom meeting.
 * @param meetingNumber The meetingNumber may be generated from a scheduled meeting or a Personal Meeting ID, if u want to start a instant meeting, set meetingNumber to nil.
 * @param directShare set YES will start share desktop directly when meeting started.
 * @param displayID set the display ID of the app you want share.
 * @return A ZoomSDKError to tell client whether the meeting started or not.
 */
- (ZoomSDKError)startMeeting:(ZoomSDKUserType)userType userID:(NSString*)userId userToken:(NSString*)userToken displayName:(NSString*)username meetingNumber:(NSString*)meetingNumber isDirectShare:(BOOL)directShare sharedApp:(CGDirectDisplayID)displayID;
/**
 * This method is used to join a Zoom meeting.
 * @param userType The userType depends on what the client account is.
 * toke4enfrocelogin\participantId is for the API user.
 * @param toke4enfrocelogin if join a meeting that need login, should set this param.
 * @param participantId set this ID you want in report.
 * @param meetingNumber The meetingNumber used to join the meeting.
 * @param username The username will be used as display name in the Zoom meeting.
 * @param pwd, The meeting password which used to join the meeting, if there does not exist meeting password, just set pwd to nil or @"".
 * @param directShare set YES will start share desktop directly when meeting started.
 * @param displayID set the display ID of the app you want share.
 * @return A ZoomSDKError to tell client whether can join the meeting or not.
 */
- (ZoomSDKError)joinMeeting:(ZoomSDKUserType)userType toke4enfrocelogin:(NSString*)toke4enfrocelogin participantId:(NSString*)participantId meetingNumber:(NSString*)meetingNumber displayName:(NSString*)username password:(NSString*)pwd isDirectShare:(BOOL)directShare sharedApp:(CGDirectDisplayID)displayID;

/**
 * This method is used to tell the client whether the meeting is ongoing or not.
 *
 * @return A ZoomSDKMeetingStatus to tell client the meeting state currently.
 */
- (ZoomSDKMeetingStatus)getMeetingStatus;

/**
 * This method is used to end/leave an ongoing meeting.
 *
 * @param cmd, leave meeting by the command type.
 */
- (void)leaveMeetingWithCmd:(LeaveMeetingCmd)cmd;

/**
 * This method is used to modify an ongoing meeting.
 *
 * @param cmd, modify the meeting with different command.
 * @param userID, user can modify the himself, set 0, only host can modify other participants,set the userID of the participant to be modified.
 
 * @return A ZoomSDKError to tell client whether modify meeting successful or not.
 */
- (ZoomSDKError)actionMeetingWithCmd:(ActionMeetingCmd)cmd userID:(unsigned int)userID;


- (ZoomSDKError)getCurrentRemoteController:(unsigned int*)userID;

/**
 * This method is used to send a chat message.
 *
 * @param content, message content u want to send.
 * @param userID, userID of the user u want to send chat to.
 * @return A ZoomSDKError to tell client whether send message successful or not.
 */
- (ZoomSDKError)sendChat:(NSString*)content toUser:(unsigned int)userID;

/**
 * This method is used to start recording.
 *
 * @param startTimestamp, start recording timestamp.
 * @param filePath, the path u want to save recording file.
 * @return A ZoomSDKError to tell client whether start recording successful or not.
 */
- (ZoomSDKError)startRecording:(time_t*)startTimestamp saveFilePath:(NSString*)filePath;
/**
 * This method is used to stop recording.
 *
 * @param stopTimestamp, stop recording timestamp.
 * @return A ZoomSDKError to tell client whether stop recording successful or not.
 */
- (ZoomSDKError)stopRecording:(time_t*)stopTimestamp;

/**
 * This method is used to start share application.
 *
 * @param shareAppWindow, the app window u want to share.
 * @return A ZoomSDKError to tell client whether start app share successful or not.
 */
- (ZoomSDKError)startAppShare:(CGWindowID)windowID displayID:(CGDirectDisplayID)displayID;
/**
 * This method is used to select one monitor to share screen.
 *
 * @param monitorID, the indentity of the monitor u want to share.
 * @return A ZoomSDKError to tell client whether start monitor share successful or not.
 */
- (ZoomSDKError)startMonitorShare:(CGDirectDisplayID)monitorID;

/**
 * This method is used to start annotation.
 *
 * @param position, the position of annotation first show.
 * @return A ZoomSDKError to tell client whether start annotation share successful or not.
 */
- (ZoomSDKError)startAnnotation:(NSPoint)position;

/**
 * This method is used to stop annotation.
 *
 * @return A ZoomSDKError to tell client whether stop annotation share successful or not.
 */
- (ZoomSDKError)stopAnnotation;

/**
 * This method is used to hide or show no video user on video wall view.
 *
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)hideOrShowNoVideoUserOnVideoWall:(BOOL)hide;


/**
 * This method is used to get participant list.
 *
 * @return An array contains participant id.
 */
- (NSArray*)getParticipantsList;

/**
 * This method is used to get main meeting UI controller.
 *
 * @return A meeting UI controller interface when function call successful, or return nil when failed.
 */
- (ZoomSDKMeetingUIController*)getMeetingUIController;

/**
 * This method is used to get user info by the selecetd user.
 *
 * @param userID, userID of the selected user.
 * @return A user info interface when function call successful, or return nil when failed.
 */
- (ZoomSDKUserInfo*)getUserByUserID:(unsigned int)userID;

/**
 * This method is used to get annotation controller.
 *
 * @return A annotataion controller interface when function call successful, or return nil when failed.
 */
- (ZoomSDKAnnotationController*)getAnnotationController;

/**
 * This method is used to get meeting configuration.
 *
 * @return A meeting configuration when function call successful, or return nil when failed.
 */
- (ZoomSDKMeetingConfiguration*)getMeetingConfiguration;

/**
 * This method is used to get meeting property.
 * @param command, user command to get differnt property.
 * @return A meeting configuration when function call successful, or return nil when failed.
 */

- (NSString*)getMeetingProperty:(MeetingPropertyCmd)command;

/**
 * This method is used to get meeting Connection Quality.
 *
 * @return A enum that discribe the Connection Quality when function call successful.
 */

- (ZoomSDKConnectionQuality)getConnectionQuality;

- (ZoomSDKError)enableMuteOnEntry:(BOOL)bEnable;

- (ZoomSDKError)enablePlayChimeWhenEnterOrExit:(BOOL)bEnable;

@end


@protocol ZoomSDKMeetingServiceDelegate <NSObject>

@optional

/**
 * Designated for Zoom Meeting State Change notify.
 *
 * @param state tell client meeting state change.
 *
 */
- (void)onMeetingStatusChange:(ZoomSDKMeetingStatus)state meetingError:(ZoomSDKMeetingError)error;

/**
 * Designated for Zoom Meeting User Audio status Change notify.
 *
 * @param userAudioStatusArray a array contains ZoomSDKUserAudioStauts elements tell client audio stauts change of each user.
 *
 */
- (void)onUserAudioStatusChange:(NSArray*)userAudioStatusArray;

/**
 * Designated for Zoom Meeting User receive chat message notify.
 *
 * @param chatInfo tell client the info of the chat message info user received.
 *
 */
- (void)onChatMessageNotification:(ZoomSDKChatInfo*)chatInfo;

/**
 * Designated for Zoom Meeting User notify that meeting record has convorted to mp4 successfully or not.
 *
 * @param success tell client the conversion finish successfully or not .
 * @param recordPath tell client the mp4 file path.
 *
 */
- (void)onRecord2MP4Done:(BOOL)success Path:(NSString*)recordPath;

/**
 * Designated for Zoom Meeting User notify the process percentage when meeting record convert to mp4 file.
 *
 * @param percentage tell client the process record convert to mp4 .
 *
 */
- (void)onRecord2MP4Progressing:(int)percentage;

/**
 * Designated for Zoom Meeting notify record status.
 *
 * @param status tell client record status.
 *
 */
- (void)onRecordStatus:(ZoomSDKRecordingStatus)status;

/**
 * Designated for Zoom Meeting new user join notify.
 *
 * @param array tell client the joined user array.
 *
 */
- (void)onUserJoin:(NSArray*)array;

/**
 * Designated for Zoom Meeting user left notify.
 *
 * @param array tell client the left user array.
 *
 */
- (void)onUserLeft:(NSArray*)array;

/**
 * Designated for Zoom Meeting notify the remote control status.
 * @param status the remote controll user's status.
 * @param userID the remote controll user's identity.
 *
 */
- (void)onRemoteControlStatus:(ZoomSDKRemoteControlStatus)status User:(unsigned int)userID;

/**
 * Designated for Zoom Meeting notify the sharing status.
 * @param status the sharing user's status.
 * @param userID the sharing user's identity.
 *
 */
- (void)onSharingStatus:(ZoomSDKShareStatus)status User:(unsigned int)userID;
@end


