#import <Foundation/Foundation.h>
#import "Message.h"

NS_ASSUME_NONNULL_BEGIN

@interface Conversation : NSObject

@property (nonatomic, strong) NSString *title;
@property (nonatomic, strong) NSDate *createdAt;
@property (nonatomic, strong) NSMutableArray<Message *> *messages;

+ (instancetype)conversationWithTitle:(NSString *)title;
- (void)addMessage:(Message *)message;
- (void)saveToUserDefaults;
+ (NSArray<Conversation *> *)loadAllConversations;
+ (void)deleteConversation:(Conversation *)conversation;

@end

NS_ASSUME_NONNULL_END 