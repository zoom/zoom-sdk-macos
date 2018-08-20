//
//  ZoomSDKCustomizedAnnotationCtr.h
//  ZoomSDK
//
//  Created by Totti on 2018/6/15.
//  Copyright © 2018 TOTTI. All rights reserved.
//  [Used for Customized UI]
#import "ZoomSDKErrors.h"

@class ZoomSDKShareElement;

typedef struct{
    float red;
    float green;
    float blue;
}Color;

@protocol ZoomSDKCustomizedAnnotationDelegate <NSObject>
- (void) onAnnotationToolChanged:(AnnotationToolType)tool;
@end

@interface ZoomSDKCustomizedAnnotation : NSObject
{
    ZoomSDKShareElement* _shareElement;
    id<ZoomSDKCustomizedAnnotationDelegate> _delegate;
}
@property(nonatomic, assign)id<ZoomSDKCustomizedAnnotationDelegate> delegate;
/**
 * @brief This method is used to check whether can clear annotation
 * @param clearType, the specific clear method u want to clear.
 * @return A ZoomSDKError enum, ZoomSDKError_Success means can clear, others will tell failure reason.
 */
- (ZoomSDKError)canClear:(AnnotationClearType)clearType;
/**
 * @brief This method is used to clear annotation
 * @param clearType, the specific clear method u want to clear.
 * @return A ZoomSDKError enum, ZoomSDKError_Success means clear successfully, others will tell failure reason.
 */
- (ZoomSDKError)clear:(AnnotationClearType)clearType;
/**
 * @brief This method is used to set annotation tool
 * @param toolType, the specific tool type u want to use.
 * @return A ZoomSDKError enum, ZoomSDKError_Success means set tool successfully, others will tell failure reason.
 */
- (ZoomSDKError)setTool:(AnnotationToolType)toolType;
/**
 * @brief This method is used to get current annotation tool type u use
 * @param toolType, a point of AnnotationToolType.
 * @return A ZoomSDKError enum, ZoomSDKError_Success means get tool type successfully, others will tell failure reason.
 */
- (ZoomSDKError)getCurrentTool:(AnnotationToolType*)toolType;
/**
 * @brief This method is used to set annotation color
 * @param red, red color value
 * @param green, green color value
 * @param blue, blue color value
 * @return A ZoomSDKError enum, ZoomSDKError_Success means set color successfully, others will tell failure reason.
 */
- (ZoomSDKError)setColor:(Color)color;
/**
 * @brief This method is used to get current annotation color u use
 * @param toolType, a point of Color.
 * @return A ZoomSDKError enum, ZoomSDKError_Success means get color successfully, others will tell failure reason.
 */
- (ZoomSDKError)getCurrentColor:(Color*)color;
/**
 * @brief This method is used to set annotation line width
 * @param lineWidth, red color value
 * @return A ZoomSDKError enum, ZoomSDKError_Success means set color successfully, others will tell failure reason.
 */
- (ZoomSDKError)setLineWidth:(long)lineWidth;
/**
 * @brief This method is used to get current annotation line width u use
 * @param lineWidth, a point of long.
 * @return A ZoomSDKError enum, ZoomSDKError_Success means get line width successfully, others will tell failure reason.
 */
- (ZoomSDKError)getCurrentLineWidth:(long*)lineWidth;
/**
 * @brief This method is used to recall the behavior u annotate before
 * @return A ZoomSDKError enum, ZoomSDKError_Success means undo successfully, others will tell failure reason.
 */
- (ZoomSDKError)undo;
/**
 * @brief This method is used to do same behavior as u annotate before
 * @return A ZoomSDKError enum, ZoomSDKError_Success means redo successfully, others will tell failure reason.
 */
- (ZoomSDKError)redo;
/**
 * @brief This method is used to know whether user can save snapshot or not
 * @return A ZoomSDKError enum, ZoomSDKError_Success means have ability to save snapshot, others will tell failure reason.
 */
- (ZoomSDKError)canSaveSnapshot;
/**
 * @brief This method is used to save annotation snapshot
 * @return A ZoomSDKError enum, ZoomSDKError_Success means save snapshot successfully, others will tell failure reason.
 */
- (ZoomSDKError)saveSnapshot:(NSString*)snapShotName;

@end

@protocol ZoomSDKCustomizedAnnotationCtrlDelegate <NSObject>
- (void)onAnnotationCleanUp:(ZoomSDKCustomizedAnnotation*)annotation;
- (void)onAnnotationStatusChanged:(ZoomSDKShareElement*)element Status:(AnnotationStatus)status;
@end


@interface ZoomSDKCustomizedAnnotationCtr : NSObject
{
    id<ZoomSDKCustomizedAnnotationCtrlDelegate> _delegate;
}
@property(nonatomic, assign) id<ZoomSDKCustomizedAnnotationCtrlDelegate> delegate;

-(ZoomSDKError)createCustomizedAnnotation:(ZoomSDKCustomizedAnnotation**)annotation ShareElement:(ZoomSDKShareElement*)element;
-(ZoomSDKError)cleanCustomizedAnnatation:(ZoomSDKCustomizedAnnotation*)annotation;
@end
