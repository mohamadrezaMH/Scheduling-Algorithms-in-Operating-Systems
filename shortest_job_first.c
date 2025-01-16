#include <stdio.h>

struct process {
    int pid;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

void swap(struct process *p1, struct process *p2) {
    struct process temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int main() {
    int n;
    float avgWaitingTime = 0, avgTurnaroundTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].pid = i + 1;
    }

    // Sorting processes based on burst time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burstTime > processes[j + 1].burstTime) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    processes[0].waitingTime = 0;

    // Calculating waiting and turnaround time for each process
    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }

    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
        avgWaitingTime += processes[i].waitingTime;
        avgTurnaroundTime += processes[i].turnaroundTime;
    }

    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    // Displaying results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);

    return 0;
}