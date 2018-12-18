//
//  ZoomSDKMeetingRecordController.h
//  ZoomSDK
//
//  Created by TOTTI on 2018/8/6.
//  Copyright © 2018 TOTTI. All rights reserved.
//
#import "ZoomSDKErrors.h"
typedef enum
{
    RecordingLayoutMode_None = 0,
    RecordingLayoutMode_ActiveVideoOnly = 1,
    RecordingLayoutMode_VideoWall = (1<<1),
    RecordingLayoutMode_VideoShare = (1<<2),
    RecordingLayoutMode_OnlyAudio = (1<<3),
    RecordingLayoutMode_OnlyShare = (1<<4),
}RecordingLayoutMode;

@interface CustomizedRecordingLayoutHelper : NSObject
- (int)getSupportLayoutMode;
- (NSArray*)getValidVideoSource;
- (NSArray*)getValidRecivedShareSource;
- (BOOL)isSendingShareSourceAvailable;
- (BOOL)haveActiveVideoSource;

- (ZoomSDKError)selectRecordingLayoutMode:(RecordingLayoutMode)mode;
- (ZoomSDKError)addVideoSourceToResArray:(unsigned int)userid;
- (ZoomSDKError)selectActiveVideoSource;
- (ZoomSDKError)selectShareSource:(unsigned int)userid;
- (ZoomSDKError)selectSendShareSource;
@end



@protocol ZoomSDKMeetingRecordDelegate <NSObject>

/**
 * @brief  Designated for Zoom Meeting User notify that meeting record has convorted to mp4 successfully or not.
 * @param success tell client the conversion finish successfully or not .
 * @param recordPath tell client the mp4 file path.
 *
 */
- (void)onRecord2MP4Done:(BOOL)success Path:(NSString*)recordPath;

/**
 * @brief  Designated for Zoom Meeting User notify the process percentage when meeting record convert to mp4 file.
 * @param percentage tell client the process record convert to mp4 .
 *
 */
- (void)onRecord2MP4Progressing:(int)percentage;

/**
 * @brief  Designated for Zoom Meeting notify record status.
 * @param status tell client record status.
 *
 */
- (void)onRecordStatus:(ZoomSDKRecordingStatus)status;

/**
 * @brief Designated for Zoom Meeting notify your record privilege change.
 * @param canRec mean your record privilege change or not.
 *
 */
- (void)onRecordPrivilegeChange:(BOOL)canRec;

/**
 * @brief Designated for Zoom Meeting notify your record privilege change.
 * @param canRec mean your record privilege change or not.
 *
 */
- (void)onCustomizedRecordingSourceReceived:(CustomizedRecordingLayoutHelper*)helper;

@end


@interface ZoomSDKMeetingRecordController : NSObject
{
    id<ZoomSDKMeetingRecordDelegate> _delegate;
}
@property(nonatomic, assign)id<ZoomSDKMeetingRecordDelegate> delegate;
/**
 * @brief This method is used to check whether specific user have privilege to start recording or not .
 * @param isCloud, YES means cloud recording, NO means local recording.
 * @param userid, the specific user identity.
 * @return A ZoomSDKError, ZoomSDKError_Success means have, other will tell failed reason.
 */
- (ZoomSDKError)canStartRecording:(BOOL)isCloud User:(unsigned int)userid;

/**
 * @brief This method is used to check whether I have have privilege to allow or disallow other user to start local recording.
 * @return A ZoomSDKError, ZoomSDKError_Success means can, other will tell failed reason.
 */
- (ZoomSDKError)canAllowDisallowRecording;

/**
 * @brief This method is used to start cloud recording.
 * @param start, set YES to start cloud recording, set NO to stop recording.
 * @return A ZoomSDKError, ZoomSDKError_Success means start/stop successfully, other will tell failed reason.
 */
- (ZoomSDKError)startCloudRecording:(BOOL)start;

/**
 * @brief This method is used to start recording.
 * @param startTimestamp, start recording timestamp.
 * @param filePath, the path u want to save recording file.
 * @return A ZoomSDKError to tell client whether start recording successful or not.
 */
- (ZoomSDKError)startRecording:(time_t*)startTimestamp saveFilePath:(NSString*)filePath;

/**
 * @brief This method is used to stop recording.
 * @param stopTimestamp, stop recording timestamp.
 * @return A ZoomSDKError to tell client whether stop recording successful or not.
 */
- (ZoomSDKError)stopRecording:(time_t*)stopTimestamp;

/**
 * @brief This method is used to check whether specific user have local recording feature.
 * @param userid, the specific user identity .
 * @return A ZoomSDKError, ZoomSDKError_Success means have, other will tell failed reason.
 */
- (ZoomSDKError)isSupportLocalRecording:(unsigned int)userid;

/**
 * @brief This method is used to allow specific user to do local recording.
 * @param allow, set YES to allow user do local recording, NO means disallow.
 * @param userid, the specific user identity .
 * @return A ZoomSDKError, ZoomSDKError_Success means allow/disallow successfully, other will tell failed reason.
 */
- (ZoomSDKError)allowLocalRecording:(BOOL)allow User:(unsigned int)userid;

/**
 * @brief This method is used to request customized local recording source notification.
 * @return A ZoomSDKError, ZoomSDKError_Success means u can receive , other will tell failed reason.
 */
- (ZoomSDKError)requestCustomizedLocalRecordingNotification:(BOOL)request;
@end
