//
//  ZPBundleHelper.h
//  SaasBeePTUIModule
//
//  Created by sanshi on 11-12-8.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ZPBundleHelper : NSObject


+ (NSBundle *)resBundle;
+ (NSString *)resBundlePath;
+ (NSString *)resBundlePathForResource:(NSString *)resName ofType:(NSString *)typeName;
+ (NSString *)mainResBundlePathForResource:(NSString *)resName ofType:(NSString *)typeName;
+ (NSImage *)resBundleImageForResource:(NSString *)resName ofType:(NSString *)typeName;
+ (NSImage*)getAvatarByPath:(NSString*)inPath;
+ (NSImage *)loadRetinaImageByName:(NSString*)resName;

+ (NSString *)resolveImagePath:(NSString *)imagePath;
+ (NSString*)localizedString:(NSString *)theKey;
+ (NSString*)localizedString:(NSString *)theKey value:(NSString*)value;
+ (void)cleanUp;
+ (NSImage*)getRetinaImage:(NSString*)name ofType:(NSString*)type;
+ (NSString*)localizedEnString:(NSString *)theKey value:(NSString*)value;
//for sdk
+ (void)setCustomBundlePath:(NSString*)bundlePath fileName:(NSString*)fileName;
@end
