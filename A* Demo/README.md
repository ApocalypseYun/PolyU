# 沿墙路径规划系统

这是一个基于Flask的沿墙路径规划系统，实现了在二维网格地图中寻找沿墙行走路径的算法。系统提供了Web界面和API接口，可以在有障碍物的环境中规划从起点到终点的最优路径。

## 功能特点

- **沿墙路径规划**: 专门设计用于需要沿墙行走的场景
- **多种算法支持**: 包括严格沿墙算法、改进沿墙算法和桥接算法
- **交互式Web界面**: 可视化网格编辑和路径显示
- **RESTful API**: 支持程序化调用

## 系统要求

- Python 3.7+
- Flask
- 现代Web浏览器

## 安装和运行

1. 确保已安装Python和Flask：
```bash
pip install flask
```

2. 运行应用：
```bash
python app.py
```

3. 在浏览器中访问：`http://localhost:5000`

## API接口说明

### 路径规划接口

**端点**: `POST /find_path`

**功能**: 在给定的网格地图中计算从起点到终点的沿墙路径

#### 请求参数

请求头：
```
Content-Type: application/json
```

请求体格式：
```json
{
    "grid": [[0, 0, 1, 0], [0, 1, 1, 0], [0, 0, 0, 0], [1, 1, 1, 1]],
    "start": [0, 0],
    "end": [2, 2]
}
```

参数说明：
- `grid`: 二维数组，表示网格地图
  - `0`: 空白可通行区域
  - `1`: 障碍物/墙壁
  - `2`: 起点标记（可选）
  - `3`: 终点标记（可选）
- `start`: 数组，格式为`[行, 列]`，表示起点坐标
- `end`: 数组，格式为`[行, 列]`，表示终点坐标

#### 约束条件

1. **终点必须在墙边**: 终点必须与至少一个障碍物相邻
2. **坐标系**: 使用行列坐标系，原点(0,0)在左上角
3. **网格大小**: 建议最小5×5，支持任意大小的矩形网格

#### 响应格式

成功响应：
```json
{
    "path": [[0, 0], [0, 1], [1, 1], [2, 1], [2, 2]]
}
```

响应说明：
- `path`: 路径点数组，每个元素为`[行, 列]`坐标
- 路径按顺序排列，从起点到终点
- 如果无法找到路径，返回空数组`[]`

#### 算法说明

系统采用多层次路径规划算法：

1. **严格沿墙算法**: 优先尝试严格沿墙行走
2. **改进沿墙算法**: 允许短暂离开墙边但会尽快回到墙边
3. **桥接算法**: 处理不连通墙体之间的路径规划

### 使用示例

#### Python调用示例

```python
import requests
import json

# 设置API地址
url = "http://localhost:5000/find_path"

# 构造请求数据
data = {
    "grid": [
        [1, 1, 1, 1, 1],
        [1, 0, 0, 0, 1],
        [1, 0, 1, 0, 1],
        [1, 0, 0, 0, 1],
        [1, 1, 1, 1, 1]
    ],
    "start": [1, 1],  # 起点坐标
    "end": [3, 3]     # 终点坐标（必须在墙边）
}

# 发送POST请求
headers = {"Content-Type": "application/json"}
response = requests.post(url, data=json.dumps(data), headers=headers)

# 处理响应
if response.status_code == 200:
    result = response.json()
    path = result["path"]
    
    if path:
        print("找到路径:")
        for i, point in enumerate(path):
            print(f"步骤 {i+1}: ({point[0]}, {point[1]})")
    else:
        print("未找到可行路径")
else:
    print(f"请求失败，状态码: {response.status_code}")
```

#### JavaScript调用示例

```javascript
// 构造请求数据
const requestData = {
    grid: [
        [1, 1, 1, 1, 1],
        [1, 0, 0, 0, 1],
        [1, 0, 1, 0, 1],
        [1, 0, 0, 0, 1],
        [1, 1, 1, 1, 1]
    ],
    start: [1, 1],
    end: [3, 3]
};

// 发送API请求
fetch('/find_path', {
    method: 'POST',
    headers: {
        'Content-Type': 'application/json',
    },
    body: JSON.stringify(requestData)
})
.then(response => response.json())
.then(data => {
    const path = data.path;
    
    if (path.length > 0) {
        console.log('找到路径:', path);
        // 处理路径数据
        path.forEach((point, index) => {
            console.log(`步骤 ${index + 1}: (${point[0]}, ${point[1]})`);
        });
    } else {
        console.log('未找到可行路径');
    }
})
.catch(error => {
    console.error('请求出错:', error);
});
```

#### cURL调用示例

```bash
curl -X POST http://localhost:5000/find_path \
  -H "Content-Type: application/json" \
  -d '{
    "grid": [
      [1,1,1,1,1],
      [1,0,0,0,1],
      [1,0,1,0,1],
      [1,0,0,0,1],
      [1,1,1,1,1]
    ],
    "start": [1,1],
    "end": [3,3]
  }'
```

## Web界面使用

1. **创建网格**: 设置行数和列数，点击"Create Grid"
2. **设置起点**: 点击"Set Start"按钮，然后在网格上点击设置起点
3. **设置终点**: 点击"Set End"按钮，在墙边位置点击设置终点
4. **添加障碍物**: 点击"Add Wall/Obstacle"按钮，在网格上拖拽添加墙体
5. **寻找路径**: 点击"Find Path"按钮执行路径规划
6. **清除**: 使用相应按钮清除单元格或整个网格

## 错误处理

常见错误情况：

1. **终点不在墙边**: 确保终点坐标与至少一个障碍物相邻
2. **起点或终点在障碍物上**: 确保起点和终点都在可通行区域
3. **无可行路径**: 检查地图连通性，确保存在可行的沿墙路径
4. **坐标超出边界**: 确保起点和终点坐标在网格范围内

## 算法复杂度

- **时间复杂度**: O(V log V)，其中V是网格中的节点数
- **空间复杂度**: O(V)
- **适用场景**: 中小规模网格（建议不超过100×100）

## 技术栈

- **后端**: Python + Flask
- **前端**: HTML + CSS + JavaScript
- **算法**: A*搜索算法 + 沿墙约束
- **数据结构**: 堆、图搜索

## 许可证

本项目仅供学习和研究使用。 