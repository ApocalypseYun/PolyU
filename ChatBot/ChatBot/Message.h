#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface Message : NSObject

@property (nonatomic, strong) NSString *content;
@property (nonatomic, assign) BOOL isUser;
@property (nonatomic, strong) NSDate *timestamp;

+ (instancetype)messageWithContent:(NSString *)content isUser:(BOOL)isUser;

@end

NS_ASSUME_NONNULL_END 