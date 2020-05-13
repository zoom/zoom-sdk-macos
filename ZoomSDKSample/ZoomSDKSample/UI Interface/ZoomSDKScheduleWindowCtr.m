//
//  ZoomSDKScheduleWindowCtr.m
//  ZoomSDKSample
//
//  Created by TOTTI on 2018/10/15.
//  Copyright © 2018 zoom.us. All rights reserved.
//

#import "ZoomSDKScheduleWindowCtr.h"
#import "ZoomSDK.h"
@interface ZoomSDKScheduleWindowCtr ()

@end

@implementation ZoomSDKScheduleWindowCtr

-(id)initWithUniqueID:(long long)meetingUniqueID
{
    if(self = [super initWithWindowNibName:@"ZoomSDKScheduleWindowCtr" owner: self])
    {
        _meetingUniqueID = meetingUniqueID;
        return self;
    }
    return nil;
}

-(void)awakeFromNib
{
    self.window.level = NSPopUpMenuWindowLevel;
    if (_meetingUniqueID)
    {
        _editMeetingItem = [[[ZoomSDK sharedSDK] getPremeetingService] createEditMeetingItemWithMeetingID:_meetingUniqueID];
        _configOption = [_editMeetingItem configOption];
        _dateOption = [_editMeetingItem dateOption];
        _videoOption = [_editMeetingItem videoOption];
        _audioOption = [_editMeetingItem audioOption];
    }
    else
    {
        _scheduleMeetingItem = [[[ZoomSDK sharedSDK] getPremeetingService] createScheduleMeetingItem];
        _configOption = [_scheduleMeetingItem configOption];
        _dateOption = [_scheduleMeetingItem dateOption];
        _videoOption = [_scheduleMeetingItem videoOption];
        _audioOption = [_scheduleMeetingItem audioOption];
    }
    [self updateUI];
}
- (void)windowDidLoad {
    [super windowDidLoad];
    [self updateUI];
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

- (void)updateUI
{
    if (_meetingUniqueID)
    {
        _scheduleEditButton.title = @"Edit";
        self.window.title = @"Edit Meeting";
        time_t startTime = [_dateOption getMeetingStartTime];
        [_time setDateValue:[NSDate dateWithTimeIntervalSince1970:startTime]];
        [_duration setStringValue:[NSString stringWithFormat:@"%d", [_dateOption getMeetingDuration]]];
        if([_dateOption isRecurringMeeting])
        {
            [_time setHidden:YES];
            [_duration setHidden:YES];
            [_timeStartLabel setHidden:YES];
            [_timeDurationLabel setHidden:YES];
            [_timeMinsLabel setHidden:YES];
        }
    }
    else
    {
        _scheduleEditButton.title = @"Schedule";
        self.window.title = @"Schedule Meeting";
        [_duration setStringValue:@"60"];
    }
    
    NSDate *now = [NSDate date];
    NSDate *startDate = [self getMeetingStartDateFromDate:now];
    
    [_time setTimeZone:[NSTimeZone localTimeZone]];
    [_time setDateValue:startDate];
    
    NSString* meetingTopic = [_configOption getMeetingTopic];
    [_topic setStringValue:meetingTopic];
    BOOL isRecurring = [_dateOption isRecurringMeeting];
    [_recurring setState:isRecurring? NSOnState: NSOffState];
    
    BOOL isHostVideoOn = [_videoOption isHostVideoOn];
    BOOL isAttendeeVideoOn = [_videoOption isParticipantVideoOn];
    if(isHostVideoOn)
    {
        [_hostVideoOn setState:NSOnState];
        [_hostVideoOff setState:NSOffState];
    }else{
        [_hostVideoOn setState:NSOffState];
        [_hostVideoOff setState:NSOnState];
    }
    if(isAttendeeVideoOn)
    {
        [_attendeeVideoOn setState:NSOnState];
        [_attendeeVideoOff setState:NSOffState];
    }else{
        [_attendeeVideoOn setState:NSOffState];
        [_attendeeVideoOff setState:NSOnState];
    }
    int supportAudioType = 0;
    ScheduleMeetingAudioType type = [_audioOption getScheduleMeetingAudioType:&supportAudioType];
    if (!(supportAudioType&ScheduleMeetingAudioType_3rd)) {
        [_3rd setHidden:YES];
    }
    if(!(supportAudioType&ScheduleMeetingAudioType_Both))
    {
        [_both setHidden:YES];
    }
    if(!(supportAudioType&ScheduleMeetingAudioType_Telephone))
    {
        [_tele setHidden:YES];
    }
    switch (type) {
            
        case ScheduleMeetingAudioType_Telephone:
        {
            [_voip setState:NSOffState];
            [_tele setState:NSOnState];
            [_both setState:NSOffState];
            [_3rd setState:NSOffState];
        }
            break;
        case ScheduleMeetingAudioType_Both:
        {
            [_voip setState:NSOffState];
            [_tele setState:NSOffState];
            [_both setState:NSOnState];
            [_3rd setState:NSOffState];
        }
            break;
        case ScheduleMeetingAudioType_3rd:
        {
            [_voip setState:NSOffState];
            [_tele setState:NSOffState];
            [_both setState:NSOffState];
            [_3rd setState:NSOnState];
        }
            break;
        case ScheduleMeetingAudioType_Voip:
        default:
        {
            [_voip setState:NSOnState];
            [_tele setState:NSOffState];
            [_both setState:NSOffState];
            [_3rd setState:NSOffState];
        }
            break;
    }
    NSArray* availableCountry = [_audioOption getAvailableDialinCountry];
    NSArray* selectedCountry = [_audioOption getSelectedDialinCountry];
    NSString* countryString =@"";
    NSString* selectedCountryString = @"";
    if([availableCountry count] > 0)
    {
        for (NSString* countryName in availableCountry) {
            countryString = [countryString stringByAppendingString:[NSString stringWithFormat:@"%@;", countryName]];
        }
    }
    _availableCountryString = countryString;
    [_availableCountry setString:_availableCountryString];
    if ([selectedCountry count] > 0) {
        for (NSString* country in selectedCountry) {
            selectedCountryString = [selectedCountryString stringByAppendingString:country];
        }
    }
    BOOL isRequiredPassword = [_configOption enableRequiredPassword];
    [_requiredPassword setState:isRequiredPassword? NSOnState: NSOffState];
    if (_requiredPassword.state != NSOnState) {
        [_password setHidden:YES];
    }
    else
    {
        [_password setStringValue:[_configOption getMeetingPassword]];
    }
    BOOL jbh = [_configOption enableJBH];
    [_enableJBH setState:jbh? NSOnState: NSOffState];
    BOOL muteOnEntry = [_configOption enableMuteOnEntry];
    [_muteOnEntry setState:muteOnEntry? NSOnState: NSOffState];
    BOOL pmi = [_configOption enableUsePMI];
    [_usePMI setState:pmi? NSOnState: NSOffState];
    BOOL canShow = NO;
    BOOL isHostInChina = [_configOption enableHostInChina:&canShow];
    if(canShow)
    {
        [_hostInChina setHidden:NO];
        [_hostInChina setState:isHostInChina? NSOnState:NSOffState];
        
    }else{
        [_hostInChina setHidden:YES];
    }
    BOOL onlySignedUserJoin = [_configOption enableOnlySignedUserJoin:&canShow];
    if(canShow)
    {
        [_onlySignedInUser setHidden:NO];
        [_onlySignedInUser setState:onlySignedUserJoin? NSOnState: NSOffState];
    }else{
        [_onlySignedInUser setHidden:YES];
    }
    BOOL enableSpecialDom = [_configOption enableSpecialDomainUserJoin:&canShow];
    NSString* specialDomains = [_configOption getSpecialDomains];
    if(canShow)
    {
        [_onlySignedInSpecialUser setHidden:NO];
        [_onlySignedInSpecialUser setState:enableSpecialDom? NSOnState:NSOffState];
        if ([_onlySignedInSpecialUser state] != NSOffState) {
            [_specialDomains setHidden:NO];
            if(specialDomains)
                [_specialDomains setStringValue:specialDomains];
        }else{
            [_specialDomains setHidden:YES];
        }
    }else{
        [_onlySignedInSpecialUser setHidden:YES];
        [_specialDomains setHidden:YES];
    }
    int recordType = 0;
    BOOL isAutoRecord = [_configOption enableAutoRecord:&recordType];
    if(!recordType)
    {
        [_autoRecord setHidden:YES];
    }else{
        [_autoRecord setHidden:NO];
        [_autoRecord setState:isAutoRecord? NSOnState:NSOffState];
        if (_autoRecord.state == NSOnState) {
            if(!(recordType&ScheduleMeetingRecordType_Local))
            {
                [_localRecord setHidden:YES];
            }else{
                [_localRecord setHidden:NO];
            }
            if(!(recordType&ScheduleMeetingRecordType_Cloud))
            {
                [_cloudRecord setHidden:YES];
            }else{
                [_cloudRecord setHidden:NO];
            }
            ScheduleMeetingRecordType type = [_configOption getMeetingRecordType];
            switch (type) {
                case ScheduleMeetingRecordType_Cloud:
                    [_localRecord setState:NSOffState];
                    [_cloudRecord setState:NSOnState];
                    break;
                case ScheduleMeetingRecordType_Local:
                    [_localRecord setState:NSOnState];
                    [_cloudRecord setState:NSOffState];
                    break;
                case ScheduleMeetingRecordType_None:
                default:
                    break;
            }
        }else{
            [_localRecord setHidden:YES];
            [_cloudRecord setHidden:YES];
        }
    }
    NSArray* scheduleUser = [_configOption getScheduleForUser:&canShow];
    if(canShow)
    {
        NSString* schedule4 = @"";
        [_schedule4Users setHidden:NO];
        if([scheduleUser count] > 0)
        {
            for(IScheduleForUser* user in scheduleUser)
            {
                schedule4 = [schedule4 stringByAppendingString:[NSString stringWithFormat:@"%@;",user.email]];
            }
        }
        [_schedule4Users setStringValue:schedule4];
    }else{
        [_schedule4Users setHidden:YES];
    }
}
#pragma mark - IBAction

-(IBAction)onRecurringClick:(id)sender
{
    [_dateOption enableRecurringMeeting:(_recurring.state == NSOnState)];
    if(_recurring.state == NSOnState)
    {
        [_time setHidden:YES];
        [_duration setHidden:YES];
        [_timeStartLabel setHidden:YES];
        [_timeDurationLabel setHidden:YES];
        [_timeMinsLabel setHidden:YES];
    }
    else
    {
        [_time setHidden:NO];
        [_duration setHidden:NO];
        [_timeStartLabel setHidden:NO];
        [_timeDurationLabel setHidden:NO];
        [_timeMinsLabel setHidden:NO];
    }
}
-(IBAction)onHostVideo:(id)sender
{
    NSButton* hostVideoButton = (NSButton*)sender;
    [_videoOption setHostVideoOn:[hostVideoButton.title isEqualToString:@"On"]];
}
-(IBAction)onAtendeeVideo:(id)sender
{
    NSButton* attendeeVideoButton = (NSButton*)sender;
    [_videoOption setParticipantVideoOn:[attendeeVideoButton.title isEqualToString:@"On"]];
}
-(IBAction)onAudioClick:(id)sender
{
    NSButton* audioButton = (NSButton*)sender;
    if ([audioButton.title isEqualToString:@"Telephone"]) {
        [_availableCountry setHidden:NO];
        [_selectedCountry setHidden:NO];
        [_audioOption setScheduleMeetingAudioType:ScheduleMeetingAudioType_Telephone];
    }else if([audioButton.title isEqualToString:@"Voip"]){
        [_availableCountry setHidden:YES];
        [_selectedCountry setHidden:YES];
        [_audioOption setScheduleMeetingAudioType:ScheduleMeetingAudioType_Voip];
    }else if([audioButton.title isEqualToString:@"Both"]){
        [_availableCountry setHidden:NO];
        [_selectedCountry setHidden:NO];
        [_audioOption setScheduleMeetingAudioType:ScheduleMeetingAudioType_Both];
    }else{
        [_availableCountry setHidden:YES];
        [_selectedCountry setHidden:YES];
        [_audioOption setScheduleMeetingAudioType:ScheduleMeetingAudioType_3rd];
    }
    
}
-(IBAction)onRequiredPassword:(id)sender
{
    [_configOption setRequirePassword:(_requiredPassword.state == NSOnState)];
    [_password setHidden:(_requiredPassword.state != NSOnState)];
}
-(IBAction)onJBHClick:(id)sender
{
    [_configOption setEnableJBH:(_enableJBH.state == NSOnState)];
}
-(IBAction)onMuteOnEntryClick:(id)sender
{
    [_configOption setEnableMuteOnEntry:(_muteOnEntry.state == NSOnState)];
}
-(IBAction)onPMIClick:(id)sender
{
    [_configOption setUsePMI:(_usePMI.state == NSOnState)];
}
-(IBAction)onSignedInUserClick:(id)sender
{
    [_configOption setEnableOnlySignedUserJoin:(_onlySignedInUser.state == NSOnState)];
}
-(IBAction)onAutoRecordClick:(id)sender
{
    [_configOption setEnableAutoRecord:(_autoRecord.state == NSOnState)];
    int recordType = 0;
    BOOL isAutoRecord = [_configOption enableAutoRecord:&recordType];
    if (_autoRecord.state == NSOnState) {
        if(!(recordType&ScheduleMeetingRecordType_Local))
        {
            [_localRecord setHidden:YES];
        }else{
            [_localRecord setHidden:NO];
        }
        if(!(recordType&ScheduleMeetingRecordType_Cloud))
        {
            [_cloudRecord setHidden:YES];
        }else{
            [_cloudRecord setHidden:NO];
        }
        ScheduleMeetingRecordType type = [_configOption getMeetingRecordType];
        switch (type) {
            case ScheduleMeetingRecordType_Cloud:
                [_localRecord setState:NSOffState];
                [_cloudRecord setState:NSOnState];
                break;
            case ScheduleMeetingRecordType_Local:
                [_localRecord setState:NSOnState];
                [_cloudRecord setState:NSOffState];
                break;
            case ScheduleMeetingRecordType_None:
            default:
                break;
        }
    }else{
        [_localRecord setHidden:YES];
        [_cloudRecord setHidden:YES];
    }
}

-(IBAction)onSignedInSpecialUserClick:(id)sender
{
    [_configOption setEnableSpecialDomainUserJoin:(_onlySignedInSpecialUser.state == NSOnState)];
    [_specialDomains setHidden:(_onlySignedInSpecialUser.state != NSOnState)];
}

-(IBAction)onHostInChinaClick:(id)sender
{
    [_configOption setEnableHostInChina:(_hostInChina.state == NSOnState)];
}

-(IBAction)onRecordTypeClick:(id)sender
{
    NSButton* recordButton = (NSButton*)sender;
    if([recordButton.title isEqualToString:@"Local"])
        [_configOption setRecordType:ScheduleMeetingRecordType_Local];
    else
        [_configOption setRecordType:ScheduleMeetingRecordType_Cloud];
}


-(IBAction)onScheduleEditMeeting:(id)sender
{
    [_configOption setMeetingTopic:[_topic stringValue]];
    time_t sTime = (long)[[_time dateValue]timeIntervalSince1970];
    [_dateOption setMeetingStartTime:sTime];
    NSNumberFormatter* formatter = [[[NSNumberFormatter alloc] init] autorelease];
    NSNumber* number = [formatter numberFromString:[_duration stringValue]];
    [_dateOption setMeetingDuration:[number unsignedIntValue]];
    if (_selectedCountry.stringValue.length >0) {
        NSArray* selectedCountry =[[_selectedCountry stringValue] componentsSeparatedByString:@";"];
        if(selectedCountry.count > 0)
            [_audioOption selectDialinCountry:selectedCountry];
    }
    if([_specialDomains stringValue].length > 0)
       [_configOption selectSpecialDomains:[_specialDomains stringValue]];
    if (_password.stringValue.length >0) {
        [_configOption setMeetingPassword:_password.stringValue];
    }
    if(_schedule4Users.stringValue.length > 0)
    {
        NSArray* schedule4users = [[_schedule4Users stringValue] componentsSeparatedByString:@";"];
        NSMutableArray* userArray = [[[NSMutableArray alloc] initWithCapacity:0] autorelease];
        for (NSString* email in schedule4users) {
            IScheduleForUser* user = [[[IScheduleForUser alloc] init] autorelease];
            user.email = email;
            user.displayName = @"";
            [userArray addObject:user];
        }
        if(schedule4users.count >0)
            [_configOption selectScheduleForUser:userArray];
    }
    if (_meetingUniqueID) {
        [[[ZoomSDK sharedSDK] getPremeetingService] editMeeting:_editMeetingItem MeetingUniqueID:_meetingUniqueID];
    }else{
         [[[ZoomSDK sharedSDK] getPremeetingService] scheduleMeeting:_scheduleMeetingItem];
    }
    
    
}

- (NSDate *)getMeetingStartDateFromDate:(NSDate *)currentDate
{
    NSDateComponents *time = [[NSCalendar currentCalendar]
                              components:NSHourCalendarUnit | NSMinuteCalendarUnit | NSSecondCalendarUnit
                              fromDate:currentDate];
    [time setMinute:-[time minute]];
    [time setSecond:-[time second]];
    [time setHour:1];
    
    return [[NSCalendar currentCalendar] dateByAddingComponents:time toDate:currentDate options:0];
}

- (void)dealloc
{
    if(_scheduleMeetingItem)
        [[[ZoomSDK sharedSDK] getPremeetingService] destoryScheduleMeetingItem:_scheduleMeetingItem];
    if(_editMeetingItem)
        [[[ZoomSDK sharedSDK] getPremeetingService] destoryScheduleMeetingItem:_editMeetingItem];
    [super dealloc];
}
- (void)showWindow:(id)sender
{
    [self updateUI];
}
@end
