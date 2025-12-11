// Preemptive Shortest Remaining Time First (SRTF) - clean version (no Gantt chart)
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#define MAX 100

struct process
{
    int pid;        // process id
    int at;         // arrival time
    int bt;         // burst time
    int bt_rem;     // remaining time
    int start;      // response time start
    int ct;         // completion time
    int tat;        // turnaround time
    int wt;         // waiting time
    bool completed; // completion flag
};

int main(void)
{
    int n;
    struct process ps[MAX];

    printf("Enter total number of processes (max %d): ", MAX);
    scanf("%d", &n);

    // Read process IDs
    printf("Enter Process IDs:\n");
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &ps[i].pid);
    }

    // Read arrival times
    printf("Enter Arrival Times:\n");
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &ps[i].at);
    }

    // Read burst times and initialize fields
    printf("Enter Burst Times:\n");
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &ps[i].bt);
        ps[i].bt_rem = ps[i].bt;
        ps[i].start = -1;
        ps[i].ct = ps[i].tat = ps[i].wt = 0;
        ps[i].completed = false;
    }

    int current_time = 0;
    int completed_count = 0;
    long sum_tat = 0, sum_wt = 0, sum_rt = 0;

    // Main SRTF simulation loop
    while (completed_count < n)
    {
        int idx = -1;
        int min_rem = INT_MAX;

        // Find the shortest remaining time process that has arrived
        for (int i = 0; i < n; ++i)
        {
            if (!ps[i].completed && ps[i].at <= current_time && ps[i].bt_rem > 0)
            {
                if (ps[i].bt_rem < min_rem)
                {
                    min_rem = ps[i].bt_rem;
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            // No process available — CPU idle
            current_time++;
            continue;
        }

        // First time CPU touches this process → response time
        if (ps[idx].start == -1)
        {
            ps[idx].start = current_time;
            sum_rt += (ps[idx].start - ps[idx].at);
        }

        // Execute for 1 time unit
        ps[idx].bt_rem--;
        current_time++;

        // If finished
        if (ps[idx].bt_rem == 0)
        {
            ps[idx].completed = true;

            ps[idx].ct = current_time;
            ps[idx].tat = ps[idx].ct - ps[idx].at;
            ps[idx].wt = ps[idx].tat - ps[idx].bt;

            sum_tat += ps[idx].tat;
            sum_wt += ps[idx].wt;

            completed_count++;
        }
    }

    // Print results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; ++i)
    {
        int rt = ps[i].start - ps[i].at;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt, rt);
    }

    printf("\nAverage Waiting Time = %.2f\n", (double)sum_wt / n);
    printf("Average Turnaround Time = %.2f\n", (double)sum_tat / n);
    printf("Average Response Time = %.2f\n", (double)sum_rt / n);

    return 0;
}