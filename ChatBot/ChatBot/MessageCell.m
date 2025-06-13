#import "MessageCell.h"

@implementation MessageCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.backgroundColor = [UIColor clearColor];
        
        // 创建气泡视图
        self.bubbleView = [[UIView alloc] init];
        self.bubbleView.layer.cornerRadius = 12;
        [self.contentView addSubview:self.bubbleView];
        
        // 创建消息标签
        self.messageLabel = [[UILabel alloc] init];
        self.messageLabel.numberOfLines = 0;
        self.messageLabel.font = [UIFont systemFontOfSize:16];
        [self.bubbleView addSubview:self.messageLabel];
        
        // 创建时间标签
        self.timeLabel = [[UILabel alloc] init];
        self.timeLabel.font = [UIFont systemFontOfSize:12];
        self.timeLabel.textColor = [UIColor grayColor];
        [self.contentView addSubview:self.timeLabel];
        
        // 设置约束
        self.bubbleView.translatesAutoresizingMaskIntoConstraints = NO;
        self.messageLabel.translatesAutoresizingMaskIntoConstraints = NO;
        self.timeLabel.translatesAutoresizingMaskIntoConstraints = NO;
        
        [NSLayoutConstraint activateConstraints:@[
            [self.bubbleView.topAnchor constraintEqualToAnchor:self.contentView.topAnchor constant:8],
            [self.bubbleView.bottomAnchor constraintEqualToAnchor:self.contentView.bottomAnchor constant:-8],
            [self.bubbleView.widthAnchor constraintLessThanOrEqualToAnchor:self.contentView.widthAnchor multiplier:0.75],
            
            [self.messageLabel.topAnchor constraintEqualToAnchor:self.bubbleView.topAnchor constant:8],
            [self.messageLabel.bottomAnchor constraintEqualToAnchor:self.bubbleView.bottomAnchor constant:-8],
            [self.messageLabel.leadingAnchor constraintEqualToAnchor:self.bubbleView.leadingAnchor constant:12],
            [self.messageLabel.trailingAnchor constraintEqualToAnchor:self.bubbleView.trailingAnchor constant:-12],
            
            [self.timeLabel.topAnchor constraintEqualToAnchor:self.bubbleView.bottomAnchor constant:4],
            [self.timeLabel.bottomAnchor constraintEqualToAnchor:self.contentView.bottomAnchor constant:-4]
        ]];
    }
    return self;
}

- (void)configureWithMessage:(Message *)message {
    self.messageLabel.text = message.content;
    
    // 设置时间格式
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    formatter.dateFormat = @"HH:mm";
    self.timeLabel.text = [formatter stringFromDate:message.timestamp];
    
    if (message.isUser) {
        // 用户消息靠右
        [NSLayoutConstraint activateConstraints:@[
            [self.bubbleView.trailingAnchor constraintEqualToAnchor:self.contentView.trailingAnchor constant:-16],
            [self.timeLabel.trailingAnchor constraintEqualToAnchor:self.bubbleView.trailingAnchor]
        ]];
        
        self.bubbleView.backgroundColor = [UIColor systemBlueColor];
        self.messageLabel.textColor = [UIColor whiteColor];
    } else {
        // AI消息靠左
        [NSLayoutConstraint activateConstraints:@[
            [self.bubbleView.leadingAnchor constraintEqualToAnchor:self.contentView.leadingAnchor constant:16],
            [self.timeLabel.leadingAnchor constraintEqualToAnchor:self.bubbleView.leadingAnchor]
        ]];
        
        self.bubbleView.backgroundColor = [UIColor systemGray5Color];
        self.messageLabel.textColor = [UIColor blackColor];
    }
}

@end 