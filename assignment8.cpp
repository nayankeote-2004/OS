#include <bits/stdc++.h>

using namespace std;

void FIFO(vector<int> requests, int head) {
    int totalSeekTime = 0;
    cout << "FIFO Sequence: " << head;
    
    for (int i = 0; i < requests.size(); i++) {
        totalSeekTime += abs(head - requests[i]);
        head = requests[i];
        cout << " -> " << head;
    }
    
    cout << "\nTotal Seek Time: " << totalSeekTime << endl;
}

void SSTF(vector<int> requests, int head) {
    int totalSeekTime = 0;
    int n = requests.size();
    vector<bool> visited(n, false);
    cout << "SSTF Sequence: " << head;
    
    for (int i = 0; i < n; i++) {
        int minSeek = INT_MAX;
        int pos = -1;
        
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(head - requests[j]) < minSeek) {
                minSeek = abs(head - requests[j]);
                pos = j;
            }
        }
        
        visited[pos] = true;
        totalSeekTime += minSeek;
        head = requests[pos];
        cout << " -> " << head;
    }
    
    cout << "\nTotal Seek Time: " << totalSeekTime << endl;
}

void SCAN(vector<int> requests, int head, int diskSize) {
    vector<int> left, right;
    int totalSeekTime = 0;
    
    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] < head)
            left.push_back(requests[i]);
        else
            right.push_back(requests[i]);
    }
    
    sort(left.begin(), left.end(), greater<int>());
    sort(right.begin(), right.end());
    
    cout << "SCAN Sequence: " << head;
    
    for (int i = 0; i < right.size(); i++) {
        totalSeekTime += abs(head - right[i]);
        head = right[i];
        cout << " -> " << head;
    }
    
    if (right.size() == 0 || right[right.size()-1] != diskSize-1) {
        totalSeekTime += abs(head - (diskSize-1));
        head = diskSize-1;
        cout << " -> " << head;
    }
    
    for (int i = 0; i < left.size(); i++) {
        totalSeekTime += abs(head - left[i]);
        head = left[i];
        cout << " -> " << head;
    }
    
    cout << "\nTotal Seek Time: " << totalSeekTime << endl;
}

void CSCAN(vector<int> requests, int head, int diskSize) {
    vector<int> left, right;
    int totalSeekTime = 0;
    
    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] < head)
            left.push_back(requests[i]);
        else
            right.push_back(requests[i]);
    }
    
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    
    cout << "C-SCAN Sequence: " << head;
    
    for (int i = 0; i < right.size(); i++) {
        totalSeekTime += abs(head - right[i]);
        head = right[i];
        cout << " -> " << head;
    }
    
    if (right.size() == 0 || right[right.size()-1] != diskSize-1) {
        totalSeekTime += abs(head - (diskSize-1));
        head = diskSize-1;
        cout << " -> " << head;
    }
    
    totalSeekTime += diskSize-1;
    head = 0;
    cout << " -> " << head;
    
    for (int i = 0; i < left.size(); i++) {
        totalSeekTime += abs(head - left[i]);
        head = left[i];
        cout << " -> " << head;
    }
    
    cout << "\nTotal Seek Time: " << totalSeekTime << endl;
}

int main() {
    int n, head, diskSize;
    cout << "Enter the number of disk requests: ";
    cin >> n;
    
    vector<int> requests(n);
    cout << "Enter the disk request sequence: ";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }
    
    cout << "Enter the initial head position: ";
    cin >> head;
    
    cout << "Enter the disk size: ";
    cin >> diskSize;
    
    cout << "\n";
    FIFO(requests, head);
    cout << "\n";
    SSTF(requests, head);
    cout << "\n";
    SCAN(requests, head, diskSize);
    cout << "\n";
    CSCAN(requests, head, diskSize);
    
    return 0;
}