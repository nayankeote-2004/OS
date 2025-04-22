#include <bits/stdc++.h>
using namespace std;

void fifoPageReplacement(const vector<int> &pageReferences, int frameCount)
{
    vector<int> frames(frameCount, -1);
    int pageFaults = 0;
    int nextToReplace = 0;

    cout << "Page Ref\t";
    for (int i = 0; i < frameCount; i++)
    {
        cout << "Frame " << i << "\t";
    }
    cout << "Status" << endl;

    for (int i = 0; i < pageReferences.size(); i++)
    {
        int currentPage = pageReferences[i];
        bool pageHit = false;

        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == currentPage)
            {
                pageHit = true;
                break;
            }
        }

        if (!pageHit)
        {
            pageFaults++;
            frames[nextToReplace] = currentPage;
            nextToReplace = (nextToReplace + 1) % frameCount;
        }

        cout << currentPage << "\t\t";

        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == -1)
            {
                cout << "-" << "\t";
            }
            else
            {
                cout << frames[j] << "\t";
            }
        }

        if (pageHit)
        {
            cout << "Hit" << endl;
        }
        else
        {
            cout << "Miss" << endl;
        }
    }

    cout << "\nTotal Page Faults: " << pageFaults << endl;
}

void lruPageReplacement(const vector<int> &pageReferences, int frameCount)
{
    vector<int> frames(frameCount, -1);
    vector<int> lastUsed(frameCount, -1);
    int pageFaults = 0;

    cout << "Page Ref\t";
    for (int i = 0; i < frameCount; i++)
    {
        cout << "Frame " << i << "\t";
    }
    cout << "Status" << endl;

    for (int i = 0; i < pageReferences.size(); i++)
    {
        int currentPage = pageReferences[i];
        bool pageHit = false;
        int frameIndex = -1;

        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == currentPage)
            {
                pageHit = true;
                frameIndex = j;
                break;
            }
        }

        if (pageHit)
        {
            lastUsed[frameIndex] = i;
        }
        else
        {
            pageFaults++;

            int lruIndex = 0;
            
            for (int j = 1; j < frameCount; j++)
            {
                if (frames[j] == -1)
                {
                    lruIndex = j;
                    break;
                }
                if (lastUsed[j] < lastUsed[lruIndex])
                {
                    lruIndex = j;
                }
            }

            frames[lruIndex] = currentPage;
            lastUsed[lruIndex] = i;
        }

        cout << currentPage << "\t\t";

        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == -1)
            {
                cout << "-" << "\t";
            }
            else
            {
                cout << frames[j] << "\t";
            }
        }

        if (pageHit)
        {
            cout << "Hit" << endl;
        }
        else
        {
            cout << "Miss" << endl;
        }
    }

    cout << "\nTotal Page Faults: " << pageFaults << endl;
}

void optimalPageReplacement(const vector<int> &pageReferences, int frameCount)
{
    vector<int> frames(frameCount, -1);
    int pageFaults = 0;

    cout << "Page Ref\t";
    for (int i = 0; i < frameCount; i++)
    {
        cout << "Frame " << i << "\t";
    }
    cout << "Status" << endl;

    for (int i = 0; i < pageReferences.size(); i++)
    {
        int currentPage = pageReferences[i];
        bool pageHit = false;

        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == currentPage)
            {
                pageHit = true;
                break;
            }
        }

        if (!pageHit)
        {
            pageFaults++;

            int emptyFrame = -1;
            for (int j = 0; j < frameCount; j++)
            {
                if (frames[j] == -1)
                {
                    emptyFrame = j;
                    break;
                }
            }

            if (emptyFrame != -1)
            {
                frames[emptyFrame] = currentPage;
            }
            else
            {
                vector<int> nextUse(frameCount, INT_MAX);

                for (int j = 0; j < frameCount; j++)
                {
                    for (int k = i + 1; k < pageReferences.size(); k++)
                    {
                        if (frames[j] == pageReferences[k])
                        {
                            nextUse[j] = k;
                            break;
                        }
                    }
                }

                int farthest = 0;
                for (int j = 1; j < frameCount; j++)
                {
                    if (nextUse[j] > nextUse[farthest])
                    {
                        farthest = j;
                    }
                }

                frames[farthest] = currentPage;
            }
        }

        cout << currentPage << "\t\t";

        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == -1)
            {
                cout << "-" << "\t";
            }
            else
            {
                cout << frames[j] << "\t";
            }
        }

        if (pageHit)
        {
            cout << "Hit" << endl;
        }
        else
        {
            cout << "Miss" << endl;
        }
    }

    cout << "\nTotal Page Faults: " << pageFaults << endl;
}

int main()
{
    int frameCount, numReferences, choice;

    cout << "Enter the number of page frames: ";
    cin >> frameCount;

    cout << "Enter the number of page references: ";
    cin >> numReferences;

    vector<int> pageReferences(numReferences);
    cout << "Enter the page references: ";
    for (int i = 0; i < numReferences; i++)
    {
        cin >> pageReferences[i];
    }

    cout << "Select page replacement algorithm:\n";
    cout << "1. FIFO\n";
    cout << "2. LRU\n";
    cout << "3. Optimal\n";
    cout << "Enter choice (1-3): ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        fifoPageReplacement(pageReferences, frameCount);
        break;
    case 2:
        lruPageReplacement(pageReferences, frameCount);
        break;
    // case 3:
    //     optimalPageReplacement(pageReferences, frameCount);
    //     break;
    default:
        cout << "Invalid choice, using FIFO by default\n";
        fifoPageReplacement(pageReferences, frameCount);
    }

    return 0;
}