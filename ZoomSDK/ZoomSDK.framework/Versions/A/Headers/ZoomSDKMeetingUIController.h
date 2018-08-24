//
//  ZoomSDKMeetingUIController.h
//  ZoomSDK
//
//  Created by TOTTI on 8/4/17.
//  Copyright © 2017 TOTTI. All rights reserved.
//
@protocol ZoomSDKMeetingUIControllerDelegate <NSObject>
/**
 * @brief Designated for Zoom Meeting notify the Invite button be clicked by user if u set showInviteButtonInToolbar =YES;
 * @param show, default show origin zoom invite window, if u don't want original action, u can set *show = N0, and do UI action yourself in this callback
 */
- (void)onToolbarInviteButtonClick:(BOOL*)show;

/**
 * @brief Designated for Zoom Meeting notify participants click leave meeting.
 * @param participantID mean participant ID of the participant who leave meeting.
 */
- (void)onClickLeaveMeeting:(unsigned int)participantID;

/**
 * @brief Designated for Zoom Meeting notify participants click start share button.
 */
- (void)onToolbarShareButtonClick;

/**
 * @brief Designated for Zoom Meeting notify need to show leave meeting window.
 */
-(void)onNeedShowLeaveMeetingWindow;

/**
 * @brief Designated for Zoom Meeting notify participant button clicked.
 */
-(void)onParticipantButtonClicked;

/**
 * @brief Designated for Zoom Meeting notify custom live stream menu button clicked.
 */
-(void)onCustomLiveButtonClicked;
@end

@interface ZoomSDKMeetingUIController :NSObject
{
    id<ZoomSDKMeetingUIControllerDelegate> _delegate;
}
@property(nonatomic, assign) id<ZoomSDKMeetingUIControllerDelegate> delegate;

//normal
- (ZoomSDKError)showMeetingComponent:(MeetingComponent)component window:(NSWindow**)window show:(BOOL)show InPanel:(BOOL)inPanel frame:(NSRect)componentFrame;

//main video
- (ZoomSDKError)enterFullScreen:(BOOL)fullScreen firstMonitor:(BOOL)firstView DualMonitor:(BOOL)secondView;
- (ZoomSDKError)switchToVideoWallView;
- (ZoomSDKError)switchToActiveSpeakerView;
- (BOOL)isInMiniVideoMode;

/*
* @brief This method is used to switch ui between mini video and mini bar, only works when isInMiniVideoMode = YES
* @return A ZoomSDKError to tell client whether function call successfully or not.
*/
- (ZoomSDKError)switchMiniVideoModeUI;

//share video
//- (ZoomSDKError)moveFloatVideoWindow:(NSPoint)position;
- (ZoomSDKError)minimizeShareFloatVideoWindow:(BOOL)bMin;
- (ZoomSDKError)switchFloatVideoToActiveSpeakerMode;
- (ZoomSDKError)switchFloatVideoToGalleryMode;

/**
 * @brief This method is used to hide or show no video user on video wall view.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)hideOrShowNoVideoUserOnVideoWall:(BOOL)hide;

/**
 * @brief This method is used to get wall view page info of meeting.
 * @param currentPageNum, current page number of the wall view.
 * @param totalPageNum, total page number of wall view.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)getWallViewPageInfo:(int*)currentPageNum TotalPageNum:(int*)totalPageNum;

/**
 * @brief This method is used to show previous or next page for video wall view of meeting.
 * @param nextPage, set YES to show next page of video wall view, set NO to show previous page.
 * @return A ZoomSDKError to tell client whether function call successfully or not.
 */
- (ZoomSDKError)showPreOrNextPageWallView:(BOOL)nextPage;

@end
