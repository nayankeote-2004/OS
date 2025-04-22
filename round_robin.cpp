#include <iostream>
#include <queue>
using namespace std;

class Process {
public:
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;

    Process() {
        pid = arrival_time = burst_time = completion_time = 
        waiting_time = turnaround_time = remaining_time = 0;
    }
};

class RoundRobin {
private:
    Process* processes;
    int n, quantum;
    queue<int> ready_queue;

public:
    RoundRobin(int size, int time_quantum) {
        n = size;
        quantum = time_quantum;
        processes = new Process[n];
    }

    void inputProcesses() {
        for(int i = 0; i < n; i++) {
            cout << "\nFor Process " << i + 1 << ":\n";
            processes[i].pid = i + 1;
            cout << "Enter Arrival Time: ";
            cin >> processes[i].arrival_time;
            cout << "Enter Burst Time: ";
            cin >> processes[i].burst_time;
            processes[i].remaining_time = processes[i].burst_time;
        }
    }

    void schedule() {
        int current_time = 0;
        int completed = 0;

        while(completed != n) {
            // Check for newly arrived processes
            for(int i = 0; i < n; i++) {
                if(processes[i].arrival_time == current_time && processes[i].remaining_time > 0) {
                    ready_queue.push(i);
                }
            }

            if(ready_queue.empty()) {
                current_time++;
                continue;
            }

            int current_process = ready_queue.front();
            ready_queue.pop();

            // Execute process for quantum time or remaining time
            int execute_time = min(quantum, processes[current_process].remaining_time);
            processes[current_process].remaining_time -= execute_time;
            current_time += execute_time;

            // Check for new arrivals during execution
            for(int i = 0; i < n; i++) {
                if(processes[i].arrival_time > current_time - execute_time && 
                   processes[i].arrival_time <= current_time && 
                   i != current_process && 
                   processes[i].remaining_time > 0) {
                    ready_queue.push(i);
                }
            }

            if(processes[current_process].remaining_time > 0) {
                ready_queue.push(current_process);
            } else {
                completed++;
                processes[current_process].completion_time = current_time;
                processes[current_process].turnaround_time = 
                    processes[current_process].completion_time - processes[current_process].arrival_time;
                processes[current_process].waiting_time = 
                    processes[current_process].turnaround_time - processes[current_process].burst_time;
            }
        }
    }

    void displayResults() {
        cout << "\nProcess\tAT\tBT\tCT\tWT\tTAT\n";
        float avg_waiting = 0, avg_turnaround = 0;

        for(int i = 0; i < n; i++) {
            cout << processes[i].pid << "\t" 
                 << processes[i].arrival_time << "\t"
                 << processes[i].burst_time << "\t"
                 << processes[i].completion_time << "\t"
                 << processes[i].waiting_time << "\t"
                 << processes[i].turnaround_time << "\n";
            
            avg_waiting += processes[i].waiting_time;
            avg_turnaround += processes[i].turnaround_time;
        }

        cout << "\nAverage Waiting Time: " << avg_waiting/n;
        cout << "\nAverage Turnaround Time: " << avg_turnaround/n << endl;
    }

    ~RoundRobin() {
        delete[] processes;
    }
};

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> quantum;

    RoundRobin rr(n, quantum);
    rr.inputProcesses();
    rr.schedule();
    rr.displayResults();

    return 0;
}