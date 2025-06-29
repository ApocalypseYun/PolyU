# Solos AI Demo

这是一个基于 SolosAirGoSDK 开发的 iOS 演示应用，展示了如何使用 Solos 智能眼镜进行拍照并通过 GPT 进行图像识别分析。

## 功能特性

🔗 **智能设备连接**
- 自动检测 Solos 智能眼镜连接状态
- 蓝牙扫描和设备选择
- 连接状态实时显示

📸 **智能拍照**
- 远程控制智能眼镜拍照
- 实时图像预览
- 高质量图像传输

🤖 **AI 图像识别**
- 集成 GPT-4 Vision 模型
- 智能图像内容分析
- 中文描述生成

## 环境要求

- iOS 15.0 或更高版本
- Xcode 14.0 或更高版本
- Solos 智能眼镜设备
- 有效的 OpenAI API Key

## 安装配置

### 1. 克隆项目
```bash
git clone [项目地址]
cd Solos-AI-Demo
```

### 2. 配置 OpenAI API Key
打开 `GPTService.swift` 文件，找到以下行：
```swift
private let apiKey = "YOUR_OPENAI_API_KEY"
```
将 `YOUR_OPENAI_API_KEY` 替换为您的实际 OpenAI API Key。

### 3. 添加 SDK 框架
确保 `SolosAirGoSDK.framework` 已正确添加到项目中，并在项目设置中设置为 "Embed & Sign"。

### 4. 权限配置
应用已预配置了必要的权限：
- 蓝牙使用权限
- 麦克风使用权限  
- 相机使用权限
- 照片库访问权限

## 使用方法

### 1. 启动应用
- 打开应用后会自动检查设备连接状态
- 如果未连接设备，会弹出连接提醒

### 2. 连接设备
- 点击"扫描设备"按钮
- 从设备列表中选择您的 Solos 智能眼镜
- 等待连接成功

### 3. 拍照识别
- 确保设备连接成功（状态显示为"✅ 设备已连接"）
- 点击"📸 智能拍照"按钮
- 等待拍照完成和 AI 分析
- 查看图像和 AI 生成的描述

## 界面说明

- **连接状态标签**：显示当前设备连接状态
- **拍照按钮**：大型按钮，用于触发拍照功能
- **图像预览区**：显示拍摄的照片
- **结果文本区**：显示 AI 分析结果
- **加载指示器**：显示处理进度

## 故障排除

### 设备连接问题
- 确保蓝牙已开启
- 检查 Solos 设备是否处于可连接状态
- 重启应用重新扫描

### 拍照失败
- 检查设备连接状态
- 确保设备有足够电量
- 检查网络连接

### GPT 分析失败
- 检查 API Key 是否正确配置
- 确保网络连接正常
- 检查 OpenAI 服务状态

## API 配置说明

### OpenAI API Key 获取
1. 访问 [OpenAI Platform](https://platform.openai.com/)
2. 注册并登录账户
3. 在 API Keys 页面创建新的 API Key
4. 将 API Key 复制到 `GPTService.swift` 中

### 模型配置
当前使用的是 `gpt-4-vision-preview` 模型，您可以根据需要在 `GPTService.swift` 中修改：
```swift
"model": "gpt-4-vision-preview"
```

## 项目结构

```
Solos-AI-Demo/
├── ViewController.swift          # 主界面控制器
├── BluetoothManager.swift        # 蓝牙设备管理
├── GPTService.swift             # GPT API 服务
├── Main.storyboard              # 界面布局
├── Info.plist                   # 应用配置
└── SolosAirGoSDK.framework/     # SDK 框架
```

## 版本信息

- **应用版本**：1.0.0
- **SDK 版本**：SolosAirGoSDK v3.3.1
- **支持 iOS 版本**：15.0+

## 开发者信息

- 开发者：刘冠中
- 创建日期：2025年6月26日
- 基于：SolosAirGoSDK v3.3.1

## 许可证

本项目仅供学习和演示用途。使用前请确保遵守相关的 SDK 许可协议和 OpenAI 使用条款。

---

如有问题或建议，请联系开发团队。 