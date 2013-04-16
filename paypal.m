//
//  PayPal.m
//  HowMuchTo
//
//  Created by Marc Chambers on 4/15/13.
//  Copyright (c) 2013 HowMuchTo, Inc. All rights reserved.
//

#import "PayPal.h"

@implementation PayPalCard : NSObject

@end

@implementation PayPal

NSString* const kPayPalAPILiveEnvironment = @"https://api.paypal.com/v1/";
NSString* const kPayPalAPISandboxEnvironment = @"https://api.sandbox.paypal.com/v1/";

-(id)init
{
    self.environment=kPayPalAPISandboxEnvironment;
    self.clientSecret=nil;
    self.clientID=nil;
    self.accessToken=nil;
    
    return self;
}

-(void)connectWithID:(NSString*)cid andSecret:(NSString*)secret completion:(void(^)(NSString* accessToken))completion failure:(void(^)(NSError* error))failure
{
    self.clientID=cid;
    self.clientSecret=secret;
    
    self.client=[AFHTTPClient clientWithBaseURL:[NSURL URLWithString:self.environment]];
    
    [self.client registerHTTPOperationClass:[AFJSONRequestOperation class]];
    [self.client setDefaultHeader:@"Accept" value:@"application/json"];
    [self.client setDefaultHeader:@"Accept-Language" value:@"en"];
    [self.client setAuthorizationHeaderWithUsername:self.clientID password:self.clientSecret];
    
    [self.client postPath:@"oauth2/token" parameters:@{@"grant_type":@"client_credentials"} success:^(AFHTTPRequestOperation *operation, id responseObject) {
        NSLog(@"Received PayPal access token");
        self.accessToken=[responseObject objectForKey:@"access_token"];
        [self.client setDefaultHeader:@"Authorization" value:[NSString stringWithFormat:@"Bearer %@", self.accessToken]];
        [self.client setParameterEncoding:AFJSONParameterEncoding];
        completion(self.accessToken);
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        NSLog(@"Failed to get PayPal access token %@", error);
        self.client=nil;
        failure(error);
    }];
}

-(void)storeCard:(PayPalCard*)card completion:(void (^)(PayPalCard* storedCard))completion failure:(void (^)(NSError* error))failure
{
    static BOOL recurseProtect=NO;
    
    if(self.client==nil)
    {
        // authenticate first, then
        // recurse back into storeCard if succeeds
        
        // fail out if they haven't connected OR provided an ID+secret
        if(self.clientID==nil || self.clientSecret==nil)
        {
            failure(nil);
            return;
        }
        
        // auth with PayPal
        [self connectWithID:self.clientID andSecret:self.clientSecret completion:^(NSString *accessToken) {
            [self storeCard:card completion:completion failure:failure];
        } failure:^(NSError *error) {
            failure(error);
        }];
        
        return;
    }
    
    // create the dictionary and store the card info
    NSMutableDictionary* cardParams=[NSMutableDictionary dictionary];
    
    if(card.number!=nil)
        [cardParams setValue:card.number forKey:@"number"];
    if(card.type!=nil)
        [cardParams setValue:card.type forKey:@"type"];
    if(card.expiresMonth>0)
        [cardParams setValue:[NSNumber numberWithInt:card.expiresMonth] forKey:@"expire_month"];
    
    if(card.expiresYear>0 && card.expiresYear<1000)
    {
        // prob. 2 digit year
        card.expiresYear=card.expiresYear+2000;
    }
    
    if(card.expiresYear>0)
        [cardParams setValue:[NSNumber numberWithInt:card.expiresYear] forKey:@"expire_year"];
    if(card.cvv2!=nil)
        [cardParams setValue:card.cvv2 forKey:@"cvv2"];
    
    //
    // HACK: SEND CVV2 AS INTEGER
    // PAYPAL IS FIXING THIS BUG ON 4/18/13
    //
    [cardParams setValue:@([card.cvv2 intValue]) forKey:@"cvv2"];
    // END CVV2 INT HACK
    
    [self.client postPath:@"vault/credit-card" parameters:cardParams success:^(AFHTTPRequestOperation *operation, id responseObject) {
        PayPalCard* responseCard=[[PayPalCard alloc] init];
        
        responseCard.number=[responseObject objectForKey:@"number"];
        responseCard.cardID=[responseObject objectForKey:@"id"];
        
        completion(responseCard);
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        failure(error);
    }];
}

@end
