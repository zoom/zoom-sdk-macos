//
//  ZoomSDKNetworkService.h
//  ZoomSDK
//
//  Created by TOTTI on 2/28/17.
//  Copyright © 2017 TOTTI. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ZoomSDKProxySettingHelper : NSObject
{
    NSString*   _proxyHost;
    int         _proxyPort;
    NSString*   _proxyDescription;
}
- (NSString*)getProxyHost;
- (int)getProxyPort;
- (NSString*)getProxyDescription;
- (void)proxyAuth:(NSString*)userName password:(NSString*)password;
- (void)cancel;
@end

@interface ZoomSDKSSLVerificationHelper :NSObject
{
    NSString* _certIssueTo;
    NSString* _certIssueBy;
    NSString* _certSerialNum;
    NSString* _certFingerprint;
}
- (NSString*)getCertIssueTo;
- (NSString*)getCertIssueBy;
- (NSString*)getCertSerialNum;
- (NSString*)getCertFingerprint;
- (void)trust;
- (void)cancel;

@end

@protocol ZoomSDKNetworkSeviceDelegate <NSObject>
/**
 * @brief Designated for ZoomSDK network proxy setting call back
 * @param proxyHelper: A ZoomSDKProxySettingHelper object contains proxy info.
 *
 */
- (void)onProxySettingNotification:(ZoomSDKProxySettingHelper*)proxyHelper;

/**
 * @brief Designated for ZoomSDK network SSL verification setting call back
 * @param sslHelper: A ZoomSDKSSLVerificationHelper object contains ssl verification info.
 *
 */
- (void)onSSLCertVerifyNotification:(ZoomSDKSSLVerificationHelper*)sslHelper;

@end

@interface ZoomSDKNetworkService : NSObject
{
    id<ZoomSDKNetworkSeviceDelegate>  _delegate;
}
@property(nonatomic, retain) id<ZoomSDKNetworkSeviceDelegate> delegate;
@end
