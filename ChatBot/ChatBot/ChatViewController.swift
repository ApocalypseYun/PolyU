import UIKit

class ChatViewController: UIViewController {
    private let tableView = UITableView()
    private let messageInputView = UIView()
    private let messageTextField = UITextField()
    private let sendButton = UIButton(type: .system)
    
    var currentConversation: Conversation?
    private var messages: [Message] = []
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupUI()
        setupKeyboardHandling()
        
        if currentConversation == nil {
            currentConversation = Conversation(title: "新对话 \(Date().formatted())")
        }
        
        messages = currentConversation?.messages ?? []
        tableView.reloadData()
    }
    
    private func setupUI() {
        // 设置导航栏
        title = currentConversation?.title ?? "新对话"
        navigationController?.navigationBar.prefersLargeTitles = false
        
        // 设置表格视图
        tableView.translatesAutoresizingMaskIntoConstraints = false
        tableView.delegate = self
        tableView.dataSource = self
        tableView.register(MessageCell.self, forCellReuseIdentifier: "MessageCell")
        tableView.separatorStyle = .none
        tableView.keyboardDismissMode = .interactive
        tableView.backgroundColor = .systemBackground
        tableView.contentInset = UIEdgeInsets(top: 8, left: 0, bottom: 8, right: 0)
        view.addSubview(tableView)
        
        // 设置输入视图
        messageInputView.translatesAutoresizingMaskIntoConstraints = false
        messageInputView.backgroundColor = .systemBackground
        messageInputView.layer.borderWidth = 0.5
        messageInputView.layer.borderColor = UIColor.systemGray4.cgColor
        view.addSubview(messageInputView)
        
        // 设置输入框
        messageTextField.translatesAutoresizingMaskIntoConstraints = false
        messageTextField.placeholder = "输入消息..."
        messageTextField.borderStyle = .roundedRect
        messageTextField.backgroundColor = .systemGray6
        messageTextField.font = .systemFont(ofSize: 16)
        messageTextField.delegate = self
        messageInputView.addSubview(messageTextField)
        
        // 设置发送按钮
        sendButton.translatesAutoresizingMaskIntoConstraints = false
        sendButton.setTitle("发送", for: .normal)
        sendButton.titleLabel?.font = .systemFont(ofSize: 16, weight: .medium)
        sendButton.addTarget(self, action: #selector(sendMessage), for: .touchUpInside)
        messageInputView.addSubview(sendButton)
        
        // 设置约束
        NSLayoutConstraint.activate([
            // 表格视图约束
            tableView.topAnchor.constraint(equalTo: view.topAnchor),
            tableView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            tableView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            tableView.bottomAnchor.constraint(equalTo: messageInputView.topAnchor),
            
            // 输入视图约束
            messageInputView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            messageInputView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            messageInputView.bottomAnchor.constraint(equalTo: view.bottomAnchor),
            messageInputView.heightAnchor.constraint(equalToConstant: 60),
            
            // 输入框约束
            messageTextField.leadingAnchor.constraint(equalTo: messageInputView.leadingAnchor, constant: 16),
            messageTextField.topAnchor.constraint(equalTo: messageInputView.topAnchor, constant: 10),
            messageTextField.bottomAnchor.constraint(equalTo: messageInputView.bottomAnchor, constant: -10),
            messageTextField.trailingAnchor.constraint(equalTo: sendButton.leadingAnchor, constant: -8),
            
            // 发送按钮约束
            sendButton.trailingAnchor.constraint(equalTo: messageInputView.trailingAnchor, constant: -16),
            sendButton.centerYAnchor.constraint(equalTo: messageInputView.centerYAnchor),
            sendButton.widthAnchor.constraint(equalToConstant: 44),
            sendButton.heightAnchor.constraint(equalToConstant: 40)
        ])
    }
    
    private func setupKeyboardHandling() {
        NotificationCenter.default.addObserver(
            self,
            selector: #selector(keyboardWillShow),
            name: UIResponder.keyboardWillShowNotification,
            object: nil
        )
        NotificationCenter.default.addObserver(
            self,
            selector: #selector(keyboardWillHide),
            name: UIResponder.keyboardWillHideNotification,
            object: nil
        )
    }
    
    @objc private func keyboardWillShow(_ notification: Notification) {
        guard let keyboardFrame = notification.userInfo?[UIResponder.keyboardFrameEndUserInfoKey] as? CGRect else { return }
        let keyboardHeight = keyboardFrame.height
        
        UIView.animate(withDuration: 0.3) {
            self.messageInputView.transform = CGAffineTransform(translationX: 0, y: -keyboardHeight)
        }
    }
    
    @objc private func keyboardWillHide(_ notification: Notification) {
        UIView.animate(withDuration: 0.3) {
            self.messageInputView.transform = .identity
        }
    }
    
    @objc private func sendMessage() {
        guard let text = messageTextField.text?.trimmingCharacters(in: .whitespacesAndNewlines),
              !text.isEmpty else { return }
        
        let message = Message(content: text, isUser: true)
        currentConversation?.addMessage(message)
        messages.append(message)
        
        messageTextField.text = ""
        tableView.reloadData()
        scrollToBottom()
        
        // 模拟AI回复
        DispatchQueue.main.asyncAfter(deadline: .now() + 1) {
            let aiMessage = Message(content: "这是一个模拟的AI回复消息。", isUser: false)
            self.currentConversation?.addMessage(aiMessage)
            self.messages.append(aiMessage)
            self.tableView.reloadData()
            self.scrollToBottom()
        }
    }
    
    private func scrollToBottom() {
        guard !messages.isEmpty else { return }
        let lastIndex = IndexPath(row: messages.count - 1, section: 0)
        tableView.scrollToRow(at: lastIndex, at: .bottom, animated: true)
    }
}

// MARK: - UITableViewDataSource
extension ChatViewController: UITableViewDataSource {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return messages.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "MessageCell", for: indexPath) as! MessageCell
        let message = messages[indexPath.row]
        cell.configure(with: message)
        return cell
    }
}

// MARK: - UITableViewDelegate
extension ChatViewController: UITableViewDelegate {
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return UITableView.automaticDimension
    }
}

// MARK: - UITextFieldDelegate
extension ChatViewController: UITextFieldDelegate {
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        sendMessage()
        return true
    }
} 