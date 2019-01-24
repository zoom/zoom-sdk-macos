//
//  ZMSDKPTImageButton.h
//  ZoomSDKSample
//
//  Created by derain on 2018/11/19.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ZMSDKTrackingButton : NSButton
{
    BOOL    _hovered;
    NSTrackingArea* _trackingArea;
}

@property(nonatomic, assign) BOOL hovered;
@property(nonatomic, retain) NSTrackingArea* trackingArea;
- (NSRect)getRectInScreen;
- (void)cleanUp;
@end


@interface ZMSDKPTImageButton : ZMSDKTrackingButton
{
    float               _angle;
    NSColor*            _normalStartColor;
    NSColor*            _normalEndColor;
    NSColor*            _hoverStartColor;
    NSColor*            _hoverEndColor;
    NSColor*            _pressedStartColor;
    NSColor*            _pressedEndColor;
    NSColor*            _disabledStartColor;
    NSColor*            _disabledEndColor;
    
    NSImage *_normalImage;
    NSImage *_highlightImage;
    NSImage *_disabledImage;
    
    NSMutableDictionary *_attributes;
    NSColor *_fontColor;
}
@property (nonatomic, readwrite, assign)float               angle;
@property (nonatomic, readwrite, retain)NSColor*            normalStartColor;
@property (nonatomic, readwrite, retain)NSColor*            normalEndColor;
@property (nonatomic, readwrite, retain)NSColor*            hoverStartColor;
@property (nonatomic, readwrite, retain)NSColor*            hoverEndColor;
@property (nonatomic, readwrite, retain)NSColor*            pressedStartColor;
@property (nonatomic, readwrite, retain)NSColor*            pressedEndColor;
@property (nonatomic, readwrite, retain)NSColor*            disabledStartColor;
@property (nonatomic, readwrite, retain)NSColor*            disabledEndColor;

@property (nonatomic, retain, readwrite) NSImage *normalImage;
@property (nonatomic, retain, readwrite) NSImage *highlightImage;
@property (nonatomic, retain, readwrite) NSImage *disabledImage;
@property (nonatomic, retain, readwrite) NSMutableDictionary *attributes;
@property (nonatomic, retain, readwrite) NSColor *fontColor;

- (void)cleanUp;
- (int)getTitleWidth;

@end
