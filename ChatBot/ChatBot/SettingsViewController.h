#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface SettingsViewController : UIViewController

@property (nonatomic, strong) UITextField *apiKeyTextField;
@property (nonatomic, strong) UITextField *baseUrlTextField;
@property (nonatomic, strong) UITextField *botIdentityTextField;
@property (nonatomic, strong) UIPickerView *modelPickerView;
@property (nonatomic, strong) UIButton *saveButton;

@end

NS_ASSUME_NONNULL_END 