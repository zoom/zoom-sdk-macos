//
//  ZMSDKMutipleDelegate.h
//  ZoomSDKSample
//
//  Created by derain on 2018/11/22.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDK.h"

@interface ZMSDKDelegateMgr : NSObject <ZoomSDKAuthDelegate>
{
    NSMutableArray* _authDelegateArray;
}
@property (nonatomic, copy, readwrite) NSMutableArray* authDelegateArray;

- (void)addAuthDelegateListener:(id<ZoomSDKAuthDelegate>)authDelegate;
- (void)removeAuthDelegateListener:(id<ZoomSDKAuthDelegate>)authDelegate;
@end
