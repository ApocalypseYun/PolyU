//
//  ViewController.swift
//  Solos-AI-Demo
//
//  Created by 刘冠中 on 2025/6/26.
//

import UIKit
import SolosAirGoSDK
import Combine

class ViewController: UIViewController {
    
    // MARK: - UI Elements
    @IBOutlet weak var connectionStatusLabel: UILabel!
    @IBOutlet weak var captureButton: UIButton!
    @IBOutlet weak var imageView: UIImageView!
    @IBOutlet weak var resultTextView: UITextView!
    @IBOutlet weak var loadingIndicator: UIActivityIndicatorView!
    
    // MARK: - Properties
    private let bluetoothManager = BluetoothManager.shared
    private let gptService = GPTService.shared
    private var cancellables = Set<AnyCancellable>()
    private var isProcessing = false
    private var isShowingAlert = false // 防止重复弹窗
    
    // MARK: - Lifecycle
    override func viewDidLoad() {
        super.viewDidLoad()
        setupUI()
        setupObservers()
        checkInitialConnection()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        // 每次视图出现时检查连接状态
        checkInitialConnection()
    }
    
    // MARK: - UI Setup
    private func setupUI() {
        title = "Solos AI Demo"
        
        // 设置连接状态标签
        connectionStatusLabel.text = "检查设备连接状态..."
        connectionStatusLabel.textColor = .systemOrange
        connectionStatusLabel.textAlignment = .center
        connectionStatusLabel.numberOfLines = 0
        
        // 设置拍照按钮
        captureButton.setTitle("📸 拍照分析", for: .normal)
        captureButton.backgroundColor = .systemGreen
        captureButton.setTitleColor(.white, for: .normal)
        captureButton.layer.cornerRadius = 25
        captureButton.titleLabel?.font = UIFont.systemFont(ofSize: 24, weight: .bold)
        captureButton.isEnabled = false
        
        // 设置图像视图
        imageView.contentMode = .scaleAspectFit
        imageView.backgroundColor = .systemGray6
        imageView.layer.cornerRadius = 12
        imageView.clipsToBounds = true
        
        // 设置结果文本视图
        resultTextView.text = "点击拍照按钮开始体验 AI 图像识别功能\n\n1. 确保您的 Solos 智能眼镜已开启并连接\n2. 点击上方的拍照按钮\n3. 等待 AI 分析图片内容\n4. 查看详细的图像描述结果"
        resultTextView.isEditable = false
        resultTextView.font = UIFont.systemFont(ofSize: 16)
        resultTextView.layer.cornerRadius = 10
        resultTextView.layer.borderWidth = 1
        resultTextView.layer.borderColor = UIColor.systemGray4.cgColor
        
        // 设置加载指示器
        loadingIndicator.hidesWhenStopped = true
        loadingIndicator.style = .large
    }
    
    private func setupObservers() {
        // 观察连接状态变化
        bluetoothManager.$isConnected
            .receive(on: DispatchQueue.main)
            .sink { [weak self] isConnected in
                self?.updateConnectionStatus(isConnected: isConnected)
            }
            .store(in: &cancellables)
        
        // 观察连接状态文本变化
        bluetoothManager.$connectionState
            .receive(on: DispatchQueue.main)
            .sink { [weak self] state in
                self?.connectionStatusLabel.text = state
            }
            .store(in: &cancellables)
        
        // 移除扫描状态观察，因为当前UI中没有单独的扫描按钮
    }
    

    
    private func checkInitialConnection() {
        DispatchQueue.main.asyncAfter(deadline: .now() + 1.0) {
            if !self.bluetoothManager.isConnected {
                self.showConnectionAlert()
            }
        }
    }
    
    private func updateConnectionStatus(isConnected: Bool) {
        captureButton.isEnabled = isConnected
        captureButton.backgroundColor = isConnected ? .systemGreen : .systemGray
        
        connectionStatusLabel.textColor = isConnected ? .systemGreen : .systemRed
        
        // 移除自动弹窗，只在用户主动操作时显示连接提示
        // if !isConnected {
        //     showConnectionAlert()
        // }
    }
    
    private func updateScanButton(isScanning: Bool) {
        // 暂时移除扫描按钮的更新逻辑，因为当前UI中没有单独的扫描按钮
        // 扫描功能通过连接弹窗来处理
    }
    
