#import "Conversation.h"

@implementation Conversation

+ (instancetype)conversationWithTitle:(NSString *)title {
    Conversation *conversation = [[Conversation alloc] init];
    conversation.title = title;
    conversation.createdAt = [NSDate date];
    conversation.messages = [NSMutableArray array];
    return conversation;
}

- (void)addMessage:(Message *)message {
    [self.messages addObject:message];
    [self saveToUserDefaults];
}

- (void)saveToUserDefaults {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSMutableArray *conversations = [[defaults arrayForKey:@"conversations"] mutableCopy] ?: [NSMutableArray array];
    
    // 将当前对话转换为可存储的格式
    NSMutableDictionary *conversationDict = [NSMutableDictionary dictionary];
    conversationDict[@"title"] = self.title;
    conversationDict[@"createdAt"] = self.createdAt;
    
    NSMutableArray *messagesArray = [NSMutableArray array];
    for (Message *message in self.messages) {
        [messagesArray addObject:@{
            @"content": message.content,
            @"isUser": @(message.isUser),
            @"timestamp": message.timestamp
        }];
    }
    conversationDict[@"messages"] = messagesArray;
    
    // 查找并更新或添加对话
    BOOL found = NO;
    for (NSInteger i = 0; i < conversations.count; i++) {
        NSDictionary *dict = conversations[i];
        if ([dict[@"title"] isEqualToString:self.title]) {
            conversations[i] = conversationDict;
            found = YES;
            break;
        }
    }
    
    if (!found) {
        [conversations addObject:conversationDict];
    }
    
    [defaults setObject:conversations forKey:@"conversations"];
    [defaults synchronize];
}

+ (NSArray<Conversation *> *)loadAllConversations {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *conversationsArray = [defaults arrayForKey:@"conversations"] ?: @[];
    
    NSMutableArray *conversations = [NSMutableArray array];
    for (NSDictionary *dict in conversationsArray) {
        Conversation *conversation = [[Conversation alloc] init];
        conversation.title = dict[@"title"];
        conversation.createdAt = dict[@"createdAt"];
        
        NSMutableArray *messages = [NSMutableArray array];
        for (NSDictionary *messageDict in dict[@"messages"]) {
            Message *message = [Message messageWithContent:messageDict[@"content"]
                                                  isUser:[messageDict[@"isUser"] boolValue]];
            message.timestamp = messageDict[@"timestamp"];
            [messages addObject:message];
        }
        conversation.messages = messages;
        
        [conversations addObject:conversation];
    }
    
    // 按创建时间排序
    return [conversations sortedArrayUsingComparator:^NSComparisonResult(Conversation *conv1, Conversation *conv2) {
        return [conv2.createdAt compare:conv1.createdAt];
    }];
}

+ (void)deleteConversation:(Conversation *)conversation {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSMutableArray *conversations = [[defaults arrayForKey:@"conversations"] mutableCopy] ?: [NSMutableArray array];
    
    [conversations removeObjectAtIndex:[conversations indexOfObjectPassingTest:^BOOL(NSDictionary *dict, NSUInteger idx, BOOL *stop) {
        return [dict[@"title"] isEqualToString:conversation.title];
    }]];
    
    [defaults setObject:conversations forKey:@"conversations"];
    [defaults synchronize];
}

@end 