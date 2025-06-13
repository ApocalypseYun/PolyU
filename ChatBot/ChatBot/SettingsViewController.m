#import "SettingsViewController.h"

@interface SettingsViewController () <UITextFieldDelegate, UIPickerViewDelegate, UIPickerViewDataSource>

@property (nonatomic, strong) NSArray *modelOptions;
@property (nonatomic, strong) UILabel *modelLabel;

@end

@implementation SettingsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"设置";
    self.view.backgroundColor = [UIColor whiteColor];
    
    // 初始化模型选项
    self.modelOptions = @[@"gpt-4", @"gpt-3.5-turbo"];
    
    // 创建输入框
    self.apiKeyTextField = [self createTextFieldWithPlaceholder:@"输入 API Key"];
    self.baseUrlTextField = [self createTextFieldWithPlaceholder:@"输入 Base URL"];
    self.botIdentityTextField = [self createTextFieldWithPlaceholder:@"输入 AI 身份设定"];
    
    // 创建模型选择标签
    self.modelLabel = [[UILabel alloc] init];
    self.modelLabel.text = @"选择模型：";
    [self.view addSubview:self.modelLabel];
    
    // 创建模型选择器
    self.modelPickerView = [[UIPickerView alloc] init];
    self.modelPickerView.delegate = self;
    self.modelPickerView.dataSource = self;
    [self.view addSubview:self.modelPickerView];
    
    // 创建保存按钮
    self.saveButton = [UIButton buttonWithType:UIButtonTypeSystem];
    [self.saveButton setTitle:@"保存设置" forState:UIControlStateNormal];
    [self.saveButton addTarget:self action:@selector(saveSettings) forControlEvents:UIControlEventTouchUpInside];
    self.saveButton.backgroundColor = [UIColor systemBlueColor];
    [self.saveButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    self.saveButton.layer.cornerRadius = 8;
    [self.view addSubview:self.saveButton];
    
    // 设置约束
    self.apiKeyTextField.translatesAutoresizingMaskIntoConstraints = NO;
    self.baseUrlTextField.translatesAutoresizingMaskIntoConstraints = NO;
    self.botIdentityTextField.translatesAutoresizingMaskIntoConstraints = NO;
    self.modelLabel.translatesAutoresizingMaskIntoConstraints = NO;
    self.modelPickerView.translatesAutoresizingMaskIntoConstraints = NO;
    self.saveButton.translatesAutoresizingMaskIntoConstraints = NO;
    
    [NSLayoutConstraint activateConstraints:@[
        [self.apiKeyTextField.topAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.topAnchor constant:20],
        [self.apiKeyTextField.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor constant:20],
        [self.apiKeyTextField.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor constant:-20],
        [self.apiKeyTextField.heightAnchor constraintEqualToConstant:44],
        
        [self.baseUrlTextField.topAnchor constraintEqualToAnchor:self.apiKeyTextField.bottomAnchor constant:20],
        [self.baseUrlTextField.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor constant:20],
        [self.baseUrlTextField.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor constant:-20],
        [self.baseUrlTextField.heightAnchor constraintEqualToConstant:44],
        
        [self.botIdentityTextField.topAnchor constraintEqualToAnchor:self.baseUrlTextField.bottomAnchor constant:20],
        [self.botIdentityTextField.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor constant:20],
        [self.botIdentityTextField.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor constant:-20],
        [self.botIdentityTextField.heightAnchor constraintEqualToConstant:44],
        
        [self.modelLabel.topAnchor constraintEqualToAnchor:self.botIdentityTextField.bottomAnchor constant:20],
        [self.modelLabel.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor constant:20],
        [self.modelLabel.heightAnchor constraintEqualToConstant:44],
        
        [self.modelPickerView.topAnchor constraintEqualToAnchor:self.modelLabel.bottomAnchor constant:10],
        [self.modelPickerView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor constant:20],
        [self.modelPickerView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor constant:-20],
        [self.modelPickerView.heightAnchor constraintEqualToConstant:100],
        
        [self.saveButton.topAnchor constraintEqualToAnchor:self.modelPickerView.bottomAnchor constant:40],
        [self.saveButton.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor constant:20],
        [self.saveButton.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor constant:-20],
        [self.saveButton.heightAnchor constraintEqualToConstant:44]
    ]];
    
    // 加载已保存的设置
    [self loadSettings];
}

- (UITextField *)createTextFieldWithPlaceholder:(NSString *)placeholder {
    UITextField *textField = [[UITextField alloc] init];
    textField.placeholder = placeholder;
    textField.borderStyle = UITextBorderStyleRoundedRect;
    textField.delegate = self;
    [self.view addSubview:textField];
    return textField;
}

- (void)saveSettings {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults setObject:self.apiKeyTextField.text forKey:@"apiKey"];
    [defaults setObject:self.baseUrlTextField.text forKey:@"baseUrl"];
    [defaults setObject:self.botIdentityTextField.text forKey:@"botIdentity"];
    [defaults setObject:self.modelOptions[[self.modelPickerView selectedRowInComponent:0]] forKey:@"model"];
    [defaults synchronize];
    
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"成功"
                                                                 message:@"设置已保存"
                                                          preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"确定"
                                                      style:UIAlertActionStyleDefault
                                                    handler:nil];
    [alert addAction:okAction];
    [self presentViewController:alert animated:YES completion:nil];
}

- (void)loadSettings {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    self.apiKeyTextField.text = [defaults stringForKey:@"apiKey"];
    
    // 设置默认的Base URL
    NSString *baseUrl = [defaults stringForKey:@"baseUrl"];
    if (!baseUrl) {
        baseUrl = @"https://api.openai.com/v1/chat/completions";
        [defaults setObject:baseUrl forKey:@"baseUrl"];
        [defaults synchronize];
    }
    self.baseUrlTextField.text = baseUrl;
    
    self.botIdentityTextField.text = [defaults stringForKey:@"botIdentity"];
    
    // 设置默认模型
    NSString *model = [defaults stringForKey:@"model"];
    if (!model) {
        model = @"gpt-4";
        [defaults setObject:model forKey:@"model"];
        [defaults synchronize];
    }
    NSInteger modelIndex = [self.modelOptions indexOfObject:model];
    if (modelIndex != NSNotFound) {
        [self.modelPickerView selectRow:modelIndex inComponent:0 animated:NO];
    }
}

#pragma mark - UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    return self.modelOptions.count;
}

#pragma mark - UIPickerViewDelegate

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    return self.modelOptions[row];
}

#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}

@end 