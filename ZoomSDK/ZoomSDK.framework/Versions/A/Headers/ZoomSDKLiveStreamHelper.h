//
//  ZoomSDKLiveSteamHelper.h
//  ZoomSDK
//
//  Created by TOTTI on 10/07/2018.
//  Copyright © 2018 TOTTI. All rights reserved.
//

#import "ZoomSDKErrors.h"

@interface ZoomSDKLiveStreamItem : NSObject
{
    NSString* _streamURL;
    NSString* _streamURLDesc;
}
-(NSString*)getLiveStreamURL;
-(NSString*)getLiveStreamURLDescription;
@end

@protocol ZoomSDKLiveStreamHelperDelegate <NSObject>

-(void)onLiveStreamStatusChange:(LiveStreamStatus)status;

@end

@interface ZoomSDKLiveStreamHelper : NSObject
{
    id<ZoomSDKLiveStreamHelperDelegate> _delegate;
}
@property(nonatomic, assign)id<ZoomSDKLiveStreamHelperDelegate> delegate;
/**
 * @brief This method is used to check if user has priviledge to use live stream.
 * @return ZoomSDKError enum, ZoomSDKError_Success means function call successful, others will return failed reason.
 */

- (ZoomSDKError)canStartLiveStream;

/**
 * @brief This method is used to get supported live stream item user can start.
 * @return A NSArray contains ZoomSDKLiveStreamItem object, or return nil when failed.
 */

-(NSArray*)getSupportLiveStreamItem;

/**
 * @brief This method is used to start a live stream
 * @param item, the specific ZoomSDKLiveStreamItem object u can get from the above interface
 * @return ZoomSDKError enum, ZoomSDKError_Success means function call successful, others will return failed reason.
 */

-(ZoomSDKError)startLiveStream:(ZoomSDKLiveStreamItem*)item;

/**
 * @brief This method is used to start a live stream use the URL user defined.
 * @param streamURL, the specific stream url of live stream
 * @param StreamKey, the specific stream key of live stream
 * @param broadcastURL, the specific broadcast url of live stream
 * @return ZoomSDKError enum, ZoomSDKError_Success means function call successful, others will return failed reason.
 */
-(ZoomSDKError)startLiveStreamByURL:(NSString*)streamURL StreamKey:(NSString*)key BroadcastURL:(NSString*)broadcastURL;

/**
 * @brief This method is used to stop a live stream.
 * @return ZoomSDKError enum, ZoomSDKError_Success means function call successful, others will return failed reason.
 */

-(ZoomSDKError)stopLiveStream;

/**
 * @brief This method is used to get current live stream status.
 * @return LiveStreamStatus enum,  LiveStreamStatus_InProgress means successful, others will tell the failed reason.
 */

-(LiveStreamStatus)getLiveStreamStatus;

@end
