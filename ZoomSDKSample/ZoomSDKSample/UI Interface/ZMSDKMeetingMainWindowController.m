//
//  ZMSDKMeetingMainWindowController.m
//  ZoomSDKSample
//
//  Created by derain on 2018/12/3.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import "ZMSDKMeetingMainWindowController.h"
#import "ZMSDKMainWindowController.h"
#import "ZMSDKConfUIMgr.h"
#import "ZMSDKThumbnailVideoItemView.h"
#import "ZMSDKHCTableItemView.h"
#import "ZMSDKPTImageButton.h"
#import "ZMSDKHCPanelistsView.h"
#import "ZMSDKButton.h"
#import "ZMSDKShareSelectWindow.h"
#import "ZMSDKThumbnailView.h"


const int DEFAULT_Toolbar_Button_height = 60;
const int DEFAULT_Thumbnail_View_Width = 320;


@implementation ZMSDKBackgroundView
@synthesize borderColor = _borderColor;
@synthesize backGroundColor = _backGroundColor;
@synthesize radius = _radius;
@synthesize borderWidth = _borderWidth;

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.radius = 4;
    }
    return self;
}
- (id)initWithCoder:(NSCoder *)decoder{
    self = [super initWithCoder:decoder];
    if(self)
    {
        self.borderColor = self.backGroundColor;
        self.radius = 0;
        self.borderWidth = 0;
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect:dirtyRect];
    if(self.borderColor)
    {
        NSBezierPath* path = [NSBezierPath bezierPathWithRoundedRect:NSMakeRect(_borderWidth, _borderWidth, NSWidth(self.frame)-2*_borderWidth, NSHeight(self.frame)-2*_borderWidth) xRadius:_radius yRadius:_radius];
        [path setLineWidth:_borderWidth];
        [self.borderColor set];
        [path stroke];
        [self.backGroundColor set];
        [path fill];
    }
}
- (void)dealloc
{
    [_backGroundColor release];
    _backGroundColor = nil;
    [_borderColor release];
    _borderColor = nil;
    [super dealloc];
}
@end


@interface ZMSDKMeetingMainWindowController ()
{
    ZoomSDKActiveVideoElement* _activeUserVideo;
    ZMSDKShareSelectWindow*    _shareSelectWindowCtr;
}
@end

@implementation ZMSDKMeetingMainWindowController
@synthesize meetingMainWindow = _meetingMainWindow;
@synthesize audioStatus = _audioStatus;
@synthesize mySelfUserInfo = _mySelfUserInfo;

- (void)windowDidLoad {
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}
-(void)awakeFromNib
{
    [self initUI];
}
- (void)uninitNotification
{
    NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
    [nc removeObserver:self];
}
-(void)initNotification
{
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowWillClose:) name:NSWindowWillCloseNotification object:nil];
}

