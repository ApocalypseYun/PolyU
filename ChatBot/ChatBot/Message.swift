import Foundation

class Message {
    let content: String
    let isUser: Bool
    var timestamp: Date
    
    init(content: String, isUser: Bool) {
        self.content = content
        self.isUser = isUser
        self.timestamp = Date()
    }
    
    static func message(content: String, isUser: Bool) -> Message {
        return Message(content: content, isUser: isUser)
    }
} 
