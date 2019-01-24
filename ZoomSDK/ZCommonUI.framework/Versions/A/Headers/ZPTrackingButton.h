//
//  ZPTrackingButton.h
//  SaasBeeUILib
//
//  Created by zoom on 13-2-25.
//  Copyright (c) 2013年 zoom. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ZPTrackingButton : NSButton
{
    BOOL    _hovered;
    NSTrackingArea* _trackingArea;
    NSString*   _customTooltip;
}

@property(nonatomic, assign) BOOL hovered;
@property(nonatomic, retain) NSTrackingArea* trackingArea;
@property(nonatomic, retain) NSString* customTooltip;
- (NSRect)getRectInScreen;
- (void)cleanUp;
@end