    private func showConnectionAlert() {
        // 防止重复弹窗
        guard !isShowingAlert, presentedViewController == nil else {
            return
        }
        
        isShowingAlert = true
        
        let alert = UIAlertController(
            title: "设备未连接",
            message: "请确保您的SolosAirGo眼镜已开启并在附近，然后点击扫描设备进行连接。",
            preferredStyle: .alert
        )
        
        alert.addAction(UIAlertAction(title: "扫描设备", style: .default) { _ in
            self.isShowingAlert = false
            self.startDeviceScanning()
        })
        
        alert.addAction(UIAlertAction(title: "取消", style: .cancel) { _ in
            self.isShowingAlert = false
        })
        
        present(alert, animated: true)
    }
    
    private func showBluetoothAlert() {
        let alert = UIAlertController(
            title: "蓝牙未开启",
            message: "请在设置中开启蓝牙后重试。",
            preferredStyle: .alert
        )
        
        alert.addAction(UIAlertAction(title: "去设置", style: .default) { _ in
            if let settingsURL = URL(string: UIApplication.openSettingsURLString) {
                UIApplication.shared.open(settingsURL)
            }
        })
        
        alert.addAction(UIAlertAction(title: "取消", style: .cancel))
        
        present(alert, animated: true)
    }
    
    private func startDeviceScanning() {
        // 检查蓝牙状态
        guard bluetoothManager.checkBluetoothStatus() else {
            showBluetoothAlert()
            return
        }
        
        bluetoothManager.startScanning()
        
        // 5秒后停止扫描并显示结果
        DispatchQueue.main.asyncAfter(deadline: .now() + 5.0) {
            self.bluetoothManager.stopScanning()
            self.showDeviceList(devices: self.bluetoothManager.devices)
        }
    }
    
    private func showDeviceList(devices: [SolosGlasses]) {
        if devices.isEmpty {
            let alert = UIAlertController(
                title: "未找到设备",
                message: "请确保您的SolosAirGo眼镜已开启并在附近。",
                preferredStyle: .alert
            )
            alert.addAction(UIAlertAction(title: "重新扫描", style: .default) { _ in
                self.startDeviceScanning()
            })
            alert.addAction(UIAlertAction(title: "取消", style: .cancel))
            present(alert, animated: true)
            return
        }
        
        let alert = UIAlertController(
            title: "选择设备",
            message: "发现 \(devices.count) 个设备，请选择要连接的设备：",
            preferredStyle: .alert
        )
        
        for device in devices {
            alert.addAction(UIAlertAction(title: device.name, style: .default) { _ in
                self.connectToDevice(device)
            })
        }
        
        alert.addAction(UIAlertAction(title: "取消", style: .cancel))
        
        present(alert, animated: true)
    }
    
    private func connectToDevice(_ device: SolosGlasses) {
        connectionStatusLabel.text = "正在连接到 \(device.name)..."
        connectionStatusLabel.textColor = .systemOrange
        
        bluetoothManager.connect(to: device)
    }
    
    // 移除了scanButtonTapped，因为当前UI中没有单独的扫描按钮
    
    @IBAction func captureButtonTapped(_ sender: UIButton) {
        guard bluetoothManager.isConnected else {
            showConnectionAlert()
            return
        }
        
        Task {
            await captureAndAnalyzePhoto()
        }
    }
    
    private func captureAndAnalyzePhoto() async {
        DispatchQueue.main.async {
            self.loadingIndicator.startAnimating()
            self.captureButton.isEnabled = false
            self.resultTextView.text = "正在拍照..."
        }
        
        // 拍照
        guard let imageData = await bluetoothManager.capturePhoto() else {
            DispatchQueue.main.async {
                self.loadingIndicator.stopAnimating()
                self.captureButton.isEnabled = true
                self.resultTextView.text = "拍照失败，请重试"
            }
            return
        }
        
        // 显示图片
        DispatchQueue.main.async {
            self.imageView.image = UIImage(data: imageData)
            self.resultTextView.text = "正在分析图片..."
        }
        
        // GPT分析
        do {
            let analysis = try await gptService.analyzeImage(imageData)
            DispatchQueue.main.async {
                self.resultTextView.text = analysis
                self.loadingIndicator.stopAnimating()
                self.captureButton.isEnabled = true
            }
        } catch {
            DispatchQueue.main.async {
                self.resultTextView.text = "分析失败: \(error.localizedDescription)"
                self.loadingIndicator.stopAnimating()
                self.captureButton.isEnabled = true
            }
        }
    }
    
    deinit {
        // 在deinit中不能捕获self，所以需要在主线程上同步执行清理
        let manager = bluetoothManager
        DispatchQueue.main.async {
            manager.stopScanning()
            manager.disconnect()
        }
    }
}

