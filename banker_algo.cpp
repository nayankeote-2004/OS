#include <bits/stdc++.h>
using namespace std;

void printSafeSequence(vector<int>& sequence) {
    cout << "Safe Sequence: ";
    for (int i = 0; i < sequence.size(); i++) {
        cout << "P" << sequence[i] + 1;
        if (i < sequence.size() - 1) cout << " -> ";
    }
    cout << endl;
}

bool isSafe(vector<vector<int>>& allocation, vector<vector<int>>& maxNeed, vector<int>& available, int n, int m, vector<int>& sequence) {
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> work = available;
    vector<bool> finish(n, false);

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maxNeed[i][j] - allocation[i][j];

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool possible = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    sequence.push_back(i);
                    found = true;
                    count++;
                }
            }
        }
        if (!found) return false;
    }
    return true;
}

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> maxNeed(n, vector<int>(m));
    vector<int> available(m);

    cout << "\nEnter allocation matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "For process " << i << ": ";
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];
    }

    cout << "\nEnter maximum need matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "For process " << i << ": ";
        for (int j = 0; j < m; j++)
            cin >> maxNeed[i][j];
    }

    cout << "\nEnter available resources: ";
    for (int i = 0; i < m; i++)
        cin >> available[i];

    vector<int> sequence;
    if (isSafe(allocation, maxNeed, available, n, m, sequence)) {
        cout << "\nSystem is in safe state.\n";
        printSafeSequence(sequence);
    } else {
        cout << "\nSystem is not in safe state!\n";
    }

    return 0;
}