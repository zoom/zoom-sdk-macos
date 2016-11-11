//
//  ZPAlert.h
//  ZCommonUI
//
//  Created by zoom on 13-3-11.
//  Copyright (c) 2013年 zoom. All rights reserved.
//

#import <Cocoa/Cocoa.h>
@interface ZPAlertWindow : NSWindow
- (void)invisibleInSharing;
@end

@interface ZPAlert : NSWindowController
{
    IBOutlet NSImageView*   _logoImageView;
    IBOutlet NSTextField*   _contentTextField;
    IBOutlet NSButton*      _okButton;
}
@property(nonatomic, assign) NSImageView* logoImageView;
@property(nonatomic, assign) NSTextField* contentTextField;
@property(nonatomic, assign) NSButton* okButton;

- (IBAction)onOKButtonClicked:(id)sender;


- (void)cleanUp;
@end
