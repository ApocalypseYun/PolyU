//
//  CSRGaiaTransport.h
//  CordovaPlugins
//
//  Created by Sam Yu on 3/10/2022.
//

#import <Foundation/Foundation.h>
#import "GaiaLibrary.h"

NS_ASSUME_NONNULL_BEGIN

@protocol CSRGaiaTransportDelegate <NSObject>
@optional
- (void)didReceiveResponse:(CSRGaiaGattCommand *_Nonnull)command;
@end

@interface CSRGaiaTransport : NSObject
- (id) initWithPeriperal:(CBPeripheral *)peripheral
   commandCharacteristic:(CBCharacteristic *)commandCharacteristic
       connectionManager: (CSRConnectionManager *) connectionManager;
- (void) uninit;
- (void) setDelegate:(id<CSRGaiaTransportDelegate>) delegate;
- (void) sendCommand:(GaiaCommandType)cmd vendor: (uint16_t)vendorId data:(NSData *)payload;
- (void) sendCommand:(GaiaCommandType)cmd vendor: (uint16_t)vendorId data:(NSData *)payload retryCount:(int)retryCount;
- (void)peripheral:(CBPeripheral *)peripheral
didWriteValueForCharacteristic:(CBCharacteristic *)characteristic
             error:(NSError *)error;
- (void) onReceiveResponse: (NSData *) data;
@end




NS_ASSUME_NONNULL_END
