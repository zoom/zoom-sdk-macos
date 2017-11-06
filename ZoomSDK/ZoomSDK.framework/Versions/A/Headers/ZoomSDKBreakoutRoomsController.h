//
//  ZoomSDKBreakoutRoomsInfo.h
//  ZoomSDK
//
//  Created by TOTTI on 8/4/17.
//  Copyright © 2017 TOTTI. All rights reserved.
//

@interface ZoomSDKBreakoutRoomsInfo : NSObject
{
    NSString* _bID;
    NSString* _roomName;
}
-(NSString*)getBID;
-(NSString*)getBreakoutRoomsName;
@end

@protocol ZoomSDKBreakoutRoomsDelegate <NSObject>
- (void)onBreakoutRoomsStarted:(NSString*)bID;
@end

@interface ZoomSDKBreakoutRoomsController:NSObject
{
    id<ZoomSDKBreakoutRoomsDelegate> _delegate;
}
@property (assign, nonatomic) id<ZoomSDKBreakoutRoomsDelegate> delegate;
-(ZoomSDKError)joinBreakoutRoom:(NSString*)bID;
-(ZoomSDKError)leaveBreakoutRoom;
/**
 @note
 input a NSArray, if call ZoomSDKError_Success, infoArray contains ZoomSDKBreakoutRoomsInfo objects.
 */
-(ZoomSDKError)getBreakoutRoomsInfo:(NSMutableArray**)infoArray;
@end


