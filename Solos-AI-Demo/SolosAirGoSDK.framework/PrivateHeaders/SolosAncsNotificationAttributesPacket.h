//
//  SolosAncsNotificationAttributesPacket.h
//  GaiaControl
//
//  Created by Sam Yu on 17/9/2022.
//

#import <Foundation/Foundation.h>


@interface SolosAncsNotificationAttributesPacket : NSObject
- (void) appendPayload : (NSData *) data;
- (BOOL) isCompleted;
- (NSString *) getAppId;
- (NSString *) getTitle;
- (NSString *) getMessage;
- (NSString *) getDate;
@end

