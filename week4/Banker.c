#include <stdio.h>
#include <stdbool.h>

int main()
{
    int p, r;

    // Read number of processes
    printf("Enter number of processes: ");
    scanf("%d", &p);

    // Read number of resources
    printf("Enter number of resources: ");
    scanf("%d", &r);

    int max[p][r], alloc[p][r], need[p][r];
    int total[r], avail[r];
    bool finished[p];

    // Read MAX matrix
    printf("\nEnter MAX matrix (%d rows each with %d values):\n", p, r);
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Read ALLOCATION matrix
    printf("\nEnter ALLOCATION matrix (%d rows each with %d values):\n", p, r);
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Read total resources provided by system
    printf("\nEnter TOTAL instances of each resource (%d values):\n", r);
    for (int i = 0; i < r; i++)
    {
        scanf("%d", &total[i]);
    }

    // Calculate AVAILABLE = TOTAL - SUM(allocated)
    for (int j = 0; j < r; j++)
    {
        int sum = 0;
        for (int i = 0; i < p; i++)
            sum += alloc[i][j];
        avail[j] = total[j] - sum;
    }

    // Calculate NEED = MAX - ALLOC
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize all processes as unfinished
    for (int i = 0; i < p; i++)
    {
        finished[i] = false;
    }

    int safeSeq[p];
    int count = 0;

    // BANKER'S ALGORITHM FOR SAFE SEQUENCE
    while (count < p)
    {
        bool found = false;

        for (int i = 0; i < p; i++)
        {
            if (!finished[i])
            {
                bool canRun = true;

                // Check if need <= available
                for (int j = 0; j < r; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        canRun = false;
                        break;
                    }
                }

                if (canRun)
                {
                    // Pretend the process finishes → release its resources
                    for (int j = 0; j < r; j++)
                    {
                        avail[j] += alloc[i][j];
                    }

                    safeSeq[count++] = i;
                    finished[i] = true;
                    found = true;
                }
            }
        }

        if (!found)
            break; // no runnable process found → unsafe
    }

    // Print result
    if (count == p)
    {
        printf("\nRequest can be fulfilled\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < p; i++)
        {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    }
    else
    {
        printf("\nRequest cannot be fulfilled\n");
    }

    return 0;
}