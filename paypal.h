//
//  PayPal.h
//  HowMuchTo
//
//  Communicate with the PayPal REST API to store credit card tokens.
//  Requires AFNetworking.
//
//  Created by Marc Chambers on 4/15/13.
//  Copyright (c) 2013 HowMuchTo, Inc. All rights reserved.
//

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
