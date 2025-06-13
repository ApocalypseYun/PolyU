from flask import Flask, render_template, request, jsonify
import heapq
import math

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/find_path', methods=['POST'])
def find_path():
    data = request.json
    grid = data['grid']
    start = tuple(data['start'])
    end = tuple(data['end'])
    
    path = wall_following_path(grid, start, end)
    return jsonify({'path': path})

def wall_following_path(grid, start, end):
    rows, cols = len(grid), len(grid[0])
    
    # 检查一个点是否在墙边
    def is_next_to_wall(node):
        x, y = node
        for dx, dy in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < rows and 0 <= ny < cols and grid[nx][ny] == 1:
                return True
        return False
    
    # 确保终点在墙边
    if not is_next_to_wall(end):
        return []  # 终点不在墙边，返回空路径
    
    # 如果起点已经在墙边
    if is_next_to_wall(start):
        # 直接尝试沿墙行走到终点
        path = strictly_follow_wall(grid, start, end)
        if path:
            return path
    
    # 找出所有墙边点
    wall_points = []
    for i in range(rows):
        for j in range(cols):
            if grid[i][j] != 1 and is_next_to_wall((i, j)):
                wall_points.append((i, j))
    
    if not wall_points:
        return []  # 没有墙边点，返回空路径
    
    # 先尝试使用改进的沿墙路径规划
    improved_path = improved_wall_path(grid, start, end)
    if improved_path:
        return improved_path
    
    # 找到最佳入口点
    best_entry = None
    best_path = None
    best_length = float('inf')
    
    # 尝试计算所有可能的路径组合
    for entry_point in wall_points:
        # 从起点到入口点
        path_to_wall = direct_path(grid, start, entry_point)
        if not path_to_wall:
            continue
        
        # 从入口点沿墙到终点
        path_along_wall = strictly_follow_wall(grid, entry_point, end)
        if not path_along_wall:
            continue
        
        # 合并路径
        if path_to_wall[-1] == path_along_wall[0]:
            complete_path = path_to_wall + path_along_wall[1:]
        else:
            complete_path = path_to_wall + path_along_wall
        
        # 检查是否是最短路径
        if len(complete_path) < best_length:
            best_length = len(complete_path)
            best_entry = entry_point
            best_path = complete_path
    
    if best_path:
        return best_path
    
    # 如果所有尝试都失败，使用改进的路径规划
    return bridge_disconnected_walls(grid, start, end)

def strictly_follow_wall(grid, start, end):
    """严格沿墙行走的路径搜索"""
    rows, cols = len(grid), len(grid[0])
    
    # 检查一个点是否在墙边
    def is_next_to_wall(node):
        x, y = node
        for dx, dy in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < rows and 0 <= ny < cols and grid[nx][ny] == 1:
                return True
        return False
    
    # 验证起点和终点都在墙边
    if not is_next_to_wall(start) or not is_next_to_wall(end):
        return []
    
    # 启发式函数
    def heuristic(a, b):
        return math.sqrt((a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2)
    
    # 获取墙边邻居
    def get_wall_neighbors(node):
        x, y = node
        neighbors = []
        
        # 优先考虑直线移动，然后是对角线移动
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)]
        
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            
            # 确保邻居在网格内且不是墙
            if 0 <= nx < rows and 0 <= ny < cols and grid[nx][ny] != 1:
                # 检查对角线移动是否穿墙
                if abs(dx) == 1 and abs(dy) == 1:
                    if grid[x][y + dy] == 1 or grid[x + dx][y] == 1:
                        continue
                
                # 严格限制只能走墙边
                if is_next_to_wall((nx, ny)):
                    neighbors.append((nx, ny))
        
        return neighbors
    
    # 初始化
    open_set = []
    heapq.heappush(open_set, (0, start))
    came_from = {}
    g_score = {}
    for i in range(rows):
        for j in range(cols):
            g_score[(i, j)] = float('inf')
    g_score[start] = 0
    f_score = {}
    for i in range(rows):
        for j in range(cols):
            f_score[(i, j)] = float('inf')
    f_score[start] = heuristic(start, end)
    
    open_set_hash = {start}
    
    while open_set:
        _, current = heapq.heappop(open_set)
        open_set_hash.remove(current)
        
        if current == end:
            # 重建路径
            path = []
            while current in came_from:
                path.append(current)
                current = came_from[current]
            path.append(start)
            return path[::-1]
        
        for neighbor in get_wall_neighbors(current):
            # 基本移动成本
            movement_cost = 1.0
            
            # 对角线移动的成本稍高
            if abs(neighbor[0] - current[0]) == 1 and abs(neighbor[1] - current[1]) == 1:
                movement_cost = 1.4
            
            # 计算从起点到邻居的距离
            temp_g_score = g_score[current] + movement_cost
            
            if temp_g_score < g_score[neighbor]:
                # 找到更好的路径
                came_from[neighbor] = current
                g_score[neighbor] = temp_g_score
                f_score[neighbor] = temp_g_score + heuristic(neighbor, end)
                
                if neighbor not in open_set_hash:
                    heapq.heappush(open_set, (f_score[neighbor], neighbor))
                    open_set_hash.add(neighbor)
    
    # 无法找到路径
    return []

