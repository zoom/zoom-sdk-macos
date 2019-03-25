//
//  ZMHMenuWindow.h
//  zChatUI
//
//  Created by Huxley Yang on 2018/1/24.
//  Copyright © 2018年 Zipow. All rights reserved.
//

#import "ZMPureWindow.h"
#import "ZMBase.h"

@class ZMHMenu, ZMHMenuItem, ZMHMenuListView;
@interface ZMHMenuWindow : NSPanel
{
    BOOL _loaded;
    ZMHMenu *_menu;
    ZMHMenuItem * _representedItem;
}

@property (assign, nonatomic) ZMHMenuWindow *subMenuWindow;
@property (retain) ZMHMenuListView *menuListView;
@property (retain, readonly) ZMHMenuItem * representedItem;
@property NSRectCorner preferredAnchorConner;

- (instancetype)initWithMenu:(ZMHMenu *)menu representedItem:(ZMHMenuItem *)item;
- (BOOL)isDescendantOf:(ZMHMenuWindow *)window;

- (void)show;
- (void)showInScreen:(NSScreen *)screen;
- (void)close;

- (BOOL)mouseOnSelfOrDescendantWindows;

- (void)performShowSubWindowWithItem:(ZMHMenuItem *)menuItem;

//- (void)noteViewCliked:(NSView *)view;//

@end