- (id)init
{
    //self = [super initWithWindow:self.meetingMainWindow];
    self = [super init];
    if(self)
    {
        _meetingMainWindow = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 1100, 700) styleMask:NSWindowStyleMaskTitled|NSWindowStyleMaskClosable backing:NSBackingStoreBuffered defer:NO];
        self.window = _meetingMainWindow;
        
        [self initNotification];
        [self initUI];
        return self;
    }
    return nil;
}
- (void)cleanUp
{
    if(_activeUserVideo)
    {
        ZoomSDKVideoContainer* videoContainer = [[[ZoomSDK sharedSDK] getMeetingService] getVideoContainer];
        [videoContainer cleanVideoElement:_activeUserVideo];
        NSView* videoview = [_activeUserVideo getVideoView];
        [videoview removeFromSuperview];
        [_activeUserVideo release];
        _activeUserVideo = nil;
    }
    if(_shareSelectWindowCtr)
    {
        [_shareSelectWindowCtr.window close];
        [_shareSelectWindowCtr release];
        _shareSelectWindowCtr = nil;
    }
    [self resetInfo];
    [self.window close];
    [self uninitNotification];
}
- (void)dealloc
{
    [self cleanUp];
    [super dealloc];
}
- (void)initUI
{
    [self.window setFrame:NSMakeRect(0, 0, 1100, 700) display:YES];
    [self.window center];
    [self.window setTitle:@"Zoom Meeting"];
    [self.window setBackgroundColor:[NSColor blackColor]];
    
    _panelistUserView = [[ZMSDKHCPanelistsView alloc] initWithFrame:NSMakeRect(self.window.contentView.frame.origin.x, DEFAULT_Toolbar_Button_height + 5, 220, self.window.contentView.frame.size.height - DEFAULT_Toolbar_Button_height - 20)];
    
    _thumbnailView = [[ZMSDKThumbnailView alloc] initWithFrame:NSMakeRect(self.window.contentView.frame.size.width - DEFAULT_Thumbnail_View_Width, self.window.contentView.frame.origin.y, DEFAULT_Thumbnail_View_Width, self.window.contentView.frame.size.height)];
    [_thumbnailView setMeetingMainWindowController:self];
    
    [self initActiveVideoUserView];
    [self initButtons];
}
- (void)initButtons
{
    
    float xpos = self.window.contentView.frame.size.width/2;
    float xposLeft = xpos;
    float xposRight = xpos;
    float yPos = 2;
    float width = 80;
    float height = DEFAULT_Toolbar_Button_height;
    float margin = 30;
    ZMSDKButton* theButton = nil;
    
    ZMSDKBackgroundView* toolbarBackgroundView = [[ZMSDKBackgroundView alloc] initWithFrame:NSMakeRect(0, 0, self.window.frame.size.width, height + yPos)];
    toolbarBackgroundView.backGroundColor = [NSColor blackColor];
    [self.window.contentView addSubview:toolbarBackgroundView];
    [toolbarBackgroundView release];
    
    NSColor* titleColor = [NSColor whiteColor];
    NSColor* pressTitleColor = [NSColor colorWithRed:145/225 green:145/225 blue:145/225 alpha:0];
    NSColor* pressBgColor = nil;
    NSColor* hoverBgColor = nil;
    hoverBgColor = [NSColor colorWithCalibratedWhite:0 alpha:0.5];
    pressBgColor = [NSColor colorWithCalibratedWhite:0 alpha:0.5];
    NSFont* theFont = [NSFont systemFontOfSize:12];
    
    theButton = [[ZMSDKButton alloc] initWithFrame:NSMakeRect(xpos, yPos, width, height)];
    theButton.tag = BUTTON_TAG_AUDIO;
    theButton.title = @"Audio";
    theButton.titleColor = titleColor;
    theButton.disableTitleColor = [NSColor grayColor];
    theButton.pressTitleColor = pressTitleColor;
    theButton.font = theFont;
    theButton.hoverBackgroundColor = hoverBgColor;
    theButton.pressBackgoundColor = pressBgColor;
    theButton.imagePosition = NSImageAbove;
    theButton.image = [NSImage imageNamed:@"toolbar_mute_voip_normal"];
    theButton.pressImage = [NSImage imageNamed:@"toolbar_mute_voip_press"];
    
    theButton.autoresizingMask = NSViewMaxXMargin;
    [theButton setTarget:self];
    [theButton setAction:@selector(onAudioButtonClicked:)];
    [theButton setHidden:YES];
    [self.window.contentView addSubview:theButton];
    [theButton release];
    theButton = nil;
    xposLeft -= width + margin;
    
    theButton = [[ZMSDKButton alloc] initWithFrame:NSMakeRect(xposLeft, yPos, width, height)];
    theButton.tag = BUTTON_TAG_VIDEO;
    theButton.title = @"Video";
    theButton.image = [NSImage imageNamed:@"toolbar_stop_video_normal"];
    theButton.pressImage = [NSImage imageNamed:@"toolbar_stop_video_press"];
    theButton.titleColor = titleColor;
    theButton.pressTitleColor = pressTitleColor;
    theButton.font = theFont;
    theButton.hoverBackgroundColor = hoverBgColor;
    theButton.pressBackgoundColor = pressBgColor;
    theButton.imagePosition = NSImageAbove;
    theButton.autoresizingMask = NSViewMaxXMargin;
    [theButton setTarget:self];
    [theButton setAction:@selector(onVideoButtonClicked:)];
    [theButton setHidden:YES];
    [self.window.contentView addSubview:theButton];
    [theButton release];
    theButton = nil;
    xposLeft -= width + margin;
    
    theButton = [[ZMSDKButton alloc] initWithFrame:NSMakeRect(xposLeft, yPos, width, height)];
    theButton.tag = BUTTON_TAG_ThUMBNAIL_VIEW;
    theButton.title = @"Thumbnail Video";
    theButton.image = [NSImage imageNamed:@"toolbar_participant_normal"];
    theButton.pressImage = [NSImage imageNamed:@"toolbar_participant_press"];
    theButton.titleColor = titleColor;
    theButton.pressTitleColor = pressTitleColor;
    theButton.font = theFont;
    theButton.hoverBackgroundColor = hoverBgColor;
    theButton.pressBackgoundColor = pressBgColor;
    theButton.imagePosition = NSImageAbove;
    theButton.autoresizingMask = NSViewMinXMargin|NSViewMaxXMargin;
    [theButton setTarget:self];
    [theButton setAction:@selector(onThumbnailButtonClicked:)];
    [theButton setHidden:YES];
    [self.window.contentView addSubview:theButton];
    [theButton release];
    theButton = nil;
    xposLeft -= width + margin;
    
    theButton = [[ZMSDKButton alloc] initWithFrame:NSMakeRect(xposLeft, yPos, width, height)];
    theButton.tag = BUTTON_TAG_PARTICIPANT;
    theButton.title = @"Participants";
    theButton.image = [NSImage imageNamed:@"toolbar_participant_normal"];
    theButton.pressImage = [NSImage imageNamed:@"toolbar_participant_press"];
    
    theButton.titleColor = titleColor;
    theButton.pressTitleColor = pressTitleColor;
    theButton.font = theFont;
    theButton.hoverBackgroundColor = hoverBgColor;
    theButton.pressBackgoundColor = pressBgColor;
    theButton.imagePosition = NSImageAbove;
    theButton.autoresizingMask = NSViewMinXMargin|NSViewMaxXMargin;
    [theButton setTarget:self];
    [theButton setAction:@selector(onParticipantButtonClicked:)];
    [theButton setHidden:YES];
    [self.window.contentView addSubview:theButton];
    [theButton release];
    theButton = nil;
    xposRight += width + margin;
    
    theButton = [[ZMSDKButton alloc] initWithFrame:NSMakeRect(xposRight, yPos, width, height)];
    theButton.tag = BUTTON_TAG_SHARE;
    theButton.title = @"Share";
    theButton.image = [NSImage imageNamed:@"toolbar_share_normal"];
    theButton.pressImage = [NSImage imageNamed:@"toolbar_share_press"];
    theButton.titleColor = titleColor;
    theButton.pressTitleColor = pressTitleColor;
    theButton.font = theFont;
    theButton.hoverBackgroundColor = hoverBgColor;
    theButton.pressBackgoundColor = pressBgColor;
    theButton.imagePosition = NSImageAbove;
    theButton.autoresizingMask = NSViewMinXMargin|NSViewMaxXMargin;
    [theButton setTarget:self];
    [theButton setAction:@selector(onShareButtonClicked:)];
    [theButton setHidden:YES];
    [self.window.contentView addSubview:theButton];
    [theButton release];
    theButton = nil;
    xposRight += width + margin;
    
    theButton = [[ZMSDKButton alloc] initWithFrame:NSMakeRect(xposRight, yPos, width, height)];
    theButton.tag = BUTTON_TAG_STOP_SHARE;
    theButton.title = @"Stop Share";
    theButton.image = [NSImage imageNamed:@"toolbar_share_stop"];
    theButton.pressImage = [NSImage imageNamed:@"toolbar_share_stop"];
    theButton.titleColor = titleColor;
    theButton.pressTitleColor = pressTitleColor;
    theButton.font = theFont;
    theButton.hoverBackgroundColor = hoverBgColor;
    theButton.pressBackgoundColor = pressBgColor;
    theButton.imagePosition = NSImageAbove;
    theButton.autoresizingMask = NSViewMinXMargin|NSViewMaxXMargin;
    [theButton setTarget:self];
    [theButton setAction:@selector(onStopShareButtonClicked:)];
    [theButton setHidden:YES];
    [self.window.contentView addSubview:theButton];
    [theButton release];
    theButton = nil;
}