def improved_wall_path(grid, start, end):
    """改进的沿墙路径搜索，允许短暂离开墙边但尽快回到墙边"""
    rows, cols = len(grid), len(grid[0])
    
    # 检查一个点是否在墙边
    def is_next_to_wall(node):
        x, y = node
        for dx, dy in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < rows and 0 <= ny < cols and grid[nx][ny] == 1:
                return True
        return False
    
    # 验证终点在墙边
    if not is_next_to_wall(end):
        return []
    
    # 启发式函数
    def heuristic(a, b):
        return math.sqrt((a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2)
    
    # 获取邻居，优先考虑墙边的邻居
    def get_neighbors(node, current_off_wall_steps=0):
        x, y = node
        wall_neighbors = []
        non_wall_neighbors = []
        
        # 优先考虑直线移动，然后是对角线移动
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)]
        
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            
            # 确保邻居在网格内且不是墙
            if 0 <= nx < rows and 0 <= ny < cols and grid[nx][ny] != 1:
                # 检查对角线移动是否穿墙
                if abs(dx) == 1 and abs(dy) == 1:
                    if grid[x][y + dy] == 1 or grid[x + dx][y] == 1:
                        continue
                
                # 分类邻居
                if is_next_to_wall((nx, ny)):
                    wall_neighbors.append((nx, ny))
                else:
                    # 如果已经离开墙边步数过多，则不再考虑非墙边邻居
                    if current_off_wall_steps < 3:  # 允许最多离开墙边3步
                        non_wall_neighbors.append((nx, ny))
        
        # 优先返回墙边的邻居
        return wall_neighbors + non_wall_neighbors
    
    # 初始化
    open_set = []
    # 队列中保存(f值, 节点, 离开墙边的步数)
    heapq.heappush(open_set, (0, start, 0 if is_next_to_wall(start) else 1))
    came_from = {}
    g_score = {}
    for i in range(rows):
        for j in range(cols):
            g_score[(i, j)] = float('inf')
    g_score[start] = 0
    f_score = {}
    for i in range(rows):
        for j in range(cols):
            f_score[(i, j)] = float('inf')
    f_score[start] = heuristic(start, end)
    
    # 记录每个节点离开墙边的步数
    off_wall_steps = {start: 0 if is_next_to_wall(start) else 1}
    
    open_set_hash = {start}
    
    while open_set:
        _, current, current_steps = heapq.heappop(open_set)
        open_set_hash.remove(current)
        
        if current == end:
            # 重建路径
            path = []
            while current in came_from:
                path.append(current)
                current = came_from[current]
            path.append(start)
            return path[::-1]
        
        # 如果当前不在墙边，增加步数
        next_steps = current_steps
        if not is_next_to_wall(current):
            next_steps = current_steps + 1
        else:
            next_steps = 0  # 重置为0，因为回到了墙边
        
        for neighbor in get_neighbors(current, current_steps):
            # 基本移动成本
            movement_cost = 1.0
            
            # 对角线移动的成本稍高
            if abs(neighbor[0] - current[0]) == 1 and abs(neighbor[1] - current[1]) == 1:
                movement_cost = 1.4
            
            # 非墙边点的成本更高，鼓励尽快回到墙边
            if not is_next_to_wall(neighbor):
                movement_cost += 2.0
            
            # 计算从起点到邻居的距离
            temp_g_score = g_score[current] + movement_cost
            
            # 更新邻居的离墙步数
            neighbor_steps = 0 if is_next_to_wall(neighbor) else next_steps
            
            if neighbor not in off_wall_steps or neighbor_steps < off_wall_steps[neighbor]:
                off_wall_steps[neighbor] = neighbor_steps
            
            if temp_g_score < g_score[neighbor]:
                # 找到更好的路径
                came_from[neighbor] = current
                g_score[neighbor] = temp_g_score
                f_score[neighbor] = temp_g_score + heuristic(neighbor, end)
                
                if neighbor not in open_set_hash:
                    heapq.heappush(open_set, (f_score[neighbor], neighbor, off_wall_steps[neighbor]))
                    open_set_hash.add(neighbor)
    
    # 无法找到路径
    return []

