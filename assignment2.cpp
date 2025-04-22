#include <bits/stdc++.h>
using namespace std;

void calculateCompletionTimeFCFS(const vector<int> &arrival_time, const vector<int> &burst_time, vector<int> &completion_time)
{
    int n = burst_time.size();
    vector<pair<int, int>> process_order(n);
    for (int i = 0; i < n; i++)
    {
        process_order[i] = {arrival_time[i], i};
    }
    sort(process_order.begin(), process_order.end());

    int current_time = process_order[0].first;
    for (int i = 0; i < n; i++)
    {
        int idx = process_order[i].second;
        current_time = max(current_time, arrival_time[idx]);
        completion_time[idx] = current_time + burst_time[idx];
        current_time = completion_time[idx];
    }
}

void calculateTurnaroundTime(const vector<int> &arrival_time, const vector<int> &completion_time, vector<int> &turnaround_time)
{
    int n = arrival_time.size();
    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = completion_time[i] - arrival_time[i];
    }
}

void calculateWaitingTime(const vector<int> &turnaround_time, const vector<int> &burst_time, vector<int> &waiting_time)
{
    int n = turnaround_time.size();
    for (int i = 0; i < n; i++)
    {
        waiting_time[i] = turnaround_time[i] - burst_time[i];
    }
}

// Making printProcessDetails more basic
void printProcessDetails(const vector<int> &at, const vector<int> &bt,
                         const vector<int> &ct, const vector<int> &tat,
                         const vector<int> &wt)
{
    int n = bt.size();
    cout << "\n--------------------Process Details--------------------\n";
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "------------------------------------------------\n";

    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << (i + 1) << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << "\n";
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    cout << "------------------------------------------------\n";
    cout << "Average TAT = " << avg_tat / n << "\n";
    cout << "Average WT  = " << avg_wt / n << "\n";
}

void calculateCompletionTimeSJFNonPreemptive(const vector<int> &burst_time, vector<int> &completion_time)
{
    int n = burst_time.size();
    vector<pair<int, int>> process_order(n);

    for (int i = 0; i < n; i++)
    {
        process_order[i] = {burst_time[i], i};
    }

    sort(process_order.begin(), process_order.end());

    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        int idx = process_order[i].second;
        completion_time[idx] = current_time + burst_time[idx];
        current_time = completion_time[idx];
    }
}

void calculateCompletionTimeSJFPreemptive(const vector<int> &arrival_time, const vector<int> &burst_time, vector<int> &completion_time)
{
    int n = burst_time.size();
    vector<int> remaining_time = burst_time;
    vector<bool> completed(n, false);
    int current_time = 0;
    int completed_count = 0;

    while (completed_count < n)
    {
        int min_id = -1;
        int min_burst = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && arrival_time[i] <= current_time && remaining_time[i] < min_burst)
            {
                min_burst = remaining_time[i];
                min_id = i;
            }
        }

        if (min_id == -1)
        {
            current_time++;
            continue;
        }

        remaining_time[min_id]--;
        current_time++;

        if (remaining_time[min_id] == 0)
        {
            completion_time[min_id] = current_time;
            completed[min_id] = true;
            completed_count++;
        }
    }
}

void calculateCompletionTimeRoundRobin(const vector<int> &arrival_time, const vector<int> &burst_time, vector<int> &completion_time, int time_quantum)
{
    int n = burst_time.size();
    vector<int> remaining_time = burst_time;
    vector<bool> completed(n, false);
    vector<bool> in_queue(n, false);
    queue<int> ready_queue;

    int current_time = 0;
    int completed_count = 0;

    // Find minimum arrival time
    int min_arrival = *min_element(arrival_time.begin(), arrival_time.end());
    current_time = min_arrival;

    // Add processes that arrive at min_arrival time
    for (int i = 0; i < n; i++)
    {
        if (arrival_time[i] == min_arrival)
        {
            ready_queue.push(i);
            in_queue[i] = true;
        }
    }

    while (completed_count < n)
    {
        if (ready_queue.empty())
        {
            current_time++;
            // Check for newly arrived processes
            for (int i = 0; i < n; i++)
            {
                if (!completed[i] && !in_queue[i] && arrival_time[i] <= current_time)
                {
                    ready_queue.push(i);
                    in_queue[i] = true;
                }
            }
            continue;
        }

        int current_process = ready_queue.front();
        ready_queue.pop();
        in_queue[current_process] = false;

        int execute_time = min(time_quantum, remaining_time[current_process]);
        remaining_time[current_process] -= execute_time;
        current_time += execute_time;

        // Check for newly arrived processes during execution
        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && !in_queue[i] && arrival_time[i] <= current_time)
            {
                ready_queue.push(i);
                in_queue[i] = true;
            }
        }

        if (remaining_time[current_process] == 0)
        {
            completion_time[current_process] = current_time;
            completed[current_process] = true;
            completed_count++;
        }
        else
        {
            ready_queue.push(current_process);
            in_queue[current_process] = true;
        }
    }
}

