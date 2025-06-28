import Foundation

class Conversation {
    let title: String
    var createdAt: Date
    var messages: [Message]
    
    init(title: String) {
        self.title = title
        self.createdAt = Date()
        self.messages = []
    }
    
    func addMessage(_ message: Message) {
        messages.append(message)
        saveToUserDefaults()
    }
    
    func saveToUserDefaults() {
        let defaults = UserDefaults.standard
        var conversations = defaults.array(forKey: "conversations") as? [[String: Any]] ?? []
        
        // 将当前对话转换为可存储的格式
        var conversationDict: [String: Any] = [:]
        conversationDict["title"] = title
        conversationDict["createdAt"] = createdAt
        
        let messagesArray = messages.map { message -> [String: Any] in
            return [
                "content": message.content,
                "isUser": message.isUser,
                "timestamp": message.timestamp
            ]
        }
        conversationDict["messages"] = messagesArray
        
        // 查找并更新或添加对话
        if let index = conversations.firstIndex(where: { ($0["title"] as? String) == title }) {
            conversations[index] = conversationDict
        } else {
            conversations.append(conversationDict)
        }
        
        defaults.set(conversations, forKey: "conversations")
        defaults.synchronize()
    }
    
    static func loadAllConversations() -> [Conversation] {
        let defaults = UserDefaults.standard
        let conversationsArray = defaults.array(forKey: "conversations") as? [[String: Any]] ?? []
        
        let conversations = conversationsArray.compactMap { dict -> Conversation? in
            guard let title = dict["title"] as? String,
                  let createdAt = dict["createdAt"] as? Date,
                  let messagesArray = dict["messages"] as? [[String: Any]] else {
                return nil
            }
            
            let conversation = Conversation(title: title)
            conversation.createdAt = createdAt
            
            conversation.messages = messagesArray.compactMap { messageDict -> Message? in
                guard let content = messageDict["content"] as? String,
                      let isUser = messageDict["isUser"] as? Bool,
                      let timestamp = messageDict["timestamp"] as? Date else {
                    return nil
                }
                
                let message = Message(content: content, isUser: isUser)
                message.timestamp = timestamp
                return message
            }
            
            return conversation
        }
        
        // 按创建时间排序
        return conversations.sorted { $0.createdAt > $1.createdAt }
    }
    
    static func deleteConversation(_ conversation: Conversation) {
        let defaults = UserDefaults.standard
        var conversations = defaults.array(forKey: "conversations") as? [[String: Any]] ?? []
        
        conversations.removeAll { ($0["title"] as? String) == conversation.title }
        
        defaults.set(conversations, forKey: "conversations")
        defaults.synchronize()
    }
} 