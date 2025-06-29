//
//  GPTService.swift
//  Solos-AI-Demo
//
//  Created by 刘冠中 on 2025/6/26.
//

import Foundation
import UIKit

class GPTService {
    static let shared = GPTService()
    
    // 请替换为您的实际 OpenAI API Key
    private let apiKey = ""
    private let baseURL = "https://api.openai.com/v1/chat/completions"
    
    private init() {}
    
    // 支持UIImage的异步方法
    func analyzeImage(_ image: UIImage) async throws -> String {
        guard let imageData = image.jpegData(compressionQuality: 0.8) else {
            throw GPTError.imageConversionFailed
        }
        return try await analyzeImage(imageData)
    }
    
    // 支持Data的异步方法
    func analyzeImage(_ imageData: Data) async throws -> String {
        let base64Image = imageData.base64EncodedString()
        
        let requestBody: [String: Any] = [
            "model": "gpt-4o",
            "messages": [
                [
                    "role": "user",
                    "content": [
                        [
                            "type": "text",
                            "text": "请详细描述这张图片中的内容，包括物体、人物、场景、颜色、动作等。请用中文回答。"
                        ],
                        [
                            "type": "image_url",
                            "image_url": [
                                "url": "data:image/jpeg;base64,\(base64Image)"
                            ]
                        ]
                    ]
                ]
            ],
            "max_tokens": 500
        ]
        
        guard let url = URL(string: baseURL) else {
            throw GPTError.invalidURL
        }
        
        var request = URLRequest(url: url)
        request.httpMethod = "POST"
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.setValue("Bearer \(apiKey)", forHTTPHeaderField: "Authorization")
        
        do {
            request.httpBody = try JSONSerialization.data(withJSONObject: requestBody)
        } catch {
            throw error
        }
        
        let (data, response) = try await URLSession.shared.data(for: request)
        
        // 添加调试信息
        print("OpenAI API Response Status: \((response as? HTTPURLResponse)?.statusCode ?? 0)")
        
        do {
            // 首先尝试解析为JSON
            guard let json = try JSONSerialization.jsonObject(with: data) as? [String: Any] else {
                print("Failed to parse JSON response")
                if let responseString = String(data: data, encoding: .utf8) {
                    print("Raw response: \(responseString)")
                }
                throw GPTError.invalidResponse
            }
            
            // 检查是否有错误
            if let error = json["error"] as? [String: Any],
               let message = error["message"] as? String {
                print("OpenAI API Error: \(message)")
                throw GPTError.apiError(message)
            }
            
            // 解析正常响应
            if let choices = json["choices"] as? [[String: Any]],
               let firstChoice = choices.first,
               let message = firstChoice["message"] as? [String: Any],
               let content = message["content"] as? String {
                return content
            } else {
                print("Invalid response structure: \(json)")
                throw GPTError.invalidResponse
            }
        } catch let error as GPTError {
            throw error
        } catch {
            print("JSON parsing error: \(error)")
            throw error
        }
    }
    
    // 保留原有的回调方法以兼容性
    func analyzeImage(_ image: UIImage, completion: @escaping (Result<String, Error>) -> Void) {
        guard let imageData = image.jpegData(compressionQuality: 0.8) else {
            completion(.failure(GPTError.imageConversionFailed))
            return
        }
        
        let base64Image = imageData.base64EncodedString()
        
        let requestBody: [String: Any] = [
            "model": "gpt-4o",
            "messages": [
                [
                    "role": "user",
                    "content": [
                        [
                            "type": "text",
                            "text": "请详细描述这张图片中的内容，包括物体、人物、场景、颜色、动作等。请用中文回答。"
                        ],
                        [
                            "type": "image_url",
                            "image_url": [
                                "url": "data:image/jpeg;base64,\(base64Image)"
                            ]
                        ]
                    ]
                ]
            ],
            "max_tokens": 500
        ]
        
        guard let url = URL(string: baseURL) else {
            completion(.failure(GPTError.invalidURL))
            return
        }
        
        var request = URLRequest(url: url)
        request.httpMethod = "POST"
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.setValue("Bearer \(apiKey)", forHTTPHeaderField: "Authorization")
        
        do {
            request.httpBody = try JSONSerialization.data(withJSONObject: requestBody)
        } catch {
            completion(.failure(error))
            return
        }
        
        URLSession.shared.dataTask(with: request) { data, response, error in
            if let error = error {
                DispatchQueue.main.async {
                    completion(.failure(error))
                }
                return
            }
            
            guard let data = data else {
                DispatchQueue.main.async {
                    completion(.failure(GPTError.noData))
                }
                return
            }
            
            do {
                // 首先尝试解析为JSON
                guard let json = try JSONSerialization.jsonObject(with: data) as? [String: Any] else {
                    print("Failed to parse JSON response")
                    if let responseString = String(data: data, encoding: .utf8) {
                        print("Raw response: \(responseString)")
                    }
                    DispatchQueue.main.async {
                        completion(.failure(GPTError.invalidResponse))
                    }
                    return
                }
                
                // 检查是否有错误
                if let error = json["error"] as? [String: Any],
                   let message = error["message"] as? String {
                    print("OpenAI API Error: \(message)")
                    DispatchQueue.main.async {
                        completion(.failure(GPTError.apiError(message)))
                    }
                    return
                }
                
                // 解析正常响应
                if let choices = json["choices"] as? [[String: Any]],
                   let firstChoice = choices.first,
                   let message = firstChoice["message"] as? [String: Any],
                   let content = message["content"] as? String {
                    
                    DispatchQueue.main.async {
                        completion(.success(content))
                    }
                } else {
                    print("Invalid response structure: \(json)")
                    DispatchQueue.main.async {
                        completion(.failure(GPTError.invalidResponse))
                    }
                }
            } catch {
                print("JSON parsing error: \(error)")
                DispatchQueue.main.async {
                    completion(.failure(error))
                }
            }
        }.resume()
    }
}

enum GPTError: LocalizedError {
    case imageConversionFailed
    case invalidURL
    case noData
    case invalidResponse
    case apiError(String)
    
    var errorDescription: String? {
        switch self {
        case .imageConversionFailed:
            return "图片转换失败"
        case .invalidURL:
            return "无效的URL"
        case .noData:
            return "没有收到数据"
        case .invalidResponse:
            return "响应格式无效"
        case .apiError(let message):
            return "API错误: \(message)"
        }
    }
} 