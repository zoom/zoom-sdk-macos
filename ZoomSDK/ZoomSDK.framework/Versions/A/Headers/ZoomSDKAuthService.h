//
//  ZoomSDKAuthService.h
//  ZoomSDK
//
//  Created by TOTTI on 7/18/16.
//  Copyright (c) 2016 Zoom Video Communications, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ZoomSDKErrors.h"
#import "ZoomSDKBuildType.h"

@interface ZoomSDKAccountInfo : NSObject
{
    ZoomSDKUserType _userType;
    NSString*   _displayName;
}
- (NSString*) getDisplayName;
- (ZoomSDKUserType) getSDKUserType;
@end

@protocol ZoomSDKAuthDelegate;
/**
 * @brief This class provides support for authorizing Zoom SDK.
 * The Authorization Code Grant requires HTTP request to allow the user to authenticate with Zoom SDK and Authorize your
 * application. Upon successful authorization, the ZoomSDKAuthDelegate will give ZoomSDKAuthError_Success to user by method onZoomSDKAuthReturn.
 * @note Before using Zoom SDK, the client should authorize the Zoom SDK at first. or the function in Zoom
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
 * @brief Designated authorizing Zoom SDK.
 * @param key: your client key, also known as API key.
 * @param secret: your client secret. DO NOT publish this secret.
 * @note If the client key or secret is empty, user will get error:ZoomSDKError_InvalidPrameter directly.
 * @return ZoomSDKError the function call synchronously and a callback in delegate onZoomSDKAuthReturn asynchronously.
 */
- (ZoomSDKError)sdkAuth:(NSString*)key appSecret:(NSString*)secret;

/**
 * @return A BOOL indicating whether the zoom sdk auth may be valid.
 */
- (BOOL)isAuthorized;

/**
 * @brief Designated login Zoom by email.
 * @param userName: your user name for login.
 * @param password: your password related to your user name.
 * @param rememberMe: set YES if you want to login automatically next time or NO for not.
 * @return ZoomSDKError the function call synchronously and a callback onZoomSDKLogin in delegate asynchronously.
 */
- (ZoomSDKError)login:(NSString*)userName Password:(NSString*)password RememberMe:(BOOL)rememberMe;

/**
 * @brief Designated login Zoom by sso token.
 * @param ssoToken: user sso login token.
 * @return ZoomSDKError the function call synchronously and a callback onZoomSDKLogin in delegate asynchronously.
 */
- (ZoomSDKError)loginSSO:(NSString*)ssoToken;

/**
 * @brief Designated Zoom user logout.
 * @return ZoomSDKError the function call synchronously and a callback onZoomSDKLogout in delegate asynchronously.
 */
- (ZoomSDKError)logout;

/**
 * @brief Designated get Zoom login account info.
 * @return ZoomSDKAccountInfo object the function call successfully synchronously.
 */
- (ZoomSDKAccountInfo*)getAccountInfo;

/**
 * @brief Designated get SDK Identity.
 * @return SDK indentity.
 */
- (NSString*)getSDKIdentity;
@end

/**
 * @brief ZoomSDKAuthDelegate
 * An Auth Service will issue the following value when the authorization state changes:
 * @note
 * - ZoomSDKAuthError_Success: Zoom SDK authorizs successfully.
 * - ZoomSDKAuthError_KeyOrSecretWrong: the client key or secret for SDK Auth is wrong.
 * - ZoomSDKAuthError_AccountNotSupport: this client account cannot support Zoom SDK.
 * - ZoomSDKAuthError_AccountNotEnableSDK: this client account does not enable Zoom SDK.
 */
@protocol ZoomSDKAuthDelegate <NSObject>

@required
/**
 * @brief Designated for Zoom SDK Auth response.
 *
 * @param returnValue tell user when the auth state changed.
 *
 */
#ifdef BUILD_FOR_ELECTRON
- (void)onZoomSDKAuthReturn:(NSNumber*)returnValue;
#else
- (void)onZoomSDKAuthReturn:(ZoomSDKAuthError)returnValue;
#endif

@optional
/**
 * @brief Designated for Zoom SDK Login response.
 * @param loginStatus tell user when the login status.
 *
 */
#ifdef BUILD_FOR_ELECTRON
- (void)onZoomSDKLogin:(NSNumber*)loginStatus failReason:(NSString*)reason;
#else
- (void)onZoomSDKLogin:(ZoomSDKLoginStatus)loginStatus failReason:(NSString*)reason;
#endif
/**
 * @brief Designated for Zoom SDK Logout response.
 */
- (void)onZoomSDKLogout;

/**
 * @brief Designated for Zoom SDK identity expired, logined user will be forced logout.
 */
- (void)onZoomIdentityExpired;

@end
