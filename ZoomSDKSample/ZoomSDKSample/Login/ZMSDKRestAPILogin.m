//
//  ZMSDKRestAPILogin.m
//  ZoomSDKSample
//
//  Created by TOTTI on 2018/11/20.
//  Copyright © 2018 zoom.us. All rights reserved.
//

#import "ZMSDKRestAPILogin.h"
#import "ZMSDKLoginWindowController.h"
#import "ZMSDKCommonHelper.h"
#import <CommonCrypto/CommonHMAC.H>

#define APIURL @"https://api.zoom.us/v2/users/"
#define Header @"{\"alg\": \"HS256\", \"typ\": \"JWT\"}"
#define PayloadFormat @"{\"iss\": \"%@\", \"exp\": \"%@\"}"
#define ZAKType  @"/token?type=zak&access_token="
#define TokenType @"/token?type=token&access_token="
#define ReponseKey @"\"token\":"

@interface ZMSDKRestAPILogin()
{
    NSString* _userID;
    NSString* _zak;
    NSString* _userToken;
    NSString* _displayName;
}
-(NSString*)getZAKToken:(BOOL)zak AccessToken:(NSString*)accessToken UserID:(NSString*)userid;
-(NSString*)base64EncodeString:(NSString*)originalString;
-(NSString*)getHMACSHA256Data:(NSString*)key Data:(NSString*)data;
@end

@implementation ZMSDKRestAPILogin
@synthesize loginWindowCtrl = _loginWindowCtrl;


-(id)initWithWindowController:(ZMSDKLoginWindowController*)loginWindowController
{
    if (self = [super init]) {
        _loginWindowCtrl = loginWindowController;
        return self;
    }
    return nil;
}
- (void)cleanUp
{
    if(_userID)
    {
        [_userID release];
        _userID = nil;
    }
    if(_zak)
    {
        [_zak release];
        _zak = nil;
    }
    if(_userToken)
    {
        [_userToken release];
        _userToken = nil;
    }
}
-(void)dealloc
{
    [self cleanUp];
    [super dealloc];
}

-(NSString*)getAccessToken:(NSString*)key Secret:(NSString*)secret ExpiredTime:(NSString*)expiredTime
{
    NSString* payload = [NSString stringWithFormat:PayloadFormat, key, expiredTime];
    NSString* base64Header = [self base64EncodeString:Header];
    NSString* base64Payload = [self base64EncodeString:payload];
    NSString* temp = [NSString stringWithFormat:@"%@.%@", base64Header,base64Payload];
    NSString* signature = [self getHMACSHA256Data:secret Data:temp];
    NSString* accessToken = [NSString stringWithFormat:@"%@.%@.%@", base64Header, base64Payload, signature];
    NSLog(@"ACCESS TOKEN:%@", accessToken);
    return accessToken;
}

-(NSString*)getToken:(NSString*)accessToken UserID:(NSString*)userid
{
    _userToken = [self getZAKToken:NO AccessToken:accessToken UserID:userid];
    [_userToken retain];
    return _userToken;
}

-(NSString*)getZAK:(NSString*)accessToken UserID:(NSString*)userid
{
    _zak  = [self getZAKToken:YES AccessToken:accessToken UserID:userid];
    [_zak retain];
    return _zak;
}

-(NSString*)getZAKToken:(BOOL)zak AccessToken:(NSString*)accessToken UserID:(NSString*)userid
{
    NSString* typeString = @"";
    if(zak)
    {
        typeString = ZAKType;
    }else{
        typeString = TokenType;
    }
    NSString* urlString = APIURL;
    urlString = [urlString stringByAppendingString:userid];
    urlString = [urlString stringByAppendingString:typeString];
    urlString = [urlString stringByAppendingString:accessToken];
    NSURL* url = [NSURL URLWithString:urlString];
    NSMutableURLRequest *req = [NSMutableURLRequest requestWithURL:url];
    req.HTTPMethod = @"GET";
    NSData *res = [NSURLConnection sendSynchronousRequest:req returningResponse:NULL error:NULL];
    NSString *response = [[[NSString alloc] initWithData:res encoding:NSUTF8StringEncoding] autorelease];
    NSRange range = [response rangeOfString:ReponseKey];
    if (range.location != NSNotFound) {
        NSUInteger length = [response length];
        NSRange ran;
        ran.length = length - 12;
        ran.location = 10;
        response = [response substringWithRange:ran];
    }
    return response;
}

-(NSString*)base64EncodeString:(NSString*)originalString
{
    NSData * data = [originalString dataUsingEncoding:NSUTF8StringEncoding];
    return [data base64EncodedStringWithOptions:0];
}

-(NSString*)getHMACSHA256Data:(NSString*)key Data:(NSString*)data
{
    NSData *saltData = [key dataUsingEncoding:NSUTF8StringEncoding];
    NSData *paramData = [data dataUsingEncoding:NSUTF8StringEncoding];
    NSMutableData* hash = [NSMutableData dataWithLength:CC_SHA256_DIGEST_LENGTH ];
    CCHmac(kCCHmacAlgSHA256, saltData.bytes, saltData.length, paramData.bytes, paramData.length, hash.mutableBytes);
    NSString *base64Hash = [hash base64EncodedStringWithOptions:0];
    return base64Hash;
}
- (void)loginRestApiWithUserID:(NSString*)userID
{
    if(userID.length > 0 && _zak.length > 0 && _userToken.length > 0)
    {
        _userID = userID;
        [_userID retain];
        [ZMSDKCommonHelper sharedInstance].hasLogin = YES;
        [ZMSDKCommonHelper sharedInstance].loginType = ZMSDKLoginType_API;
        [_loginWindowCtrl createMainWindow];
        [_loginWindowCtrl.window close];
        [_loginWindowCtrl.mainWindowController updateUI];
        
        NSMenuItem* appMenuItem =[[[NSApplication sharedApplication] mainMenu] itemWithTag:0];
        NSMenu* appSubMenu = appMenuItem.submenu;
        NSMenuItem* logOutMenuItem =[appSubMenu itemWithTag:12];
        [logOutMenuItem setHidden:NO];
        [_loginWindowCtrl.mainWindowController initApiUserInfoWithID:_userID zak:_zak userToken:_userToken];
    }
}
@end
