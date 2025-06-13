document.addEventListener('DOMContentLoaded', function() {
    const gridContainer = document.getElementById('grid-container');
    const createGridBtn = document.getElementById('create-grid');
    const setStartBtn = document.getElementById('set-start');
    const setEndBtn = document.getElementById('set-end');
    const setObstacleBtn = document.getElementById('set-obstacle');
    const clearCellBtn = document.getElementById('clear-cell');
    const findPathBtn = document.getElementById('find-path');
    const clearGridBtn = document.getElementById('clear-grid');
    
    let gridRows, gridCols;
    let grid = [];
    let mode = null;
    let startCell = null;
    let endCells = [];
    let isMouseDown = false;
    
    createGridBtn.addEventListener('click', createGrid);
    setStartBtn.addEventListener('click', () => { mode = 'start'; });
    setEndBtn.addEventListener('click', () => { mode = 'end'; });
    setObstacleBtn.addEventListener('click', () => { mode = 'obstacle'; });
    clearCellBtn.addEventListener('click', () => { mode = 'clear'; });
    findPathBtn.addEventListener('click', findPath);
    clearGridBtn.addEventListener('click', clearGrid);
    
    // 添加鼠标事件监听器
    document.addEventListener('mousedown', () => { isMouseDown = true; });
    document.addEventListener('mouseup', () => { isMouseDown = false; });
    
    // 检查一个点是否在墙边
    function isNextToWall(row, col) {
        const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];
        for (const [dx, dy] of directions) {
            const nx = row + dx;
            const ny = col + dy;
            if (nx >= 0 && nx < gridRows && ny >= 0 && ny < gridCols && grid[nx][ny] === 1) {
                return true;
            }
        }
        return false;
    }
    
    function createGrid() {
        gridRows = parseInt(document.getElementById('rows').value);
        gridCols = parseInt(document.getElementById('cols').value);
        
        if (isNaN(gridRows) || isNaN(gridCols) || gridRows < 5 || gridCols < 5) {
            alert('Please enter valid grid dimensions (minimum 5x5)');
            return;
        }
        
        // Clear previous grid
        gridContainer.innerHTML = '';
        grid = Array(gridRows).fill().map(() => Array(gridCols).fill(0));
        startCell = null;
        endCells = [];
        
        // Set grid template
        gridContainer.style.gridTemplateColumns = `repeat(${gridCols}, 30px)`;
        
        // Create cells
        for (let i = 0; i < gridRows; i++) {
            for (let j = 0; j < gridCols; j++) {
                const cell = document.createElement('div');
                cell.className = 'cell';
                cell.dataset.row = i;
                cell.dataset.col = j;
                
                // 设置边界为墙
                if (i === 0 || i === gridRows - 1 || j === 0 || j === gridCols - 1) {
                    cell.classList.add('obstacle');
                    grid[i][j] = 1; // 1表示墙
                }
                
                // 单击处理
                cell.addEventListener('click', () => {
                    handleCellInteraction(cell);
                });
                
                // 鼠标进入处理（用于拖动）
                cell.addEventListener('mouseenter', () => {
                    if (isMouseDown && (mode === 'obstacle' || mode === 'clear')) {
                        handleCellInteraction(cell);
                    }
                });
                
                gridContainer.appendChild(cell);
            }
        }
        
        // 更新墙边单元格标记
        updateWallAdjacentCells();
    }
    
    function handleCellInteraction(cell) {
        const row = parseInt(cell.dataset.row);
        const col = parseInt(cell.dataset.col);
        
        if (mode === 'start') {
            // 清除之前的起点
            if (startCell) {
                startCell.classList.remove('start');
                grid[parseInt(startCell.dataset.row)][parseInt(startCell.dataset.col)] = 0;
            }
            
            cell.classList.add('start');
            cell.classList.remove('obstacle', 'end', 'wall-adjacent');
            grid[row][col] = 2; // 2 for start
            startCell = cell;
        } 
        else if (mode === 'end') {
            // 检查是否在墙边
            if (!isNextToWall(row, col)) {
                alert('End points must be next to a wall!');
                return;
            }
            
            if (cell.classList.contains('end')) {
                cell.classList.remove('end');
                grid[row][col] = 0;
                endCells = endCells.filter(endCell => 
                    endCell.dataset.row !== cell.dataset.row || 
                    endCell.dataset.col !== cell.dataset.col
                );
                
                // 恢复墙边标记
                if (isNextToWall(row, col)) {
                    cell.classList.add('wall-adjacent');
                }
            } else {
                cell.classList.add('end');
                cell.classList.remove('obstacle', 'start', 'wall-adjacent');
                grid[row][col] = 3; // 3 for end
                endCells.push(cell);
            }
        } 
        else if (mode === 'obstacle') {
            cell.classList.add('obstacle');
            cell.classList.remove('start', 'end', 'path', 'wall-adjacent');
            grid[row][col] = 1; // 1 for obstacle
            
            // 如果这是起点，清除起点引用
            if (startCell === cell) {
                startCell = null;
            }
            
            // 如果这是终点，从列表中移除
            endCells = endCells.filter(endCell => 
                endCell.dataset.row !== cell.dataset.row || 
                endCell.dataset.col !== cell.dataset.col
            );
            
            // 更新网格后检查哪些单元格是墙边
            updateWallAdjacentCells();
        } 
        else if (mode === 'clear') {
            // 不允许清除边界墙
            if (row === 0 || row === gridRows - 1 || col === 0 || col === gridCols - 1) {
                return;
            }
            
            cell.classList.remove('obstacle', 'start', 'end', 'path');
            grid[row][col] = 0; // 0 for empty
            
            if (startCell === cell) {
                startCell = null;
            }
            
            endCells = endCells.filter(endCell => 
                endCell.dataset.row !== cell.dataset.row || 
                endCell.dataset.col !== cell.dataset.col
            );
            
            // 更新网格后检查哪些单元格是墙边
            updateWallAdjacentCells();
        }
    }
    
    // 更新网格，标记墙边单元格，让用户能够直观看到哪些单元格可以设为终点
    function updateWallAdjacentCells() {
        document.querySelectorAll('.cell').forEach(cell => {
            if (!cell.classList.contains('obstacle') && 
                !cell.classList.contains('start') && 
                !cell.classList.contains('end') && 
                !cell.classList.contains('path')) {
                
                const row = parseInt(cell.dataset.row);
                const col = parseInt(cell.dataset.col);
                
                if (isNextToWall(row, col)) {
                    cell.classList.add('wall-adjacent');
                } else {
                    cell.classList.remove('wall-adjacent');
                }
            }
        });
    }
    
    function clearGrid() {
        // 重置所有非边界单元格
        const cells = document.querySelectorAll('.cell');
        cells.forEach(cell => {
            const row = parseInt(cell.dataset.row);
            const col = parseInt(cell.dataset.col);
            
            // 保留边界墙
            if (row === 0 || row === gridRows - 1 || col === 0 || col === gridCols - 1) {
                cell.className = 'cell obstacle';
                grid[row][col] = 1;
            } else {
                cell.className = 'cell';
                grid[row][col] = 0;
            }
        });
        
        startCell = null;
        endCells = [];
        
        // 更新墙边单元格
        updateWallAdjacentCells();
    }
    
    function findPath() {
        // 清除之前的路径
        document.querySelectorAll('.path').forEach(cell => {
            cell.classList.remove('path');
            
            // 恢复墙边标记
            const row = parseInt(cell.dataset.row);
            const col = parseInt(cell.dataset.col);
            
            if (!cell.classList.contains('start') && 
                !cell.classList.contains('end') && 
                !cell.classList.contains('obstacle') &&
                isNextToWall(row, col)) {
                cell.classList.add('wall-adjacent');
            }
        });
        
        if (!startCell) {
            alert('Please set a start point');
            return;
        }
        
        if (endCells.length === 0) {
            alert('Please set at least one end point');
            return;
        }
        
        const startRow = parseInt(startCell.dataset.row);
        const startCol = parseInt(startCell.dataset.col);
        
        // Find paths to all end points
        endCells.forEach(endCell => {
            const endRow = parseInt(endCell.dataset.row);
            const endCol = parseInt(endCell.dataset.col);
            
            fetch('/find_path', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({
                    grid: grid,
                    start: [startRow, startCol],
                    end: [endRow, endCol]
                }),
            })
            .then(response => response.json())
            .then(data => {
                const path = data.path;
                
                if (path.length === 0) {
                    alert(`No wall-following path found to end point at (${endRow}, ${endCol})`);
                    return;
                }
                
                // Display the path
                path.forEach((point, index) => {
                    // Skip start and end points
                    if (index === 0 || index === path.length - 1) return;
                    
                    const [row, col] = point;
                    const pathCell = document.querySelector(`.cell[data-row="${row}"][data-col="${col}"]`);
                    pathCell.classList.add('path');
                    pathCell.classList.remove('wall-adjacent');  // 移除墙边标记，避免视觉混乱
                });
            })
            .catch(error => {
                console.error('Error finding path:', error);
                alert('Error finding path');
            });
        });
    }
    
    // Initialize with a default grid
    createGrid();
});
