//
//  VPNKicker.h
//  VPNKicker
//
//  Created by Toshimi Ataku on 2020/05/26.
//  Copyright © 2020 Toshimi Ataku. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Appkit/AppKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPNKicker : NSObject
@property (weak) IBOutlet NSTextField *challenge;
@property (weak) IBOutlet NSTextField *vpnOTP;

- init;
- (IBAction)doGetChallenge:(id)sender;
- (IBAction)doGotChallenge:(id)sender;
- (IBAction)doCaliculate:(id)sender;
- (IBAction)doConnect:(id)sender;

// for Preference Dialog
@property (weak) IBOutlet NSTextField *dlgVpnId;
@property (weak) IBOutlet NSSecureTextField *dlgVpnPassword;
@property (weak) IBOutlet NSTextField *dlgVpnSitePwd;
@property (weak) IBOutlet NSTextField *dlgCmdCurl;
@property (weak) IBOutlet NSTextField *dlgPathToIdFile;
@property (weak) IBOutlet NSPanel *dlgPrefs;

- (IBAction)doDlgSave:(id)sender;

@end

NS_ASSUME_NONNULL_END
