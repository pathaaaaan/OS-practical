// First Come First Serve (FCFS) Scheduling Algorithm in C

#include <stdio.h>
void swap(float *xp, float *yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}
// Sort according to Arrival Time
void sortArray(float bt[], float at[], int p[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                swap(&at[j], &at[j + 1]);
                swap(&bt[j], &bt[j + 1]);
                int temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}
int main()
{
    int n;
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    float bt[n], at[n], wt[n], ct[n], tat[n];
    int p[n];
    float sum_tat = 0, sum_wt = 0;
    // Input
    printf("\nEnter Arrival Times:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &at[i]);
        p[i] = i + 1;
    }
    printf("\nEnter Burst Times:\n");
    for (int i = 0; i < n; i++)
        scanf("%f", &bt[i]);
    // Sort processes by arrival time
    sortArray(bt, at, p, n);
    // Calculate CT, TAT, WT
    ct[0] = at[0] + bt[0];
    tat[0] = ct[0] - at[0];
    wt[0] = tat[0] - bt[0];
    sum_tat += tat[0];
    sum_wt += wt[0];
    for (int i = 1; i < n; i++)
    {
        if (at[i] > ct[i - 1])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i - 1] + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        sum_tat += tat[i];
        sum_wt += wt[i];
    }
    // Print Table
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%.0f\t%.0f\t%.0f\t%.0f\t%.0f\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    // Print Averages
    printf("Average TAT = %.2f\n", sum_tat / n);
    printf("Average WT = %.2f\n", sum_wt / n);
    return 0;
}