#import <UIKit/UIKit.h>
#import "Conversation.h"

NS_ASSUME_NONNULL_BEGIN

@interface ChatViewController : UIViewController

@property (nonatomic, strong, nullable) Conversation *currentConversation;
@property (nonatomic, strong) UITableView *chatTableView;
@property (nonatomic, strong) UITextField *messageTextField;
@property (nonatomic, strong) UIButton *sendButton;

- (instancetype)initWithConversation:(Conversation *)conversation;

@end

NS_ASSUME_NONNULL_END 