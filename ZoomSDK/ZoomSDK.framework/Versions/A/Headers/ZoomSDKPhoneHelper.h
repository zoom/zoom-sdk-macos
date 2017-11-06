//
//  ZoomSDKPhoneHelper.h
//  ZoomSDK
//
//  Created by TOTTI on 5/19/17.
//  Copyright © 2017 TOTTI. All rights reserved.
//

#import "ZoomSDKErrors.h"

@protocol ZoomSDKPhoneHelperDelegate <NSObject>
/**
 * @brief Invite callout user status callback.
 * @param status: phone status 
 * @param reason: if status = PhoneStatus_Failed, reason will be assigned the failed reason.
 */
-(void)onInviteCalloutUserStatus:(PhoneStatus)status FailedReason:(PhoneFailedReason)reason;

/**
 * @brief telephone user callback.
 * @param status: phone status
 * @param reason: if status = PhoneStatus_Failed, reason will be assigned the failed reason.
 */
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

@interface ZoomSDKCallInPhoneNumInfo : NSObject
{
    NSString* _id;
    NSString* _code;
    NSString* _name;
    NSString* _number;
    NSString* _displayNumber;
    CallInNumberType _type;
}
-(NSString*) getID;
-(NSString*) getCode;
-(NSString*) getName;
-(NSString*) getNumber;
-(NSString*) getDisplayNumber;
-(CallInNumberType) getType;
@end

@interface ZoomSDKPhoneHelper : NSObject
{
    id<ZoomSDKPhoneHelperDelegate> _delegate;
    PhoneStatus _callMeStatus;
}
@property(nonatomic, assign)id<ZoomSDKPhoneHelperDelegate> delegate;
/**
 * @brief Get client support phone callout or not.
 * @return BOOL value to tell client support phone callout or not.
 */
-(BOOL)isSupportPhone;

/**
 * @brief Get client callout country info.
 * @return A NSArray contains the callout country info.
 */
-(NSArray*)getSupportCountryInfo;

/**
 * @brief This method is used to invite callout user.
 * @param userName: callout user name
 * @param number: callout phone number
 * @param countryCode: callout user's country code
 * @return A ZoomSDKError to tell client invite callout user successfully or not.
 */
-(ZoomSDKError)inviteCalloutUser:(NSString*)userName PhoneNumber:(NSString*)number CountryCode:(NSString*)countryCode;

/**
 * @brief This method is used to cancel callout action.
 * @return A ZoomSDKError to tell client invite cancel callout user successfully or not.
 */
-(ZoomSDKError)cancelCalloutUser;

/**
 * @brief This method is used to get invite callout user status.
 * @return A PhoneStatus to tell client detail status of callout user.
 */
-(PhoneStatus)getInviteCalloutUserStatus;

/**
 * @brief This method is call telephone user for audio service.
 * @param number: my phone number
 * @param countryCode: my country code
 * @return A ZoomSDKError to tell client call me successfully or not.
 */
-(ZoomSDKError)callMe:(NSString*)number CountryCode:(NSString*)countryCode;

/**
 * @brief This method is hangup call me.
 * @return A ZoomSDKError to tell client hangup successfully or not.
 */
-(ZoomSDKError)hangUp;

/**
 * @brief This method is used to get my telephone status.
 * @return A PhoneStatus to tell client detail status of my telephone.
 */
-(PhoneStatus)getCallMeStatus;

/**
 * @brief This method is used to get participant ID to join current meeting.
 * @return A unsigned int value of participant ID.
 */
-(unsigned int)getCallInParticipantID;

/**
* @brief This method is used to get call in number for current meeting.
* @return A array contains ZoomSDKCallInPhoneNumInfo objects.
*/
-(NSArray*)getCallInNumberInfo;

@end
