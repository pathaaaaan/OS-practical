// Shortest Job First (SJF) Scheduling Algorithm in C

#include <stdio.h>
#define max 30
int main()
{
    int n, i, j, t = 0, min, p[max], bt[max], at[max], wt[max], tat[max], ct[max], completed[max];
    float awt = 0, atat = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the process numbers: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &p[i]);
    }
    printf("Enter the Burst Times: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
    }
    printf("Enter the Arrival Times: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &at[i]);
        completed[i] = 0;
    }
    int count = 0;
    printf("\nGantt Chart: ");
    while (count < n)
    {
        min = -1;
        for (i = 0; i < n; i++)
        {
            if (!completed[i] && at[i] <= t)
            {
                if (min == -1 || bt[i] < bt[min] ||
                    (bt[i] == bt[min] && at[i] < at[min]) ||
                    (bt[i] == bt[min] && at[i] == at[min] && p[i] < p[min]))
                {
                    min = i;
                }
            }
        }
        if (min == -1)
        {
            t++;
            continue;
        }
        t += bt[min];
        ct[min] = t;
        tat[min] = ct[min] - at[min];
        wt[min] = tat[min] - bt[min];
        awt += wt[min];
        atat += tat[min];
        completed[min] = 1;
        count++;
        printf("P%d ", p[min]);
    }
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage Waiting Time = %.2f", awt / n);
    printf("\nAverage Turnaround Time = %.2f\n", atat / n);
    return 0;
}