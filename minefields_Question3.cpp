#include <iostream>
#include <vector>

using namespace std;

int dfs(vector<vector<int>>& map, vector<vector<bool>>& visited_cells, int row, int col) {
    int val_rows = map.size();
    int val_cols = map[0].size();

    if (row < 0 || row >= val_rows || col < 0 || col >= val_cols || visited_cells[row][col] || map[row][col] == 0)
        return 0;

    int val_count = 1;
    visited_cells[row][col] = true;

    val_count += dfs(map, visited_cells, row + 1, col);
    val_count += dfs(map, visited_cells, row - 1, col);
    val_count += dfs(map, visited_cells, row, col + 1);
    val_count += dfs(map, visited_cells, row, col - 1);

    return val_count;
}

int countArea(vector<vector<int>>& map) {
    int val_rows = map.size();
    int val_cols = map[0].size();
    int maxArea = 0;

    vector<vector<bool>> visited_cells(val_rows, vector<bool>(val_cols, false));

    for (int row = 0; row < val_rows; row++) {
        for (int col = 0; col < val_cols; col++) {
            if (!visited_cells[row][col] && map[row][col] == 1) {
                int count = dfs(map, visited_cells, row, col);
                maxArea = max(maxArea, count);
            }
        }
    }

    return maxArea;
}

int main() {
    int val_rows, val_cols;

    cout << "Please provide the number of rows: ";
    cin >> val_rows;
    cout << "Please provide the number of columns: ";
    cin >> val_cols;

    vector<vector<int>> map(val_rows, vector<int>(val_cols));

    for (int row = 0; row < val_rows; row++) {
        cout << "Enter the " << row + 1 << " row: ";
        for (int col = 0; col < val_cols; col++) {
            cin >> map[row][col];
        }
    }

    int maxArea = countArea(map);

    cout << "The Maximum area: " << maxArea << endl;

    return 0;
}
