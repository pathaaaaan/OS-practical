#include <stdio.h>
#include <stdbool.h>
struct process_struct
{
    float at;  // Arrival Time
    float bt;  // Burst Time
    float ct;  // Completion Time
    float wt;  // Waiting Time
    float tat; // Turnaround Time
    float rt;  // Response Time
    float start_time;
    int process_num;
} ps[100];
int main()
{
    int n;
    float bt_remaining[100];
    bool is_completed[100] = {false};
    int current_time = 0;
    int completed = 0;
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    printf("\nEnter Process Numbers: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ps[i].process_num);
    }
    printf("\nEnter Arrival Times: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &ps[i].at);
    }
    printf("\nEnter Burst Times: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &ps[i].bt);
        bt_remaining[i] = ps[i].bt;
    }
    while (completed != n)
    {
        int min_index = -1;
        int minimum = 10000000;
        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && is_completed[i] == false)
            {
                if (bt_remaining[i] < minimum)
                {
                    minimum = bt_remaining[i];
                    min_index = i;
                }
                else if (bt_remaining[i] == minimum)
                {
                    if (ps[i].at < ps[min_index].at)
                    {
                        minimum = bt_remaining[i];
                        min_index = i;
                    }
                }
            }
        }
        if (min_index == -1)
        {
            current_time++;
        }
        else
        {
            if (bt_remaining[min_index] == ps[min_index].bt)
                ps[min_index].start_time = current_time;
            bt_remaining[min_index] -= 1;
            current_time++;
            if (bt_remaining[min_index] == 0)
            {
                ps[min_index].ct = current_time;
                ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
                ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;
                ps[min_index].rt = ps[min_index].start_time - ps[min_index].at;
                sum_tat += ps[min_index].tat;
                sum_wt += ps[min_index].wt;
                sum_rt += ps[min_index].rt;
                completed++;
                is_completed[min_index] = true;
            }
        }
    }
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
               ps[i].process_num,
               ps[i].at,
               ps[i].bt,
               ps[i].ct,
               ps[i].tat,
               ps[i].wt,
               ps[i].rt);
    }
    printf("\nAverage Waiting Time = %.2f", sum_wt / n);
    printf("\nAverage Response Time = %.2f", sum_rt / n);
    printf("\nAverage Turnaround Time = %.2f\n", sum_tat / n);
    return 0;
}