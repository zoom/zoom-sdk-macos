//
//  ZPBundleHelper.h
//  SaasBeePTUIModule
//
//  Created by sanshi on 11-12-8.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "zoom_client_conf.h"

@interface ZPBundleHelper : NSObject


+ (NSBundle *)resBundle;
+ (NSString *)resBundlePath;
+ (NSString *)resBundlePathForResource:(NSString *)resName ofType:(NSString *)typeName;
+ (NSString *)mainResBundlePathForResource:(NSString *)resName ofType:(NSString *)typeName;
+ (NSImage *)resBundleImageForResource:(NSString *)resName ofType:(NSString *)typeName;
+ (NSImage*)getAvatarByPath:(NSString*)inPath;
+ (NSImage *)getImageByName:(NSString*)resName;//[Zoom-33534]

+ (NSString *)resolveImagePath:(NSString *)imagePath;
+ (NSString*)localizedString:(NSString *)theKey;
+ (NSString*)localizedString:(NSString *)theKey value:(NSString*)value;
+ (void)cleanUp;
+ (NSString*)localizedEnString:(NSString *)theKey value:(NSString*)value;

//for sdk
+ (void)setCustomBundlePath:(NSString*)bundlePath fileName:(NSString*)fileName;
#ifdef BUILD_FOR_SDK
+ (NSString *)resBundlePathForSDKElectron:(NSString *)originPath;
#endif
@end
