paypal-rest-api-ios
===================

Objective-C class to tokenize credit cards with the PayPal REST API from iOS.

Requirements
============

A PayPal REST API developer account.

AFNetworking included in your project.

Usage
=====

```objective-c
#import "PayPal.h"

-(void)whatever
{
     // init the PayPal API object
     // and get a blank credit card object.
     //
     PayPal* pp=[[PayPal alloc] init];
     PayPalCard* ppCardToStore=[[PayPalCard alloc] init];
     
     // Collect this card information from the customer with
     // something like PaymentKit, card.io or your own custom form.
     //
     ppCardToStore.number=@"4242424242424242";
     ppCardToStore.expiresMonth=6;
     ppCardToStore.expiresYear=2017;
     ppCardToStore.cvv2=@"123";
     
     // These credentials are from your developer portal
     // 
     pp.clientID=@"your client ID";
     pp.clientSecret=@"your client secret";

     // Storing the card is asynchronous and we use blocks to
     // catch the success or failure.
     //
     [pp storeCard:ppCardToStore completion:^(PayPalCard* storedCard) {

          // storedCard will have the id property populated
          // this is your card token, store it on your server

     } failure:^(NSError* error) {

          // check error for the reason this failed
          // there are numerous reasons; could've been a 
          // bad card, a network error, auth failure, etc.

     }];
}
```

Questions, comments, concerns? Open an issue or hit me up on Twitter (@marcchambers)


