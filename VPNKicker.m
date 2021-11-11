//
//  VPNKicker.m
//  VPNKicker
//
//  Created by Toshimi Ataku on 2020/05/26.
//  Copyright © 2020 Toshimi Ataku. All rights reserved.
//

#import "VPNKicker.h"
#import "dotkeyux.h"
#import <stdlib.h>
#import <unistd.h>

@implementation VPNKicker

+ (void)initialize {
   // Register the preference defaults early.
    id keys[] = {
        @"vpnId",
        @"vpnPassword",
        @"vpnSitePwd",
        @"cmdCurl",
        @"pathToIdFile",
    };
    id objs[] = {
        @"",
        @"",
        @"",
        @"https://%@:%@@vpnweb.exa-corp.co.jp/webotp/dsp_challenge.php",
        @"/usr/local/etc/openvpn/XXXXX-XX.user"
    };
    int dictSize = sizeof(keys) / sizeof(keys[0]) > sizeof(objs) / sizeof(objs[0]) ? sizeof(objs) / sizeof(objs[0]) : sizeof(keys) / sizeof(keys[0]);
    int go = 1;

    NSDictionary *dict = [NSDictionary dictionaryWithObjects:objs forKeys:keys count: dictSize];
    NSUserDefaults *pref = [NSUserDefaults standardUserDefaults];
    if (go)
        [pref registerDefaults:dict];
}

- (void)awakeFromNib {
    NSUserDefaults *pref = [NSUserDefaults standardUserDefaults];
    NSDictionary *dict = [pref dictionaryRepresentation];
    [dict enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) {
        if ([key compare:@"vpnId"] == NSOrderedSame) {
            _dlgVpnId.stringValue = obj;
        } else if ([key compare:@"vpnPassword"] == NSOrderedSame) {
            _dlgVpnPassword.stringValue = obj;
        } else if ([key compare:@"vpnSitePwd"] == NSOrderedSame) {
            _dlgVpnSitePwd.stringValue = obj;
        } else if ([key compare:@"cmdCurl"] == NSOrderedSame) {
            _dlgCmdCurl.stringValue = obj;
        } else if ([key compare:@"pathToIdFile"] == NSOrderedSame) {
            _dlgPathToIdFile.stringValue = obj;
        }
    }];
}

NSRange skipToNextToken(NSString *body, NSString *sstr, NSRange range)
{
    NSRange rng;
    rng = [body rangeOfString:sstr options:NSCaseInsensitiveSearch range:range];
    if (rng.location == NSNotFound)
        return rng;
    range.length -= rng.location - range.location;
    range.location = rng.location;
    NSLog(@"%@", [body substringWithRange:range]);
    
    return range;
}

id extractChallengeValue(NSData *_dt, NSURLResponse *_resp, NSError *error)
{
    // 真面目にやるには
    // 1. _respからContent-Typeのcharsetに対応するencodingを調べ
    // 2. NSStringを作成する
    // としなければならない
    id data = [[NSString alloc] initWithBytes:[_dt bytes] length:[_dt length] encoding:NSJapaneseEUCStringEncoding];
    NSLog(@"%@", _resp);
    // 1. skip to <body>
    // 2. skip to </table>
    // 3. skip to <table>
    // 4. skip to <table>
    // 5. skip to <tr
    // 6. skip to <tr
    // 7. skip to <td
    // 8. skip to <td
    // 9. skip to >
    // 10. next-char
    // 11. mark
    // 12. skip to </td>
    // 13. pick mark-current

    NSRange rng, beg, end;
    id d2;

    beg.location = 0;
    beg.length = [data length];
    beg = skipToNextToken(data, @"</table>", beg);
    if (beg.location == NSNotFound)
        return nil;
    
    beg.location++;
    beg.length--;
    beg = skipToNextToken(data, @"<table",beg);
    if (beg.location == NSNotFound)
        return nil;

    beg.location++;
    beg.length--;
    beg = skipToNextToken(data, @"<table", beg);
    if (beg.location == NSNotFound)
        return nil;

    beg.location++;
    beg.length--;
    beg = skipToNextToken(data, @"<tr", beg);
    if (beg.location == NSNotFound)
        return nil;

    beg.location++;
    beg.length--;
    beg = skipToNextToken(data, @"<tr", beg);
    if (beg.location == NSNotFound)
        return nil;

    beg.location++;
    beg.length--;
    beg = skipToNextToken(data, @"<td", beg);
    if (beg.location == NSNotFound)
        return nil;

    beg.location++;
    beg.length--;
    beg = skipToNextToken(data, @"<td", beg);
    if (beg.location == NSNotFound)
        return nil;

    beg.location++;
    beg.length--;
    beg = skipToNextToken(data, @">", beg);
    if (beg.location == NSNotFound)
        return nil;

    beg.location += 1;
    beg.length -= 1;
    end = beg;

    end = skipToNextToken(data, @"</td>", end);
    if (end.location == NSNotFound)
        return nil;

    rng.location = beg.location;
    rng.length = end.location - beg.location;
    d2 = [data substringWithRange:rng];

    return d2;
}