void calculateCompletionTimePriorityNonPreemptive(const vector<int> &arrival_time, const vector<int> &burst_time, const vector<int> &priority, vector<int> &completion_time)
{
    int n = burst_time.size();
    vector<int> remaining_time = burst_time;
    vector<bool> completed(n, false);
    int current_time = 0;
    int completed_count = 0;

    while (completed_count < n)
    {
        int highest_priority_process = -1;
        int highest_priority = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && arrival_time[i] <= current_time && priority[i] < highest_priority)
            {
                highest_priority = priority[i];
                highest_priority_process = i;
            }
        }

        if (highest_priority_process == -1)
        {
            current_time++;
            continue;
        }

        int process = highest_priority_process;
        current_time += remaining_time[process];
        completion_time[process] = current_time;
        completed[process] = true;
        completed_count++;
    }
}

void calculateCompletionTimePriorityPreemptive(const vector<int> &arrival_time, const vector<int> &burst_time, const vector<int> &priority, vector<int> &completion_time)
{
    int n = burst_time.size();
    vector<int> remaining_time = burst_time;
    vector<bool> completed(n, false);
    int current_time = 0;
    int completed_count = 0;

    while (completed_count < n)
    {
        int highest_priority_process = -1;
        int highest_priority = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && arrival_time[i] <= current_time && priority[i] < highest_priority && remaining_time[i] > 0)
            {
                highest_priority = priority[i];
                highest_priority_process = i;
            }
        }

        if (highest_priority_process == -1)
        {
            current_time++;
            continue;
        }

        remaining_time[highest_priority_process]--;
        current_time++;

        if (remaining_time[highest_priority_process] == 0)
        {
            completion_time[highest_priority_process] = current_time;
            completed[highest_priority_process] = true;
            completed_count++;
        }
    }
}

// Main function with simpler menu
int main()
{
    int n;
    cout << "How many processes? ";
    cin >> n;

    // Process arrays
    vector<int> at(n);  // arrival time
    vector<int> bt(n);  // burst time
    vector<int> pr(n);  // priority
    vector<int> ct(n);  // completion time
    vector<int> tat(n); // turnaround time
    vector<int> wt(n);  // waiting time

    // Input process details
    cout << "\nEnter process details:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "\nProcess P" << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> at[i];
        cout << "Burst Time: ";
        cin >> bt[i];
        cout << "Priority (1 is highest): ";
        cin >> pr[i];
    }

    int choice;
    bool running = true;

    while (running)
    {
        cout << "\n=== CPU Scheduling Menu ===\n";
        cout << "1. FCFS\n";
        cout << "2. SJF (Non-Preemptive)\n";
        cout << "3. SJF (Preemptive)\n";
        cout << "4. Round Robin\n";
        cout << "5. Priority (Non-Preemptive)\n";
        cout << "6. Priority (Preemptive)\n";
        cout << "7. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice == 7)
        {
            running = false;
            continue;
        }

        // Clear previous results
        for (int i = 0; i < n; i++)
        {
            ct[i] = tat[i] = wt[i] = 0;
        }

        switch (choice)
        {
        case 1:
            calculateCompletionTimeFCFS(at, bt, ct);
            cout << "\nFirst Come First Serve:\n";
            break;
        case 2:
            calculateCompletionTimeSJFNonPreemptive(bt, ct);
            cout << "\nShortest Job First (Non-Preemptive):\n";
            break;
        case 3:
            calculateCompletionTimeSJFPreemptive(at, bt, ct);
            cout << "\nShortest Job First (Preemptive):\n";
            break;
        case 4:
        {
            int tq;
            cout << "Time Quantum: ";
            cin >> tq;
            calculateCompletionTimeRoundRobin(at, bt, ct, tq);
            cout << "\nRound Robin (TQ=" << tq << "):\n";
            break;
        }
        case 5:
            calculateCompletionTimePriorityNonPreemptive(at, bt, pr, ct);
            cout << "\nPriority Scheduling (Non-Preemptive):\n";
            break;
        case 6:
            calculateCompletionTimePriorityPreemptive(at, bt, pr, ct);
            cout << "\nPriority Scheduling (Preemptive):\n";
            break;
        default:
            cout << "Wrong choice!\n";
            continue;
        }

        calculateTurnaroundTime(at, ct, tat);
        calculateWaitingTime(tat, bt, wt);

        printProcessDetails(at, bt, ct, tat, wt);
    }
    cout << "\nThank you!\n";
    return 0;
}
