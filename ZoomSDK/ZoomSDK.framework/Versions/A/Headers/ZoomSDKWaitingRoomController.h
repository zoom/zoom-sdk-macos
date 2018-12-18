//
//  ZoomSDKWaitingRoomController.h
//  ZoomSDK
//
//  Created by TOTTI on 8/4/17.
//  Copyright © 2017 TOTTI. All rights reserved.
//

@class ZoomSDKUserInfo;

@protocol ZoomSDKWaitingRoomDelegate <NSObject>
-(void)onUserJoinWaitingRoom:(unsigned int)userid;
-(void)onUserLeftWaitingRoom:(unsigned int)userid;
@end

@interface ZoomSDKWaitingRoomController : NSObject
{
    id<ZoomSDKWaitingRoomDelegate> _delegate;
}
@property (assign, nonatomic) id<ZoomSDKWaitingRoomDelegate> delegate;
- (BOOL)isSupportWaitingRoom;
- (BOOL)isEnableWaitingRoomOnEntry;
- (ZoomSDKError)enableWaitingRoomOnEntry:(BOOL)enable;
- (NSArray*)getWaitRoomUserList;
- (ZoomSDKUserInfo*)getWaitingRoomUserInfo:(unsigned int)userid;
- (ZoomSDKError)admitToMeeting:(unsigned int)userid;
- (ZoomSDKError)putIntoWaitingRoom:(unsigned int)userid;
@end
