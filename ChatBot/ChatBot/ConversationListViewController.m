#import "ConversationListViewController.h"
#import "ChatViewController.h"
#import "Conversation.h"

@interface ConversationListViewController () <UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) NSArray<Conversation *> *conversations;

@end

@implementation ConversationListViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"对话列表";
    self.view.backgroundColor = [UIColor systemBackgroundColor];
    
    // 设置导航栏按钮
    self.createButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAdd
                                                                     target:self
                                                                     action:@selector(createNewChat)];
    self.navigationItem.rightBarButtonItem = self.createButton;
    
    // 设置表格视图
    self.tableView = [[UITableView alloc] init];
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    self.tableView.backgroundColor = [UIColor systemBackgroundColor];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"ConversationCell"];
    [self.view addSubview:self.tableView];
    
    // 设置约束
    self.tableView.translatesAutoresizingMaskIntoConstraints = NO;
    [NSLayoutConstraint activateConstraints:@[
        [self.tableView.topAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.topAnchor],
        [self.tableView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor],
        [self.tableView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor],
        [self.tableView.bottomAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.bottomAnchor]
    ]];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self loadConversations];
}

- (void)loadConversations {
    self.conversations = [Conversation loadAllConversations];
    [self.tableView reloadData];
}

- (void)createNewChat {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"新对话"
                                                                 message:@"请输入对话标题"
                                                          preferredStyle:UIAlertControllerStyleAlert];
    
    [alert addTextFieldWithConfigurationHandler:^(UITextField *textField) {
        textField.placeholder = @"对话标题";
    }];
    
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"取消"
                                                          style:UIAlertActionStyleCancel
                                                        handler:nil];
    
    UIAlertAction *createAction = [UIAlertAction actionWithTitle:@"创建"
                                                          style:UIAlertActionStyleDefault
                                                        handler:^(UIAlertAction *action) {
        NSString *title = alert.textFields.firstObject.text;
        if (title.length > 0) {
            Conversation *newConversation = [Conversation conversationWithTitle:title];
            ChatViewController *chatVC = [[ChatViewController alloc] initWithConversation:newConversation];
            [self.navigationController pushViewController:chatVC animated:YES];
        }
    }];
    
    [alert addAction:cancelAction];
    [alert addAction:createAction];
    [self presentViewController:alert animated:YES completion:nil];
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.conversations.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ConversationCell" forIndexPath:indexPath];
    Conversation *conversation = self.conversations[indexPath.row];
    
    // 设置单元格内容
    cell.textLabel.text = conversation.title;
    
    // 设置时间
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    formatter.dateStyle = NSDateFormatterMediumStyle;
    formatter.timeStyle = NSDateFormatterShortStyle;
    cell.detailTextLabel.text = [formatter stringFromDate:conversation.createdAt];
    
    // 设置样式
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    return cell;
}

#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    Conversation *conversation = self.conversations[indexPath.row];
    ChatViewController *chatVC = [[ChatViewController alloc] initWithConversation:conversation];
    [self.navigationController pushViewController:chatVC animated:YES];
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        Conversation *conversation = self.conversations[indexPath.row];
        [Conversation deleteConversation:conversation];
        [self loadConversations];
    }
}

@end 