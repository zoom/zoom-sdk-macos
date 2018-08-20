//
//  ZoomSDKASController.h
//  ZoomSDK
//
//  Created by TOTTI on 8/4/17.
//  Copyright © 2017 TOTTI. All rights reserved.
//

#import "ZoomSDKErrors.h"
#import "ZoomSDKBuildType.h"
#import "ZoomSDKCustomizedAnnotationCtr.h"
#import "ZoomSDKShareContainer.h"
#import "ZoomSDKRemoteControllerHelper.h"

@interface ZoomSDKAnnotationController :NSObject
- (BOOL)isAnnotationDisable;
- (ZoomSDKError)setTool:(AnnotationToolType)type onScreen:(ScreenType)screen;
- (ZoomSDKError)clear:(AnnotationClearType)type onScreen:(ScreenType)screen;
- (ZoomSDKError)setColor:(float)red Green:(float)green Black:(float)black onScreen:(ScreenType)screen;
- (ZoomSDKError)setLineWidth:(long)lineWidth onScreen:(ScreenType)screen;
- (ZoomSDKError)undo:(ScreenType)screen;
- (ZoomSDKError)redo:(ScreenType)screen;

@end


@interface ZoomSDKShareSource :NSObject
{
    unsigned int _userID;
    BOOL  _isShowInFirstScreen;
    BOOL  _isShowInSecondScreen;
    BOOL  _canBeRemoteControl;
    
}
- (BOOL)isShowInFirstScreen;
- (BOOL)isShowInSecondScreen;
- (BOOL)canBeRemoteControl;
- (unsigned int)getUserID;
@end

@interface ZoomSDKShareInfo: NSObject
{
    ZoomSDKShareContentType  _shareType;
    CGWindowID    _windowID; //Only usefully to _shareType = ZoomSDKShareContentType_AS or ZoomSDKShareContentType_WB
    CGDirectDisplayID  _displayID; //Only useful to _shareType = ZoomSDKShareContentType_DS;
}
- (ZoomSDKShareContentType) getShareType;
/**
 * @brief Designated for get share window ID when meeting is sharing whiteboard or application.
 * @param windowID: A pointer of CGWindowID, if function call successfully it will return the shared app window id.
 */
- (ZoomSDKError)getWindowID:(CGWindowID*)windowID;
 /**
 * @brief Designated for get monitor display ID when meeting is sharing destop.
 * @param displayID: A pointer of CGDirectDisplayID, if function call successfully it will return the shared monitor display ID.
 */
- (ZoomSDKError)getDisplayID:(CGDirectDisplayID*)displayID;

@end

@interface ZoomSDKSplitScreenInfo : NSObject
{
    BOOL _isInSplitScreenMode;
    BOOL _isSupportSplitScreenMode;
}

-(BOOL)isInSplitScreenMode;
-(BOOL)isSupportSplitScreenMode;
@end

@protocol ZoomSDKASControllerDelegate <NSObject>
@optional
/**
 * @brief Designated for Zoom Meeting notify the sharing status.
 * @param status the sharing user's status.
 * @param userID the sharing user's identity.
 *
 */
- (void)onSharingStatus:(ZoomSDKShareStatus)status User:(unsigned int)userID;

/**
 * @brief Designated for Zoom Meeting notify the share is locked by host or not
 * @param shareLocked YES mean share is locked by host, NO means not locked.
 */
- (void)onShareStatusLocked:(BOOL)shareLocked;

/**
 * @brief Designated for Zoom Meeting notify the share content is changed by new share start.
 * @param shareInfo include share content type and window ID or monitor ID.
 */
- (void)onShareContentChanged:(ZoomSDKShareInfo*)shareInfo;
@end

@interface ZoomSDKASController : NSObject
{
    id<ZoomSDKASControllerDelegate> _delegate;
    ZoomSDKShareContainer* _shareContainer;
    ZoomSDKAnnotationController* _annotationController;
    ZoomSDKCustomizedAnnotationCtr* _customizedAnnotationCtr;
    ZoomSDKRemoteControllerHelper*  _remoteControllerHelper;
}
@property(nonatomic, assign)id<ZoomSDKASControllerDelegate> delegate;
/**
 * @brief This method is used to start share application.
 * @param shareAppWindow, the app window u want to share.
 * @return A ZoomSDKError to tell client whether start app share successful or not.
 */
