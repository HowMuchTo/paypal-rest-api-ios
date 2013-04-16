//
//  PayPal.h
//  HowMuchTo
//
//  Communicate with the PayPal REST API to store credit card tokens.
//  Requires AFNetworking.
//
//  Created by Marc Chambers on 4/15/13.
//
//  Copyright (c) 2013 HowMuchTo, Inc. 
//  http://howmuch.to
//  
//  Permission is hereby granted, free of charge, to any person obtaining
//  a copy of this software and associated documentation files (the
//  "Software"), to deal in the Software without restriction, including
//  without limitation the rights to use, copy, modify, merge, publish,
//  distribute, sublicense, and/or sell copies of the Software, and to
//  permit persons to whom the Software is furnished to do so, subject to
//  the following conditions:
//  
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
//  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
//  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#import <Foundation/Foundation.h>
#import "AFNetworking.h"

@interface PayPalCard : NSObject

@property (nonatomic, retain) NSString* number;
@property (nonatomic, retain) NSString* type;
@property (nonatomic, assign) int expiresMonth;
@property (nonatomic, assign) int expiresYear;
@property (nonatomic, assign) NSString* cvv2;
@property (nonatomic, retain) NSString* firstName;
@property (nonatomic, retain) NSString* lastName;
@property (nonatomic, retain) NSString* cardID;

@end

extern NSString* const kPayPalAPILiveEnvironment;
extern NSString* const kPayPalAPISandboxEnvironment;

@interface PayPal : NSObject

@property (nonatomic, retain) NSString* environment;
@property (nonatomic, retain) NSString* clientID;
@property (nonatomic, retain) NSString* clientSecret;
@property (nonatomic, retain) NSString* accessToken;

@property (nonatomic, retain) AFHTTPClient* client;

-(void)storeCard:(PayPalCard*)card completion:(void (^)(PayPalCard* storedCard))completion failure:(void (^)(NSError* error))failure;
-(void)connectWithID:(NSString*)cid andSecret:(NSString*)secret completion:(void(^)(NSString* accessToken))completion failure:(void(^)(NSError* error))failure;

@end
