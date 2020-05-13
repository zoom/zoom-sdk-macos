//
//  ZMSDKInitHelper.m
//  ZoomSDKSample
//
//  Created by TOTTI on 2018/11/19.
//  Copyright © 2018 zoom.us. All rights reserved.
//

#import "ZMSDKInitHelper.h"
#import "ZoomSDK.h"
#import "ZMSDKCommonHelper.h"

static  ZMSDKInitHelper *initHelper = nil;
@implementation ZMSDKInitHelper

-(id)init
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        initHelper = [super init];
    });
    return initHelper;
}


+(void)initSDK:(BOOL)useCustomizedUI
{
    ZoomSDK* sdk = [ZoomSDK sharedSDK];
   /* NSString *localeIdentifier = [[NSLocale currentLocale] objectForKey:NSLocaleCountryCode];
    if(localeIdentifier && [localeIdentifier.uppercaseString isEqualToString:@"CN"])
        [[ZoomSDK sharedSDK] setAppLocale:ZoomSDKLocale_CN];
    else
        [[ZoomSDK sharedSDK] setAppLocale:ZoomSDKLocale_Def];*/
    
    [sdk initSDK:useCustomizedUI];
    [ZMSDKCommonHelper sharedInstance].isUseCutomizeUI = useCustomizedUI;
}

+(void)setDomain:(NSString*)domain
{
    ZoomSDK* sdk = [ZoomSDK sharedSDK];
    [sdk setZoomDomain:domain];
}
@end