- (ZoomSDKError)startAppShare:(CGWindowID)windowID;

/**
 * @brief This method is used to select one monitor to share screen.
 * @param monitorID, the indentity of the monitor u want to share.
 * @return A ZoomSDKError to tell client whether start monitor share successful or not.
 */
- (ZoomSDKError)startMonitorShare:(CGDirectDisplayID)monitorID;

/**
 * @brief This method is used to stop current share.
 * @return A ZoomSDKError to tell client whether stop current share successful or not.
 */
- (ZoomSDKError)stopShare;

/**
 * @brief This method is used to get userid list user who is sharing.
 * @return A NSArray contain the userid of all users who are sharing.
 */
- (NSArray*)getShareSourceList;

/**
 * @brief This method is used to get sharesource info by the specific userid.
 * @param userID, userID of the selected user.
 * @return ZoomSDKShareSource object when function call successful, or return nil when failed.
 */
- (ZoomSDKShareSource*)getShareSourcebyUserId:(unsigned int)userID;

/**
 * @brief This method is used to get sharesource info by the specific userid.
 * @param userID, userID of the sharing user u want to view.
 * @param screen, select a screen u want to view in if u support dual mode.
 * @return ZoomSDKShareSource object when function call successful, or return nil when failed.
 */
- (ZoomSDKError)viewShare:(unsigned int) userID onScreen:(ScreenType)screen;

/**
 * @brief This method is used to judge whether user self can start share or not.
 * @return A BOOL to tell client can share or not.
 */
- (BOOL)canStartShare;

/**
 * @brief This method is used to judge whether this meeting's share is locked by host or not.
 * @return A BOOL to tell client meeting's share is locked or not.
 */
- (BOOL)isShareLocked;

/**
 * @brief This method is used to get annotation controller.
 * @return A annotataion controller interface when function call successful, or return nil when failed.
 */
- (ZoomSDKAnnotationController*)getAnnotationController;

/**
 * @brief This method is used to get customized annotation controller.
 * @return A customized annotataion controller interface when function call successful, or return nil when failed.
 */
- (ZoomSDKCustomizedAnnotationCtr*)getCustomizedAnnotationCtr;

/**
 * @brief This method is used to get customized share render container.
 * @return A ZoomSDKShareContainer object when function call successful, or return nil when failed.
 */
- (ZoomSDKShareContainer*)getShareContainer;

/**
 * @brief This method is used to get remote controller helper.
 * @return A ZoomSDKRemoteControllerHelper object when function call successful, or return nil when failed.
 */
- (ZoomSDKRemoteControllerHelper*)getRemoteControllerHelper;

/**
 * @brief This method is used to start annotation.
 * @param position, the position of annotation first show.
 * @param screen, which screen u want to start annotation.
 * @return A ZoomSDKError to tell client whether start annotation share successful or not.
 */
- (ZoomSDKError)startAnnotation:(NSPoint)position onScreen:(ScreenType)screen;

/**
 * @brief This method is used to stop annotation.
 * @param screen, which screen u want to stop annotation.
 * @return A ZoomSDKError to tell client whether stop annotation share successful or not.
 */
- (ZoomSDKError)stopAnnotation:(ScreenType)screen;

/**
 * @brief This method is used to get remote controller userid
 * @param userID, input a unsigned it pointer.
 * @return A ZoomSDKError to tell client whether send message successful or not, if success, the userID value will be assigned to the remote controller userid.
 */
- (ZoomSDKError)getCurrentRemoteController:(unsigned int*)userID;

/**
 * @brief This method is used to get screen split mode info when watch somebody's share
 */

- (ZoomSDKSplitScreenInfo*)getCurrentSplitScreenModeInfo;

/**
 * @brief This method is used to switch to split screen mode.
 * @param switchTo, YES means use side by side mode, NO means not to switch.
 */
-(ZoomSDKError)switchSplitScreenMode:(BOOL)switchTo;

/**
 * @brief This method is used to clean up ascontroller
 */
- (void)cleanUp;
@end


