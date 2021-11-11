//
//  AppDelegate.h
//  VPNKicker
//
//  Created by Toshimi Ataku on 2020/05/26.
//  Copyright © 2020 Toshimi Ataku. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (weak) IBOutlet NSTextField *vpnUsername;
@property (weak) IBOutlet NSSecureTextField *vpnPassword;
@property (weak) IBOutlet NSSecureTextField *otpPassphrase;

@property (weak) IBOutlet NSButton *doGetChallenge;
@property (weak) IBOutlet NSButton *doCaliculate;
@property (weak) IBOutlet NSButton *doConnect;

@end

