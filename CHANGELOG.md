# CHANGELOG

## 2017-06-19

### Added

1. support query and notify share locking status

   (void)onShareStatusLocked:(BOOL)shareLocked;

2. add switch video wall to next page api

   (ZoomSDKError)showPreOrNextPageWallView:(BOOL)nextPage;

3. add join/leave audio api

   ActionMeetingCmd_JoinVoip
    
   ActionMeetingCmd_LeaveVoip

4. Custom input meeting password feature

   (ZoomSDKError)inputPassword:(NSString*)password;

5. add config for hide "exit full screen” button and disable double click to enter fullscreen 

   BOOL _hideExitFullScreenButton;
   
   BOOL _disableDoubleClickToFullScreen;

6. add get meeting type api and user role api

   (UserRole)getUserRole;
   
   (MeetingType)getMeetingType;

7. join/leave bo support

   (ZoomSDKError)joinBreakoutRoom:(NSString*)bID;
   
   (ZoomSDKError)leaveBreakoutRoom;

8. allow or disallow "can unmute by self if mute by host”config

    //can unmute by self when mute by host
    
    ActionMeetingCmd_EnableUnmuteBySelf,
    
    ActionMeetingCmd_DisableUnmuteBySelf,

    //mute/unmute all only for host
    
    ActionMeetingCmd_MuteAll,
    
    ActionMeetingCmd_UnmuteAll,

9. Call out/Invite by phone support

   (ZoomSDKError)inviteCalloutUser:(NSString*)userName PhoneNumber:(NSString*)number CountryCode:(NSString*)countryCode;
    

10. Waiting room:admit attendee into the meeting

    (ZoomSDKError)admitToMeeting:(unsigned int)userid;

11. Bugs fix.

## 2017-01-23

### Added

1. Support to join Webinar meeting with as Panelist;

2. Support to pin/spotlight video;

3. Support H.323/SIP callout directly

4. Add watermark “Powered by Zoom” 

5. Support to start/join meeting without audio;
  
6. Support to start/join meeting without video;
  
7. Support Multi-share;
