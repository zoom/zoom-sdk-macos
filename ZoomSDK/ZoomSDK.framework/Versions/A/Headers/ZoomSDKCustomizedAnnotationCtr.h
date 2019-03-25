//
//  ZoomSDKCustomizedAnnotationCtr.h
//  ZoomSDK
//
//  Created by TOTTI on 2018/6/15.
//  Copyright © 2018 Zoom Video Communications,Inc. All rights reserved.
//  [Used for Customized UI]
#import "ZoomSDKErrors.h"

@class ZoomSDKShareElement;

typedef struct{
    float red;
    float green;
    float blue;
}Color;

@protocol ZoomSDKCustomizedAnnotationDelegate <NSObject>
/**
 * @brief Callback of that annotation tools change.
 * @param tool Specify the tool to annotate.
 */
- (void) onAnnotationToolChanged:(AnnotationToolType)tool;
@end

@interface ZoomSDKCustomizedAnnotation : NSObject
{
    ZoomSDKShareElement* _shareElement;
    id<ZoomSDKCustomizedAnnotationDelegate> _delegate;
}
@property(nonatomic, assign)id<ZoomSDKCustomizedAnnotationDelegate> delegate;
/**
 * @brief Query if it is able to clear annotations.
 * @param clearType Specify the ways to clear annotations.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)canClear:(AnnotationClearType)clearType;
/**
 * @brief Clear annotations.
 * @param clearType Specify the way to clear annotations.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)clear:(AnnotationClearType)clearType;
/**
 * @brief Set annotation tools.
 * @param toolType Specify the tool type to clear annotations.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)setTool:(AnnotationToolType)toolType;
/**
 * @brief Get the current annotation tool type.
 * @param toolType The type of annotation tools.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)getCurrentTool:(AnnotationToolType*)toolType;
/**
 * @brief Set the colors of annotation tools.
 * @param color The structural object of Color.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)setColor:(Color)color;
/**
 * @brief Get the color of the current annotation tools.
 * @param color The pointer to the object of color.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)getCurrentColor:(Color*)color;
/**
 * @brief Set the line width of annotation tools.
 * @param lineWidth Specify the line width to annotate.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)setLineWidth:(long)lineWidth;
/**
 * @brief Get the line width of the current annotation tool.
 * @param lineWidth The pointer to the object of long.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)getCurrentLineWidth:(long*)lineWidth;
/**
 * @brief Undo the last annotation.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)undo;
/**
 * @brief Redo the annotation having been deleted. 
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)redo;
/**
 * @brief Determine if it is enabled to save the snapshot.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)canSaveSnapshot;
/**
 * @brief Save the snapshot in the specified path.
 * @param snapShotName Name of the snapshot.  
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)saveSnapshot:(NSString*)snapShotName;

@end

@protocol ZoomSDKCustomizedAnnotationCtrlDelegate <NSObject>
/**
 * @brief Notification of clearing up annotations in the meeting.
 * @param annotation The object of ZoomSDKCustomizedAnnotation.
 */
- (void)onAnnotationCleanUp:(ZoomSDKCustomizedAnnotation*)annotation;
/**
 * @brief Notify annotation status changes.
 * @param element The pointer to ZoomSDKShareElement.
 * @param status Annotation status.
 */
- (void)onAnnotationStatusChanged:(ZoomSDKShareElement*)element Status:(AnnotationStatus)status;
@end


@interface ZoomSDKCustomizedAnnotationCtr : NSObject
{
    id<ZoomSDKCustomizedAnnotationCtrlDelegate> _delegate;
}
@property(nonatomic, assign) id<ZoomSDKCustomizedAnnotationCtrlDelegate> delegate;

/**
 * @brief Create custom annotation.
 * @param annotation Specify the annotation that you want to create.
 * @param element The pointer to ZoomSDKShareElement.						  
 * @return If the function succeeds, it will return ZoomSDKError_Success, otherwise failed.
 */  
-(ZoomSDKError)createCustomizedAnnotation:(ZoomSDKCustomizedAnnotation**)annotation ShareElement:(ZoomSDKShareElement*)element;
/**
 * @brief Destroy custom annotations.
 * @param annotation Specify the annotation that you want to destroy.
 * @return If the function succeeds, it will return ZoomSDKError_Success, otherwise failed.
 */
-(ZoomSDKError)cleanCustomizedAnnatation:(ZoomSDKCustomizedAnnotation*)annotation;
@end
