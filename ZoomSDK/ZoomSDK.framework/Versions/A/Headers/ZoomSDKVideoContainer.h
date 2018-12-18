//
//  ZoomSDKVideoContainer.h
//  ZoomSDK
//
//  Created by Totti on 25/12/2017.
//  Copyright © 2017 TOTTI. All rights reserved.
//  [Used for Customized UI]
#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

@class  ZoomSDKVideoContainer;
@interface ZoomSDKVideoElement : NSObject
{
    VideoRenderElementType _elementType;
    VideoRenderDataType    _dataType;
    unsigned int           _userid;
    NSView*                _videoView;
    NSRect                 _viewFrame;
}

@property(nonatomic, assign)unsigned int userid;
@property(nonatomic, assign)NSView*  videoView;
/**
 * @brief create video element object for each user
 * @param rect: video view frame contained in this objcet u want to set
 */
- (id)initWithFrame:(NSRect)rect;
/**
 * @brief show video or not,
 * @param show: set YES to show video, set NO to hide the view
 */
- (ZoomSDKError)showVideo:(BOOL)show;
/**
 * @brief get view element type enum: preview/active/normal
 */
- (VideoRenderElementType)getElementType;
/**
 * @brief get view data type enum: avatar/video
 */
- (VideoRenderDataType)getDataType;
/**
 * @brief get NSView object in this element
 */
- (NSView*)getVideoView;
/**
 * @brief resize video view depends on your requirement
 * @param frame: video view frame contained in this objcet u want to show
 */
- (ZoomSDKError)resize:(NSRect)frame;
@end

@interface ZoomSDKPreViewVideoElement : ZoomSDKVideoElement
/**
 * @brief show preview video or not,
 * @param start: set YES to start preview, set NO to stop the preview
 */
-(ZoomSDKError)startPreview:(BOOL)start;
@end


@interface ZoomSDKActiveVideoElement : ZoomSDKVideoElement
/**
 * @brief show active video or not,
 * @param start: set YES to start active video view, set NO to stop.
 */
-(ZoomSDKError)startActiveView:(BOOL)start;
@end

@interface ZoomSDKNormalVideoElement : ZoomSDKVideoElement
/**
 * @brief subscribe this video or not
 * @param subscribe: set YES to show avatar or video view, set NO to show a black view.
 */
-(ZoomSDKError)subscribeVideo:(BOOL)subscribe;
@end

@protocol ZoomSDKVideoContainerDelegate <NSObject>
/**
 * @brief callback if any user id changed in this video container
 * @param element: element of the changed user.
 * @param userid: userid of the changed user.
 */
-(void)onRenderUserChanged:(ZoomSDKVideoElement*)element User:(unsigned int)userid;

/**
 * @brief callback if any data of user changed in this video container
 * @param element: element of the changed user.
 * @param type: current data type of this changed user.
 */
-(void)onRenderDataTypeChanged:(ZoomSDKVideoElement*)element DataType:(VideoRenderDataType)type;
@end

@interface ZoomSDKVideoContainer : NSObject
{
    id<ZoomSDKVideoContainerDelegate> _delegate;
    NSMutableArray*                          _elementArray;
}
@property(nonatomic,assign) id<ZoomSDKVideoContainerDelegate> delegate;
/**
 * @brief create a video element in this video container
 * @param element: element u want to create.
 */
-(ZoomSDKError)createVideoElement:(ZoomSDKVideoElement**)element;
/**
 * @brief destroy a existed video element in this video container
 * @param element: element u want to destroy.
 */
-(ZoomSDKError)cleanVideoElement:(ZoomSDKVideoElement*)element;
/**
 * @brief return a array contains ZoomSDKVideoElement objects.
 */
-(NSArray*)getVideoElementList;
@end