- (void)onThumbnailButtonClicked:(id)sender
{
    NSRect rect = self.window.contentView.frame;
    if(!_thumbnailView.superview)
    {
        [self.window.contentView addSubview:_thumbnailView];
        [_thumbnailView setHidden:NO];
        [_activeUserVideo resize:NSMakeRect(rect.origin.x, rect.origin.y + DEFAULT_Toolbar_Button_height + 2, self.window.frame.size.width - DEFAULT_Thumbnail_View_Width - 10, rect.size.height - DEFAULT_Toolbar_Button_height - 2)];
        return;
    }
    if([_thumbnailView isHidden])
    {
        [_thumbnailView setHidden:NO];
        [_activeUserVideo resize:NSMakeRect(rect.origin.x, rect.origin.y + DEFAULT_Toolbar_Button_height + 2, self.window.frame.size.width - DEFAULT_Thumbnail_View_Width - 10, rect.size.height - DEFAULT_Toolbar_Button_height - 2)];
    }
    else
    {
        [_thumbnailView setHidden:YES];
        [_activeUserVideo resize:NSMakeRect(rect.origin.x, rect.origin.y + DEFAULT_Toolbar_Button_height + 2, self.window.frame.size.width, rect.size.height - DEFAULT_Toolbar_Button_height - 2)];
    }
}
- (void)onParticipantButtonClicked:(id)sender
{
    if(!_panelistUserView.superview)
    {
        [self.window.contentView addSubview:_panelistUserView];
        [_panelistUserView setHidden:NO];
        return;
    }

    if([_panelistUserView isHidden])
        [_panelistUserView setHidden:NO];
    else
        [_panelistUserView setHidden:YES];
}
- (void)onShareButtonClicked:(id)sender
{
    if(_shareSelectWindowCtr)
    {
        [_shareSelectWindowCtr.window makeKeyAndOrderFront:nil];
        [_shareSelectWindowCtr.window center];
    }
}
- (void)onAudioButtonClicked:(id)sender
{
    switch (_audioStatus)
    {
        case Audio_Status_UnMuted:
        {
            ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
            [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_MuteAudio userID:0 onScreen:ScreenType_First];
        }
            break;
        case Audio_Status_Muted:
        {
            ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
            [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_UnMuteAudio userID:0 onScreen:ScreenType_First];
        }
            break;
        case Audio_Status_No:
        {
            ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
            [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_JoinVoip userID:0 onScreen:ScreenType_First];
        }
            break;
        default:
            break;
    }
}
- (void)onVideoButtonClicked:(id)sender
{
    ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
   
    if(self.mySelfUserInfo)
    {
        if([self.mySelfUserInfo isVideoOn])
        {
            [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_MuteVideo userID:0 onScreen:ScreenType_First];
        }
        else
        {
            [[meetingService getMeetingActionController] actionMeetingWithCmd:ActionMeetingCmd_UnMuteVideo userID:0 onScreen:ScreenType_First];
        }
    }
}
- (void)onStopShareButtonClicked:(id)sender
{
    ZoomSDKError ret = ZoomSDKError_Failed;
    if(_shareSelectWindowCtr)
       ret = [_shareSelectWindowCtr stopShare];
    ZMSDKButton* stopShareButton = [self.window.contentView viewWithTag:BUTTON_TAG_STOP_SHARE];
    if(stopShareButton && ret == ZoomSDKError_Success)
       [stopShareButton setHidden:YES];
}

