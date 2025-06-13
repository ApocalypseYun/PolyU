#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^CompletionHandler)(NSString * _Nullable response, NSError * _Nullable error);

@interface NetworkManager : NSObject

+ (instancetype)sharedManager;

- (void)sendMessage:(NSString *)message
        completion:(CompletionHandler)completion;

@end

NS_ASSUME_NONNULL_END 