#import "ChatViewController.h"
#import "SettingsViewController.h"
#import "NetworkManager.h"
#import "MessageCell.h"

@interface ChatViewController () <UITableViewDelegate, UITableViewDataSource, UITextFieldDelegate>

@end

@implementation ChatViewController

- (instancetype)initWithConversation:(Conversation *)conversation {
    self = [super init];
    if (self) {
        self.currentConversation = conversation;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = self.currentConversation.title;
    self.view.backgroundColor = [UIColor systemBackgroundColor];
    
    // 设置导航栏按钮
    UIBarButtonItem *settingsButton = [[UIBarButtonItem alloc] initWithImage:[UIImage systemImageNamed:@"gear"]
                                                                       style:UIBarButtonItemStylePlain
                                                                      target:self
                                                                      action:@selector(openSettings)];
    self.navigationItem.rightBarButtonItem = settingsButton;
    
    // 添加返回按钮
    UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithImage:[UIImage systemImageNamed:@"list.bullet"]
                                                                   style:UIBarButtonItemStylePlain
                                                                  target:self
                                                                  action:@selector(backToList)];
    self.navigationItem.leftBarButtonItem = backButton;
    
    // 设置聊天表格视图
    self.chatTableView = [[UITableView alloc] init];
    self.chatTableView.delegate = self;
    self.chatTableView.dataSource = self;
    self.chatTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    self.chatTableView.backgroundColor = [UIColor systemBackgroundColor];
    [self.chatTableView registerClass:[MessageCell class] forCellReuseIdentifier:@"MessageCell"];
    [self.view addSubview:self.chatTableView];
    
    // 设置输入框和发送按钮
    UIView *inputView = [[UIView alloc] init];
    inputView.backgroundColor = [UIColor systemGray6Color];
    [self.view addSubview:inputView];
    
    self.messageTextField = [[UITextField alloc] init];
    self.messageTextField.placeholder = @"输入消息...";
    self.messageTextField.borderStyle = UITextBorderStyleRoundedRect;
    self.messageTextField.delegate = self;
    [inputView addSubview:self.messageTextField];
    
    self.sendButton = [UIButton buttonWithType:UIButtonTypeSystem];
    [self.sendButton setTitle:@"发送" forState:UIControlStateNormal];
    [self.sendButton addTarget:self action:@selector(sendMessage) forControlEvents:UIControlEventTouchUpInside];
    [inputView addSubview:self.sendButton];
    
    // 设置约束
    self.chatTableView.translatesAutoresizingMaskIntoConstraints = NO;
    inputView.translatesAutoresizingMaskIntoConstraints = NO;
    self.messageTextField.translatesAutoresizingMaskIntoConstraints = NO;
    self.sendButton.translatesAutoresizingMaskIntoConstraints = NO;
    
    [NSLayoutConstraint activateConstraints:@[
        [self.chatTableView.topAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.topAnchor],
        [self.chatTableView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor],
        [self.chatTableView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor],
        [self.chatTableView.bottomAnchor constraintEqualToAnchor:inputView.topAnchor],
        
        [inputView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor],
        [inputView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor],
        [inputView.bottomAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.bottomAnchor],
        [inputView.heightAnchor constraintEqualToConstant:60],
        
        [self.messageTextField.leadingAnchor constraintEqualToAnchor:inputView.leadingAnchor constant:16],
        [self.messageTextField.centerYAnchor constraintEqualToAnchor:inputView.centerYAnchor],
        [self.messageTextField.trailingAnchor constraintEqualToAnchor:self.sendButton.leadingAnchor constant:-8],
        
        [self.sendButton.trailingAnchor constraintEqualToAnchor:inputView.trailingAnchor constant:-16],
        [self.sendButton.centerYAnchor constraintEqualToAnchor:inputView.centerYAnchor],
        [self.sendButton.widthAnchor constraintEqualToConstant:60]
    ]];
}

#pragma mark - Actions

- (void)backToList {
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)openSettings {
    SettingsViewController *settingsVC = [[SettingsViewController alloc] init];
    [self.navigationController pushViewController:settingsVC animated:YES];
}

- (void)sendMessage {
    NSString *message = self.messageTextField.text;
    if (message.length > 0) {
        Message *userMessage = [Message messageWithContent:message isUser:YES];
        [self.currentConversation addMessage:userMessage];
        [self.chatTableView reloadData];
        self.messageTextField.text = @"";
        
        // 滚动到底部
        NSIndexPath *lastIndexPath = [NSIndexPath indexPathForRow:self.currentConversation.messages.count - 1 inSection:0];
        [self.chatTableView scrollToRowAtIndexPath:lastIndexPath atScrollPosition:UITableViewScrollPositionBottom animated:YES];
        
        [[NetworkManager sharedManager] sendMessage:message completion:^(NSString * _Nullable response, NSError * _Nullable error) {
            if (error) {
                UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"错误"
                                                                             message:error.localizedDescription
                                                                      preferredStyle:UIAlertControllerStyleAlert];
                UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"确定"
                                                                  style:UIAlertActionStyleDefault
                                                                handler:nil];
                [alert addAction:okAction];
                [self presentViewController:alert animated:YES completion:nil];
                return;
            }
            
            if (response) {
                Message *aiMessage = [Message messageWithContent:response isUser:NO];
                [self.currentConversation addMessage:aiMessage];
                [self.chatTableView reloadData];
                
                // 滚动到底部
                NSIndexPath *lastIndexPath = [NSIndexPath indexPathForRow:self.currentConversation.messages.count - 1 inSection:0];
                [self.chatTableView scrollToRowAtIndexPath:lastIndexPath atScrollPosition:UITableViewScrollPositionBottom animated:YES];
            }
        }];
    }
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.currentConversation.messages.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    MessageCell *cell = [tableView dequeueReusableCellWithIdentifier:@"MessageCell" forIndexPath:indexPath];
    Message *message = self.currentConversation.messages[indexPath.row];
    [cell configureWithMessage:message];
    return cell;
}

#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [self sendMessage];
    return YES;
}

@end 