-(void)updateInMeetingUI
{
    ZMSDKButton* theButton = [self.window.contentView viewWithTag:BUTTON_TAG_AUDIO];
    if(theButton)
       [theButton setHidden:NO];
    theButton = [self.window.contentView viewWithTag:BUTTON_TAG_VIDEO];
    if(theButton)
       [theButton setHidden:NO];
    theButton = [self.window.contentView viewWithTag:BUTTON_TAG_PARTICIPANT];
    if(theButton)
        [theButton setHidden:NO];
    theButton = [self.window.contentView viewWithTag:BUTTON_TAG_SHARE];
    if(theButton)
        [theButton setHidden:NO];
    theButton = [self.window.contentView viewWithTag:BUTTON_TAG_ThUMBNAIL_VIEW];
    if(theButton)
        [theButton setHidden:NO];
    
    if(!_shareSelectWindowCtr)
    {
        _shareSelectWindowCtr = [[ZMSDKShareSelectWindow alloc] init];
        [_shareSelectWindowCtr setMeetingMainWindowController:self];
    }
}
- (void)showSelf
{
    [self relayoutWindowPosition];
    [self.window makeKeyAndOrderFront:nil];
}
- (void)relayoutWindowPosition
{
    [self.window setLevel:NSPopUpMenuWindowLevel];
    [self.window center];
}
- (void)updateUI
{
    return;
}

