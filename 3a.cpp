#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// Calculate conflicts
int getConflicts(vector<int> &state, int N) {
    int conflicts = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (state[i] == state[j] ||
                abs(state[i] - state[j]) == abs(i - j)) {
                conflicts++;
            }
        }
    }
    return conflicts;
}

// Generate successors
vector<vector<int>> generateSuccessors(vector<int> state, int N) {
    vector<vector<int>> successors;
    for (int col = 0; col < N; col++) {
        for (int row = 1; row <= N; row++) {
            if (state[col] != row) {
                vector<int> newState = state;
                newState[col] = row;
                successors.push_back(newState);
            }
        }
    }
    return successors;
}

int main() {
    int N, K;

    cout << "Enter matrix size: ";
    cin >> N;

    cout << "Enter beam size: ";
    cin >> K;

    vector<vector<int>> beam(K, vector<int>(N));

    // Input initial states
    for (int i = 0; i < K; i++) {
        cout << "Enter initial state " << i + 1 << ": ";
        for (int j = 0; j < N; j++) {
            cin >> beam[i][j];
        }
    }

    int level = 1;

    while (true) {
        vector<vector<int>> allSuccessors;

        // Generate successors
        for (int i = 0; i < K; i++) {
            vector<vector<int>> temp = generateSuccessors(beam[i], N);
            allSuccessors.insert(allSuccessors.end(), temp.begin(), temp.end());
        }

        // Sort based on conflicts
        sort(allSuccessors.begin(), allSuccessors.end(),
             [&](vector<int> &a, vector<int> &b) {
                 return getConflicts(a, N) < getConflicts(b, N);
             });

        cout << "\nLevel " << level << " successor:\n";

        vector<vector<int>> newBeam;

        for (int i = 0; i < K; i++) {
            vector<int> state = allSuccessors[i];
            int c = getConflicts(state, N);

            for (int x : state) cout << x << " ";
            cout << "(conflicts: " << c << ")\n";

            if (c == 0) {
                cout << "\nSolution found!\n";
                return 0;
            }

            newBeam.push_back(state);
        }

        beam = newBeam;
        level++;
    }
}



