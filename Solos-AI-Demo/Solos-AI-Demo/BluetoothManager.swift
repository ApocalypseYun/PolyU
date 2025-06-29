//
//  BluetoothManager.swift
//  Solos-AI-Demo
//
//  Created by 刘冠中 on 2025/6/26.
//

import Foundation
import SwiftUI
@preconcurrency import SolosAirGoSDK

@MainActor
class BluetoothManager: NSObject, ObservableObject {
    static let shared = BluetoothManager()
    
    @Published var isConnected = false
    @Published var connectionState: String = "已断开连接"
    @Published var connectedDevice: SolosGlasses?
    @Published var devices: [SolosGlasses] = []
    @Published var isScanning = false
    @Published var isCameraConnected = false
    @Published var availableCameras: [CameraReference] = []
    
    private var manager: Manager
    private var scanner: SolosAirGoSDK.Scanner
    private let scannerQueue = DispatchQueue(label: "scanner.queue")
    
    override init() {
        // 使用官方SDK的配置
        let brandConfig = BrandConfiguration.solosAirGoV
        self.manager = Manager(config: brandConfig)
        self.scanner = manager.getScanner()
        
        super.init()
        
        // 添加扫描监听器
        scanner.addScanCallbackListener(self)
    }
    
    func checkBluetoothStatus() -> Bool {
        // 简单返回true，让SDK处理蓝牙状态检查
        return true
    }
    
    func startScanning() {
        isScanning = true
        devices.removeAll()
        
        // 在独立队列中执行扫描，避免主线程隔离问题
        let currentScanner = scanner
        scannerQueue.async {
            currentScanner.startScan()
        }
    }
    
    func stopScanning() {
        isScanning = false
        
        // 在独立队列中停止扫描
        let currentScanner = scanner
        scannerQueue.async {
            currentScanner.stopScan()
        }
    }
    
    func connect(to device: SolosGlasses) {
        Task { @MainActor in
            do {
                // 添加状态变化监听器
                device.addStatusChangeListener(DeviceStatusListener(manager: self))
                
                // 添加相机可用性监听器
                device.addCameraAvailabilityListener(CameraAvailabilityListener(manager: self))
                
                // 连接设备
                try await device.connect()
                
                self.connectedDevice = device
                self.isConnected = true
                self.connectionState = "已连接到 \(device.name)"
                
                // 设备连接成功后，自动尝试连接相机
                await self.connectToCamera()
                
            } catch {
                print("连接失败: \(error.localizedDescription)")
                self.connectionState = "连接失败: \(error.localizedDescription)"
            }
        }
    }
    
    func disconnect() {
        Task { @MainActor in
            do {
                try await connectedDevice?.disconnect()
            } catch {
                print("断开连接失败: \(error.localizedDescription)")
            }
            connectedDevice = nil
            isConnected = false
            connectionState = "已断开连接"
        }
    }
    
    // MARK: - Camera Connection
    func connectToCamera() async {
        guard connectedDevice != nil else {
            print("没有连接的设备，无法连接相机")
            return
        }
        
        await MainActor.run {
            self.connectionState = "正在连接相机..."
        }
        
        // 开始扫描相机
        await scanForCameras()
        
        // 等待一段时间让扫描完成
        try? await Task.sleep(nanoseconds: 3_000_000_000) // 3秒
        
        // 尝试连接第一个找到的相机
        if let firstCamera = availableCameras.first {
            await connectToSpecificCamera(firstCamera)
        } else {
            await MainActor.run {
                print("未找到可用的相机设备")
                self.connectionState = "未找到相机设备"
            }
        }
    }
    
    func scanForCameras() async {
        guard let device = connectedDevice else { return }
        
        await MainActor.run {
            self.availableCameras.removeAll()
        }
        
        // 获取相机扫描器并开始扫描
        if let cameraScanner = device.cameraScanner {
            cameraScanner.addScanCallbackListener(CameraScanListener(manager: self))
            cameraScanner.startScan()
            
            print("开始扫描相机设备...")
        }
    }
    
