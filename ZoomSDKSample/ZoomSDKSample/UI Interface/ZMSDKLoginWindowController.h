//
//  ZMSDKLoginWindowController.h
//  ZoomSDKSample
//
//  Created by derain on 2018/11/15.
//  Copyright © 2018年 zoom.us. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ZMSDKMainWindowController.h"

@class ZMSDKAuthHelper;
@class ZMSDKRestAPILogin;
@class ZMSDKEmailLogin;
@class ZMSDKSSOLogin;
@class ZMSDKJoinOnly;

#define kZMSDKLoginEmailRemember @"email remember me"
#define kZMSDKLoginSSORemember @"sso remember me"

@interface ZMSDKLoginWindowController : NSWindowController
{
    IBOutlet NSTabView* _baseTabView;
    //set domain
    IBOutlet NSImageView* _domainLogoImageView;
    IBOutlet NSTextField* _setDomainTextField;
    IBOutlet NSButton* _setDomainButton;
    IBOutlet NSButton* _setUseCustomizedUIButton;
    
    //auth
    IBOutlet NSImageView* _authLogoImageView;
    IBOutlet NSTextField* _sdkKeyTextField;
    IBOutlet NSTextField* _sdkSecretTextField;
    IBOutlet NSButton* _authButton;
    IBOutlet NSButton *_chooseAuthJWTToken;
    
    //loading
    IBOutlet NSProgressIndicator* _loadingProgressIndicator;
    IBOutlet NSTextField* _loadingTextField;
    
    //error
    IBOutlet NSImageView* _errorLogoImageView;
    IBOutlet NSTextField* _connectFailedTextField;
    IBOutlet NSTextField* _errorMessageTextField;
    IBOutlet NSButton* _errorBackButton;
    
    //login
    IBOutlet NSTabView* _loginTabView;
    //email login
    IBOutlet NSImageView* _emailLoginLogoImageView;
    IBOutlet NSTextField* _emailTextField;
    IBOutlet NSTextField* _emailPSWTextField;
    IBOutlet NSButton* _emailRememerMeButton;
    IBOutlet NSButton* _emailLoginButton;
    //rest api login
    IBOutlet NSTextField* _keyField;
    IBOutlet NSTextField* _secretField;
    IBOutlet NSTextField* _expiredTimeField;
    IBOutlet NSTextField* _userIDField;
    IBOutlet NSTextField* _responseLabel;
    IBOutlet NSTextView*  _responseView;

    //sso login
    IBOutlet NSImageView* ssoLoginLogoImageView;
    IBOutlet NSTextField* _ssoTokenTextField;
    IBOutlet NSButton* _ssoRememerMeButton;
    IBOutlet NSButton* _ssoLoginButton;
    
    //join only
    IBOutlet NSImageView* _joinOnlyLogoImageView;
    IBOutlet NSTextField* _joinOnlyMeetingIDTextField;
    IBOutlet NSTextField* _joinOnlyUserNameTextField;
    IBOutlet NSTextField* _joinOnlyMeetingPSWTextField;
    IBOutlet NSButton* _JoinOnlyButton;
    
    ZMSDKMainWindowController* _mainWindowController;
    ZMSDKAuthHelper* _authHelper;
    ZMSDKRestAPILogin* _restAPIHelper;
    ZMSDKEmailLogin* _emailLoginHelper;
    ZMSDKSSOLogin* _ssoLoginHelper;
    ZMSDKJoinOnly* _joinOnlyHelper;
}
@property(nonatomic, retain, readwrite)ZMSDKMainWindowController *mainWindowController;
@property(nonatomic, retain, readwrite)ZMSDKAuthHelper* authHelper;
@property(nonatomic, retain, readwrite)ZMSDKRestAPILogin* restAPIHelper;
@property(nonatomic, retain, readwrite)ZMSDKEmailLogin* emailLoginHelper;
@property(nonatomic, retain, readwrite)ZMSDKSSOLogin* ssoLoginHelper;
@property(nonatomic, retain, readwrite)ZMSDKJoinOnly* joinOnlyHelper;

- (IBAction)onSetDomainClicked:(id)sender;
- (IBAction)onAuthClicked:(id)sender;
- (IBAction)onEmailLoginClicked:(id)sender;
- (IBAction)onEmailRemeberMeClicked:(id)sender;
- (IBAction)onSSORememberMeClicked:(id)sender;
- (IBAction)onSSOLoginClicked:(id)sender;
- (IBAction)onJoinOnlyClicked:(id)sender;
- (IBAction)onErrorBackClicked:(id)sender;
- (IBAction)onGetAccessToken:(id)sender;
- (IBAction)onGetToken:(id)sender;
- (IBAction)onGetZAK:(id)sender;
- (IBAction)onApiLogin:(id)sender;
- (void)showSelf;
- (void)switchToConnectingTab;
- (void)switchToLoginTab;
- (void)switchToErrorTab;
- (void)switchToAuthTab;
- (void)switchToDomainTab;
- (void)showErrorMessage:(NSString*)error;

- (void)createMainWindow;
- (void)logOut;
- (void)updateUIWithLoginStatus:(BOOL)hasLogin;
@end
