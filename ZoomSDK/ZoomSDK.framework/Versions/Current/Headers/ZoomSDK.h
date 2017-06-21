//
//  ZoomSDK.h
//  ZoomSDK
//
//  Created by TOTTI on 7/18/16.
//  Copyright (c) 2016 Zoom Video Communications, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

//Zoom SDK Errors
#import <ZoomSDKErrors.h>

//Zoom SDK AuthService
#import <ZoomSDKAuthService.h>

//Zoom SDK MeetingService
#import <ZoomSDKMeetingService.h>

//Zoom SDK SettingsService
#import <ZoomSDKSettingService.h>

//Zoom SDK PremeetingService
#import <ZoomSDKPremeetingService.h>

//Zoom SDK NetworkService
#import <ZoomSDKNetworkService.h>

/**
 * The ZoomSDK class is a class that exposes a Zoom API Rest Client.
 *
 * Access to this class and all other components of the ZoomSDK can be granted by including `<ZoomSDK/ZoomSDK.h>`
 * in your source code.
 *
 * This class provides a class method sharedSDK which provides a preconfigured SDK client,
 * including a ZoomSDKMeetingService.
 *
 */
@interface ZoomSDK : NSObject
{
    NSString               *_zoomDomain;
    ZoomSDKMeetingService  *_meetingService;
    ZoomSDKAuthService     *_authService;
    ZoomSDKSettingService  *_settingService;
    ZoomSDKPremeetingService *_premeetingService;
    ZoomSDKNetworkService    *_networkService;
}

@property (retain, nonatomic) NSString *zoomDomain;

/**
 * Returns the ZoomSDK default SDK client
 *
 * This method is guaranteed to only instantiate one sharedSDK over the lifetime of an app.
 *
 * This client must be configured with your client key and client secret.
 *
 * *Note*: sharedSDK returns a ZoomSDK configured with a ZoomSDKMeetingService.
 *
 * @return a preconfigured SDK client
 */
+ (ZoomSDK*)sharedSDK;
/**
 * Sets the Zoom SDK client domain
 *
 * @param domain A domain which used as start/join zoom meeting
 *
 * *Note*: the domain should not include protocol "https" or "http", the format is just like "zoom.us" or "www.zoom.us".
 */
- (void)setZoomDomain:(NSString*)domain;
/**
 * Returns the ZoomSDK default Auth Service
 *
 * *Note*: Auth Service should be called at first, the Zoom SDK can be used after authorizing successfully.
 *
 * @return a preconfigured Auth Service
 */
- (ZoomSDKAuthService*)getAuthService;

/**
 * Returns the ZoomSDK default Meeting Service
 *
 * @return a preconfigured Meeting Service
 */
- (ZoomSDKMeetingService*)getMeetingService;

/**
 * Returns the ZoomSDK default Meeting Settings
 *
 * @return a object of Settings Service
 */
- (ZoomSDKSettingService*)getSettingService;

/**
 * Returns the ZoomSDK default Premeeting Service
 *
 * @return a object of Settings Service
 */
- (ZoomSDKPremeetingService*)getPremeetingService;

/**
 * Returns the ZoomSDK default Network Service
 *
 * @return a object of Network Service
 */
- (ZoomSDKNetworkService*)getNetworkService;

/**
 * Sets the new prodcut name
 *
 * @param bundlePath: file position of the prodcut customize strings.
 * @param fileName: file name of customize strings.
 *
 */
- (void)setCustomBundlePath:(NSString*)bundlePath fileName:(NSString*)fileName;

/**
 * Returns the ZoomSDK default Version Number
 *
 */
- (NSString*)getSDKVersionNumber;
@end


