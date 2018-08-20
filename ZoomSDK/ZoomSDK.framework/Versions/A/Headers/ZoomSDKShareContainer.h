//
//  ZoomSDKShareContainer.h
//  ZoomSDK
//
//  Created by Totti on 2018/6/22.
//  Copyright © 2018 TOTTI. All rights reserved.
//  [Used for Customized UI]
#import "ZoomSDKErrors.h"

@protocol ZoomSDKShareElementDelegate <NSObject>
/**
 * @brief callback if the user u want to watch share has started send share datea
 */
-(void)onShareContentStartReceiving;
/**
 * @brief callback if the shared user change in this element
 * @param userid: current user id of this element who share
 */
-(void)onShareSourceUserIDNotify:(unsigned int)userid;

@end

@interface ZoomSDKShareElement : NSObject
{
    unsigned int         _userId;
    ViewShareMode        _viewMode;
    NSView*              _shareView;
    id<ZoomSDKShareElementDelegate>   _delegate;
    NSRect                            _frame;
}
@property(nonatomic, assign) unsigned int userId;
@property(nonatomic, assign) ViewShareMode viewMode;
@property(nonatomic, assign) NSView*  shareView;
@property(nonatomic, assign) id<ZoomSDKShareElementDelegate> delegate;
/**
 * @brief create a share element
 * @param frame: share view frame owned by this element
 */
- (id)initWithFrame:(NSRect)frame;
/**
 * @brief resize frame of the share view owned by this element
 * @param frame: share view frame u want to set
 */
- (ZoomSDKError)resize:(NSRect)frame;
/**
 * @brief show the share view
 * @param show: set YES to show or NO to hide
 */
- (ZoomSDKError)ShowShareRender:(BOOL)show;
@end

@protocol ZoomSDKShareContainerDelegate <NSObject>
-(void)onShareElementDestroy:(ZoomSDKShareElement*)element;
@end

@interface ZoomSDKShareContainer : NSObject
{
    NSMutableArray*                          _elementArray;
    id<ZoomSDKShareContainerDelegate>        _delegate;
}
@property(nonatomic, assign)id<ZoomSDKShareContainerDelegate>  delegate;
-(ZoomSDKError)createShareElement:(ZoomSDKShareElement**)element;
-(ZoomSDKError)cleanShareElement:(ZoomSDKShareElement*)element;
-(NSArray*)getShareElementArray;
-(ZoomSDKShareElement*)getShareElementByUserID:(unsigned int)userid;

@end
