//
//  ZMSDKMeetingMainWindowController.h
//  ZoomSDKSample
//
//  Created by derain on 2018/12/3.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ZoomSDK.h"

@class ZMSDKMainWindowController;
@class ZMSDKTrackingButton;
@class ZMSDKHCPanelistsView;
@class ZMSDKThumbnailView;

enum MeetiongToolbarButtonTags
{
    BUTTON_TAG_OFFSET = 499,
    BUTTON_TAG_AUDIO,
    BUTTON_TAG_VIDEO,
    BUTTON_TAG_SHARE,
    BUTTON_TAG_PARTICIPANT,
    BUTTON_TAG_STOP_SHARE,
    BUTTON_TAG_ThUMBNAIL_VIEW,
};

typedef enum
{
    Audio_Status_No = 0,
    Audio_Status_Muted,
    Audio_Status_UnMuted,
}SelfAudioStatus;


@interface ZMSDKBackgroundView : NSView
{
    NSColor*    _borderColor;
    NSColor*    _backGroundColor;
    float       _radius;
    NSInteger   _borderWidth;
}
@property (retain) NSColor* borderColor;
@property (retain) NSColor* backGroundColor;
@property (assign) float radius;
@property (assign) NSInteger borderWidth;

@end



@interface ZMSDKMeetingMainWindowController : NSWindowController <NSTableViewDataSource, NSTableViewDelegate>
{
    NSButton*              _manegePanelistButton;
    NSButton*              _manegeShareButton;
    
    NSWindow*              _meetingMainWindow;
    ZMSDKHCPanelistsView*  _panelistUserView;
    ZMSDKThumbnailView*    _thumbnailView;
    SelfAudioStatus        _audioStatus;
    ZoomSDKUserInfo*       _mySelfUserInfo;
}
@property(nonatomic, retain, readwrite)NSWindow* meetingMainWindow;
@property(nonatomic, assign, readwrite)SelfAudioStatus audioStatus;
@property(nonatomic, retain, readwrite)ZoomSDKUserInfo* mySelfUserInfo;

- (void)showSelf;
- (void)relayoutWindowPosition;
- (void)updateUI;

- (void)onUserJoin:(unsigned int)userID;
- (void)onUserleft:(unsigned int)userID;
- (void)onUserVideoStatusChange:(BOOL)videoOn UserID:(unsigned int)userID;
- (void)onUserAudioStatusChange:(NSArray*)userAudioStatusArray;
- (void)resetInfo;
- (void)updateInMeetingUI;
- (void)onSelfShareStart;
- (void)onSelfShareStop;
- (void)cleanUp;
@end

