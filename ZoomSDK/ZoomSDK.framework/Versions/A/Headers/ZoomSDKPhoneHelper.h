//
//  ZoomSDKPhoneHelper.h
//  ZoomSDK
//
//  Created by TOTTI on 5/19/17.
//  Copyright © 2017 TOTTI. All rights reserved.
//

#import "ZoomSDKErrors.h"

@protocol ZoomSDKPhoneHelperDelegate <NSObject>
-(void)onInviteCalloutUserStatus:(PhoneStatus)status FailedReason:(PhoneFailedReason)reason;
-(void)onCallMeStatus:(PhoneStatus)status FailedReason:(PhoneFailedReason)reason;
@end

@interface ZoomSDKPhoneSupportCountryInfo : NSObject
{
    NSString* _countryID;
    NSString* _countryName;
    NSString* _countryCode;
}
-(NSString*)getCountryID;
-(NSString*)getCountryName;
-(NSString*)getCountryCode;
@end

@interface ZoomSDKPhoneHelper : NSObject
{
    id<ZoomSDKPhoneHelperDelegate> _delegate;
    PhoneStatus _callMeStatus;
}
@property(nonatomic, assign)id<ZoomSDKPhoneHelperDelegate> delegate;
-(BOOL)isSupportPhone;
-(NSArray*)getSupportCountryInfo;
-(ZoomSDKError)inviteCalloutUser:(NSString*)userName PhoneNumber:(NSString*)number CountryCode:(NSString*)countryCode;
-(ZoomSDKError)cancelCalloutUser;
-(PhoneStatus)getInviteCalloutUserStatus;
-(ZoomSDKError)callMe:(NSString*)number CountryCode:(NSString*)countryCode;
-(ZoomSDKError)hangUp;
-(PhoneStatus)getCallMeStatus;
@end
