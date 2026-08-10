#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    double g, h, f;
};

struct Compare {
    bool operator()(Node a, Node b) {
        return a.f > b.f;
    }
};

double heuristic(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) +
                (y1 - y2) * (y1 - y2));
}

int main() {

    int rows, cols;

    cout << "Enter maze size: ";
    cin >> rows >> cols;

    int sx, sy, gx, gy;

    cout << "Enter Start position: ";
    cin >> sx >> sy;

    cout << "Enter Treasure position: ";
    cin >> gx >> gy;

    vector<vector<int>> maze(rows, vector<int>(cols, 0));

    cout << "Enter number of danger zones: ";
    int d;
    cin >> d;

    cout << "Enter danger zone positions:\n";
    for (int i = 0; i < d; i++) {
        int x, y;
        cin >> x >> y;
        maze[x][y] = 1;
    }

    priority_queue<Node, vector<Node>, Compare> pq;

    vector<vector<double>> gCost(rows, vector<double>(cols, 1e9));
    vector<vector<pair<int, int>>> parent(rows,
        vector<pair<int, int>>(cols, {-1, -1}));

    vector<vector<bool>> visited(rows,
        vector<bool>(cols, false));

    pq.push({sx, sy, 0,
             heuristic(sx, sy, gx, gy),
             heuristic(sx, sy, gx, gy)});

    gCost[sx][sy] = 0;

    // Right, Down, Left, Up
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    while (!pq.empty()) {

        Node cur = pq.top();
        pq.pop();

        int x = cur.x;
        int y = cur.y;

        if (visited[x][y])
            continue;

        visited[x][y] = true;

        if (x == gx && y == gy)
            break;

        for (int i = 0; i < 4; i++) {

            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < rows &&
                ny >= 0 && ny < cols &&
                maze[nx][ny] == 0 &&
                !visited[nx][ny]) {

                double newG = gCost[x][y] + 1;

                if (newG < gCost[nx][ny]) {

                    gCost[nx][ny] = newG;
                    parent[nx][ny] = {x, y};

                    double h = heuristic(nx, ny, gx, gy);

                    pq.push({nx, ny, newG, h, newG + h});
                }
            }
        }
    }

    if (!visited[gx][gy]) {
        cout << "\nTreasure cannot be reached.\n";
        return 0;
    }

    vector<pair<int, int>> path;

    int x = gx, y = gy;

    while (!(x == sx && y == sy)) {
        path.push_back({x, y});
        auto p = parent[x][y];
        x = p.first;
        y = p.second;
    }

    path.push_back({sx, sy});

    reverse(path.begin(), path.end());

    cout << "\nShortest Path:\n";
    for (int i = 0; i < path.size(); i++) {
        cout << "(" << path[i].first << "," << path[i].second << ")";
        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << "\nPath Cost: " << path.size() - 1 << endl;

    return 0;
}