    func connectToSpecificCamera(_ camera: CameraReference) async {
        do {
            await MainActor.run {
                self.connectionState = "正在连接相机 \(camera.name)..."
            }
            
            try await camera.connect()
            
            await MainActor.run {
                self.isCameraConnected = true
                self.connectionState = "相机已连接: \(camera.name)"
                print("相机连接成功: \(camera.name)")
            }
        } catch {
            await MainActor.run {
                print("相机连接失败: \(error.localizedDescription)")
                self.connectionState = "相机连接失败: \(error.localizedDescription)"
            }
        }
    }
    
    func capturePhoto() async -> Data? {
        guard let device = connectedDevice else {
            print("没有连接的设备")
            return nil
        }
        
        // 检查相机是否可用
        guard device.camera != nil else {
            print("相机不可用")
            // 尝试重新连接相机
            await connectToCamera()
            
            // 再次检查
            guard let camera = device.camera else {
                print("相机仍然不可用")
                return nil
            }
            
            // 使用第二次检查中获得的camera
            do {
                let photo = try await camera.takePhoto(resolution: ._1280_960)
                return photo.data
            } catch {
                print("拍照失败: \(error.localizedDescription)")
                return nil
            }
        }
        
        do {
            // 使用正确的API：takePhoto返回Photo类型（非可选）
            let photo = try await device.camera!.takePhoto(resolution: ._1280_960)
            return photo.data
        } catch {
            print("拍照失败: \(error.localizedDescription)")
            return nil
        }
    }
}

// 移除CBCentralManagerDelegate，使用SDK内部的蓝牙管理

// MARK: - ScanCallbackListener
extension BluetoothManager: ScanCallbackListener {
    nonisolated func onScanResult(_ glasses: SolosGlasses) {
        Task { @MainActor in
            if !self.devices.contains(where: { $0.id == glasses.id }) {
                self.devices.append(glasses)
            }
        }
    }
    
    nonisolated func onScanFailed(_ error: SolosCameraError) {
        Task { @MainActor in
            print("扫描失败: \(error.localizedDescription)")
            self.connectionState = "扫描失败: \(error.localizedDescription)"
        }
    }
}

// MARK: - DeviceStatusListener
class DeviceStatusListener: StatusChangeListener {
    weak var manager: BluetoothManager?
    
    init(manager: BluetoothManager) {
        self.manager = manager
    }
    
    nonisolated func onStatusChanged(status: GlassesStatus) {
        Task { @MainActor in
            guard let manager = self.manager else { return }
            
            switch status {
            case .connected:
                manager.isConnected = true
                manager.connectionState = "设备已连接"
            case .disconnected:
                manager.isConnected = false
                manager.connectionState = "设备已断开连接"
                manager.connectedDevice = nil
            default:
                // 只处理已知的状态
                break
            }
        }
    }
}

// MARK: - CameraAvailabilityListener
class CameraAvailabilityListener: SolosAirGoSDK.CameraAvailabilityListener {
    weak var manager: BluetoothManager?
    
    init(manager: BluetoothManager) {
        self.manager = manager
    }
    
    nonisolated func onCameraAvailabilityChanged(available: Bool) {
        Task { @MainActor in
            guard let manager = self.manager else { return }
            manager.isCameraConnected = available
            
            if available {
                print("相机现在可用")
                manager.connectionState = "相机已连接"
            } else {
                print("相机不可用")
                if manager.isConnected {
                    manager.connectionState = "设备已连接，但相机未连接"
                }
            }
        }
    }
}

// MARK: - CameraScanListener
class CameraScanListener: CameraScanCallbackListener {
    weak var manager: BluetoothManager?
    
    init(manager: BluetoothManager) {
        self.manager = manager
    }
    
    nonisolated func onScanResult(_ camera: CameraReference) {
        Task { @MainActor in
            guard let manager = self.manager else { return }
            
            print("发现相机设备: \(camera.name)")
            
            if !manager.availableCameras.contains(where: { $0.name == camera.name }) {
                manager.availableCameras.append(camera)
            }
        }
    }
} 
