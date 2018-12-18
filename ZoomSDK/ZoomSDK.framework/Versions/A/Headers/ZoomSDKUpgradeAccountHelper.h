//
//  ZoomSDKUpgradeAccountHelper.h
//  ZoomSDK
//
//  Created by Totti on 2018/6/29.
//  Copyright © 2018 TOTTI. All rights reserved.
//

#import "ZoomSDKErrors.h"

@interface ZoomSDKUpgradeAccountHelper : NSObject
{
    SDKReminderType                          _type;
}

-(SDKReminderType)getReminderType;
-(ZoomSDKError)upgradeAccountFreeTrial;
-(ZoomSDKError)upgradeAccount;
@end
