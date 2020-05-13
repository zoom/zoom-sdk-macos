//
//  ZMSDKRestAPILogin.h
//  ZoomSDKSample
//
//  Created by TOTTI on 2018/11/20.
//  Copyright © 2018 zoom.us. All rights reserved.
//

#import <Foundation/Foundation.h>
@class ZMSDKLoginWindowController;
@interface ZMSDKRestAPILogin : NSObject
{
    ZMSDKLoginWindowController* _loginWindowCtrl;
}
@property(nonatomic, assign, readwrite)ZMSDKLoginWindowController* loginWindowCtrl;
-(id)initWithWindowController:(ZMSDKLoginWindowController*)loginWindowController;
-(NSString*)getAccessToken:(NSString*)key Secret:(NSString*)secret ExpiredTime:(NSString*)expiredTime;
-(NSString*)getToken:(NSString*)accessToken UserID:(NSString*)userid;
-(NSString*)getZAK:(NSString*)accessToken UserID:(NSString*)userid;
-(void)loginRestApiWithUserID:(NSString*)userID;
@end
