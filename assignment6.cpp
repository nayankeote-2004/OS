#include <bits/stdc++.h>
using namespace std;

void FirstFit(vector<int> block, vector<int> process, int n, int m)
{
    vector<int> allocation(m, -1);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (block[j] >= process[i] && allocation[i] == -1)
            {
                allocation[i] = j;
                block[j] -= process[i];
                break;
            }
        }
    }

    cout << "Process No.\tProcess Size\tBlock No.\tBlock Size\n";
    for (int i = 0; i < m; i++)
    {
        cout << i + 1 << "\t\t" << process[i] << "\t\t";

        if (allocation[i] != -1)
        {
            cout << allocation[i] + 1 << "\t\t" << block[allocation[i]] + process[i] << "\n";
        }
        else
        {
            cout << "Not Allocated\n";
        }
    }
}

void BestFit(vector<int> block, vector<int> process, int n, int m)
{
    vector<int> allocation(m, -1);

    for (int i = 0; i < m; i++)
    {
        int bestIdx = -1;

        for (int j = 0; j < n; j++)
        {
            if (block[j] >= process[i])
            {
                if (bestIdx == -1 || block[j] < block[bestIdx])
                {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            block[bestIdx] -= process[i];
        }
    }

    cout << "\nBest Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock No.\tBlock Size\n";
    for (int i = 0; i < m; i++)
    {
        cout << i + 1 << "\t\t" << process[i] << "\t\t";

        if (allocation[i] != -1)
        {
            cout << allocation[i] + 1 << "\t\t" << block[allocation[i]] + process[i] << "\n";
        }
        else
        {
            cout << "Not Allocated\n";
        }
    }
}

void WorstFit(vector<int> block, vector<int> process, int n, int m)
{
    vector<int> allocation(m, -1);
    for (int i = 0; i < m; i++)
    {
        int maxIdx = -1;
        for (int j = 0; j < n; j++)
        {
            if (block[j] >= process[i])
            {
                if (maxIdx == -1 || block[j] > block[maxIdx])
                {
                    maxIdx = j;
                }
            }
        }

        if (maxIdx != -1)
        {
            allocation[i] = maxIdx;
            block[maxIdx] -= process[i];
        }
    }

    cout << "\nWorst Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock No.\tBlock Size\n";
    for (int i = 0; i < m; i++)
    {
        cout << i + 1 << "\t\t" << process[i] << "\t\t";

        if (allocation[i] != -1)
        {
            cout << allocation[i] + 1 << "\t\t" << block[allocation[i]] + process[i] << "\n";
        }
        else
        {
            cout << "Not Allocated\n";
        }
    }
}

void NextFit(vector<int> block, vector<int> process, int n, int m)
{
    vector<int> allocation(m, -1);
    int j = 0;

    for (int i = 0; i < m; i++)
    {
        int startJ = j;

        do
        {
            if (block[j] >= process[i])
            {
                allocation[i] = j;
                block[j] -= process[i];
                break;
            }
            j = (j + 1) % n;
        } while (j != startJ);
    }

    cout << "\nNext Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock No.\tBlock Size\n";
    for (int i = 0; i < m; i++)
    {
        cout << i + 1 << "\t\t" << process[i] << "\t\t";

        if (allocation[i] != -1)
        {
            cout << allocation[i] + 1 << "\t\t" << block[allocation[i]] + process[i] << "\n";
        }
        else
        {
            cout << "Not Allocated\n";
        }
    }
}

int main()
{
    int n, m;
    cout << "Enter the number of blocks: ";
    cin >> n;
    cout << "Enter the number of processes: ";
    cin >> m;

    vector<int> block(n), process(m);

    cout << "Enter the size of each block:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> block[i];
    }

    cout << "Enter the size of each process:\n";
    for (int i = 0; i < m; i++)
    {
        cin >> process[i];
    }

    cout << "\nFirst Fit Allocation:\n";
    FirstFit(block, process, n, m);

    vector<int> blockCopy1 = block; // Make a copy for Best Fit
    BestFit(blockCopy1, process, n, m);

    vector<int> blockCopy2 = block; // Make a copy for Next Fit
    NextFit(blockCopy2, process, n, m);

    vector<int> blockCopy3 = block; // Make a copy for Worst Fit
    WorstFit(blockCopy3, process, n, m);

    return 0;
}