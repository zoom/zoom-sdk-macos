//
//  ZoomSDKAuthService.h
//  ZoomSDK
//
//  Created by TOTTI on 7/18/16.
//  Copyright (c) 2016 Zoom Video Communications, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ZoomSDKErrors.h"

@interface ZoomSDKAccountInfo : NSObject
{
    NSString*   _displayName;
}
- (NSString*) getDisplayName;
@end

@protocol ZoomSDKAuthDelegate;
/**
 * This class provides support for authorizing Zoom SDK.
 *
 * The Authorization Code Grant requires HTTP request to allow the user to authenticate with Zoom SDK and Authorize your
 * application. Upon successful authorization, the ZoomSDKAuthDelegate will give ZoomSDKAuthError_Success to user by method onZoomSDKAuthReturn.
 *
 * **Note**: Before using Zoom SDK, the client should authorize the Zoom SDK at first. or the function in Zoom
 *   SDK cannot work correctly.
 */
@interface ZoomSDKAuthService : NSObject
{
    BOOL _isAuthorized;
    BOOL _isLogin;
    id<ZoomSDKAuthDelegate> _delegate;
    
}
@property (assign, nonatomic) id<ZoomSDKAuthDelegate> delegate;


/**
 * Designated authorizing Zoom SDK.
 * @param key: your client key, also known as API key.
 * @param secret: your client secret. DO NOT publish this secret.
 * If the client key or secret is empty, user will get error:ZoomSDKError_InvalidPrameter directly.
* @return ZoomSDKError the function call synchronously and a callback in delegate onZoomSDKAuthReturn asynchronously.
 */
- (ZoomSDKError)sdkAuth:(NSString*)key appSecret:(NSString*)secret;

/**
 * @return A BOOL indicating whether the zoom sdk auth may be valid.
 */
- (BOOL)isAuthorized;

/**
 * Designated login Zoom.
 * @param userName: your user name for login.
 * @param password: your password related to your user name.
 * @param rememberMe: set YES if you want to login automatically next time or NO for not.
 * @return ZoomSDKError the function call synchronously and a callback onZoomSDKLogin in delegate asynchronously.
 */
- (ZoomSDKError)login:(NSString*)userName Password:(NSString*)password RememberMe:(BOOL)rememberMe;

/**
 * Designated Zoom user logout.
 * @return ZoomSDKError the function call synchronously and a callback onZoomSDKLogout in delegate asynchronously.
 */
- (ZoomSDKError)logout;

/**
 * Designated get Zoom login account info.
 * @return ZoomSDKAccountInfo object the function call successfully synchronously.
 */
- (ZoomSDKAccountInfo*)getAccountInfo;

@end

/**
 * ZoomSDKAuthDelegate
 * An Auth Service will issue the following value when the authorization state changes:
 *
 * - ZoomSDKAuthError_Success: Zoom SDK authorizs successfully.
 * - ZoomSDKAuthError_KeyOrSecretWrong: the client key or secret for SDK Auth is wrong.
 * - ZoomSDKAuthError_AccountNotSupport: this client account cannot support Zoom SDK.
 * - ZoomSDKAuthError_AccountNotEnableSDK: this client account does not enable Zoom SDK.
 */
@protocol ZoomSDKAuthDelegate <NSObject>

@required
/**
 * Designated for Zoom SDK Auth response.
 *
 * @param returnValue tell user when the auth state changed.
 *
 */
- (void)onZoomSDKAuthReturn:(ZoomSDKAuthError)returnValue;

@optional
/**
 * Designated for Zoom SDK Login response.
 *
 * @param loginStatus tell user when the login status.
 *
 */
- (void)onZoomSDKLogin:(ZoomSDKLoginStatus)loginStatus failReason:(NSString*)reason;
/**
 * Designated for Zoom SDK Logout response.
 *
 *
 */
- (void)onZoomSDKLogout;


@end
