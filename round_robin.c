#include <stdio.h>

struct process
{
    int pid;
    int remainingTime;
    int burstTime;
    int waitingTime;
    int finishedTime;
};

int main()
{
    int n, quantum;
    int sum_of_burstTime = 0;
    float avgWaitingTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process processes[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].pid = i + 1;
        sum_of_burstTime += processes[i].burstTime;
    }

    printf("Enter the quantum time: ");
    scanf("%d", &quantum);
    printf("\n");
    int j = 0; // time
    int i = 0; // process number
    while (j < sum_of_burstTime)
    {
        if (processes[i].remainingTime <= 0)
        {
            i++;
            if (i >= n)
            {
                i = 0;
            }
            continue;
        }
        else
        {
            if (processes[i].remainingTime > quantum)
            {
                j += quantum;
                processes[i].remainingTime -= quantum;
                printf("process %d is running at time %d to %d. \n", processes[i].pid, j - quantum , j);
                i++;
                if (i >= n)
                {
                    i = 0;
                }
            }
            else
            {
                j += processes[i].remainingTime;
                printf("process %d is running at time %d to %d and completed at time %d.\n", processes[i].pid , j - processes[i].remainingTime, j , j);
                processes[i].remainingTime = 0;
                processes[i].finishedTime = j;
                i++;
                if (i >= n)
                {
                    i = 0;
                }
                continue;
            }
        }
    }
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        processes[i].waitingTime = processes[i].finishedTime - processes[i].burstTime;
        avgWaitingTime += processes[i].waitingTime;
        printf("waiting time of process %d is %d \n", processes[i].pid, processes[i].waitingTime);
    }

    avgWaitingTime /= n;
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);

    return 0;
}