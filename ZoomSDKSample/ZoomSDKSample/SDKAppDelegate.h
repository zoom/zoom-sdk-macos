//
//  SDKAppDelegate.h
//  ZoomSDKSample
//
//  Created by TOTTI on 2018/11/19.
//  Copyright © 2018 zoom.us. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
@class ZMSDKLoginWindowController;
@interface SDKAppDelegate : NSObject<NSApplicationDelegate>
{
    IBOutlet NSMenuItem*   _logOutMenuItem;
}
@property(nonatomic, retain)ZMSDKLoginWindowController* loginWindowCtrl;

-(IBAction)logout:(id)sender;
@end
