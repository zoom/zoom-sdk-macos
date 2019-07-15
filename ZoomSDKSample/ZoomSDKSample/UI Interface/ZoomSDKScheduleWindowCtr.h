//
//  ZoomSDKScheduleWindowCtr.h
//  ZoomSDKSample
//
//  Created by TOTTI on 2018/10/15.
//  Copyright © 2018 zoom.us. All rights reserved.
//

#import <Cocoa/Cocoa.h>
@class ZoomSDKScheduleMeetingItem;
@class ZoomSDKMeetingItem;
@class ScheduleMeetingAudioOption;
@class ScheduleMeetingDateOption;
@class ScheduleMeetingVideoOption;
@class ScheduleMeetingConfigOption;
@class IMeetingDateOption;
@class IMeetingAudioOption;
@class IMeetingVideoOption;
@class IMeetingConfigOption;
@interface ZoomSDKScheduleWindowCtr : NSWindowController
{
    IBOutlet NSTextField*   _topic;
    IBOutlet NSDatePicker*  _time;
    IBOutlet NSTextField*   _duration;
    IBOutlet NSTextField*   _timeStartLabel;
    IBOutlet NSTextField*   _timeDurationLabel;
    IBOutlet NSTextField*   _timeMinsLabel;
    IBOutlet NSButton*      _recurring;
    IBOutlet NSButton*      _hostVideoOn;
    IBOutlet NSButton*      _hostVideoOff;
    IBOutlet NSButton*      _attendeeVideoOn;
    IBOutlet NSButton*      _attendeeVideoOff;
    IBOutlet NSButton*      _tele;
    IBOutlet NSButton*      _voip;
    IBOutlet NSButton*      _both;
    IBOutlet NSButton*      _3rd;
    IBOutlet NSTextView*    _availableCountry;
    IBOutlet NSTextField*   _selectedCountry;
    IBOutlet NSButton*      _requiredPassword;
    IBOutlet NSTextField*   _password;
    IBOutlet NSButton*      _enableJBH;
    IBOutlet NSButton*      _muteOnEntry;
    IBOutlet NSButton*      _usePMI;
    IBOutlet NSButton*      _hostInChina;
    IBOutlet NSButton*      _onlySignedInUser;
    IBOutlet NSButton*      _onlySignedInSpecialUser;
    IBOutlet NSTextField*   _specialDomains;
    IBOutlet NSButton*      _autoRecord;
    IBOutlet NSButton*      _localRecord;
    IBOutlet NSButton*      _cloudRecord;
    IBOutlet NSTextField*   _schedule4Users;
    IBOutlet NSButton*      _scheduleEditButton;
    ZoomSDKScheduleMeetingItem*  _scheduleMeetingItem;
    ZoomSDKScheduleMeetingItem*  _editMeetingItem;
    ScheduleMeetingAudioOption*  _audioOption;
    ScheduleMeetingDateOption*   _dateOption;
    ScheduleMeetingVideoOption*  _videoOption;
    ScheduleMeetingConfigOption*  _configOption;
    long long                     _meetingUniqueID;
    NSString*                     _availableCountryString;
}

-(id)initWithUniqueID:(long long)meetingUniqueID;
-(IBAction)onRecurringClick:(id)sender;
-(IBAction)onHostVideo:(id)sender;
-(IBAction)onAtendeeVideo:(id)sender;
-(IBAction)onAudioClick:(id)sender;
-(IBAction)onRequiredPassword:(id)sender;
-(IBAction)onJBHClick:(id)sender;
-(IBAction)onMuteOnEntryClick:(id)sender;
-(IBAction)onPMIClick:(id)sender;
-(IBAction)onHostInChinaClick:(id)sender;
-(IBAction)onSignedInUserClick:(id)sender;
-(IBAction)onSignedInSpecialUserClick:(id)sender;
-(IBAction)onAutoRecordClick:(id)sender;
-(IBAction)onRecordTypeClick:(id)sender;
-(IBAction)onScheduleEditMeeting:(id)sender;
- (void)showWindow:(id)sender;
@end
