# Zoom MacOS Software Development Kit (SDK)
<div align="center">
<img src="https://s3.amazonaws.com/user-content.stoplight.io/8987/1541013063688" width="400px" max-height="400px" style="margin:auto;"/>
</div>

## :rotating_light: Announcement :rotating_light:
The Client SDK hereby introduced the **AES 256-bit GCM encryption** as addressed in our [90-Day Security Plan](https://blog.zoom.us/wordpress/2020/04/22/zoom-hits-milestone-on-90-day-security-plan-releases-zoom-5-0/) to **our SDK version 4.6.21666.0427**. Please note that: This AES 256-bit GCM encryption is **backward INCOMPATIBLE, which means the older version of SDK will NOT be able to join a meeting with GCM encryption enabled,** and as mentioned in the [90-Day Security Plan](https://blog.zoom.us/wordpress/2020/04/22/zoom-hits-milestone-on-90-day-security-plan-releases-zoom-5-0/), **the system-wide account enablement of AES 256-bit GCM encryption will take place on May 30, 2020**. Please plan to upgrade your SDK accordingly, and we will soon take away the older version of SDK that are not compatible with GCM encryption. Thank you!

## Latest SDK Notifications
1. When you are deploying your app with Zoom macos SDK, please don't forget to re-sign the frameworks in `ZoomSDK` and please don't re-sign the files in `Plugins`. 
2. Due to the enhanced security requirements added in Mac OS 10.14, if you are planning to use Mac OS SDK in Mac OS 10.14 or above, please add **Camera** and **Microphone** privacy settings in your `.plist` file.
3. **Unfortunately, our Mac OS SDK does not support Xcode 11 at this point. Please do not compile and build your application with Xcode 11. We are working on the Xcode 11 support and it is a priority for us. Pardon the inconvenience. Until then, please use Xcode 10 and here are the options for installing or using Xcode 10:**
   * [Working with multiple versions of Xcode](https://medium.com/@hacknicity/working-with-multiple-versions-of-xcode-e331c01aa6bc).  Make sure to follow instructions carefully, before launching for the first time.
   * Use a [hosted service](https://support.macincloud.com/support/solutions/articles/8000042681-how-to-utilize-a-different-xcode-version-for-build-process-on-mac) supporting [many versions of Xcode](https://support.macincloud.com/support/solutions/articles/8000023177-versions-of-tools-and-applications-on-vsts-agent-plan-servers-).
5. Please be aware that some of our interfaces are deprecated in the latest release, please check out our [CHANGELOG](https://github.com/zoom/zoom-sdk-macos/blob/master/CHANGELOG.md) for more detail
6. Our brand new [Zoom Developer Community Forum](https://devforum.zoom.us/) is now online!!! Check it out! We are here to help! :D

## Full Documentation && Community Support
You can find the full Zoom MacOS SDK documentation and the community support forum here:
<div align="center">
   <a target="_blank" href="https://marketplace.zoom.us/docs/sdk/native-sdks/macos" style="text-decoration:none">
   <img src="https://s3-us-west-1.amazonaws.com/sdk.zoom.us/Doc-button.png" width="350px" max-height="350px" style="margin:1vh 1vw;"/>
   </a>
   <a target="_blank" href="https://devforum.zoom.us/c/desktop-sdk" style="text-decoration:none">
   <img src="https://s3-us-west-1.amazonaws.com/sdk.zoom.us/Forum-button.png" width="350px" max-height="350px" style="margin:1vh 1vw;"/>
   </a>
</div>

## What is Zoom Mac SDK?
Zoom SDK makes it easy to integrate Zoom with your MacOS applications, and boosts up your applications with the power of Zoom.

* **Easy to use**: Our SDK is built to be easy to use. Just import the libraries, call a few functions, and we will take care all video conferencing related stuffs for you.
* **Localizable**: Our SDK naturally supports 7 major languages, and you can add more to grow your applications internationally.
* **Custom Meeting UI**: If you want to add your own decorations to your Zoom meeting rooms, try our Custom UI feature to make your meeting room special.

## Disclaimer

**Please be aware that all hard-coded variables and constants shown in the documentation and in the demo, such as Zoom Token, Zoom Access, Token, etc., are ONLY FOR DEMO AND TESTING PURPOSES. We STRONGLY DISCOURAGE the way of HARDCODING any Zoom Credentials (username, password, API Keys & secrets, SDK keys & secrets, etc.) or any Personal Identifiable Information (PII) inside your application. WE DON’T MAKE ANY COMMITMENTS ABOUT ANY LOSS CAUSED BY HARD-CODING CREDENTIALS OR SENSITIVE INFORMATION INSIDE YOUR APP WHEN DEVELOPING WITH OUR SDK**.

## Getting Started

The following instructions will get you a copy of the project up and running on your local machine for development and testing purposes.
* For detailed instructions, please refer to our documentation website: [https://marketplace.zoom.us/docs/sdk/native-sdks/macos](https://marketplace.zoom.us/docs/sdk/native-sdks/macos);
* If you need support or assistance, please visit our [Zoom Developer Community Forum](https://devforum.zoom.us/);

### Prerequisites

Before you try out our SDK, you would need the following to get started:

* **A Zoom Account**: If you do not have one, you can sign up at [https://zoom.us/signup](https://zoom.us/signup).
  * Once you have your Zoom Account, sign up for a 60-days free trial at [https://marketplace.zoom.us/](https://marketplace.zoom.us/)
* **A device with Mac OS**:
  * OS: MacOS 10.6 or later.


### Installing

Clone or download a copy of our SDK files from GitHub. After you unzipped the file, you should have the following folders:

```
.
├── CHANGELOG.md
├── LICENSE.md
├── Plugins
├── README.md
├── SDK\ Resources
├── ZoomSDK
├── [ZoomSDKSample] <-- demo app is inside
└── version.txt
```
Once you have the files ready, please following the instructions to build and run your demo app: [https://marketplace.zoom.us/docs/sdk/native-sdks/macos](https://marketplace.zoom.us/docs/sdk/native-sdks/macos).


## Documentation

Please visit [[https://marketplace.zoom.us/docs/sdk/native-sdks/macos](https://marketplace.zoom.us/docs/sdk/native-sdks/macos)] for details of each features and functions.

## Navigating SDK sample files

The following table provides the link to the implementation of each features in our demo app:

| UI mode            | Feature                                                      | Corresponding sample files                                   |
| ------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Essential features | SDK Initialization & Authentication                          | * [ZMSDKInitHelper.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/Init/ZMSDKInitHelper.m) <br />* [ZMSDKAuthHelper.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/Auth/ZMSDKAuthHelper.m) |
|                    | Authenticate with Zoom REST API and start a meeting as API user | * [ZMSDKRestAPILogin.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/Login/ZMSDKRestAPILogin.m) <br />* [ZMSDKApiMeetingInterface.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/StartJoinMeeting/ZMSDKApiMeetingInterface.m) |
|                    | Login with email & password                                  | * [ZMSDKEmailLogin.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/Login/ZMSDKEmailLogin.m) <br />* [ZMSDKDelegateMgr.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/ZMSDKDelegateMgr.m) |
|                    | Login with SSO token                                         | * [ZMSDKSSOLogin.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/Login/ZMSDKSSOLogin.m) <br />* [ZMSDKDelegateMgr.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/ZMSDKDelegateMgr.m) |
|                    | Start an instant meeting(For Logged-in user)                 | * [ZMSDKEmailMeetingInterface.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/StartJoinMeeting/ZMSDKEmailMeetingInterface.m) <br />* [ZMSDKSSOMeetingInterface.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/StartJoinMeeting/ZMSDKSSOMeetingInterface.m) |
|                    | Join a meeting                                               | * [ZMSDKJoinOnly.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/Login/ZMSDKJoinOnly.m) |
|                    | Schedule a meeting (For logged-in user)                      | * [ZMSDKScheduleWindowCtr.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/UI%20Interface/ZoomSDKScheduleWindowCtr.m) |
|                    | Settings                                                     | * [ZMSDKSettingWindowController.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/UI%20Interface/ZMSDKSettingWindowController.m) |
| Custom UI          | Video view                                                   | * [ZMSDKMeetingMainWindowController.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/UI%20Interface/ZMSDKMeetingMainWindowController.m) |
|                    | Thumbnail View                                               | * [ZMSDKThumbnailView.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/UI%20Interface/ZMSDKThumbnailView.m) <br />* [ZMSDKThumbnailVideoItemView.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/ZMSDKThumbnailVideoItemView.m) |
|                    | Share View                                                   | * [ZMSDKShareSelectWindow.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/UI%20Interface/ZMSDKShareSelectWindow.m) |
|                    | Panelist View                                                | * [ZMSDKHCPanelistsView.m](https://github.com/zoom/zoom-sdk-macos/blob/master/ZoomSDKSample/ZoomSDKSample/UI%20Interface/ZMSDKHCPanelistsView.m) |

## SDK Reference

You may find the SDK interface reference at [https://marketplace.zoom.us/docs/sdk/native-sdks/macos/sdk-reference](https://marketplace.zoom.us/docs/sdk/native-sdks/macos/sdk-reference).
If you would like to get a local copy of the SDK reference, you may [download it here](https://github.com/zoom/zoom-sdk-macos/archive/gh-pages.zip).

## Versioning

For the versions available, see the [tags on this repository](https://github.com/zoom/zoom-sdk-macos/tags).

## Change log

Please refer to our [CHANGELOG](https://github.com/zoom/zoom-sdk-macos/blob/master/CHANGELOG.md) for all changes.

## Frequently Asked Questions (FAQ)
* 1️⃣ `SDK_Transcode.app`, `airhost.app`, and `aomhost.app` must be rebuilt with support for the Hardened Runtime...
  * When you are deploying your app with Zoom macos SDK, please don't forget to re-sign the frameworks in `ZoomSDK`. Append your own credentials onto the frameworks and try again.
* Please visit our [Zoom Developer Community Forum](https://devforum.zoom.us/) for further assistance.
* :two: `Unexpeceted service error: build aborted due to an internal error: unable to write manifest to ....: No such file or directory`
* Please change the Project settings at: File -> Project Settings -> Build Systems -> Legacy Build System and try again.

## Support

For any issues regarding our SDK, please visit our new Community Support Forum at https://devforum.zoom.us/.

## License

Use of this software is subject to important terms and conditions as set forth in the License file

Please refer to [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* :star: If you like our SDK, please give us a "Star". Your support is what keeps us moving forward and delivering happiness to you! Thanks a million! :smiley:
* If you need any support or assistance, we are here to help you: [Zoom Developer Community Forum](https://devforum.zoom.us/);

---
Copyright ©2020 Zoom Video Communications, Inc. All rights reserved.
