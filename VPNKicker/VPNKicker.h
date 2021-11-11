//
//  VPNKicker.h
//  VPNKicker
//
//  Created by Toshimi Ataku on 2020/05/26.
//  Copyright © 2020 Toshimi Ataku. All rights reserved.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPNKicker : NSApplication

@property (weak) IBOutlet NSTextField *vpnId;
@property (weak) IBOutlet NSSecureTextField *vpnPassword;
@property (weak) IBOutlet NSSecureTextField *otpPassPhrase;

- (IBAction)doGetChallenge:(id)sender;
- (IBAction)doCaliculateOTP:(id)sender;
- (IBAction)doConnect:(id)sender;

@end

NS_ASSUME_NONNULL_END
