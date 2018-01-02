# CHANGELOG

## 2017-12-26


1.    ZoomSDKASController.h

1)    Interface added in object ZoomSDKAnnotationController:

  - (BOOL)isAnnotationDisable;

2)    Interface modified:
Old: (ZoomSDKError)startAppShare:(CGWindowID)windowID displayID:(CGDirectDisplayID)displayID;

New: (ZoomSDKError)startAppShare:(CGWindowID)windowID;

Old: (ZoomSDKAnnotationController*)getAnnotationController:(ScreenType)type;

New: ZoomSDKAnnotationController*)getAnnotationController;

Old: (ZoomSDKError)startAnnotation:(BOOL)selfShare Position:(NSPoint)position onScreen:(ScreenType)screen

New: (ZoomSDKError)startAnnotation:(NSPoint)position onScreen:(ScreenType)screen

Old: (ZoomSDKError)stopAnnotation:(BOOL)selfShare onScreen:(ScreenType)screen;
 
New: (ZoomSDKError)stopAnnotation:(ScreenType)screen

2.    ZoomSDKActionController.h

1)    Interface added in object ZoomSDKAnnotationController:

- (BOOL)isMySelf;

3.    ZoomSDKMeetingConfiguration.h

1)    Interface added in object ZoomSDKMeetingConfiguration:

- (ZoomSDKError)modifyWindowTitle:(BOOL)modify NewMeetingNum:(unsigned int)meetingnumber;

2)    new property added in ZoomSDKMeetingConfiguration:

BOOL hideLeaveMeetingWindow;

3)    Interface added:
Old: - (ZoomSDKError)hideSDKButtons:(SDKButton)button;

New:- (ZoomSDKError)hideSDKButtons:(BOOL)hide ButtonType:(SDKButton)button;

4.    ZoomSDKMeetingService.h

1)    Interface modified:

Old:- (void)onMeetingStatusChange:(ZoomSDKMeetingStatus)state meetingError:(ZoomSDKMeetingError)error;

New: - (void)onMeetingStatusChange:(ZoomSDKMeetingStatus)state meetingError:(ZoomSDKMeetingError)error EndReason:(EndMeetingReason)reason;

Old: (ZoomSDKConnectionQuality)getConnectionQuality

New: (ZoomSDKConnectionQuality)getConnectionQuality:(ConnectionComponent)component Sending:(BOOL)sending;


5.    ZoomSDKMeetingUIController.h

1)    Interface modified:

Old: (ZoomSDKError)modifyMeetingInfoInMainWindow:(unsigned int)newMeetingNum;

New: (ZoomSDKError)modifyWindowTitle:(BOOL)modify NewMeetingNum:(unsigned int)meetingnumber in ZoomSDKMeetingConfiguration.h

2)    Delegate Interface added:

-(void)onNeedShowLeaveMeetingWindow;

## 2017-11-02

### Added

1. add interface to check sharing content

2. add support for split screen during sharing

3. add interface to inform active speaker

4. add support to change in meeting name

5. add support to minimize video

6. add callback interface for clicking toolbar share button 

7. add support for webinar join window info prefill

8. for code refactor details, please visit : https://developer.zoom.us/docs/macos/mac-sdk-refactor-details/

9. add support to hide each individual button on fitbar during sharing.

10. bug fix

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