- (void)onUserJoin:(unsigned int)userID
{
    [_panelistUserView onUserJoin:userID];
    [_thumbnailView onUserJoin:userID];
}
- (void)initActiveVideoUserView
{
    if(!_activeUserVideo)
    {
        _activeUserVideo = [[ZoomSDKActiveVideoElement alloc] initWithFrame:NSMakeRect(self.window.contentView.frame.origin.x, self.window.contentView.frame.origin.y + DEFAULT_Toolbar_Button_height + 2, self.window.frame.size.width, self.window.contentView.frame.size.height - DEFAULT_Toolbar_Button_height - 2)];//NSMakeRect(self.window.contentView.frame.origin.x,self.window.contentView.frame.origin.y,self.window.contentView.frame.size.width - DEFAULT_Thumbnail_View_Width,self.window.contentView.frame.size.height)];
        ZoomSDKVideoContainer* videoContainer = [[[ZoomSDK sharedSDK] getMeetingService] getVideoContainer];
        [videoContainer createVideoElement:&_activeUserVideo];
        [self.window.contentView addSubview:[_activeUserVideo getVideoView]];
    }
}

- (void)onUserleft:(unsigned int)userID
{
    [_panelistUserView onUserleft:userID];
    [_thumbnailView onUserleft:userID];
}

- (void)windowWillClose:(NSNotification *)notification
{
    NSWindow *window = notification.object;
    if(window == self.window && [self.window isVisible])
    {
        ZoomSDKMeetingService* meetingService = [[ZoomSDK sharedSDK] getMeetingService];
        [meetingService leaveMeetingWithCmd:(LeaveMeetingCmd_End)];
    }
}