def bridge_disconnected_walls(grid, start, end):
    """处理不连通墙体的情况，允许在墙体之间创建桥接路径"""
    rows, cols = len(grid), len(grid[0])
    
    # 检查一个点是否在墙边
    def is_next_to_wall(node):
        x, y = node
        for dx, dy in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < rows and 0 <= ny < cols and grid[nx][ny] == 1:
                return True
        return False
    
    # 验证终点在墙边
    if not is_next_to_wall(end):
        return []
    
    # 找到所有墙边点
    wall_points = []
    for i in range(rows):
        for j in range(cols):
            if grid[i][j] != 1 and is_next_to_wall((i, j)):
                wall_points.append((i, j))
    
    # 使用BFS找到墙边点的连通分量
    def find_connected_components():
        visited = set()
        components = []
        
        for point in wall_points:
            if point in visited:
                continue
                
            # 新的连通分量
            component = []
            queue = [point]
            visited.add(point)
            
            while queue:
                current = queue.pop(0)
                component.append(current)
                
                # 检查相邻的墙边点
                x, y = current
                for dx, dy in [(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)]:
                    nx, ny = x + dx, y + dy
                    neighbor = (nx, ny)
                    
                    if (0 <= nx < rows and 0 <= ny < cols and 
                        grid[nx][ny] != 1 and 
                        is_next_to_wall(neighbor) and 
                        neighbor not in visited):
                        visited.add(neighbor)
                        queue.append(neighbor)
            
            components.append(component)
        
        return components
    
    # 找到每个点所属的连通分量
    components = find_connected_components()
    
    # 如果起点和终点在同一个连通分量内，直接使用strictly_follow_wall
    start_component = None
    end_component = None
    
    for i, component in enumerate(components):
        if is_next_to_wall(start) and start in component:
            start_component = i
        if end in component:
            end_component = i
    
    # 如果起点和终点在同一个连通分量，应该能直接找到路径
    if start_component is not None and start_component == end_component:
        return strictly_follow_wall(grid, start, end)
    
    # 尝试在各个连通分量之间建立桥接
    best_path = None
    best_length = float('inf')
    
    # 如果起点不在墙边，找到起点到各个连通分量的最短路径
    start_to_component = {}
    if not is_next_to_wall(start):
        for i, component in enumerate(components):
            best_entry = None
            best_entry_path = None
            best_entry_length = float('inf')
            
            for entry in component:
                path = direct_path(grid, start, entry)
                if path and len(path) < best_entry_length:
                    best_entry = entry
                    best_entry_path = path
                    best_entry_length = len(path)
            
            if best_entry is not None:
                start_to_component[i] = (best_entry, best_entry_path)
    else:
        # 如果起点在墙边，找到它所属的组件
        for i, component in enumerate(components):
            if start in component:
                start_to_component[i] = (start, [start])
                break
    
    # 找到终点所在的连通分量
    end_component_idx = None
    for i, component in enumerate(components):
        if end in component:
            end_component_idx = i
            break
    
    if end_component_idx is None:
        return []  # 终点不在任何连通分量中
    
    # 如果起点所在的连通分量能直接到达终点所在的连通分量
    if end_component_idx in start_to_component:
        entry, path_to_entry = start_to_component[end_component_idx]
        path_along_wall = strictly_follow_wall(grid, entry, end)
        
        if path_along_wall:
            # 合并路径
            if path_to_entry[-1] == path_along_wall[0]:
                return path_to_entry + path_along_wall[1:]
            else:
                return path_to_entry + path_along_wall
    
    # 需要在多个连通分量之间建立桥接
    # 对于每对连通分量，找到它们之间最短的桥接路径
    bridges = {}
    for i in range(len(components)):
        for j in range(i+1, len(components)):
            best_bridge = None
            best_bridge_path = None
            best_bridge_length = float('inf')
            
            for start_point in components[i]:
                for end_point in components[j]:
                    path = direct_path(grid, start_point, end_point)
                    if path and len(path) < best_bridge_length:
                        best_bridge = (start_point, end_point)
                        best_bridge_path = path
                        best_bridge_length = len(path)
            
            if best_bridge is not None:
                bridges[(i, j)] = (best_bridge, best_bridge_path)
                bridges[(j, i)] = ((best_bridge[1], best_bridge[0]), best_bridge_path[::-1])
    
    # 使用Dijkstra算法找到从起点所在连通分量到终点所在连通分量的最短路径
    def find_shortest_component_path(start_components, end_component):
        if not start_components:
            return None
            
        distances = {i: float('inf') for i in range(len(components))}
        for i in start_components:
            distances[i] = 0
        
        prev = {}
        visited = set()
        
        while len(visited) < len(components):
            # 找到未访问的距离最小的连通分量
            min_dist = float('inf')
            min_component = None
            
            for i in range(len(components)):
                if i not in visited and distances[i] < min_dist:
                    min_dist = distances[i]
                    min_component = i
            
            if min_component is None or min_component == end_component:
                break
                
            visited.add(min_component)
            
            # 更新邻居距离
            for j in range(len(components)):
                if j != min_component and (min_component, j) in bridges:
                    _, bridge_path = bridges[(min_component, j)]
                    new_dist = distances[min_component] + len(bridge_path)
                    
                    if new_dist < distances[j]:
                        distances[j] = new_dist
                        prev[j] = min_component
        
        # 重建路径
        if end_component not in prev and end_component not in start_components:
            return None
            
        path = []
        current = end_component
        
        while current in prev:
            path.append(current)
            current = prev[current]
            
        path.append(current)  # 添加起始连通分量
        return path[::-1]
    
    # 找到连通分量级别的路径
    component_path = find_shortest_component_path(start_to_component.keys(), end_component_idx)
    
    if component_path is None:
        return []  # 无法找到路径
    
    # 构建实际路径
    final_path = []
    
    # 首先从起点到第一个连通分量
    first_component = component_path[0]
    entry, path_to_entry = start_to_component[first_component]
    final_path.extend(path_to_entry)
    
    # 在连通分量之间建立桥接
    current_point = entry
    
    for i in range(len(component_path) - 1):
        curr_comp = component_path[i]
        next_comp = component_path[i + 1]
        
        # 获取桥接
        (bridge_start, bridge_end), bridge_path = bridges[(curr_comp, next_comp)]
        
        # 在当前连通分量内从当前点到桥接起点
        if current_point != bridge_start:
            wall_path = strictly_follow_wall(grid, current_point, bridge_start)
            if wall_path:
                # 避免重复点
                if final_path[-1] == wall_path[0]:
                    final_path.extend(wall_path[1:])
                else:
                    final_path.extend(wall_path)
        
        # 添加桥接路径
        if final_path[-1] == bridge_path[0]:
            final_path.extend(bridge_path[1:])
        else:
            final_path.extend(bridge_path)
        
        current_point = bridge_end
    
    # 最后从最后一个连通分量到终点
    if current_point != end:
        wall_path = strictly_follow_wall(grid, current_point, end)
        if wall_path:
            # 避免重复点
            if final_path[-1] == wall_path[0]:
                final_path.extend(wall_path[1:])
            else:
                final_path.extend(wall_path)
    
    return final_path

