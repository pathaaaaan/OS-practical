#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

struct PageTable
{
    int frame_no;
    int last_access;
    bool valid;
};

bool isPagePresent(struct PageTable *PT, int page, int pt_size)
{
    if (page < 0 || page >= pt_size)
        return false;
    return PT[page].valid;
}

void updatePageTable(struct PageTable *PT, int page, int fr_no, int status, int time, int pt_size)
{
    if (page < 0 || page >= pt_size)
        return;
    PT[page].valid = (status == 1);
    PT[page].frame_no = fr_no;
    PT[page].last_access = time;
}

void printFrameContents(int frame[], int no_of_frames)
{
    for (int i = 0; i < no_of_frames; i++)
    {
        if (frame[i] == -1)
            printf("- ");
        else
            printf("%d ", frame[i]);
    }
    printf("\n");
}

int findLRU(int frame[], struct PageTable *PT, int no_of_frames)
{
    int min_time = INT_MAX;
    int lru_index = -1;

    for (int i = 0; i < no_of_frames; i++)
    {
        int page = frame[i];
        if (page == -1)
            return i; // empty frame found
        if (PT[page].last_access < min_time)
        {
            min_time = PT[page].last_access;
            lru_index = i;
        }
    }
    return lru_index;
}

int main()
{
    int no_of_frames, n;

    scanf("%d", &no_of_frames);
    scanf("%d", &n);

    int *ref = malloc(n * sizeof(int));
    int max_page = 0;

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ref[i]);
        if (ref[i] > max_page)
            max_page = ref[i];
    }

    int pt_size = max_page + 1;
    struct PageTable *PT = malloc(pt_size * sizeof(struct PageTable));

    for (int i = 0; i < pt_size; i++)
    {
        PT[i].valid = false;
        PT[i].frame_no = -1;
        PT[i].last_access = -1;
    }

    int frame[no_of_frames];
    for (int i = 0; i < no_of_frames; i++)
        frame[i] = -1;

    int page_faults = 0;

    printf("*Frame contents over time:*\n");

    for (int t = 0; t < n; t++)
    {
        int page = ref[t];

        if (!isPagePresent(PT, page, pt_size))
        {
            page_faults++;

            int idx = findLRU(frame, PT, no_of_frames);

            int old_page = frame[idx];
            if (old_page != -1)
                updatePageTable(PT, old_page, -1, 0, t, pt_size);

            frame[idx] = page;
            updatePageTable(PT, page, idx, 1, t, pt_size);

            printFrameContents(frame, no_of_frames);
        }
        else
        {
            // page hit → update last access
            PT[page].last_access = t;
        }
    }

    printf("\nTotal Page Faults = %d\n", page_faults);
    printf("Page Fault Ratio = %.2f\n", (float)page_faults / n);
    printf("Page Hit Ratio = %.2f\n", (float)(n - page_faults) / n);

    free(ref);
    free(PT);
    return 0;
}