- (void)resetInfo
{
    [_thumbnailView resetInfo];
    if(_activeUserVideo)
    {
        ZoomSDKVideoContainer* videoContainer = [[[ZoomSDK sharedSDK] getMeetingService] getVideoContainer];
        [videoContainer cleanVideoElement:_activeUserVideo];
        NSView* videoview = [_activeUserVideo getVideoView];
        [videoview removeFromSuperview];
        [_activeUserVideo release];
        _activeUserVideo = nil;
    }
    [_panelistUserView resetInfo];
    [_panelistUserView setHidden:YES];
    
    ZMSDKButton* theButton = [self.window.contentView viewWithTag:BUTTON_TAG_AUDIO];
    if(theButton)
        [theButton setHidden:YES];
    theButton = [self.window.contentView viewWithTag:BUTTON_TAG_VIDEO];
    if(theButton)
        [theButton setHidden:YES];
    theButton = [self.window.contentView viewWithTag:BUTTON_TAG_PARTICIPANT];
    if(theButton)
        [theButton setHidden:YES];
    theButton = [self.window.contentView viewWithTag:BUTTON_TAG_SHARE];
    if(theButton)
        [theButton setHidden:YES];
    theButton = [self.window.contentView viewWithTag:BUTTON_TAG_ThUMBNAIL_VIEW];
    if(theButton)
        [theButton setHidden:YES];
}
- (void)onSelfShareStart
{
    ZMSDKButton* stopShareButton = [self.window.contentView viewWithTag:BUTTON_TAG_STOP_SHARE];
    if(stopShareButton)
        [stopShareButton setHidden:NO];
}
- (void)onSelfShareStop
{
    ZMSDKButton* stopShareButton = [self.window.contentView viewWithTag:BUTTON_TAG_STOP_SHARE];
    if(stopShareButton)
        [stopShareButton setHidden:YES];
}
- (void)onUserAudioStatusChange:(NSArray*)userAudioStatusArray
{
    if(!userAudioStatusArray || userAudioStatusArray.count == 0)
        return;
    ZoomSDKUserInfo* mySelf = nil;
    for (ZoomSDKUserAudioStauts* key in userAudioStatusArray)
    {
        unsigned int userID = [key getUserID];
        ZoomSDKUserInfo* userInfo = [[[[ZoomSDK sharedSDK] getMeetingService] getMeetingActionController] getUserByUserID:userID];
        if([userInfo isMySelf])
        {
            mySelf = userInfo;
        }
        
        ZoomSDKAudioStatus status = [key getStatus];
        ZoomSDKAudioType type = [key getType];
        if(mySelf)
        {
            switch (status)
            {
                case ZoomSDKAudioStatus_Muted:
                case ZoomSDKAudioStatus_MutedByHost:
                case ZoomSDKAudioStatus_MutedAllByHost:
                {
                    _audioStatus = Audio_Status_Muted;
                }
                    break;
                case ZoomSDKAudioStatus_UnMuted:
                case ZoomSDKAudioStatus_UnMutedByHost:
                case ZoomSDKAudioStatus_UnMutedAllByHost:
                {
                    _audioStatus = Audio_Status_UnMuted;
                }
                    break;
                case ZoomSDKAudioStatus_None:
                {
                    _audioStatus = Audio_Status_No;
                }
                    break;
                default:
                    break;
            }
            [self updateToolbarAudioButtonsWithAudioType:type audioStatus:status];
        }
        NSLog(@"userID %d status:%d type:%d", userID, status, type);
    }
}
- (void)onUserVideoStatusChange:(BOOL)videoOn UserID:(unsigned int)userID
{
    [_thumbnailView onUserVideoStatusChange:videoOn UserID:userID];
    ZMSDKButton* theButton = [self.window.contentView viewWithTag:BUTTON_TAG_VIDEO];
    if(theButton && !theButton.isHidden)
    {
        ZoomSDKUserInfo* userInfo = [[[[ZoomSDK sharedSDK] getMeetingService] getMeetingActionController] getUserByUserID:userID];
        if([userInfo isMySelf])
        {
            self.mySelfUserInfo = userInfo;
            if(!videoOn)
            {
                theButton.title = @"Start Video";
                theButton.image = [NSImage imageNamed:@"toolbar_start_video_normal"];
                theButton.pressImage = [NSImage imageNamed:@"toolbar_start_video_press"];
            }
            else
            {
                theButton.title = @"Stop Video";
                theButton.image = [NSImage imageNamed:@"toolbar_stop_video_normal"];
                theButton.pressImage = [NSImage imageNamed:@"toolbar_stop_video_press"];
            }
        }
    }
}
- (void)updateToolbarAudioButtonsWithAudioType:(ZoomSDKAudioType)audioType audioStatus:(ZoomSDKAudioStatus)status
{
    ZMSDKButton* theButton = [self.window.contentView viewWithTag:BUTTON_TAG_AUDIO];
    if(theButton && !theButton.isHidden)
    {
        if(audioType == ZoomSDKAudioType_Voip)
        {
            switch (status) {
                case ZoomSDKAudioStatus_Muted:
                case ZoomSDKAudioStatus_MutedByHost:
                case ZoomSDKAudioStatus_MutedAllByHost:
                {
                    theButton.image = [NSImage imageNamed:@"toolbar_unmute_voip_normal"];
                    theButton.pressImage = [NSImage imageNamed:@"toolbar_unmute_voip_press"];
                    theButton.title = @"Unmute";
                }
                    break;
                case ZoomSDKAudioStatus_UnMuted:
                case ZoomSDKAudioStatus_UnMutedByHost:
                case ZoomSDKAudioStatus_UnMutedAllByHost:
                {
                    theButton.image = [NSImage imageNamed:@"toolbar_mute_voip_normal"];
                    theButton.pressImage = [NSImage imageNamed:@"toolbar_mute_voip_press"];
                    theButton.title = @"Mute";
                }
                    break;
                default:
                    break;
            }
        }
        else if(audioType == ZoomSDKAudioType_Phone)
        {
            switch (status) {
                case ZoomSDKAudioStatus_Muted:
                case ZoomSDKAudioStatus_MutedByHost:
                case ZoomSDKAudioStatus_MutedAllByHost:
                {
                    theButton.image = [NSImage imageNamed:@"toolbar_unmute_tele_normal"];
                    theButton.pressImage = [NSImage imageNamed:@"toolbar_unmute_tele_press"];
                    theButton.title = @"Unmute";
                }
                    break;
                case ZoomSDKAudioStatus_UnMuted:
                case ZoomSDKAudioStatus_UnMutedByHost:
                case ZoomSDKAudioStatus_UnMutedAllByHost:
                {
                    theButton.image = [NSImage imageNamed:@"toolbar_mute_tele_normal"];
                    theButton.pressImage = [NSImage imageNamed:@"toolbar_mute_tele_press"];
                    theButton.title = @"Mute";
                }
                    break;
                default:
                    break;
            }
        }
        else
        {
            theButton.image = [NSImage imageNamed:@"toolbar_noaudio_normal"];
            theButton.pressImage = [NSImage imageNamed:@"toolbar_noaudio_highlight"];
            theButton.title = @"Join Audio";
        }
    }
}

@end