def direct_path(grid, start, end):
    """从起点到墙边的直接路径（最短路径）"""
    rows, cols = len(grid), len(grid[0])
    
    # 启发式函数
    def heuristic(a, b):
        return math.sqrt((a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2)
    
    # 定义邻居
    def get_neighbors(node):
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)]
        neighbors = []
        for dx, dy in directions:
            nx, ny = node[0] + dx, node[1] + dy
            if 0 <= nx < rows and 0 <= ny < cols and grid[nx][ny] != 1:  # 1表示障碍物
                # 检查对角线移动是否穿过墙
                if abs(dx) == 1 and abs(dy) == 1:
                    if grid[node[0]][node[1] + dy] == 1 or grid[node[0] + dx][node[1]] == 1:
                        continue
                neighbors.append((nx, ny))
        return neighbors
    
    # 初始化
    open_set = []
    heapq.heappush(open_set, (0, start))
    came_from = {}
    g_score = {}
    for i in range(rows):
        for j in range(cols):
            g_score[(i, j)] = float('inf')
    g_score[start] = 0
    f_score = {}
    for i in range(rows):
        for j in range(cols):
            f_score[(i, j)] = float('inf')
    f_score[start] = heuristic(start, end)
    
    open_set_hash = {start}
    
    while open_set:
        _, current = heapq.heappop(open_set)
        open_set_hash.remove(current)
        
        if current == end:
            # 重建路径
            path = []
            while current in came_from:
                path.append(current)
                current = came_from[current]
            path.append(start)
            return path[::-1]
        
        for neighbor in get_neighbors(current):
            # 基本移动成本
            movement_cost = 1.0
            
            # 对角线移动的成本稍高
            if abs(neighbor[0] - current[0]) == 1 and abs(neighbor[1] - current[1]) == 1:
                movement_cost = 1.4
            
            # 计算从起点到邻居的距离
            temp_g_score = g_score[current] + movement_cost
            
            if temp_g_score < g_score[neighbor]:
                # 找到更好的路径
                came_from[neighbor] = current
                g_score[neighbor] = temp_g_score
                f_score[neighbor] = temp_g_score + heuristic(neighbor, end)
                
                if neighbor not in open_set_hash:
                    heapq.heappush(open_set, (f_score[neighbor], neighbor))
                    open_set_hash.add(neighbor)
    
    # 无法找到路径
    return []

if __name__ == '__main__':
    app.run(debug=True)
