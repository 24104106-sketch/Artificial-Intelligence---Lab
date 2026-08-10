#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

const int N = 4;

struct State {
    vector<int> board;
    int row;
    int h; // heuristic

    bool operator<(const State &other) const {
        return h > other.h;   // Min-heap for A*
    }
};

// Check if queen placement is safe
bool isSafe(vector<int> &board, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

// Heuristic: Count attacking pairs
int heuristic(vector<int> &board, int rows) {
    int conflicts = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = i + 1; j < rows; j++) {
            if (board[i] == board[j] ||
                abs(board[i] - board[j]) == abs(i - j))
                conflicts++;
        }
    }
    return conflicts;
}

// Print board
void printBoard(vector<int> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

// ---------------- DFS ----------------
void DFS() {
    stack<State> st;

    State start;
    start.board = vector<int>(N, -1);
    start.row = 0;
    st.push(start);

    while (!st.empty()) {
        State cur = st.top();
        st.pop();

        if (cur.row == N) {
            cout << "DFS Solution:\n";
            printBoard(cur.board);
            return;
        }

        for (int col = N - 1; col >= 0; col--) {
            if (isSafe(cur.board, cur.row, col)) {
                State next = cur;
                next.board[cur.row] = col;
                next.row++;
                st.push(next);
            }
        }
    }
}

// ---------------- BFS ----------------
void BFS() {
    queue<State> q;

    State start;
    start.board = vector<int>(N, -1);
    start.row = 0;
    q.push(start);

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.row == N) {
            cout << "BFS Solution:\n";
            printBoard(cur.board);
            return;
        }

        for (int col = 0; col < N; col++) {
            if (isSafe(cur.board, cur.row, col)) {
                State next = cur;
                next.board[cur.row] = col;
                next.row++;
                q.push(next);
            }
        }
    }
}

// ---------------- A* ----------------
void AStar() {
    priority_queue<State> pq;

    State start;
    start.board = vector<int>(N, -1);
    start.row = 0;
    start.h = 0;
    pq.push(start);

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        if (cur.row == N) {
            cout << "A* Solution:\n";
            printBoard(cur.board);
            return;
        }

        for (int col = 0; col < N; col++) {
            if (isSafe(cur.board, cur.row, col)) {
                State next = cur;
                next.board[cur.row] = col;
                next.row++;
                next.h = heuristic(next.board, next.row);
                pq.push(next);
            }
        }
    }
}

int main() {

    DFS();

    BFS();

    AStar();

    return 0;
}
