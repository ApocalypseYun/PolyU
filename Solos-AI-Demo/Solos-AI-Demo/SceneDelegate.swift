//
//  SceneDelegate.swift
//  Solos-AI-Demo
//
//  Created by 刘冠中 on 2025/6/26.
//

import UIKit

class SceneDelegate: UIResponder, UIWindowSceneDelegate {

    var window: UIWindow?

    func scene(_ scene: UIScene, willConnectTo session: UISceneSession, options connectionOptions: UIScene.ConnectionOptions) {
        // Use this method to optionally configure and attach the UIWindow `window` to the provided UIWindowScene `scene`.
        // If using a storyboard, the `window` property will automatically be initialized and attached to the scene.
        // This delegate does not imply the connecting scene or session are new (see `application:configurationForConnectingSceneSession` instead).
        
        print("Scene正在连接")
        
        guard let windowScene = (scene as? UIWindowScene) else { 
            print("无法获取windowScene")
            return 
        }
        
        // 确保窗口被正确创建（如果使用storyboard，这通常会自动处理）
        if window == nil {
            print("手动创建窗口")
            window = UIWindow(windowScene: windowScene)
            
            // 从storyboard加载初始视图控制器
            let storyboard = UIStoryboard(name: "Main", bundle: nil)
            if let rootViewController = storyboard.instantiateInitialViewController() {
                window?.rootViewController = rootViewController
                window?.makeKeyAndVisible()
                print("窗口配置完成")
            } else {
                print("无法从storyboard加载初始视图控制器")
            }
        } else {
            print("窗口已存在")
        }
    }

    func sceneDidDisconnect(_ scene: UIScene) {
        // Called as the scene is being released by the system.
        // This occurs shortly after the scene enters the background, or when its session is discarded.
        // Release any resources associated with this scene that can be re-created the next time the scene connects.
        // The scene may re-connect later, as its session was not necessarily discarded (see `application:didDiscardSceneSessions` instead).
        print("Scene断开连接")
    }

    func sceneDidBecomeActive(_ scene: UIScene) {
        // Called when the scene has moved from an inactive state to an active state.
        // Use this method to restart any tasks that were paused (or not yet started) when the scene was inactive.
        print("Scene变为活跃状态")
    }

    func sceneWillResignActive(_ scene: UIScene) {
        // Called when the scene will move from an active state to an inactive state.
        // This may occur due to temporary interruptions (ex. an incoming phone call).
        print("Scene将变为非活跃状态")
    }

    func sceneWillEnterForeground(_ scene: UIScene) {
        // Called as the scene transitions from the background to the foreground.
        // Use this method to undo the changes made on entering the background.
        print("Scene进入前台")
    }

    func sceneDidEnterBackground(_ scene: UIScene) {
        // Called as the scene transitions from the foreground to the background.
        // Use this method to save data, release shared resources, and store enough scene-specific state information
        // to restore the scene back to its current state.
        print("Scene进入后台")
    }
}

