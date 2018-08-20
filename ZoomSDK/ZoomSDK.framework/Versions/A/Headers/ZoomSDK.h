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

//Zoom SDK Customized Video UI
#import <ZoomSDKVideoContainer.h>

//Zoom SDK Customized Share UI
#import <ZoomSDKShareContainer.h>
/**
 * The ZoomSDK class is a class that exposes a Zoom API Rest Client.
 *
 * Access to this class and all other components of the ZoomSDK can be granted by including `<ZoomSDK/ZoomSDK.h>`
 * in your source code.
 * This class provides a class method sharedSDK which provides a preconfigured SDK client
 */
@interface ZoomSDK : NSObject
{
    NSString               *_zoomDomain;
    ZoomSDKMeetingService  *_meetingService;
    ZoomSDKAuthService     *_authService;
    ZoomSDKSettingService  *_settingService;
    ZoomSDKPremeetingService *_premeetingService;
    ZoomSDKNetworkService    *_networkService;
    NSMutableArray           *_languageArray;
    BOOL                     _needCustomizedUI;
}

@property (retain, nonatomic) NSString *zoomDomain;
@property (assign, nonatomic) BOOL needCustomizedUI;
/**
 * @brief This method is guaranteed to only instantiate one sharedSDK over the lifetime of an app.
 * @note This client must be configured with your client key and client secret.
 * @return a preconfigured ZoomSDK default client
 */
+ (ZoomSDK*)sharedSDK;

- (void)initSDK:(BOOL)customizedFlag;
/**
 * @brief Sets the Zoom SDK client domain
 * @note the domain should not include protocol "https" or "http", the format is just like "zoom.us" or "www.zoom.us".
 * @param domain: A domain which used as start/join zoom meeting
 */
- (void)setZoomDomain:(NSString*)domain;
/**
 * @brief  get the ZoomSDK default Auth Service
 * @note Auth Service should be called at first, the Zoom SDK can be used after authorizing successfully.
 * @return a preconfigured Auth Service
 */
- (ZoomSDKAuthService*)getAuthService;

/**
 * @brief get the ZoomSDK default Meeting Service
 * @return a preconfigured Meeting Service
 */
- (ZoomSDKMeetingService*)getMeetingService;

/**
 * @brief get the ZoomSDK default Meeting Settings
 * @return a object of Settings Service
 */
- (ZoomSDKSettingService*)getSettingService;

/**
 * @brief get the ZoomSDK default Premeeting Service
 * @return a object of Settings Service
 */
- (ZoomSDKPremeetingService*)getPremeetingService;

/**
 * @brief get the ZoomSDK default Network Service
 * @return a object of Network Service
 */
- (ZoomSDKNetworkService*)getNetworkService;

/**
 * @brief Sets the customized bundle path
 * @param bundlePath: file position of the prodcut customize strings.
 * @param fileName: file name of customize strings.
 *
 */
//- (void)setCustomBundlePath:(NSString*)bundlePath fileName:(NSString*)fileName;

/**
 * @return the ZoomSDK default Version Number
 */
- (NSString*)getSDKVersionNumber;

/**
 * @brief get the supproted localization lanuguages
 * @param the items in NSArray is the name of the supported lanuguages, which type is NSString.
 */
- (NSMutableArray*)getLanguageArray;

/**
 * @brief set the language of the app
 * @param preferLanguage: the name the the language, which is get from - (NSMutableArray *)getLanguageArray.
 * @return ZoomSDKError: return value ZoomSDKError_Success means the prefered language is successfully setted.
    you can call this api when you first call [ZoomSDK sharedSDk] in the app, otherwise you need restart the app to make the prefered Language work.
 */
- (ZoomSDKError)setPreferLanguage:(NSString *)preferLanguage;
@end