id comphandler(id data, id resp, id err) {
    return data;
}
- (IBAction)doGetChallenge:(id)sender {
    id user = [_dlgVpnId stringValue];
    id passwd = [_dlgVpnPassword stringValue];
    NSLog(@"CmdCurl:%@", [_dlgCmdCurl stringValue]);
    NSLog(@"User:%@", user);
    NSLog(@"Password:%@", passwd);

    _challenge.stringValue = @"";  // Clear contents
    id url = [NSURL
              URLWithString:
              [[NSString alloc] initWithFormat:[_dlgCmdCurl stringValue], user, passwd ]
              ];
    NSURLSessionDataTask *dtask = [[NSURLSession sharedSession] dataTaskWithURL:url completionHandler:
                                   ^(NSData *_dt, NSURLResponse *_resp, NSError *error) {
        if (_dt == nil) {
            NSLog(@"%@", error);
            return;
        }
        NSLog(@"DataLen=%lu", (unsigned long)[_dt length]);
        NSString *data = [[NSString alloc] initWithBytes:[_dt bytes] length:[_dt length] encoding:NSJapaneseEUCStringEncoding];
//        NSLog(@"%@", _resp);
//        NSLog(@"%@", data);
        NSString *challengeValue = extractChallengeValue(_dt, _resp, error);
        dispatch_async(dispatch_get_main_queue(), ^{
            [self doGotChallenge:challengeValue];
        });
    }];
    NSLog(@"Resume");
    [dtask resume];
//    _challenge.stringValue = @"XXX";
}

- (IBAction)doGotChallenge:(id)sender {
    if (sender != nil) {
        NSLog(@"%@", sender);
        _challenge.stringValue = sender;
    }
    [self doCaliculate:self];
}

- (IBAction)doCaliculate:(id)sender {
    char pass[ONETIME_KEY_MAX_LEN + 1];
    
    NSLog(@"[%@]", [_dlgVpnId stringValue]);
    NSLog(@"[%@]", [_dlgVpnPassword stringValue]);
    NSLog(@"[%@]", [_challenge stringValue]);
    NSLog(@"[%@]", [_dlgVpnSitePwd stringValue]);
    if (genOTP(pass, [_challenge stringValue].UTF8String, [_dlgVpnSitePwd stringValue].UTF8String)) {
        NSLog(@"KeyCrunchFunc failed");
        return;
    }
    _vpnOTP.stringValue = [[NSString string] initWithUTF8String: pass];
}

int writeIdInfo(const char *path, const char *user, const char *pwd)
{
    FILE *fp;
    if ((fp = fopen(path, "w")) == NULL)
        return 0;
    fprintf(fp, "%s\n%s\n", user, pwd);
    fclose(fp);
    return 1;
}

void runVPN(const char *config)
{
    pid_t pid;
    int fds[2];
    enum { READEND = 0, WRITEEND = 1 };
    
    if (pipe(fds) < 0) {
        perror("pipe");
        return;
    }
    if ((pid = fork()) < 0) {
        perror("fork");
        return;
    }
    if (pid == 0) {         // Child proc
        close(fds[READEND]);
        if (dup2(fds[WRITEEND], 1) != 1) {
            return;
        }
        close(fds[WRITEEND]);
        const char *fmt = "sudo /usr/local/sbin/openvpn --config /usr/local/etc/openvpn/client-ivpn-win10.ovpn 2>&1";
        char *cmd = malloc(strlen(fmt) + strlen(config) + 1);
        if (cmd) {
            sprintf(cmd, fmt, config);
            system(cmd);
        }
        free(cmd);
    } else {                // Parent proc
        char bf[1];
        ssize_t sz;
        int c;
        FILE *fp;

        close(fds[WRITEEND]);
        if ((fp = fopen("/Users/ataku/Downloads/openvpn.log", "w")) == NULL)
            return;
        while ((sz = read(fds[READEND], bf, 1)) > 0) {
            c = bf[0];
            fputc(c, fp);
            fflush(fp);
        }
        fclose(fp);
        close(fds[WRITEEND]);
    }
}

- (IBAction)doConnect:(id)sender {
    id user = [_dlgVpnId stringValue];
    id vpnotp = [_vpnOTP stringValue];
    if (!writeIdInfo([_dlgPathToIdFile stringValue].UTF8String,
                    [user cStringUsingEncoding:NSUTF8StringEncoding],
                    [vpnotp cStringUsingEncoding:NSUTF8StringEncoding]))
        return;
    runVPN("");
}

- (IBAction)doDlgSave:(id)sender {
    NSLog(@"[%@]", [_dlgVpnId stringValue]);
    NSLog(@"[%@]", [_dlgVpnSitePwd stringValue]);
    NSUserDefaults *pref = [NSUserDefaults standardUserDefaults];
    [pref setObject:[_dlgVpnId stringValue] forKey:@"vpnId"];
    [pref setObject:[_dlgVpnPassword stringValue] forKey:@"vpnPassword"];
    [pref setObject:[_dlgVpnSitePwd stringValue] forKey:@"vpnSitePwd"];
    [pref setObject:[_dlgCmdCurl stringValue] forKey:@"cmdCurl"];
    [pref setObject:[_dlgPathToIdFile stringValue] forKey:@"pathToIdFile"];

    [_dlgPrefs performClose:sender];
}
@end
