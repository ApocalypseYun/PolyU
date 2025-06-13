#import "Message.h"

@implementation Message

+ (instancetype)messageWithContent:(NSString *)content isUser:(BOOL)isUser {
    Message *message = [[Message alloc] init];
    message.content = content;
    message.isUser = isUser;
    message.timestamp = [NSDate date];
    return message;
}

@end 